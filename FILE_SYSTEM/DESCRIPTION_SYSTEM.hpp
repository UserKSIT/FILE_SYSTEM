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
    friend class Descatalog;
private:
    Descatalog *root;
    User *table_users;
public:
    Desp_sys();
    
    Desp_sys & get_PTR_CATALOG() const;
    Desp_sys & get_PTR_TABLE_USERS() const;
    
    Desp_sys & set_PTR_CATALOG();
    Desp_sys & set_PTR_TABLE_USERS();
};

#endif /* DESCRIPTION_SYSTEM_hpp */
