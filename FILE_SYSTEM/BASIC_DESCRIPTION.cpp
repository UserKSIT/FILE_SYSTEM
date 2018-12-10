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
    name = object.name;
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
    access_user.clear();
}
//копирующий конструктор
Descatalog& Descatalog::operator = (const Descatalog &object){
    std::map<ID, Basic_description *>::iterator p;
    if (this != &object){
        size = object.size;
        name = object.name;
        parent = object.parent;

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
bool Descatalog::insert(ID &iden, const Basic_description *object){
    bool res = false;
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p == struct_catalog.end()){
        std::pair<std::map<ID, Basic_description *>::iterator, bool> pp = struct_catalog.insert(std::make_pair(iden, object->clone()));
        if (!pp.second)
            throw std::ios_base::failure("can't insert new item into map");
        res = true;
    }
    else
        std::cout << "Erro. Duplicate object" << std::endl;
    return res;
}
//delete object in catalog
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
    else
        std::cout << "Not found" << std::endl;
    return res;
}

bool Descatalog::change_name(const string &new_name, const ID &key){
    bool res = false;
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(key);
    if (p != struct_catalog.end()){
        Basic_description * ptr = p->second->clone();
        ID save_me = p->first;
        save_me.name = new_name;
        struct_catalog.erase(p);
        insert(save_me, ptr);
        
        res = true;
    }
    else
        std::cout << "Not found" << std::endl;
    return res;
}
//delete user in table access
bool ProtectedDesfile::remove_user(const string &name){
    bool res = false;
    std::map<const string, const string>::iterator p = table_users_access.find(name);
    if (p != table_users_access.end()){
        table_users_access.erase(p);
        res = true;
    }
    else
        std::cout << "Not found" << std::endl;
    return res;
}
//change object in catalog
bool Descatalog::replace(ID &iden, const Basic_description *object)
{
    bool res = false;
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        delete p->second;
        p->second = object->clone();
        res = true;
    }
    else
        std::cout << "Not found" << std::endl;
    return res;
}
//move in next catalog
Descatalog * Descatalog::next(ID &iden){// to do
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        if (current_user == check_access(current_user)){
            Descatalog * ptr = dynamic_cast<Descatalog *>(p->second);
            current_location += iden.name;
            current_location += "/";
        return ptr;
        }
    }
    else
        std::cout << "Not found" << std::endl;
    return nullptr;
}
//back in previos catalog
Descatalog * Descatalog::back(){
    if (parent != nullptr){
        long int sz1 = name.size();
        long int sz2 = current_location.size();
        long delta = sz2 - sz1 - 1;
        
        current_location = current_location.substr(0, delta);
        return parent;
    }
    else
        return nullptr;
}
//add new object in catalog
Descatalog * Descatalog::add_object(const string &name){
    //
    Basic_description *ptr = nullptr;
    Descatalog catalog(name);
    catalog.set_parent(this);
    Desfile file(name);
    ID id(name);
    
    int ans = Answer(Sh, NumSh);
        if (!std::cin.good())
            throw std::ios_base::failure("Error when a category object was entered");
        switch (ans){
            case 1:{
                
                quantity_catalog++;
                ptr = &catalog;
                break;
            }
            case 2:{
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
        std::cout << "Error definition Basic desription" << std::endl;
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
//insert in table access (for all type object)
bool Basic_description::insert_access(const string &user, const string &mode){
    bool res = false;
    std::map<const string, const string>::iterator p = access_user.find(user);
    if (p == access_user.end()){
        std::pair<std::map<const string, const string>::iterator, bool> pp =
        access_user.insert(std::make_pair(user, mode));
        if (!pp.second)
            throw std::ios_base::failure("can't insert new item into map");
        res = true;
    }
    else
        std::cout << "Erro. Duplicate object" << std::endl;
    return res;
}
//insert in special table access for protected file
bool ProtectedDesfile::insert_user(const string &user, const string& key){
    bool res = false;
    std::map<const string, const string>::iterator p = table_users_access.find(user);
    if (p == table_users_access.end()){
        std::pair<std::map<const string, const string>::iterator, bool> pp =
        table_users_access.insert(std::make_pair(user, key));
        if (!pp.second)
            throw std::ios_base::failure("can't insert new item into map");
        res = true;
    }
    else
        std::cout << "Erro. Duplicate object" << std::endl;
    return res;
}
//virtual print content catalog
std::ostream & Descatalog::print(std::ostream &flow) const{
    std::map<ID, Basic_description *>::const_iterator p;
    for (p = struct_catalog.begin(); p != struct_catalog.end(); ++p)
        flow << p->first.name << std::endl;
    return flow;
}
//virtual print content file and protected file
std::ostream & Desfile::print(std::ostream &flow) const{
    flow << ptr_stream->return_info(shift_stream, size) << std::endl;
    return flow;
}
std::ostream & ProtectedDesfile::print(std::ostream &flow) const{
    flow << ptr_stream->return_info(shift_stream, size) << std::endl;
    return flow;
}
//set parent catalog for move like in tree
Descatalog & Descatalog::set_parent(Descatalog *pt){
    parent = pt;
    return *this;
}
//reserve place for data file
Desfile & Desfile::open_stream(){
    ptr_stream->open_stream_for_file(shift_stream);
    return *this;
}

int Desfile::open(){
    int res = 0;
    if (tag == 1){
        std::cout << "File have been open" << std::endl;
        return res;
    }
    std::string key;
    key = check_access(current_user);
    if (key != ""){
        if (key == "r")
        {
            tag = 1;
            res = 1;
        }
        if (key == "w"){
            tag = 1;
            res = 2;
        }
        if (key == "rw"){
            tag = 1;
            res = 3;
        }
    }
    return res;
}

int ProtectedDesfile::open(){
    //check table_users_access
    std::map<const string, const string>::iterator p = table_users_access.find(current_user);
    if (p != table_users_access.end()){
        std::ostringstream out;
        out << ptr_stream->return_info(shift_stream, size);
        
        std::string info = out.str();
        std::string key;
        
        TPasswordEncryptDecrypt enigma;
        
        info = enigma.decryptMe(info, key);
        
        ptr_stream->delete_info(shift_stream, size);
        
        reserve_shift = shift_stream;
        ptr_stream = &temp;
        ptr_stream->open_stream_for_file(shift_stream);
        ptr_stream->push_stream(info, shift_stream, size);
        return 3;
        }
    else
        return 0;
    //decrypt file
    //change ptr
}
//virtual open?
Basic_description * Descatalog::open_file(ID &iden, int &res){
    map <ID, Basic_description *>::const_iterator p = struct_catalog.find(iden);
    if (p != struct_catalog.end()){
        res = p->second->open();
        return p->second;
    }
    else
        return nullptr;
}
//
bool Desfile::close_file(){
    if (tag == 1){
        tag = 0;
        return true;
    }
    else{
        std::cout << "There haven't open file" << std::endl;
        return false;
    }
}

bool ProtectedDesfile::close_file(){
    if (tag == 1){
        tag = 0;
        std::ostringstream out;
        
        out << ptr_stream->return_info(shift_stream, size);
        
        std::string info = out.str();
        std::string key;
        
        TPasswordEncryptDecrypt enigma;
        
        info = enigma.encryptMe(info, key);
            
        ptr_stream->delete_info(shift_stream, size);
        shift_stream = reserve_shift;
        ptr_stream = &sym;
        ptr_stream->push_stream(info, shift_stream, size);
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


std::string Basic_description::check_access(const string &id) const{
    std::map<const string, const string>::const_iterator p = access_user.find(id);
    if (p != access_user.end())
        return p->second;
    else
        return "";
}

map <ID, Basic_description *>::const_iterator Descatalog::find(ID &iden, bool &flag) const {
    std::map<ID, Basic_description *>::const_iterator p = struct_catalog.find(iden);
    if(p == struct_catalog.end()){
        std::cout << "The object with Name \"" << iden.name << "\" is absent in container" << std::endl;
        flag = false;
    }
    else{
        std::cout << "The object with Name \"" << &(*p).first << "\" is a " << iden.name << std::endl;
        flag = true;
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
        name = object.name;
        
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
    name = object.name;
    
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
std::string Descatalog::show_access(const ID &key) const{
    std::ostringstream out;
    map<ID, Basic_description *>::const_iterator c = struct_catalog.find(key);
    if (c != struct_catalog.end()){
        out << c->second->show_access();
    }
    else
        std::cout << "Not found" << std::endl;
    return out.str();
}

std::string Basic_description::show_access() const{
    std::ostringstream out;
    map<const string, const string>::const_iterator p;
    for (p = access_user.begin(); p != access_user.end(); p++)
        out << p->first << ' ' << p->second << std::endl;
    
    return out.str();
}

//to do
bool Descatalog::crypt_file(ID &key){
    map<ID, Basic_description *>::iterator p = struct_catalog.find(key);
    if(p != struct_catalog.end()){
        Desfile * ptr = dynamic_cast<Desfile *>(p->second);
        if (ptr != nullptr){
            if (current_user == ptr->get_master()){
                std::ostringstream out;
                
                out << *ptr;
                
                std::string info = out.str();
                std::string key;
    
                TPasswordEncryptDecrypt enigma;
                info = enigma.encryptMe(info, key);

                std::cout << info << std::endl;
                
                ptr->delete_info();
                std::cout << "Ok" << std::endl;
                
                
                ProtectedDesfile crypt_f(p->first.name);
                int sz = info.size();
                crypt_f.set_size(sz);
                if(!crypt_f.replace_user(current_user, key)){
                    throw std::invalid_argument("Incorrect access");
                }
                crypt_f.write_file(info);
                
                
                
                Basic_description * ptr = &crypt_f;
                ID buf(p->first.name);
                buf.location = p->first.location;
                buf.virtual_adress = p->first.virtual_adress;
                replace(buf, ptr);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool Descatalog::decrypt_file(ID &key){
    std::map<ID, Basic_description *>::iterator p = struct_catalog.find(key);
    if(p != struct_catalog.end()){
        ProtectedDesfile * ptr = dynamic_cast<ProtectedDesfile *>(p->second);
        if (ptr != nullptr){
            if (current_user == ptr->get_master()){
                std::ostringstream out;
                
                out << *ptr;
                
                std::string info = out.str();
                std::string key = ptr->get_key();
                
                TPasswordEncryptDecrypt enigma;
                info = enigma.decryptMe(info, key);
                
                std::cout << info << std::endl;
                
                ptr->delete_info();
                std::cout << "Ok" << std::endl;
                
                
                Desfile decrypt_f(p->first.name);
                int sz = info.size();
                
                decrypt_f.set_size(sz);
                
                decrypt_f.write_file(info);
                
                
                
                Basic_description * ptr = &decrypt_f;
                ID buf(p->first.name);
                buf.location = p->first.location;
                buf.virtual_adress = p->first.virtual_adress;
                replace(buf, ptr);
                return true;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;
}

bool ProtectedDesfile::decrypt(){
    std::map<const string, const string>::iterator p = table_users_access.find(current_user);
    if (p != table_users_access.end()){
        std::ostringstream out;
        out << ptr_stream->return_info(shift_stream, size);
        
        std::cout << out.str() << std::endl;
        
        TPasswordEncryptDecrypt enigma;
        
        std::string info = out.str();
        std::string key = p->second;
        
        info = enigma.decryptMe(info, key);
        
        ptr_stream->delete_info(shift_stream, size);
        
        ptr_stream = &main_s;
        shift_stream = reserve_shift;
        Desfile dec(name);
        size = info.size();
        
        ptr_stream->push_stream(info, shift_stream, size);
        return 3;
    }
    else
        return 0;
}

bool ProtectedDesfile::replace_user(const string &name, const string &key)
{
    bool res = false;
    std::map<const string, const string>::iterator p = table_users_access.find(name);
    if (p != table_users_access.end()){
        table_users_access.erase(p);
        table_users_access.insert(std::make_pair(name, key));
        res = true;
    }
    else
        std::cout << "Not found" << std::endl;
    return res;
}

std::string Descatalog::get_status() const{
    std::ostringstream out;
    
    out << "Name catalog: " << name << std::endl;
    out << "Size: " << size << std::endl;
    out << "Table access:" << std::endl;
    out << &access_user << std::endl;
    out << &struct_catalog << std::endl;
    
    return out.str();
}//to do
std::string Desfile::get_status() const{
    std::ostringstream out;
    
    out << "Name file: " << name << std::endl;
    out << "Time:" << std::endl << timeinfo << std::endl;
    out << "Master: " << master << std::endl;
    long int tmp = shift_stream;
    out << "Shift in file: " << tmp << std::endl;
    out << "Size: " << size << std::endl;
    out << "Table access:" << std::endl;
    out << &access_user << std::endl;
    
    return out.str();
}//to do
std::string ProtectedDesfile::get_status() const{
    std::ostringstream out;
    
    out << "Name file: " << name << std::endl;
    out << "Time:" << std::endl << timeinfo << std::endl;
    out << "Master: " << master << std::endl;
    long int tmp = shift_stream;
    out << "Shift in file: " << tmp << std::endl;
    out << "Size: " << size << std::endl;
    out << "Table access:" << std::endl;
    out << &access_user << std::endl;
    out << "Table user have acess to content:" << std::endl;
    out << &table_users_access << std::endl;
    
    return out.str();
}

bool Descatalog::pull_in_buffer(ID &key, ID &BUFFER_key, Basic_description *& BUFFER_ptr){
    map<ID, Basic_description *>::iterator p = struct_catalog.find(key);
    if (p != struct_catalog.end()){
        BUFFER_key = p->first;
        BUFFER_ptr = p->second->clone();
        
        return true;
    }
    else{
        std::cout << "Not found" << std::endl;
        return false;
    }
}

bool Descatalog::extract_out_buffer(ID &BUFFER_key, Basic_description *& BUFFER_ptr){
    if (!BUFFER_key.empty() && BUFFER_ptr != nullptr){
        this->insert(BUFFER_key, BUFFER_ptr);
        
        BUFFER_key.clear();
        delete BUFFER_ptr;
        BUFFER_ptr = nullptr;
        
        return true;
    }
    else
        return false;
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
    read_struct_catalog(istr, struct_catalog);
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
    //read_time(istr, timeinfo);
    istr >> timeinfo->tm_sec >> timeinfo->tm_min >> timeinfo->tm_hour >>timeinfo->tm_mday;
    istr >> timeinfo->tm_mon >> timeinfo->tm_year >> timeinfo->tm_wday >> timeinfo->tm_yday;
    istr >> timeinfo->tm_isdst;
    long int buf;
    istr >> buf;
    shift_stream = buf;
    return istr;
}
std::istream& ProtectedDesfile::read(std::istream& istr){
    //read_time(istr, timeinfo);
    istr >> timeinfo->tm_sec >> timeinfo->tm_min >> timeinfo->tm_hour >>timeinfo->tm_mday;
    istr >> timeinfo->tm_mon >> timeinfo->tm_year >> timeinfo->tm_wday >> timeinfo->tm_yday;
    istr >> timeinfo->tm_isdst;
    long int buf;
    istr >> buf;
    shift_stream = buf;
    //read_table_access_user(istr, table_users_access);
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
std::istream & read_time(std::istream & flow, tm * object){
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
std::ostream& operator << (std::ostream& ostr, map<ID, Basic_description *> &table)
{
    if(!table.empty()){
        Basic_description * ptr;
        size_t sz = table.size();
        //write size map;
        ostr << sz << ' ';
        
        map<ID, Basic_description *>::const_iterator i;
        
        for(i = table.begin(); i != table.end(); i++){
            ptr = i->second;
            if (dynamic_cast<Descatalog *>(ptr)){
                ostr << "Catalog" << ' ';
            }
            ptr = i->second;
            if (dynamic_cast<Desfile *>(ptr)){
                ostr << "File" << ' ';
            }
            ptr = i->second;
            if (dynamic_cast<ProtectedDesfile *>(ptr)){
                ostr << "Protected_File" << ' ';
            }
            //write data key
            ostr << i->first.name << ' ' << i->first.location << ' ' << i->first.virtual_adress << ' ';
            //write object
            i->second->write(ostr);
        }
    }
    return ostr;
}
//read map struct catalog
std::istream& read_struct_catalog(std::istream& istr, map<ID, Basic_description *> &table)//?
//add check sucsess insert
{
    size_t sz;
    string name, location, buf;
    long int virtual_adress;
    
    Basic_description * ptr;
    Descatalog catalog;
    Desfile file;
    ProtectedDesfile pfile;
    
    ID iden;
    //read size map
    istr >> sz;

    for(int i = 0; i < sz; i++){
        //read key map
        istr >> name;
        istr >> location;
        istr >> virtual_adress;
        //init buffer for insert
        iden.name = name;
        iden.location = location;
        iden.virtual_adress = virtual_adress;
        //read type object
        istr >> buf;
        //init type object
        if (buf == "Catalog"){
            //quantity_catalog++;
            ptr = &catalog;
            //sys.seekg(virtual_adress);
            ptr->read(istr);
            
            table.insert(std::make_pair(iden, ptr->clone()));
        }
        if (buf == "File"){
            //quantity_file++;
            ptr = &file;
            //sys.seekg(virtual_adress);
            ptr->read(istr);
        
            table.insert(std::make_pair(iden, ptr->clone()));
        }
        if (buf == "Protected_File"){
            //quantity_file++;
            ptr = &pfile;
            //sys.seekg(virtual_adress);
            ptr->read(istr);
            
            table.insert(std::make_pair(iden, ptr->clone()));
        }
    }
    return istr;
}
std::istream& read_table_access_pf(std::istream& istr, map<const string, int> &table){
    size_t sz;
    string name;
    int key;
    
    istr >> sz;
    
    for(int i = 0; i != sz; i++){
        istr >> name;
        istr >> key;
        
        table.insert(std::make_pair(name, key));
    }
    return istr;
}

std::ostream& operator << (std::ostream& ostr, set<const string> &table){
    size_t sz = table.size();
    
    ostr << sz << ' ';
    
    set<const string>::const_iterator i;
    
    for(i = table.begin(); i != table.end(); i++){
        ostr << *i << ' ';
    }
    return ostr;
}

std::string ProtectedDesfile::get_key(){
    std::map<const string, const string>::iterator p = table_users_access.find(current_user);
    if (p != table_users_access.end())
        return p->second;
    else
        return "";
}

void ProtectedDesfile::set_key(const string &key){
    std::map<const string, const string>::iterator p = table_users_access.find(current_user);
    if (p != table_users_access.end()){
        table_users_access.erase(p);
        table_users_access.insert(std::make_pair(current_user, key));
    }
    return;
}

bool Basic_description::remove_access(const string &name){
    bool res = false;
    std::map<const string, const string>::iterator p = access_user.find(name);
    if (p != access_user.end()){
        access_user.erase(p);
        res = true;
    }
    else
        std::cout << "Not found" << std::endl;
    return res;
}



