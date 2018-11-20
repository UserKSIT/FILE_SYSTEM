//
//  DESCRIPTION_SYSTEM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "DESCRIPTION_SYSTEM.hpp"
#include <string>

Desp_sys::Desp_sys(){
    string * tmp = new string[5];
    *tmp = "Admin";
    root = new Descatalog;
    table_users = new User;
    table_users->set_name(tmp);
    delete [] tmp;
}
