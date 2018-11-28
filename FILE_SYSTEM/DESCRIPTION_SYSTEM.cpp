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

Desp_sys::Desp_sys():quantity_file(0), quantity_catalog(1), current_user(""){
    root = new Descatalog("Admin", "root/", "Admin", "rw");
}

/*bool Desp_sys::insert(const string &id, const User &object){
    bool res = false;
    map<const string, User>::iterator p = table_users.find(id);
    if (p == table_users.end()){
        pair<map<const string, User *>::iterator, bool> pp = table_users.insert(make_pair(id, object));
        if (!pp.second)
            throw std::out_of_range("can't insert new item into map");
        res = true;
    }
    return res;
}*/

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
/*
bool Desp_sys::change(const string &id, const User *object){
    bool res = false;
    std::map<const std::string, User *>::iterator iter = table_users.find(id);
    if (iter != table_users.end()){
        object->info_key = table_users[id]->info_key;
        pair<map<const string, User *>::iterator, bool> pp = table_users.insert(make_pair(id, object));
        if (!pp.second)
            throw std::out_of_range("can't insert new item into map");
        res = true;
    }
    return res;
}
*/

Desp_sys & Desp_sys::start_work(const string &id){
    /*
    open file and copy in RAM
     */
    current_user = id;
    return *this;
}

Desp_sys & Desp_sys::end_work(){
    /*
     open file and copy in file
     */
    current_user = "";
    return *this;
}

Desp_sys & Desp_sys::change_table_users(){
    if (current_user == "Admin"){
        int choice;
        std::cout << "1. Append user" << std::endl;
        std::cout << "2. Delete user" << std::endl;
        //std::cout << "3. Change user" << std::endl;
        switch (ltmp::GET_NUM(choice, 2)) {
            case 0:
                break;
            case 1:{
                User tmp;
                string id;
                std::cout << "Id = ";
                std::cin >> id;
                std::cin.clear();
                std::cin >> tmp;
                //insert(id, tmp);
                break;
            }
            case 2:{
                string id;
                std::cout << "Id = ";
                std::cin >> id;
                std::cin.clear();
                remove(id);
                break;
            }
            /*case 3:{
                User tmp;
                string id;
                std::cout << "Id = ";
                std::cin >> id;
                std::cin.clear();
                std::cin >> tmp;
                
                break;
            }*/
            default:
                break;
        }
        return *this;
    }
    else{
        std::cout << "You are not authorized to do this" << std::endl;
        return *this;
    }
}

void Desp_sys::get_stat() const{
    std::cout << "Quantity file = " << quantity_file << std::endl;
    std::cout << "Quantity catalog = " << quantity_catalog << std::endl;
    /* обход иерхии*/
}


