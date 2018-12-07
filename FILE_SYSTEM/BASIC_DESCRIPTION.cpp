//
//  BASIC_DESCRIPTION.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "BASIC_DESCRIPTION.hpp"

//добавить проверку прав доступа
using namespace std;




//копирующий конструктор для клона
Descatalog::Descatalog(const Descatalog &object){
    size = object.size;

    parent = object.parent;
    
    std::map<const string, const string>::const_iterator i;
    for (i = object.access_user.begin(); i != object.access_user.end(); ++i)
        access_user.insert(std::make_pair(i->first, i->second));
    
    std::map<ID, Basic_description *>::const_iterator p;
    for (p = object.struct_catalog.begin(); p != object.struct_catalog.end(); ++p)
        struct_catalog.insert(std::make_pair(p->first, p->second->clone()));
}

Descatalog::~Descatalog(){
    std::map<ID, Basic_description *>::iterator p;
    for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p){
        delete p->second;
        p->second = nullptr;
    }
}
//копирующий конструктор
Descatalog& Descatalog::operator = (const Descatalog &object){
    std::map<ID, Basic_description *>::iterator p;
    if (this != &object){
        size = object.size;

        //------------------------------
        access_user.clear();
        
        std::map<const string, const string>::const_iterator bb;
        for (bb = object.access_user.begin(); bb != object.access_user.end(); ++bb)
            access_user.insert(std::make_pair(bb->first, bb->second));
        //----------------------------------------------------------
        for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p)
            delete p->second;
        struct_catalog.clear();
        
        std::map<ID, Basic_description *>::const_iterator pp;
        for (pp = object.struct_catalog.begin(); pp != object.struct_catalog.end(); ++pp)
            struct_catalog.insert(std::make_pair(pp->first, pp->second->clone()));
    }
    return *this;
}
//копирующий конструктор
Basic_description& Basic_description::operator = (const Basic_description &object){
    if (this != &object){
        size = object.size;
        //------------------------------
        access_user.clear();
        
        std::map<const string, const string>::const_iterator pp;
        for (pp = object.access_user.begin(); pp != object.access_user.end(); ++pp)
            access_user.insert(std::make_pair(pp->first, pp->second));
    }
    return *this;
}

//вставка файла или подкатолога
bool Descatalog::insert(ID &iden, const Basic_description *object){
    bool res = false;
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p == struct_catalog.end()){
        std::pair<std::map<ID, Basic_description *>::iterator, bool> pp = struct_catalog.insert(std::make_pair(iden, object->clone()));
        if (!pp.second)
            throw std::out_of_range("can't insert new item into map");
        res = true;
    }
    return res;
}

bool Descatalog::remove(ID &iden)// to do
{
    bool res = false;
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
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

bool Descatalog::replace(ID &iden, const Basic_description *object)
{
    bool res = false;
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        delete p->second;
        p->second = object->clone();
        res = true;
    }
    return res;
}

Descatalog * Descatalog::next(ID &iden){// to do
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        //if (check_access(name, "move")){
            Descatalog * ptr = dynamic_cast<Descatalog *>(p->second);
            current_location += iden.name;
            current_location += "/";
        return ptr;
        //}
    }
    return nullptr;
}

Descatalog * Descatalog::back(){//change?
    if (parent != nullptr){
        //int sz1 = name.size();
        //int sz2 = current_location.size();
        //int delta = sz2 - sz1 - 1;
        
        //current_location = current_location.substr(0, delta);
        return parent;
    }
    else
        return nullptr;
}

Descatalog * Descatalog::add_object(const string &name){
    //
    Basic_description *ptr = nullptr;
    Descatalog catalog;
    catalog.set_parent(this);
    Desfile file;
    ID id(name);
    
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
        std::cout << "W?" << std::endl;
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

Descatalog * Descatalog::delete_catalog(ID &iden){
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        //динамическое приведение типа
        Descatalog * ptr = dynamic_cast<Descatalog *>(p->second);
        if (ptr)
            this->remove(iden);
        else
            std::cout << "Not found" << std::endl;
    }
    return this;
}

Descatalog * Descatalog::delete_file(ID &iden){//t
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        //динамическое приведение типа
        Desfile * ptr = dynamic_cast<Desfile *>(p->second);
        if (ptr)
            this->remove(iden);
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
    std::map<ID, Basic_description *>::const_iterator p;
    for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p)
        flow << p->first.name << std::endl;
    return flow;
}

std::ostream & Desfile::print(std::ostream &flow) const{
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

Basic_description * Descatalog::open_file(ID &iden, int &res){
    map <ID, Basic_description *>::const_iterator p = struct_catalog.find(iden);
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

map <ID, Basic_description *>::const_iterator Descatalog::find(ID &iden) const {
    std::map<ID, Basic_description *>::const_iterator p = struct_catalog.find(iden);
    if(p == struct_catalog.end())
        std::cout << "The object with Name \"" << iden.name << "\" is absent in container" << std::endl;
    else{
        std::cout << "The object with Name \"" << &(*p).first << "\" is a " << iden.name << std::endl;
        }
    return p;
}
//приравнивающий конструктор
Desfile& Desfile::operator = (const Desfile &object)
{
    if(this != &object){
        //-----------------------------
        size = 0;
        
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
    
    timeinfo = object.timeinfo;
    master = object.master;
    ptr_stream = object.ptr_stream;
    
    std::map<const string, const string>::const_iterator pp;
    for (pp = object.access_user.begin(); pp != object.access_user.end(); ++pp)
        access_user.insert(std::make_pair(pp->first, pp->second));
    
    if (shift_stream == 0)
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


//write file
std::ostream& Descatalog::write(std::ostream& ostr)
{
    ostr << "Catalog" << ' ' << size << ' ' << &access_user << &struct_catalog << '\n';
    
    return ostr;
}
//read catalog
std::istream& Descatalog::read(std::istream& istr)
{
    istr >> size;
    read_access_user(istr, access_user);
    //read_struct_catalog(istr, struct_catalog);
    return istr;
}
//write file
std::ostream& Desfile::write(std::ostream& ostr){
    
    ostr << "File" << timeinfo << ' ' << shift_stream << '\n';
    
    return ostr;
}
//write protected file
std::ostream& ProtectedDesfile::write(std::ostream& ostr){
    ostr << "Protected_File" << timeinfo  << ' ' << shift_stream << &table_users_access << '\n';
    
    return ostr;
}
std::istream& Desfile::read(std::istream& istr){
    return istr;
}
std::istream& ProtectedDesfile::read(std::istream& istr){
    return istr;
}
//write time info
std::ostream & operator << (std::ostream & flow, tm * object){
    flow << object->tm_sec << ' ' << object->tm_min << ' ' << object->tm_hour << ' ' << object->tm_mday << ' ';
    flow << object->tm_mon << ' ' << object->tm_year <<  ' ' << object->tm_wday << ' ' << object->tm_yday << ' ';
    flow << object->tm_isdst << ' ';
    
    return flow;
}
//read time info
std::istream & operator << (std::istream & flow, tm * object){
    flow >> object->tm_sec >> object->tm_min >> object->tm_hour >>object->tm_mday;
    flow >> object->tm_mon >> object->tm_year >> object->tm_wday >> object->tm_yday;
    flow >> object->tm_isdst;
    
    return flow;
}
//write map <string, string>
std::ostream& operator << (std::ostream& ostr, map<const string, const string> &table)
{
    size_t sz = table.size();
    
    ostr << sz << ' ';
    
    map<const string, const string>::const_iterator i;
    
    for(i = table.begin(); i != table.end(); i++){
        ostr << i->first << ' ';
        ostr << i->second << ' ';
    }
    return ostr;
}
//read map <string, string>
std::istream& read_access_user(std::istream& istr, map<const string, const string> &table)
{
    size_t sz;
    string first, second;
    
    istr >> sz;
    
    for(int i = 0; i != sz; i++){
        istr >> first;
        istr >> second;
        
        table.insert(std::make_pair(first, second));
    }
    return istr;
}
//write map struct catalog
std::ostream& operator << (std::ostream& ostr, map<const string, Basic_description *> &table)
{
    if(!table.empty()){
        size_t sz = table.size();
        
        ostr << sz << ' ';
        
        map<const string, Basic_description *>::const_iterator i;
        
        for(i = table.begin(); i != table.end(); i++){
            ostr << i->first << ' ';
            
            i->second->write(ostr);
        }
    }
    return ostr;
}
//read map struct catalog
std::istream& read_struct_catalog(std::istream& istr, map<const string, Basic_description *> &table)//?
//add check sucsess insert
{
    size_t sz;
    string id, buf;
    istr >> sz;
    Basic_description * ptr;
    Descatalog catalog;
    Desfile file;
    ProtectedDesfile pfile;

    
    for(int i = 0; i < sz; i++){
        istr >> id;
        istr >> buf;
        if (buf == "Catalog"){
            quantity_catalog++;
            ptr = &catalog;
            //переместить указатель
            ptr->read(istr);
            
            table.insert(std::make_pair(id, ptr->clone()));
        }
        if (buf == "File"){
            quantity_file++;
            ptr = &file;
            //переместить указатель
            ptr->read(istr);
        
            table.insert(std::make_pair(id, ptr->clone()));
        }
        if (buf == "Protected_File"){
            quantity_file++;
            ptr = &pfile;
            //переместить указатель
            ptr->read(istr);
            
            table.insert(std::make_pair(id, ptr->clone()));
        }
    }
    return istr;
}


