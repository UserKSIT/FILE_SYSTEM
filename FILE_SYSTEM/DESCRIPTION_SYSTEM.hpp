//
//  DESCRIPTION_SYSTEM.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef DESCRIPTION_SYSTEM_hpp
#define DESCRIPTION_SYSTEM_hpp

#include "USER.hpp"
#include "BASIC_DESCRIPTION.hpp"
#include <map>
#include <string>

extern string current_user;
extern string current_location;
extern std::fstream sys;
extern int quantity_file;
extern int quantity_catalog;


using namespace std;
class Desp_sys{
private:
    Descatalog * root;
    map<const string, User> table_users;
    const string & get_name (map<const string, User>::const_iterator &i) const ;
    const string & get_info_key(map<const string, User>::const_iterator &i) const;
public:
    Desp_sys();
    //return pointer root
    Descatalog * get_root() const {return root;}
    //retrun pointer table of users
    //Desp_sys & get_table_users() const;
    //retrun statistic
    void get_stat() const;

    //friend bool upload_file(std::fstream &file, Desp_sys object);
    
    bool check_in_table(const string &);
    
    //All friends class's
 
    //set pointer root
    Desp_sys & set_root();
    
    friend std::ostream & operator << (std::ostream &flow, const Desp_sys &object);
    //start work with user
    Desp_sys & start_work(const string &);
    //end work
    Desp_sys & end_work();
    //append user in table of users
    bool insert_user(const string &, const User);
    //delete user
    bool remove(const string &);
    //change parametr user
    bool change(const string &, const User &);
    
};
bool push_file(const string &info, std::ios::pos_type &virtual_adress, int &size);

void return_info(const std::ios::pos_type &virtual_adress, const int &size, Desp_sys &object);


#endif /* DESCRIPTION_SYSTEM_hpp */
