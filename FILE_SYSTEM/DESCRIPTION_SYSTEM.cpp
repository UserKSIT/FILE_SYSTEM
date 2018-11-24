//
//  DESCRIPTION_SYSTEM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "DESCRIPTION_SYSTEM.hpp"
#include <string>
#include <vector>

Desp_sys::Desp_sys(){
    root = new Descatalog;
}

int Desp_sys::append_user(const string &id, const string &name){
    User tmp;
    tmp.set_id(id);
    tmp.set_name(name);
    tmp.set_info_key("");
    
    table_users.push_back(tmp);

    return 1;
}

int Desp_sys::start_work(const string &id){
    current_user = id;
    return 1;
}

int Desp_sys::end_work(){
    
    return 1;
}
