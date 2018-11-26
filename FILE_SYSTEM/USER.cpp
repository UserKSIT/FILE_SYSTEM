//
//  USER.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "USER.hpp"
#include <string>



const string & User::set_name(const string & new_name){
    this->name = new_name;
    return this->name;
}

