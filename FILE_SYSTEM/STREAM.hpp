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

using namespace std;
class Desstream{
private:
    string name;
    ios::pos_type virtual_adress;
    streamsize size;
public:
    Desstream(const string &name): name(name), virtual_adress(0){}
    
    const ios::pos_type & push_stream(const ios::pos_type &, streamsize &, const string &);
    const string & pop_stream(ios::pos_type &);
};

#endif /* STREAM_hpp */
