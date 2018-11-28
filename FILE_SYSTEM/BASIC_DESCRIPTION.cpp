//
//  BASIC_DESCRIPTION.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "BASIC_DESCRIPTION.hpp"
//#include "DESCRIPTION_SYSTEM.hpp"
#include "USER.hpp"
#include "STREAM.hpp"
#include <ctime>
#include <map>
#include <string>
//добавить проверку прав доступа
using namespace std;

    Descatalog::Descatalog(const string &name, const string &location, const string &master, const string &vista){
    //insert access_user
    //ptr = global;
    //virtual_adress = sizeof(global) + sizeof(global->table_users);
    Basic_description::size = sizeof(*this);
}

Descatalog::Descatalog(const Descatalog &object){
    std::map<const string, Basic_description *>::const_iterator p;
    for (p = object.struct_catalog.begin(); p != object.struct_catalog.end(); ++p)
        struct_catalog.insert(std::make_pair(p->first, p->second->clone()));
    //динамическое приведение
}

Descatalog::~Descatalog(){
    std::map<const string, Basic_description *>::iterator p;
    for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p){
        delete p->second;
        p->second = nullptr;
    }
}

Descatalog& Descatalog::operator = (const Descatalog &object){
    std::map<const string, Basic_description *>::iterator p;
    if (this != &object){
        for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p)
            delete p->second;
        struct_catalog.clear();
        
        std::map<const string, Basic_description *>::const_iterator pp;
        for (pp = object.struct_catalog.begin(); pp != object.struct_catalog.end(); ++pp)
            struct_catalog.insert(std::make_pair(pp->first, pp->second->clone()));
        //динамическое приведение к файлу и каталогу
    }
    return *this;
}

bool Descatalog::insert(const string &name, const Basic_description *object){
    bool res = false;
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p == struct_catalog.end()){
        std::pair<std::map<const string, Basic_description *>::iterator, bool> pp =
        struct_catalog.insert(std::make_pair(name, object->clone()));
        if (!pp.second)
            throw std::out_of_range("can't insert new item into map");
        //динамическое приведение к файлу
        res = true;
    }
    return res;
}

bool Descatalog::remove(const string &name)
{
    bool res = false;
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        delete p->second;
        p->second = nullptr;
        struct_catalog.erase(p);
        res = true;
    }
    return res;
}

bool Descatalog::replace(const string &name, const Basic_description *object)
{
    bool res = false;
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        delete p->second;
        p->second = object->clone();
        res = true;
    }
    return res;
}
