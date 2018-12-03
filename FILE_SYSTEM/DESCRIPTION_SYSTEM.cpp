//
//  DESCRIPTION_SYSTEM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "DESCRIPTION_SYSTEM.hpp"
#include "BASIC_DESCRIPTION.hpp"
#include "USER.hpp"
#include "Library_Template.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Desp_sys::Desp_sys(){
    root = new Descatalog("root");
    current_user = "";
    current_location = "root/";
    quantity_file = 0;
    quantity_catalog = 1;
    User object("ADMIN");
    this->insert_user("ADMIN", object);
    
}

bool Desp_sys::check_in_table(const string &id){
    map<const string, User>::iterator p = table_users.find(id);
    if (p != table_users.end())
        return true;
    else
        return false;
}

bool Desp_sys::insert_user(const string &id, const User &object){
    bool res = false;
    map<const string, User>::iterator p = table_users.find(id);
    if (p == table_users.end()){
    table_users.insert(make_pair(id, object));
        res = true;
    }
    return res;
}

bool Desp_sys::remove(const std::string &id){
    bool res = false;
    std::map<const std::string, User>::iterator iter = table_users.find(id);
    if (iter != table_users.end()){
        //delete iter->second;
        //iter->second = nullptr;
        table_users.erase(iter);
        res = true;
    }
    return res;
}

bool Desp_sys::change(const string &id, const User &object){
    bool res = false;
    std::map<const std::string, User>::iterator iter = table_users.find(id);
    if (iter != table_users.end()){
        //object->info_key = table_users[id]->info_key;
        table_users.insert(make_pair(id, object));
        res = true;
    }
    return res;
}

Desp_sys & Desp_sys::start_work(const string &id){
    current_user = id;
    return *this;
}

Desp_sys & Desp_sys::end_work(){
    current_location = "root/";
    current_user = "";
    return *this;
}

void Desp_sys::get_stat() const{
    std::cout << "Quantity file = " << quantity_file << std::endl;
    std::cout << "Quantity catalog = " << quantity_catalog << std::endl;
    /* обход иерхии*/
}


