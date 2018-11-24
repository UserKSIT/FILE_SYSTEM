//
//  DESCRIPTION_SYSTEM.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef DESCRIPTION_SYSTEM_hpp
#define DESCRIPTION_SYSTEM_hpp

#include <stdio.h>
#include "USER.hpp"
#include "BASIC_DESCRIPTION.hpp"
#include <vector>
#include <string>

using namespace lcu;
using namespace bac;


class Desp_sys{
private:
    Descatalog *root;
    vector<User> table_users;
    string current_user;
public:
    Desp_sys();
    
    Desp_sys & get_root() const;
    Desp_sys & get_table_users() const;
    void get_stat() const;
    
    Desp_sys & set_root();
    Desp_sys & change_table_users(const string &);
    
    int start_work(const string &);
    int end_work();
    int append_user(const string &, const string &);
    
    friend class Desfile;
};

#endif /* DESCRIPTION_SYSTEM_hpp */
