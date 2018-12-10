
#include "Crypt.hpp"

/*
 ################################################
 #                                              #
 #  PC1 CIPHER 256-bit keys ~ Alexander Pukall  #
 #  (c) NERRANT THOMAS ~ February 2003          #
 #  http://thomasnerrant.com                    #
 #                                              #
 ################################################
 */
//---------------------------------------------------------------------------

using namespace std;

//---------------------------------------------------------------------------
#define default_password "abcdefghijklmnopqrstuvwxyz012345"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
TPasswordEncryptDecrypt::TPasswordEncryptDecrypt()
{
}
//---------------------------------------------------------------------------
TPasswordEncryptDecrypt::~TPasswordEncryptDecrypt()
{
}
//---------------------------------------------------------------------------
void TPasswordEncryptDecrypt::initVars ()
{
    m_x1a2 = m_ax = m_bx = m_cx = m_dx = m_si = m_cntr = 0;
}
//---------------------------------------------------------------------------
void TPasswordEncryptDecrypt::common(const string &inText,const string &inKey)
{
    string encKey = inKey;
    
    m_cle = default_password;
    size_t count = encKey.size();
    if( count > 32 )
    {
        count = 32;
    }
    
    for (size_t i = 0; i < count; i++)
    {
        m_cle [i] = encKey [i];
    }
}
//---------------------------------------------------------------------------
unsigned short TPasswordEncryptDecrypt::code()
{
    unsigned short tmp;
    
    m_dx = m_x1a2 + m_cntr;
    m_ax = m_x1a0[m_cntr];
    m_cx = 0x015a;
    m_bx = 0x4e35;
    
    tmp = m_ax;
    m_ax = m_si;
    m_si = tmp;
    
    tmp = m_ax;
    m_ax = m_dx;
    m_dx = tmp;
    
    if (m_ax != 0)
    {
        m_ax = m_ax * m_bx;
    }
    tmp = m_ax;
    m_ax = m_cx;
    m_cx = tmp;
    
    if (m_ax != 0)
    {
        m_ax = m_ax * m_si;
        m_cx = m_ax + m_cx;
    }
    
    tmp = m_ax;
    m_ax = m_si;
    m_si = tmp;
    m_ax = m_ax * m_bx;
    m_dx = m_cx + m_dx;
    
    m_ax = m_ax + 1;
    
    m_x1a2 = m_dx;
    m_x1a0[m_cntr++] = m_ax;
    
    return (m_ax ^ m_dx);
}
//---------------------------------------------------------------------------
unsigned short __fastcall TPasswordEncryptDecrypt::assemble()
{
    int x = 1;
    unsigned short assres;
    
    m_x1a0[0] = (m_cle[x++] * 256) + m_cle[x++];
    
    assres = code();
    
    for (int i = 1; i < 16; i++)
    {
        m_x1a0[i] = m_x1a0[i - 1] ^ ((m_cle[x++] * 256) + m_cle[x++]);
        assres ^= code();
    }
    m_cntr = 0;
    
    return assres;
}
//---------------------------------------------------------------------------
string TPasswordEncryptDecrypt::encryptMe(const string &inText,const string &inKey )
{
    short s, d, e;
    unsigned short assres, cfc, cfd;
    string retval;
    
    initVars ();
    common (inText, inKey);
    
    for( size_t i = 0; i < inText.size(); i++)
    {
        s = inText[i];
        assres = assemble();
        cfc = assres >> 8;
        cfd = assres & 255; /* cfc^cfd = random byte */
        
        for (int j = 0; j < 32; j++) //we mix the plaintext byte with the key
        {
            m_cle[j+1] ^= s;
        }
        s ^= (cfc ^ cfd);
        
        d = (s >> 4); /* we split the 's' crypted byte into two 4 bits parts 'd' and 'e' */
        e = (s & 15);
        
        retval += (char) (0x61 + d);
        retval += (char) (0x61 + e);
    }
    
    return retval;
    
}
//---------------------------------------------------------------------------
string TPasswordEncryptDecrypt::decryptMe(const string &inText, const string &inKey )
{
    short c, d, e;
    unsigned short assres, cfc, cfd;
    string retval;
    
    initVars ();
    common( inText, inKey );
    
    for ( size_t i = 0; i < inText.size(); i+=2 )
    {
        d = inText[i];
        e = inText[i+1]; /* read the second letter in the file */
        
        d -= 0x61; /* retrieve the 4 bits from the first letter */
        d <<= 4;
        
        e -= 0x61; /* retrieve the 4 bits from the second letter */
        c = d + e; /* 4 bits of the first letter + 4 bits of the second = 8 bits */
        
        assres = assemble ();
        cfc = assres >> 8;
        cfd = assres & 255; /* cfc^cfd = random byte */
        
        c ^= (cfc ^ cfd);
        
        for (int j = 0; j < 32; j++) //we mix the plaintext byte with the key
        {
            m_cle[j+1] ^= c;
        }
        retval += (char) c;
    }
    
    return retval;
}
//---------------------------------------------------------------------------
