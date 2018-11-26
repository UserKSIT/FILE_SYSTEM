//
//  DESCRIPTION_SYSTEM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "DESCRIPTION_SYSTEM.hpp"
#include "BASIC_DESCRIPTION.hpp"
#include <string>
#include <vector>
#include <iostream>


Desp_sys::Desp_sys(){
    root = new Descatalog("Admin", "root/", "Admin", "rw");
    hard_drive = new fstream;
    hard_drive->open("FILE_SYSTEM.txt");
    if (!hard_drive)
        throw ;//std::system_error("File can't open");
    current_user = "";
    quantity_file = 0;
    quantity_catalog = 0;
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
    current_user = "";
    return 1;
}
