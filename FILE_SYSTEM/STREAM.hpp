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
#include <iomanip>

extern std::fstream sys;

using namespace std;

class Desstream{
private:
    string name;
    std::ios::pos_type virtual_adress;
    static const int block = 508;
public:
    Desstream(const string &);
    
    bool push_stream(const string &, const std::ios::pos_type &, int &);
    bool delete_info(const std::ios::pos_type &, int &);
    std::ostream & return_info(std::ostream &, const std::ios::pos_type &, const int &) const;
    
    std::ios::pos_type & open_stream_for_file(std::ios::pos_type &);
    
};

int Input( char *, size_t);

#endif /* STREAM_hpp */
