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
#include <map>

using namespace std;

class Desstream{
private:
    string name;
    int virtual_adress;
    int size;
public:
    Desstream(const string &name): name(name), virtual_adress(0){}
    
    const int & push_stream(const int &, int &, const string &);
    const string & pop_stream(int &);
};

#endif /* STREAM_hpp */
