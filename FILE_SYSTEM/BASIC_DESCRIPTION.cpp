//
//  BASIC_DESCRIPTION.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "BASIC_DESCRIPTION.hpp"
#include "DESCRIPTION_SYSTEM.hpp"
#include "USER.hpp"
#include "STREAM.hpp"
#include <ctime>
#include <map>
#include <set>
/*
using namespace std;
//copy constructor for catalog
Descatalog::Descatalog(const Descatalog &object){
   // virtual_adress
    
    map <Id, Basic_description *>::iterator i;

    Basic_description::size = sizeof(*this);
    }*/
//main constructor for catalog
Descatalog::Descatalog(const string &name, const string &location, const string &master, const string &vista, Desp_sys *global){
    //insert access_user
    ptr = global;
    virtual_adress = sizeof(global) + sizeof(global->table_users);
    Basic_description::size = sizeof(*this);
}/*
//main constructor for file
Desfile::Desfile(const string &master, const string &name, const string &location, const string &vista): ptr_stream(nullptr){
    time_t seconds = time(NULL);
    timeinfo = localtime(&seconds);
    
    this->master = master;
    
    Basic_description::size = sizeof(*this);
}
//copy constructor for file
Desfile::Desfile(const Desfile &object): ptr_stream(object.ptr_stream), timeinfo(object.timeinfo){

    this->master = object.master;
    
    Basic_description::size = sizeof(*this);
}

//int Desfile::open_file() const{
   // Desp_sys::hard_drive->seekg(*ptr_stream, std::ios::beg);//?
    //return Desp_sys::hard_drive->tellg();
//}

 virtual std::ostream & Descatalog::print(std::ostream &flow) const{
    map <Id, Basic_description *>::iterator i;
    for (i = struct_catalog.begin(); i < struct_catalog.end(); i++)
        //flow << i.id.name << i.id.location << std::endl;
    return flow;
}

Descatalog & Descatalog::add_file(){
        
        return *this;
    }
    
    Basic_description & Descatalog::search(const string &) const{
        
    }

*/
