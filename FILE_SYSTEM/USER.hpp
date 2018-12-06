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
    
    const string & set_name(const string &_name) {name = _name; return name; }
    const string & set_info_key(const string &_key) {info_key = _key; return info_key;}
    
    friend std::istream & operator >> (std::istream &flow, User &object);
};


#endif /* USER_hpp */
