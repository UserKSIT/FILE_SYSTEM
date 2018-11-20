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

using namespace lcu;

namespace bac {
    struct Id{
        string * name;
        string * location;
        Id (string *name = nullptr, string *location = nullptr): name(name), location(location){}
    };
    
    class Basic_description{
    protected:
        int size;
        Level_access * access_users;
        Id identity;
    public:
        virtual Basic_description * clone() const = 0;
        virtual ~Basic_description(){delete [] access_users;};
        
        void set_indentity(const string *, const string *);
    };
    
    class Descatalog: public Basic_description{
    private:
        FILE * virtual_adress;
        Basic_description * struct_catalog;
    public:
        Descatalog();
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        
        
    };
    
    class Desfile: public Basic_description{
    protected:
        string * time_last_mod;
        string * master;
        //Desstream * ptr_stream;
    public:
        
    };
}

#endif /* BASIC_DESCRIPTION_hpp */
