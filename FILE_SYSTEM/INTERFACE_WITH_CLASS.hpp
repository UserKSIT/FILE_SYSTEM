//
//  INTERFACE_WITH_CLASS.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 28/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef INTERFACE_WITH_CLASS_hpp
#define INTERFACE_WITH_CLASS_hpp

#include <stdio.h>
#include <fstream>
#include <iostream>

class Interface{
private:
    static const int block = 508;
    std::fstream FILE;
public:
    Interface(){FILE.open("FILE_SYSTEM.txt");}
    ~Interface(){FILE.close();}
    
    const std::ios::pos_type get_end_file() {return FILE.tellg();}
    const int & get_block() const {return block;}
};

#endif /* INTERFACE_WITH_CLASS_hpp */
