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
#include <string>
#include <fstream>
#include <ctime>
//#include "Library_Template.hpp"


//copy constructor for catalog
Descatalog::Descatalog(const Descatalog &object): opp(object.opp), quant(object.quant){
    virtual_adress = Desp_sys::hard_drive->seekg(std::ios::end);
        for (int i = 0; i < opp; i++)
            struct_catalog[i] = *object.struct_catalog[i].clone();
    Basic_description::identity.name = object.identity.name;
    Basic_description::identity.location = object.identity.location;
    Basic_description::access_users.set_id(object.access_users.get_id());
    Basic_description::access_users.set_vista(object.access_users.get_vista());
    Basic_description::size = sizeof(*this);
    }
//main constructor for catalog
Descatalog::Descatalog(const string &name, const string &location, const string &master, const string &vista): opp(0), quant(0), struct_catalog(nullptr){
    virtual_adress = Desp_sys::hard_drive->seekg(std::ios::end);
    Basic_description::identity.name = name;
    Basic_description::identity.location = location;
    Basic_description::access_users.set_id(master);
    Basic_description::access_users.set_vista(vista);
    Basic_description::size = sizeof(*this);
}
//main constructor for file
Desfile::Desfile(const string &master, const string &name, const string &location, const string &vista): ptr_stream(nullptr){
    time_t seconds = time(NULL);
    timeinfo = localtime(&seconds);
    
    Basic_description::identity.name = name;
    Basic_description::identity.location = location;
    Basic_description::access_users.set_vista(vista);
    Basic_description::access_users.set_id(master);
    this->master = master;
    
    Basic_description::size = sizeof(*this);
}
//copy constructor for file
Desfile::Desfile(const Desfile &object): ptr_stream(object.ptr_stream), timeinfo(object.timeinfo){
    Basic_description::identity.name = object.identity.name;
    Basic_description::identity.location = object.identity.location;
    Basic_description::access_users.set_vista(object.access_users.get_vista());
    Basic_description::access_users.set_id(object.master);
    this->master = object.master;
    
    Basic_description::size = sizeof(*this);
}

int Desfile::open_file() const{
    Desp_sys::hard_drive->seekg(*ptr_stream, std::ios::beg);//?
    return Desp_sys::hard_drive.tellg();
}

    /*Descatalog & Descatalog::add_file(){
        
        return *this;
    }*/
    
    /*Basic_description & Descatalog::search(const string &) const{
        
    }*/
