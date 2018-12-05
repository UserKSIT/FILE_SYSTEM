//
//  BASIC_DESCRIPTION.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "BASIC_DESCRIPTION.hpp"
#include "USER.hpp"
#include "STREAM.hpp"
#include <ctime>
#include <map>
#include <string>
#include <iostream>
//добавить проверку прав доступа
using namespace std;

//копирующий конструктор для клона
Descatalog::Descatalog(const Descatalog &object){
    size = object.size;
    location = object.location;
    name = object.name;
    virtual_adress = object.virtual_adress;
    parent = object.parent;
    
    std::map<const string, const string>::const_iterator i;
    for (i = object.access_user.begin(); i != object.access_user.end(); ++i)
        access_user.insert(std::make_pair(i->first, i->second));
    
    std::map<const string, Basic_description *>::const_iterator p;
    for (p = object.struct_catalog.begin(); p != object.struct_catalog.end(); ++p)
        struct_catalog.insert(std::make_pair(p->first, p->second->clone()));
}

Descatalog::~Descatalog(){
    std::map<const string, Basic_description *>::iterator p;
    for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p){
        delete p->second;
        p->second = nullptr;
    }
}
//копирующий конструктор
Descatalog& Descatalog::operator = (const Descatalog &object){
    std::map<const string, Basic_description *>::iterator p;
    if (this != &object){
        size = object.size;
        location = object.location;
        name = object.name;
        //------------------------------
        access_user.clear();
        
        std::map<const string, const string>::const_iterator bb;
        for (bb = object.access_user.begin(); bb != object.access_user.end(); ++bb)
            access_user.insert(std::make_pair(bb->first, bb->second));
        //----------------------------------------------------------
        for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p)
            delete p->second;
        struct_catalog.clear();
        
        std::map<const string, Basic_description *>::const_iterator pp;
        for (pp = object.struct_catalog.begin(); pp != object.struct_catalog.end(); ++pp)
            struct_catalog.insert(std::make_pair(pp->first, pp->second->clone()));
    }
    return *this;
}
//копирующий конструктор
Basic_description& Basic_description::operator = (const Basic_description &object){
    if (this != &object){
        size = object.size;
        location = object.location;
        name = object.name;
        //------------------------------
        access_user.clear();
        
        std::map<const string, const string>::const_iterator pp;
        for (pp = object.access_user.begin(); pp != object.access_user.end(); ++pp)
            access_user.insert(std::make_pair(pp->first, pp->second));
    }
    return *this;
}

//вставка файла или подкатолога
bool Descatalog::insert(const string &name, const Basic_description *object){
    bool res = false;
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p == struct_catalog.end()){
        std::pair<std::map<const string, Basic_description *>::iterator, bool> pp = struct_catalog.insert(std::make_pair(name, object->clone()));
        //struct_catalog.insert(std::make_pair(name, object->clone()));
        if (!pp.second)
            throw std::out_of_range("can't insert new item into map");
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

bool ProtectedDesfile::remove_user(const string &name){
    bool res = false;
    std::map<const string, const string>::iterator p = table_users_access.find(name);
    if (p != table_users_access.end()){
        table_users_access.erase(p);
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

Descatalog * Descatalog::next(const string &name){// to do
    std::map<const string, Basic_description *>::iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        if (check_access(name, "move")){
            Descatalog * ptr = dynamic_cast<Descatalog *>(p->second);
            current_location += name;
            current_location += "/";
        return ptr;
        }
    }
    return nullptr;
}

Descatalog * Descatalog::back(){
    if (parent != nullptr){
        int sz1 = name.size();
        int sz2 = current_location.size();
        int delta = sz2 - sz1 - 1;
        
        current_location = current_location.substr(0, delta);
        return parent;
    }
    else
        return nullptr;
}

Descatalog * Descatalog::add_object(const string &id){
    //
    Basic_description *ptr = nullptr;
    Descatalog catalog(id);
    catalog.set_parent(this);
    Desfile file(id);
    
    int ans = Answer(Sh, NumSh);
        if (!std::cin.good())
            throw std::out_of_range("Error when a category object was entered");
        switch (ans){
            case 1:{
                
                quantity_catalog++;
                ptr = &catalog;
                break;
            }
            case 2:{
                // почему если вставить сюда происходит SIGABIRT - вызывается чисто виртуальная ф-ция?
                quantity_file++;
                ptr = &file;
                break;
            }
        }
    if (ptr != nullptr){
        if (this->insert(id, ptr))
            std::cout << "Ok" << std::endl;
        else
            std::cout << "Duplicate name" << std::endl;
    }
    else
        std::cout << "Wtf?" << std::endl;
    return this;
}

int Answer(const std::string alt[], int n)
{
    std::cout << current_location << std::endl;
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

Descatalog * Descatalog::delete_file(const string &name){//t
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

bool ProtectedDesfile::insert_user(const string &user, const string &mode){
    bool res = false;
    std::map<const string, const string>::iterator p = table_users_access.find(user);
    if (p == table_users_access.end()){
        std::pair<std::map<const string, const string>::iterator, bool> pp =
        table_users_access.insert(std::make_pair(user, mode));
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

Descatalog & Descatalog::set_parent(Descatalog *pt){
    parent = pt;
    return *this;
}

Desfile & Desfile::open_stream(){
    ptr_stream->open_stream_for_file(shift_stream);
    return *this;
}

int Desfile::open(){
    if (tag == 1){
        std::cout << "File have been open" << std::endl;
        return 0;
    }
    int res = 0;
    int ans;
    ans = Answer(Mode, NumMode);
        if (!std::cin.good())
            throw std::out_of_range("Error when a category object was entered");
        switch (ans){
            case 0:
                break;
            case 1:
                if (check_access(current_user, "r"))
                {
                    tag = 1;
                    res = 1;
                }
                break;
            case 2:
                if (check_access(current_user, "w")){
                    tag = 1;
                    res = 2;
                }
                break;
            case 3:
                if (check_access(current_user, "rw")){
                    tag = 1;
                    res = 3;
                }
                break;
        }
    return res;
}

Basic_description * Descatalog::open_file(const string &name, int &res){
    map <const string, Basic_description *>::const_iterator p = struct_catalog.find(name);
    if (p != struct_catalog.end()){
        Desfile *ptr = dynamic_cast<Desfile *>(p->second);
        res = ptr->open();
        return p->second;
    }
    else
        return nullptr;
}

bool Desfile::close_file() const{
    if (tag == 1){
        tag = 0;
        return true;
    }
    else{
        std::cout << "There haven't open file" << std::endl;
        return false;
    }
}

void Desfile::write_file(const string &info){
    ptr_stream->push_stream(info, shift_stream, size);
}


bool Basic_description::check_access(const string &id, const string &mode){
    bool res = false;
    std::map<const string, const string>::iterator p = access_user.find(id);
    if (p != access_user.end()){
        if (p->second == "rw")
            return true;
        if (p->second == mode)
            return true;
        }
        else
            return res;
    return res;
}

map <const string, Basic_description *>::const_iterator Descatalog::find(const string &name) const {
    std::map<const string, Basic_description *>::const_iterator p = struct_catalog.find(name);
    if(p == struct_catalog.end())
        std::cout << "The object with Name \"" << name << "\" is absent in container" << std::endl;
    else{
        std::cout << "The object with Name \"" << (*p).first << "\" is a " << this->get_name() << std::endl;
        }
    return p;
}

bool check_master(const string &name, Descatalog &object){
    std::map<const string, Basic_description *>::const_iterator p = object.struct_catalog.find(name);
    if (p != object.struct_catalog.end()){
        Desfile * ptr = dynamic_cast<Desfile *>(p->second);
        if (current_user == ptr->master)
            return true;
        else
            return false;
    }
    else
        return false;
}
//приравнивающий конструктор
Desfile& Desfile::operator = (const Desfile &object)
{
    if(this != &object){
        //-----------------------------
        size = 0;
        location = object.location;
        name = object.name;
        
        access_user.clear();
        
        std::map<const string, const string>::const_iterator pp;
        for (pp = object.access_user.begin(); pp != object.access_user.end(); ++pp)
            access_user.insert(std::make_pair(pp->first, pp->second));
        //-----------------------------
        
        timeinfo = object.timeinfo;
        master = object.master;
        ptr_stream = object.ptr_stream;
        
        //--------------------------------------
        ptr_stream->delete_info(shift_stream, size);
        
        shift_stream = ptr_stream->open_stream_for_file(shift_stream);
        
        ptr_stream->push_stream(object.ptr_stream->return_info(object.shift_stream, object.size), shift_stream, size);
        //----------------------------------------
    }
    return *this;
}
//копирующий конструктор для клона
Desfile::Desfile(const Desfile &object){
    size = object.size;
    location = object.location;
    name = object.name;
    
    timeinfo = object.timeinfo;
    master = object.master;
    ptr_stream = object.ptr_stream;
    
    std::map<const string, const string>::const_iterator pp;
    for (pp = object.access_user.begin(); pp != object.access_user.end(); ++pp)
        access_user.insert(std::make_pair(pp->first, pp->second));
    
    shift_stream = ptr_stream->open_stream_for_file(shift_stream);
}

void  Basic_description::change_access(const string &id, const string &mode){
    std::map<const string, const string>::iterator pp = access_user.find(id);
    if (pp != access_user.end()){
        if (pp->first != "ADMIN"){
            access_user.erase(pp);
            access_user.insert(std::make_pair(id, mode));
            return;
        }
        else{
            std::cout << "This is ADMIN" << std::endl;
            return;
        }
    }
    else{
        access_user.insert(std::make_pair(id, mode));
        return;
    }
}
/*
//1
std::ostream& Descatalog::write(std::ostream& ostr, Descatalog const& pr)
{
    ostr << size << location << name << virtual_adress << &access_user << &struct_catalog;
    return ostr;
}
//3
std::ostream& operator << (std::ostream& ostr, std::pair<std::string , Basic_description *> const& pr)
{
    ostr << pr.first.size()<< pr.first << sizeof(Basic_description) << pr.second;
    return ostr;
}
//4
std::ostream& operator << (std::ostream& ostr, const Basic_description * pr)
{
    ostr << pr->size << pr->location << pr->name << &pr->access_user;
    return ostr;
}
//2//5
std::ostream& operator << (std::ostream& ostr, std::pair<std::string , std::string> const& pr)
{
    ostr << pr.first.size() << pr.first << pr.second.size() << pr.second;
    return ostr;
}



std::istream& Descatalog::read(std::istream& istr, Descatalog const& pr)
{
    std::vector<char> buf_int(sizeof(int));
    istr.read(&buf_int[0], sizeof(int));
    //преобразование к int
    std::vector<char> buf_string(sizeof(string));
    istr.read(&buf_string[0], sizeof(string));
    //преоб
    istr.read(&buf_string[0], sizeof(string));
    
    
    
    std::size_t sz;
    istr >> pr.first >> sz;
    if(!istr)
        return istr;
    std::vector<char> tmp(sz);// vector испульзуется из-за того, string не дает contiguous гарантии
    istr.read(&tmp[0], sz);
    pr.second.assign(tmp.begin(), tmp.end());
    return istr;
}

std::istream& operator >>(std::istream& istr, std::pair<char, std::string>& pr)
{
    std::size_t sz;
    istr >> pr.first >> sz;
    if(!istr)
        return istr;
    std::vector<char> tmp(sz);// vector испульзуется из-за того, string не дает contiguous гарантии
    istr.read(&tmp[0], sz);
    pr.second.assign(tmp.begin(), tmp.end());
    return istr;
}
*/
//забей на DOS и просто записывай каталог в файл
//для пользователй выдели больше места и не еби себе мозг


















