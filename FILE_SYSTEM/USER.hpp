//
//  USER.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef USER_hpp
#define USER_hpp

#include <string>
#include <iostream>

using namespace std;

class User{
private:
    string name;
    string info_key;
public:
    User(const string &name = ""): name(name), info_key(""){}
    
    const string & get_name() const {return name;}
    const string & get_info_key() const {return info_key;}
    
    bool set_name(const string &_name) {name = _name; return true; }
    bool set_info_key(const string &_key) {info_key = _key; return true;}
    
    friend std::istream & operator >> (std::istream &flow, User &object);
};


#endif /* USER_hpp */
