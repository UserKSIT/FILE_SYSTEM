//
//  Crypt.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 10/12/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef Crypt_hpp
#define Crypt_hpp

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

#include <string>
#define __fastcall

//---------------------------------------------------------------------------
class TPasswordEncryptDecrypt
{
private:
    void __fastcall initVars ();
    void __fastcall common(const std::string &inText, const std::string &inKey);
    unsigned short __fastcall code ();
    unsigned short __fastcall assemble ();
    
    std::string m_cle;
    unsigned short m_x1a0[16], m_x1a2, m_ax, m_bx, m_cx, m_dx, m_si, m_cntr;
    
public:
    TPasswordEncryptDecrypt ();
    ~TPasswordEncryptDecrypt ();
    
    std::string encryptMe(const std::string &inText, const std::string &inKey );
    std::string decryptMe(const std::string &inText, const std::string &inKey );
};
//---------------------------------------------------------------------------
#endif /* Crypt_hpp */
