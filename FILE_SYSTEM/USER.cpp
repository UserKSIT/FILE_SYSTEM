//
//  USER.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "USER.hpp"
#include <string>

using namespace lcu;

string * User::set_name(string * new_name){
    this->name = new_name;
    return this->name;
}

