//
//  STREAM.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef STREAM_hpp
#define STREAM_hpp

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Library_Template.hpp"
#include <sstream>
#include <iterator>
#include <vector>
#include <cassert>

extern std::fstream sys;

using namespace std;

class Desstream{
private:
    string name;
    std::ios::pos_type virtual_adress;
    static const int block = 508;
public:
    Desstream():name(""), virtual_adress(0){}
    Desstream(const string &);
    
    void init_stream(const string &);
    
    bool push_stream(const string &, const std::ios::pos_type &, int &);
    bool delete_info(const std::ios::pos_type &, int &);
    std::string return_info(const std::ios::pos_type &, const int &) const;
    
    std::ios::pos_type & open_stream_for_file(std::ios::pos_type &);
    
};

int Input( char *, size_t);

#endif /* STREAM_hpp */
