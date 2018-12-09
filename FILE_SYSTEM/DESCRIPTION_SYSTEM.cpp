//
//  DESCRIPTION_SYSTEM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "DESCRIPTION_SYSTEM.hpp"

using namespace std;

Desp_sys::Desp_sys(const string & word){
        if(word == "Yes"){
            root = new Descatalog;
            current_user = "";
            current_location = "root/";
            quantity_file = 0;
            quantity_catalog = 1;
            User object("ADMIN");
            this->insert_user("ADMIN", object);
    }
    
}

bool Desp_sys::check_in_table(const string &id){
    map<const string, User>::iterator p = table_users.find(id);
    if (p != table_users.end())
        return true;
    else
        return false;
}

bool Desp_sys::insert_user(const string &id, const User object){
    bool res = false;
    map<const string, User>::iterator p = table_users.find(id);
    if (p == table_users.end()){
        table_users.insert(make_pair(id, object));
    }
    return res;
}

bool Desp_sys::remove(const std::string &id){
    bool res = false;
    std::map<const std::string, User>::iterator iter = table_users.find(id);
    if (iter != table_users.end()){
        table_users.erase(iter);
        res = true;
    }
    return res;
}

bool Desp_sys::change(const string &id, const User &object){
    bool res = false;
    std::map<const std::string, User>::iterator iter = table_users.find(id);
    if (iter != table_users.end()){
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
/*
Desp_sys * download_file(std::fstream &file){
    
    return nullptr;
}
*/
const string & Desp_sys::get_name(map<const string, User>::const_iterator &i) const {
    return i->second.get_name();
}

const string & Desp_sys::get_info_key(map<const string, User>::const_iterator &i) const{
    return i->second.get_info_key();
}

std::ostream & operator << (std::ostream &flow, const Desp_sys &object) {
    map<const string, User>::const_iterator i;
    for (i = object.table_users.begin(); i != object.table_users.end(); i++){
        flow << "Id user: " << i->first << "  Name user: " << object.get_name(i) << "  Info key: " << object.get_info_key(i) << std::endl;
    }
    return flow;
}

Desp_sys & read_out_file(std::istream& istr, Desp_sys &object){
    Desp_sys SYSTEM;
    
    size_t sz_table;
    string key, name, info_key;
    int next = 1;
    long int st_cat;
    User buf;
    
    sys.seekg(0, std::ios::beg);

    istr >> sz_table;
    for(int i = 0; i < sz_table; i++){
        istr >> key;
        istr >> name;
        istr >> info_key;
        
        buf.set_name(name);
        buf.set_info_key(info_key);
        object.insert_user(key, buf);
    }
    istr >> next;
    
    
    st_cat = sys.tellg();
    
    
    while (next != 0){
        istr >> sz_table;
        for(int i = 0; i < sz_table; i++){
            istr >> key;
            istr >> name;
            istr >> info_key;
            
            buf.set_name(name);
            buf.set_info_key(info_key);
            object.insert_user(key, buf);
        }
        istr >> next;
    }
    
    sys.seekg(st_cat);
    
   
    
    return object;
}


















































































/*
bool upload_file(std::fstream &file, Desp_sys &object){
    if (file.is_open())
        std::cout << "File is open\n";
    else{
        std::cout << "Fuck you nigga\n";
        return false;
    }
    file.seekg(std::ios::beg);
    
    std::cout << sizeof(string) << std::endl;
    
    int sz = object.table_users.size();
    file.write((char *) &sz, sizeof(int));
    
    map<const string, User>::const_iterator i;
    for (i = object.table_users.begin(); i != object.table_users.end(); i++){
        file.write(i->first.c_str(), sizeof(string));
        file.write((char *) &object.get_name(i), sizeof(string));
        file.write((char *) &object.get_info_key(i), sizeof(string));
    }
    
    for (int i = 0; i < 31; i++){
        file.write("0", sizeof(string));
        file.write("0", sizeof(string));
        file.write("0", sizeof(string));
    }
    return true;
}

bool push_file(const string &info, std::ios::pos_type &virtual_adress, int &size){
    bool res = true;
    if (info.size() == 0)
        return res;
    int block = 508;
    
    int edge = virtual_adress;
    edge += size;
    sys.seekg(edge);
    int residue_block = size % block;
    std::ios::pos_type prev = 0;
    string cur;
    int quant = 0;
    
    int dif = 0;
    if (size == 0){
        quant = info.size() / block;
        if (quant > 0)
            for (int i = 0; i <= quant; i++){
                sys.write(info.substr(508*i, 508*(i + 1)).c_str(), 508);
                
                prev = sys.tellp();
                sys.seekp(std::ios::end);
                cur = sys.tellp();
                sys.seekp(prev);
                sys.write(cur.c_str(), 4);
                sys.seekp(std::ios::end);
            }
        else
            sys.write(info.substr(0, 508).c_str(), 508);
    }
    else{
        if (residue_block != 0){
            sys.write(info.substr(0, block - residue_block).c_str(), block - residue_block);
            dif = 1;
        
            int check = (info.size() - dif*(block - residue_block));
            if ( check > 0){
                quant = check / block;
                for (int i = 0; i <= quant; i++){
                    prev = sys.tellp();
                    sys.seekp(std::ios::end);
                    cur = sys.tellp();
                    sys.seekp(prev);
                    sys.write(cur.c_str(), 4);
                    sys.seekp(std::ios::end);
                    
                    sys.write(info.substr((info.size() - dif*(block - residue_block)) - i * 508, (info.size() - dif*(block - residue_block)) - 508 * (i + 1)).c_str(), 508);
                }
            }
        }
    }

    return res;
}

void return_info(const std::ios::pos_type &virtual_adress, const int &size, Desp_sys &object){
    sys.seekg(virtual_adress);
    int block = 508;
    int quant = size / block;
    int residue = size % block;
    
    char * next = new char[4];
    int tmp;
    
    int sub = 0;
    int __residue = 0;
    
    
    User app;
    int j = 1;
    
    int __i;
    
    char * str_id = new char[24];
    char * str_name = new char[24];
    char * str_key = new char[24];
    char * str__ = nullptr;
    char * __str = nullptr;
    char * __str__ = new char[24];
    
    
    for(int i = 0; i < quant; i++){
        if (sub != 0){
            __str = new char[24 - sub];
            sys.read(__str, 24 - sub);
            
            __i = 0;
            for(int g = 0; g < sub; g++){
                __str__[__i] = str__[g];
                __i++;
            }
            for(int g = 24 - sub; g < 24; g++){
                __str__[__i] = __str[g];
                __i++;
            }
            
            if (__residue == 2){
                app.set_name(str_name);
                app.set_info_key(__str__);
                
                object.insert_user(str_id, app);
            }else if (__residue == 1){
                sys.read(str_key, 24);
                
                app.set_name(__str__);
                app.set_info_key(str_key);
                
                object.insert_user(str_id, app);
            }else{
                sys.read(str_name, 24);
                sys.read(str_key, 24);
                
                app.set_name(__str__);
                app.set_info_key(str_key);
                
                object.insert_user(str_id, app);
            }
            delete [] str__;
            delete [] __str;
        }
        while ((508 / (j*72)) > 0){
        sys.read(str_id, 24);
        sys.read(str_name, 24);
        sys.read(str_key, 24);
        
        app.set_name(str_name);
        app.set_info_key(str_key);
        
        object.insert_user(str_id, app);
            j++;
        }
        sub = 508 - (508 / (j*72));
        __residue = sub / 24;
        
        if (__residue == 2){
            sys.read(str_id, 24);
            sys.read(str_name, 24);
        }else if (__residue == 1){
            sys.read(str_id, 24);
        }else{
            str__ = new char [sub];
            sys.read(str__, sub);
        }
        
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }
    while ((508 / (j*72)) > 0){
        sys.read(str_id, 24);
        sys.read(str_name, 24);
        sys.read(str_key, 24);
        
        app.set_name(str_name);
        app.set_info_key(str_key);
        
        object.insert_user(str_id, app);
    }
    
    
    delete [] str_id;
    delete [] str_name;
    delete [] str_key;
    delete [] str__;
    delete [] __str;
    delete []  __str__;
    delete [] next;
}
}*/


