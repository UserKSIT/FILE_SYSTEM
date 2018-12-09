//
//  main.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 12/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include "DESCRIPTION_SYSTEM.hpp"
#include "gtest/gtest.h"


fstream sys;

string current_user;
string current_location;

int tag = 0;

Desstream main_s;
Desstream temp;
Desstream sym;

Basic_description * BUFFER_ptr;
ID BUFFER_key;

int quantity_file;
int quantity_catalog;

int Answer(const std::string alt[], int n);

int Add(Descatalog *&);
int Find(Descatalog *&);
int Remove(Descatalog *&);
int ShowAll(Descatalog *&);
int OpenF(Descatalog *&);
int NextC(Descatalog *&);
int BackC(Descatalog *&);
int ChangeT(Descatalog *&);
int ShowT(Descatalog *&);
int Status(Descatalog *&);
int ChangeName(Descatalog *&);
int Copy(Descatalog *&);
int GetInfo(Descatalog *&);
int Pull(Descatalog *&);
int Extract(Descatalog *&);
int Encrypt(Descatalog *&);
int Decrypt(Descatalog *&);

int Write(Desfile *);
int Read(Desfile *);

int Work(Desp_sys &);
int Change_Table(Desp_sys &);
int Get_status(Desp_sys &);

char *Get_String(void);

const std::string Menu_Catalog[] = { "1. Add a object", "2. Find a object",
    "3. Delete a object", "4. Show all", "5. Open file", "6. Next catalog", "7. Back", "8. Change table access","9. Show table access", "10. Get status","11. Get data", "12. Copy", "13. Put in the buffer", "14. Pull out the buffer", "15. Encrypt file", "16. Decrypt file", "17. Change name", "0. End work" };
const std::string Menu_File_1[] = { "1. Show info", "0. Close file"};
const std::string Menu_File_2[] = {"1. Write info", "0. Close file"};
const std::string Menu_File_3[] = {"1. Write info", "2. Read info", "0. Close file"};

const std::string Menu_start[] = {"1. Start work", "2. Change table users", "3. Show statistic", "0. Quit programm"};

int(*Funcs[])(Descatalog *&) = { nullptr, Add, Find, Remove, ShowAll, OpenF, NextC, BackC, ChangeT, ShowT, Status, GetInfo, Copy, Pull, Extract, Encrypt, Decrypt, ChangeName};

int(*Funcs_file1[])(Desfile *) = {nullptr, Read};
int(*Funcs_file2[])(Desfile *) = {nullptr, Write};
int(*Funcs_file3[])(Desfile *) = {nullptr, Write, Read};

int(*Func_work[])(Desp_sys &) = { nullptr, Work, Change_Table, Get_status};

const int NumWork = sizeof(Menu_start)/sizeof(Menu_start[0]);

const int NumCatalog = sizeof(Menu_Catalog)/sizeof(Menu_Catalog[0]);

const int NumFile1 = sizeof(Funcs_file1)/sizeof(Funcs_file1[0]);
const int NumFile2 = sizeof(Funcs_file2)/sizeof(Funcs_file2[0]);
const int NumFile3 = sizeof(Funcs_file3)/sizeof(Funcs_file3[0]);

int Decrypt(Descatalog *&view){
    return 0;
}


int Encrypt(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    ID key(name);
    view->crypt_file(key);
    
    return 0;
}


int GetInfo(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    // to do
    
    return 0;
}

int Copy(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    ID key(name);
    view->pull_in_buffer(key, BUFFER_key, BUFFER_ptr);
    return 0;
}

int Extract(Descatalog *&view){
    if(view->extract_out_buffer(BUFFER_key, BUFFER_ptr))
        std::cout << "Ok" << std::endl;
    else
        std::cout << "Buffer is empty" << std::endl;
    
    return 0;
}

int Pull(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    ID key(name);
    view->pull_in_buffer(key, BUFFER_key, BUFFER_ptr);
    view->remove(key);
    return 0;
}

int ChangeName(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    std::string new_name;
    std::cout << "Enter a new name object: --> ";
    std::cin >> new_name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a new name was entered");
    
    ID key(name);
    
    view->change_name(new_name, key);
    return 0;
}


int Status(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a id was entered");
    ID buf(name);
    
    bool flag = false;
    map<ID, Basic_description *>::const_iterator p = view->find(buf, flag);
    if (flag){
        std::cout << p->second->get_status() << std::endl;
    }
    else{
        std::cout << "Object not found" << std::endl;
    }
    return 0;
}
int ShowT(Descatalog *&view){
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    
    ID buf(name);
    
    std::cout << view->show_access(buf) << std::endl;
    return 0;
}

int ChangeT(Descatalog *&object){
    /*string id, mode, name;
    std::cout << "Enter a name file: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a id was entered");
    if (check_master(name, *object)){
    
    std::cout << "Enter a id: --> ";
    std::cin >> id;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a id was entered");
    std::cout << "Enter a mode: --> ";
    std::cin >> mode;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a id was entered");
    
    object->change_access(id, mode);
    }
    else{
        std::cout << "You haven't master rule" << std::endl;
    }
    */
    return 0;
}


int Get_status(Desp_sys &object){
    std::cout << "Quantity file: " << quantity_file << std::endl;
    std::cout << "Quantity catalog: " << quantity_catalog << std::endl;
    return 0;
}

int Change_Table(Desp_sys &object){
    std::string user;
    std::cout << "Enter a id: --> ";
    std::cin >> user;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a id was entered");
    
    if (user == "ADMIN"){
        int choice;
        std::cout << "1. Append user" << std::endl;
        std::cout << "2. Delete user" << std::endl;
        std::cout << "3. Show table" << std::endl;
        ltmp::GET_NUM(choice, 3);
        switch (choice) {
            case 0:
                break;
            case 1:{
                string id, name;
                std::cout << "Id = ";
                std::cin >> id;
                std::cin.clear();
                std::cout << "Name = ";
                std::cin >> name;
                User tmp(name);
                std::cin.clear();
                object.insert_user(id, tmp);
                break;
            }
            case 2:{
                string id;
                std::cout << "Id = ";
                std::cin >> id;
                std::cin.clear();
                object.remove(id);
                break;
            }
            case 3:
                std::cout << object << std::endl;
                break;
        }
        return 0;
    }
    else{
        std::cout << "You are not authorized to do this" << std::endl;
        return 0;
    }
}

int Work(Desp_sys &object){
    std::string user;
    std::cout << "Enter a id: --> ";
    std::cin >> user;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a id was entered");
    
    
    if (object.check_in_table(user)){
        object.start_work(user);
        
        std::cin.clear();
        
        
        Descatalog * ptr = object.get_root();
        int ind;
        try{
            while ((ind = Answer(Menu_Catalog, NumCatalog)))
                Funcs[ind](ptr);
        }
        catch (const std::exception &er)
        {
            std::cout << er.what() << std::endl;
        }
    }
    else
        std::cout << "This user is not foun in the table" << std::endl;
    
    object.end_work();
    
    std::cin.clear();
    return 0;
}

int Write(Desfile *object){
    string info;
    std::cout << "Input info" << std::endl;
    getline(cin, info);
    if (!std::cin.good())
        throw std::invalid_argument("Error when a shape name was entered");
    
    
    object->write_file(info);
    
    std::cin.clear();
    
    return 0;
}

int Read(Desfile *object){
    std::cout << *object << std::endl;
    
    std::cout.clear();
    
    return 0;
}

int Add(Descatalog *&view)
{
    string id;
    std::cout << "Enter name object" << std::endl;
    std::cin >> id;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    
    view->add_object(id);
    
    return 0;
}
int Find(Descatalog *&view)
{
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a shape name was entered");
    
    bool flag = false;
    ID buf(name);
    view->find(buf, flag);
    if (flag)
        std::cout << "Found!" << std::endl;
    else
        std::cout << "Not found" << std::endl;
    
    return 0;
}
int Remove(Descatalog *&view)
{
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    
    
    ID buf(name);
    if (view->remove(buf))
        std::cout << "Ok" << std::endl;
    else
        std::cout << "The object with Name \"" << name << "\" is absent in container"
        << std::endl;
    
    return 0;
}
int ShowAll(Descatalog *&view){
    std::cout << *view << std::endl;
    return 0;
}

int NextC(Descatalog *&view){
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    ID buf;
    buf.name = name;
    Descatalog * next = view->next(buf);
    
    if (next != nullptr){
        std::cout << "Ok" << std::endl;
        view = next;
    }
    else
        std::cout << "The object with Name \"" << name << "\" is absent in container" << std::endl;
    
    return 0;
}

int OpenF(Descatalog *&view){
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    int res;
    ID buf(name);
    buf.name = name;
    Basic_description * Bptr = view->open_file(buf, res);
    int ind;
    if (res > 0){
        Desfile * ptr = dynamic_cast<Desfile *>(Bptr);
        if (res == 1){
            try {
                while (ind = Answer(Menu_File_1, NumFile1))
                    Funcs_file1[ind](ptr);
            } catch (const std::exception &er) {
                std::cout << er.what() << std::endl;
            }
        }
        if (res == 2){
            try {
                while (ind = Answer(Menu_File_2, NumFile2))
                    Funcs_file2[ind](ptr);
            } catch (const std::exception &er) {
                std::cout << er.what() << std::endl;
            }
        }
        if (res == 3){
            try {
                while (ind = Answer(Menu_File_3, NumFile3))
                    Funcs_file3[ind](ptr);
            } catch (const std::exception &er) {
                std::cout << er.what() << std::endl;
            }
        }
        ptr->close_file();
    }
    else
        std::cout << "You havrn't right for this file" << std::endl;
    
    return 0;
}
// to do
int BackC(Descatalog *& view){
    Descatalog * parent = view->back();
    if(parent != nullptr){
        view = parent;
        std::cout << "Ok" << std::endl;
    }
    else
        std::cout << "This is a root" << std::endl;
    return 0;
}

int main(int argc, char * argv[]) {
    sys.open("/Programms C++/FILE_SYSTEM/FILE_SYSTEM/FILE_SYSTEM.txt",  std::ios::out | std::ios::in);
    if (sys.is_open())
        std::cout << "File is open\n";
    else{
        std::cout << "Fatal error\n";
        return 0;
    }
    sys.seekp(std::ios::beg);
    std::cout << sys.tellp() << std::endl;

/*    string ret, n, g;
    //getline(sys, ret);
    sys.seekp(std::ios::end);
    sys << "zbs nigga\npizdec nahui blyat\n";
    sys.seekg(std::ios::beg);
    sys >> ret;
    std::cout << ret << std::endl;
    sys >> n;
    std::cout << n << std::endl;
    ret = ret + " " + n;
    std::cout << ret << std::endl;
    sys.seekg(12);
    getline(sys, g, '\n');
    std::cout << g << std::endl;
    sys.close();
    return 0;*/
    
    main_s.init_stream("MAIN");
    temp.init_stream("TEMP");
    sym.init_stream("SYMKEY");
    
    //::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    Desp_sys SYSTEM("Yes");
 
    int ind;
    try{
        while ((ind = Answer(Menu_start, NumWork)))
            Func_work[ind](SYSTEM);
    }
    catch (const std::exception &er)
    {
        std::cout << er.what() << std::endl;
    }

    std::cout << "That's all. Buy!" << std::endl;
       sys.close();
    return 0;

}

TEST(StreamFunction, PushInfo){
    Desfile object;
    object.open_stream();
    string info;
    std::cout << "Input info" << std::endl;

    getline(cin, info);

    for (int i = 0; i < 102; i++){
        object.write_file(info);
    }
    
    std::cout << "Look -> ";
    std::cout << object << std::endl;
    sys.close();
}



