//
//  INTERFACE.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 02/12/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef INTERFACE_hpp
#define INTERFACE_hpp

//#include <stdio.h>
//#include <iostream>
#include "DESCRIPTION_SYSTEM.hpp"

namespace itf{
    
    
    const std::string Names[] = { "Unknown", "Circle", "Rectangle" };
    const std::string Menu_Catalog[] = { "1. Add a object", "2. Find a object",
    "3. Delete a object", "4. Show all", "5. Open file", "6. Next catalog", "7. Back", "0. Quit" };
    const std::string Menu_File_1[] = { "1. Show info", "0. Close file"};
    const std::string Menu_File_2[] = {"1. Write info", "0. Close file"};
    const std::string Menu_FIle_3[] = {"1. Write info", "2. Read info", "0. Close file"};

    const std::string Choice = "Make your choice";
    const std::string Msg = "You are wrong; repeate please";
    
    int Answer(const std::string alt[], int n);
    
    int Add(Descatalog *);
    int Find(Descatalog*);
    int Remove(Descatalog *);
    int ShowAll(Descatalog *);
    int OpenF(Descatalog *);
    int NextC(Descatalog *);
    int BackC(Descatalog *);
    
    int(*Funcs[])(Descatalog *) = {Add, Find, Remove, ShowAll, OpenF, NextC, BackC, nullptr};
    const int NumCatalog = sizeof(Menu_Catalog)/sizeof(Menu_Catalog[0]);
    

    //int Answer(const std::string *, int);
}

#endif /* INTERFACE_hpp */
