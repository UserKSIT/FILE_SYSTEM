//
//  main.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 12/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "DESCRIPTION_SYSTEM.hpp"
fstream sys;
string current_user;
string current_location;

Desstream main_s("MAIN");
Desstream temp("TEMP");
Desstream sym("SYMKEY");

int quantity_file;
int quantity_catalog;

int main() {
       sys.open("FILE_SYSTEM", std::ios::in | std::ios::out | std::ios::binary);
    Descatalog * view;
    Desp_sys SYSTEM;
    
    Desstream main("MAIN");
    Desstream temp("TEMP");
    Desstream sym("SYMKEY");
    
    view = SYSTEM.get_root();
    std::cout << *view;
    
    
    
    std::cout << "Hello, World!\n";
    sys.close();
    return 0;
}

