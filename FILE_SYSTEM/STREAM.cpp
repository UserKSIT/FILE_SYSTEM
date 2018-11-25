//
//  STREAM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "STREAM.hpp"
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include "BASIC_DESCRIPTION.hpp"

const ios::pos_type & Desstream::push_stream(const ios::pos_type &adress, streamsize & size, const string &data){
    std::fstream file;
    file.open("FILE_SYSTEM.txt");
    if (!file){
        std::cout << "cannot open file" << std::endl;
        return adress;
    }
    file.seekg(adress, std::ios::beg);
    file.seekg(size, std::ios::cur);
    char * buf = new char[data.size()];
    for (int i = 0; i < data.size(); i++)// костыль
        buf[i] = data[i];
    file.write(buf, data.size());
    
    size += data.size();
    file.close();
    return adress;
}
