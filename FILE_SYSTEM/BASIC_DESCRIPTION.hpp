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


namespace bac {
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
        FILE * virtual_adress;
        Basic_description * struct_catalog;
    public:
        Descatalog();
        ~Descatalog(){delete [] struct_catalog; delete virtual_adress;}
        
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        void set_indentity(const string&, const string&);
        
        Descatalog & add_file();
        Descatalog & add_catalog();
        
        Descatalog & open_file(const Basic_description *) const;
        
        int delete_file(const Basic_description &);
        int deleta_catalog(const Basic_description &);
        
        
        
    };
    
    class Desfile: public Basic_description{
    protected:
        string time_last_mod;
        string master;
        //Desstream * ptr_stream;
    public:
        virtual Desfile * clone() const {
            return new Desfile(*this);
        }
        
        virtual void set_indentity(const string *, const string *);
        
    };
}

#endif /* BASIC_DESCRIPTION_hpp */
