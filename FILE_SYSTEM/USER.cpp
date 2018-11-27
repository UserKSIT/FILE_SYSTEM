//
//  USER.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "USER.hpp"
#include <string>
#include <iostream>
using namespace std;


/*
const string & User::set_name(const string & new_name){
    this->name = new_name;
    return this->name;
}
*/

std::istream & operator >> (std::istream &flow, User &object){
    string name;
    std::cout << "Name = ";
    std::cin >> name;
    object.name = name;
    object.info_key = "";
    std::cin.clear();
    
    return flow;
}
