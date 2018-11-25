//
//  BASIC_DESCRIPTION.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef BASIC_DESCRIPTION_hpp
#define BASIC_DESCRIPTION_hpp

#include <stdio.h>
#include <fstream>
#include "USER.hpp"
#include "STREAM.hpp"
#include "DESCRIPTION_SYSTEM.hpp"

using namespace lcu;
using namespace std;


namespace cfc {
    struct Id{
        string name;
        string location;
        Id (const string &name = "", const string &location = ""): name(name), location(location){}
    };
    
    class Basic_description{
    protected:
        int size;
        Level_access * access_users;
        Id identity;
        virtual void set_indentity(const string&, const string&);
    public:
        Basic_description();
        virtual Basic_description * clone() const = 0;
        virtual ~Basic_description(){delete [] access_users;};
        
        
    };
    
    class Descatalog: public Basic_description{
    private:
        ios::pos_type virtual_adress;
        Basic_description * struct_catalog;
        static const int size = 10;
        int opp;
    public:
        Descatalog(const Descatalog &);
        ~Descatalog(){delete [] struct_catalog;}
        
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        virtual void set_indentity(const string&, const string&);
        
        //function add object - file or catalog
        Descatalog & add_file(const Basic_description &);
        Descatalog & add_catalog();
        
        //function open file
        
        
        //function delete object - file or catalog
        
        int deleta_catalog(const Basic_description &);

        Basic_description & search(const string &) const;
        
        void exibition() const;
        friend std::ostream & operator << (std::ostream &flow, const Descatalog &object);
        
        Descatalog &operator =(const Descatalog&);
        Descatalog &operator =(Descatalog &&);
        
        
    };
    
    class Desfile: public Basic_description{
    protected:
        string time_last_mod;
        string master;
        Desstream * ptr_stream;
    public:
        Desfile();
        
        virtual Desfile * clone() const {
            return new Desfile(*this);
        }
        
        virtual void set_indentity(const string &, const string &);
        
        
        
        Desfile &operator =(const Desfile&);
        Desfile &operator =(Desfile &&);
        
        void get_info() const;
        void change_acess();
        
        //-----------------------------------------------------
        
        
        ifstream & open_file_read(const Desfile &) const;//?
        fstream & open_file_write(Desfile &);
        
        void close_file(ifstream &);
        void close_file(fstream &);

        ifstream & write_file(ifstream &);
        fstream & write_file(fstream &);
        
        int delete_file(const Desfile &);
        
        friend std::ostream & operator << (std::ostream &flow,  fstream &object);//read file
        friend std::ostream & operator << (std::ostream &flow,  ifstream &object);
        //----------------------------------------------------
    };
    
}


#endif /* BASIC_DESCRIPTION_hpp */
