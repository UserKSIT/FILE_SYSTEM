//
//  USER.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "USER.hpp"

using namespace std;

std::istream & operator >> (std::istream &flow, User &object){
    flow >> object.name;
    flow >> object.info_key;
    
    return flow;
}
