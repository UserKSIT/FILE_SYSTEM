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

namespace bac {
    Descatalog::Descatalog(): Basic_description(), struct_catalog(nullptr), virtual_adress(nullptr){
        Basic_description::identity.name = "Admin";
        Basic_description::identity.location = "root/";
        n = 1;
        N = 1;
        
    }
    void Descatalog::set_indentity(const string &name, const string &location){
        Basic_description::identity.name = name;
        Basic_description::identity.location = location;
    }
    
    Descatalog & Descatalog::add_file(){
        if (n < N)  
            struct_catalog[n++] = struct_catalog->clone();
        return *this;
    }
}
