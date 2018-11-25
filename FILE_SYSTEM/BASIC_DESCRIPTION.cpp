//
//  BASIC_DESCRIPTION.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "BASIC_DESCRIPTION.hpp"
#include "USER.hpp"
#include <string>
#include <fstream>
#include "Library_Template.hpp"

using namespace lcu;
using namespace ltmp;

namespace cfc {
    Descatalog::Descatalog(const Descatalog &object): Basic_description(), virtual_adress(0), opp(object.opp){
        Basic_description::identity.name = "Admin";
        Basic_description::identity.location = "root/";
        
        for (int i = 0; i < opp; i++)
            struct_catalog[i] = object.struct_catalog[i]->clone();
        
    }
    void Descatalog::set_indentity(const string &name, const string &location){
        Basic_description::identity.name = name;
        Basic_description::identity.location = location;
    }
    
    Descatalog & Descatalog::add_file(const Basic_description &object){
        if (opp < size)
            struct_catalog[opp++] = object.clone();
        return *this;
    }
    
    Basic_description & Descatalog::search(const string &) const{
        
    }
}
