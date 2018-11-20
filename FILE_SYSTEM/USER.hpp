//
//  USER.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef USER_hpp
#define USER_hpp

#include <stdio.h>
#include <string>

using namespace std;

namespace lcu {
    class Basic_user{
    protected:
        string * id;
    public:
        Basic_user();
    
        string * get_id();
    
        string * set_id();
    };
    
    class User: public Basic_user{
    private:
        string * name;
        string * info_key;
    public:
        User():info_key(nullptr){}
        
        string * get_name();
        string * get_info_key();
        
        string * set_name(string *);
        string * set_info_key();
    };
    
    class Level_access: public Basic_user{
    private:
        string * vista;
    public:
        Level_access();
        
    };
}



#endif /* USER_hpp */
