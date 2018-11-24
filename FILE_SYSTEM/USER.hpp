//
//  USER.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef USER_hpp
#define USER_hpp

#include <stdio.h>
#include <string>

using namespace std;

namespace lcu {
    class Basic_user{
    protected:
        string id;
    public:
        Basic_user(const string &id = ""): id(id){}
    
        const string & get_id() const {return this->id;}
        const string & set_id(const string &id) {this->id = id; return this->id;}
    };
    
    class User: public Basic_user{
    private:
        string name;
        string info_key;
    public:
        User(const string &name = "", const string &id = ""): Basic_user(id), name(name), info_key(nullptr) {this->id = id;}
        
        const string & get_name();
        const string & get_info_key();
        
        const string & set_name(const string &);
        const string & set_info_key(const string &);
    };
    
    class Level_access: public Basic_user{
    private:
        string vista;
    public:
        Level_access(const string &vista = "", const string &id = ""): Basic_user(id), vista(vista){this->id = id;}
        
        const string & set_vista(const string &vista){this->vista = vista; return this->vista;}
        const string & get_vista() const {return vista;}
    };
}



#endif /* USER_hpp */
