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
#include <iostream>
//добавить проверку прав доступа
using namespace std;

    /*Descatalog::Descatalog(const string &name, const string &location, const string &master, const string &vista){
    //insert access_user
    //ptr = global;
    //virtual_adress = sizeof(global) + sizeof(global->table_users);
    Basic_description::size = sizeof(*this);
}*/

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



bool Descatalog::remove(const string &name)// to do
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

Descatalog * Descatalog::next(const string &name){
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        //динамическое приведение типа
        Descatalog * ptr = dynamic_cast<Descatalog *>(p->second);
        if (ptr){
            current_location = current_location + ptr->get_name();
            return ptr;
        }
        else
            return nullptr;
    }
    else
        return nullptr;
}

Descatalog * Descatalog::add_object(const string &id){
    Basic_description *ptr = nullptr;
    Descatalog catalog(id);
    Desfile file(id);
    std::string name;
    int ans;
    while(ans = Answer(Sh, NumSh)){
        std::cout << "Enter a shape name: --> ";
        std::cin >> name;
        
        if (!std::cin.good())
            throw std::out_of_range("Error when a shape name was entered");
        switch (ans){
            case 1:
                ptr = &catalog;
                break;
            case 2:
                ptr = &file;
                break;
        }
        if (!std::cin.good())
            throw std::out_of_range("Error when shape values were entered");
        std::cin.ignore(80, '\n');
        if (this->insert(name, ptr))
            std::cout << "Ok" << std::endl;
        else
            std::cout << "Duplicate name" << std::endl;
    }
    return this;
}

int Answer(const std::string alt[], int n)
{
    int answer;
    std::string prompt = Choice;
    std::cout << "\nWhat do you want to do:" << std::endl;
    for(int i = 0; i < n; i++)
        std::cout << alt[i].c_str() << std::endl;
    do{
        std::cout << prompt.c_str() << ": -> ";
        prompt = Msg;
        std::cin >> answer;
        if (!std::cin.good()){
            std::cout << "Error when number of choice was entered; \nRepeat, please." << std::endl;
            std::cin.ignore(80, '\n');
            std::cin.clear();
        }
    } while (answer < 0 || answer >= n);
    std::cin.ignore(80, '\n');
    return answer;
}

Descatalog * Descatalog::delete_catalog(const string &name){
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        //динамическое приведение типа
        Descatalog * ptr = dynamic_cast<Descatalog *>(p->second);
        if (ptr)
            this->remove(name);
        else
            std::cout << "Not found" << std::endl;
    }
    return this;
}

Descatalog * Descatalog::delete_file(const string &name){//to do
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        //динамическое приведение типа
        Desfile * ptr = dynamic_cast<Desfile *>(p->second);
        if (ptr)
            this->remove(name);
        else
            std::cout << "Not found" << std::endl;
    }
    return this;
}

bool Basic_description::insert_access(const string &user, const string &mode){
    bool res = false;
    std::map<const string, const string>::iterator p = access_user.find(user);
    if (p == access_user.end()){
        std::pair<std::map<const string, const string>::iterator, bool> pp =
        access_user.insert(std::make_pair(user, mode));
        if (!pp.second)
            throw std::out_of_range("can't insert new item into map");
        //динамическое приведение к файлу
        res = true;
    }
    return res;
}

std::ostream & Descatalog::print(std::ostream &flow) const{
    std::map<const string, Basic_description *>::const_iterator p;
    for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p)
        flow << p->first << std::endl;
    return flow;
}

std::ostream & Desfile::print(std::ostream &flow) const{
    return ptr_stream->return_info(flow, shift_stream, size);
}

std::ostream & ProtectedDesfile::print(std::ostream &flow) const{
    return ptr_stream->return_info(flow, shift_stream, size);
}




