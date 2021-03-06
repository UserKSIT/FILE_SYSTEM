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


//set table_user_access
fstream sys;

string current_user;
string current_location;

int tag = 0;

Desstream main_s("MAIN");
Desstream temp("TEMP");
Desstream sym("SYMKEY");



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
int SetPT(Descatalog *&);

int Write(Basic_description *);
int Read(Basic_description *);

int Work(Desp_sys &);
int Change_Table(Desp_sys &);
int Get_status(Desp_sys &);

char *Get_String(void);

const std::string Menu_Catalog[] = { "1. Add a object", "2. Find a object",
    "3. Delete a object", "4. Show all", "5. Open file", "6. Next catalog", "7. Back", "8. Change table access","9. Show table access", "10. Get status","11. Get data", "12. Copy", "13. Put in the buffer", "14. Pull out the buffer", "15. Encrypt file", "16. Decrypt file", "17. Change name", "18. Set table access for Protected File", "0. End work" };
const std::string Menu_File_1[] = { "1. Show info", "0. Close file"};
const std::string Menu_File_2[] = {"1. Write info", "0. Close file"};
const std::string Menu_File_3[] = {"1. Write info", "2. Read info", "0. Close file"};

const std::string Menu_start[] = {"1. Start work", "2. Change table users", "3. Show statistic", "0. Quit programm"};

int(*Funcs[])(Descatalog *&) = { nullptr, Add, Find, Remove, ShowAll, OpenF, NextC, BackC, ChangeT, ShowT, Status, GetInfo, Copy, Pull, Extract, Encrypt, Decrypt, ChangeName, SetPT};

int(*Funcs_file1[])(Basic_description *) = {nullptr, Read};
int(*Funcs_file2[])(Basic_description *) = {nullptr, Write};
int(*Funcs_file3[])(Basic_description *) = {nullptr, Write, Read};

int(*Func_work[])(Desp_sys &) = { nullptr, Work, Change_Table, Get_status};

const int NumWork = sizeof(Menu_start)/sizeof(Menu_start[0]);

const int NumCatalog = sizeof(Menu_Catalog)/sizeof(Menu_Catalog[0]);

const int NumFile1 = sizeof(Funcs_file1)/sizeof(Funcs_file1[0]);
const int NumFile2 = sizeof(Funcs_file2)/sizeof(Funcs_file2[0]);
const int NumFile3 = sizeof(Funcs_file3)/sizeof(Funcs_file3[0]);

int SetPT(Descatalog *&view){
    std::cin.clear();
    std::string name;
    std::cout << "Enter a name file: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    ID buf(name);
    bool flag;
    map<ID, Basic_description *>::const_iterator p = view->find(buf, flag);
    if (flag){
        ProtectedDesfile * ptr = dynamic_cast<ProtectedDesfile *>(p->second);
        if (ptr != nullptr){
            if (current_user == ptr->get_master()){
                int choice;
                std::string id;
                std::cout << "1. Add user" <<std::endl;
                std::cout << "2. Remove user" << std::endl;
                std::cout << "0. Quit" << std::endl;
                ptr->show_table();
                ltmp::GET_NUM(choice, 2);
                
                switch (choice) {
                    case 0:
                        break;
                    case 1:
                        std::cin.clear();
                        std::cout << "Enter a id: --> ";
                        std::cin >> id;
                        if (!std::cin.good())
                            throw std::invalid_argument("Error when a id was entered");
                        
                        ptr->insert_user(id, "");
                        break;
                    case 2:
                        std::cin.clear();
                        std::cout << "Enter a id: --> ";
                        std::cin >> id;
                        if (!std::cin.good())
                            throw std::invalid_argument("Error when a id was entered");
                        
                        ptr->remove_user(id);
                        break;
                    default:
                        break;
                }
            }
            else
                std::cout << "You haven't rules" << std::endl;
        }else
            std::cout << "Not found" << std::endl;
    }
    else
        std::cout << "Not found" << std::endl;
    
    return 0;
}

int Decrypt(Descatalog *&view){
    std::cin.clear();
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    ID key(name);
    
    view->decrypt_file(key);
    
    return 0;
}


int Encrypt(Descatalog *&view){
    std::cin.clear();
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
    std::cin.clear();
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    ID buf(name);
    bool flag = false;
    
    map <ID, Basic_description *>::const_iterator p = view->find(buf, flag);
    if (flag){
        Desfile * ptr = dynamic_cast<Desfile *>(p->second);
        std::cout << *ptr << std::endl;
    }
    else
        std::cout << "Not found" << std::endl;
    
    return 0;
}

int Copy(Descatalog *&view){
    std::cin.clear();
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
    std::cin.clear();
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
    std::cin.clear();
    std::string name;
    std::cout << "Enter a name object: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    
    std::cin.clear();
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
    std::cin.clear();
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
    std::cout << view->show_access() << std::endl;
    return 0;
}

int ChangeT(Descatalog *&object){//add menu
    if("rw" == object->get_master()){
        int choice;
        std::string id, mode;
        std::cout << "1. Add (if such already exists will be replaced) user" <<std::endl;
        std::cout << "2. Remove user" << std::endl;
        ltmp::GET_NUM_CHOICE(choice, 2);
        switch (choice) {
            case 1:{
                std::cin.clear();
                std::cout << "Enter a id: --> ";
                std::cin >> id;
                if (!std::cin.good())
                    throw std::invalid_argument("Error when a id was entered");
               
                
                bool loop = true;
                while (loop){
                    std::cout << "Enter a mode: --> ";
                    std::cin >> mode;
                    if (!std::cin.good())
                        throw std::invalid_argument("Error when a id was entered");
                    if (mode == "rw" || mode == "r" || mode == "w")
                        loop = false;
                    else
                        std::cout << "Exist only \"r\" \"w\" \"rw\"" << std::endl;
                }
                object->change_access(id, mode);}
                break;
            case 2:
                std::cin.clear();
                std::cout << "Enter a id: --> ";
                std::cin >> id;
                if (!std::cin.good())
                    throw std::invalid_argument("Error when a id was entered");
                
                object->remove_access(id);
                break;
            default:
                break;
        }
    }
    else
        std::cout << "You haven't master rule" << std::endl;
    return 0;
}


int Get_status(Desp_sys &object){
    std::cout << "Quantity file: " << quantity_file << std::endl;
    std::cout << "Quantity catalog: " << quantity_catalog << std::endl;
    return 0;
}

int Change_Table(Desp_sys &object){
    std::cin.clear();
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
                std::cin.clear();
                std::cout << "Id = ";
                std::cin >> id;
        
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
    std::cin.clear();
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
    return 0;
}

int Write(Basic_description *object){
    std::cin.clear();
    string info;
    std::cout << "Input info" << std::endl;
    getline(cin, info);
    if (!std::cin.good())
        throw std::invalid_argument("Error when a shape name was entered");
    
    
    object->write_file(info);
    
    return 0;
}

int Read(Basic_description *object){
    std::cout << *object << std::endl;
    
    std::cout.clear();
    
    return 0;
}

int Add(Descatalog *&view)
{
    std::cin.clear();
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
    std::cin.clear();
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
    std::cin.clear();
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
    std::cin.clear();
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
    std::cin.clear();
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    
    
    int res;
    ID buf(name);
    buf.name = name;
    
    Basic_description * ptr = view->open_file(buf, res);
    
    int ind;
    std::cin.clear();
    if (res > 0){
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
    
    main_s.init_stream("MAIN");
    temp.init_stream("TEMP");
    sym.init_stream("SYMKEY");
    
    
    
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
    
    Desp_sys SYSTEM;
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
    string info = "Hello world!";

    for (int i = 0; i < 50; i++)
        object.write_file(info);

    std::cout << "Look -> ";
    std::cout << object << std::endl;
}

TEST(StreamFunction, ReturnInfo){
    Desfile object;
    object.open_stream();
    string info = "Hello world!";
    
    for (int i = 0; i < 50; i++)
        object.write_file(info);
    
    std::cout << "Look -> ";
    std::cout << object << std::endl;
}

TEST(StreamFunction, DeleteInfo){
    Desfile object;
    object.open_stream();
    string info = "Hello world!";
    
    for (int i = 0; i < 50; i++)
        object.write_file(info);
    
    std::cout << "Look before delete-> ";
    std::cout << object << std::endl;
    
    object.delete_info();
    
    std::cout << "Look after delete-> ";
    std::cout << object << std::endl;
}

TEST(CatalogFunction, ReplaceObject){
    current_user = "ADMIN";
    Desp_sys test;
    Descatalog * ptr = test.get_root();
    
    ID buf1("file1");
    ID buf2("dir1");
    
    Desfile cont1("file1");
    Descatalog cont2("dir1");
    
    Basic_description * p1 = &cont1;
    Basic_description * p2 = &cont2;
    
    ptr->insert(buf1, p1);
    ptr->insert(buf2,p2);
    
    std::cout << "Look what in catalog before" << std::endl;
    std::cout << *ptr << std::endl;
    ptr->pull_in_buffer(buf1, BUFFER_key, BUFFER_ptr);
    ptr->remove(buf1);
    std::cout << "Look what in catalog after" << std::endl;
    std::cout << *ptr << std::endl;
    
    Descatalog * next = ptr->next(buf2);
    ptr = next;
    
    //Call except, but it's normal
    /*std::cout << "Look what in catalog before" << std::endl;
    std::cout << *ptr << std::endl;
    next->extract_out_buffer(BUFFER_key, BUFFER_ptr);
    std::cout << "Look what in catalog after" << std::endl;
    std::cout << *ptr << std::endl;
    current_user = "";*/
}

TEST(CatalogFunction, EncryptFile){
    Desp_sys test;
    Descatalog * ptr = test.get_root();
    
    ID buf("file1");
    
    Desfile cont("file1");
    Basic_description * p = &cont;
    
    ptr->insert(buf, p);
    
    bool flag;
    map<ID, Basic_description *>::const_iterator i = ptr->find(buf, flag);
    Desfile * z = dynamic_cast<Desfile *>(i->second);
    z->write_file("Hello world!");
    
    std::cout << *z << std::endl;
    ptr->crypt_file(buf);
    
    map<ID, Basic_description *>::const_iterator j = ptr->find(buf, flag);
    ProtectedDesfile * x = dynamic_cast<ProtectedDesfile *>(j->second);
    std::cout << *x << std::endl;
    
    ptr->decrypt_file(buf);
    
    map<ID, Basic_description *>::const_iterator k = ptr->find(buf, flag);
    Desfile * v = dynamic_cast<Desfile *>(k->second);
    std::cout << *v << std::endl;
}

TEST(AccessTable, InsertUser){
    Desfile file;
    Descatalog catalog;
    
    std::string id = "guest";
    std::string mode = "rw";
    std::string mode2 = "r";
    
    file.insert_access(id, mode);
    catalog.insert_access(id, mode);
    
    std::cout << "Look what in file" << std::endl;
    file.show_access();
    std::cout << "Look what in catalog" << std::endl;
    catalog.show_access();
    
    std::cout << "Try replace" << std::endl;
    file.insert_access(id, mode2);
    catalog.insert_access(id, mode2);
    
    std::cout << "Look what in file" << std::endl;
    file.show_access();
    std::cout << "Look what in catalog" << std::endl;
    catalog.show_access();
}

TEST(AccessTable, RemoveUser){
    Desfile file;
    Descatalog catalog;
    
    std::string id = "guest";
    std::string mode = "rw";
    
    file.insert_access(id, mode);
    catalog.insert_access(id, mode);
    
    std::cout << "Before delete" << std::endl;
    std::cout << "Look what in file" << std::endl;
    file.show_access();
    std::cout << "Look what in catalog" << std::endl;
    catalog.show_access();
    
    std::cout << "Try change ADMIN" << std::endl;
    ASSERT_FALSE(file.change_access("ADMIN", "w"));
    ASSERT_FALSE(catalog.change_access("ADMIN", "w"));
    std::cout << "Try delete ADMIN" << std::endl;
    ASSERT_FALSE(file.remove_access("ADMIN"));
    ASSERT_FALSE(catalog.remove_access("ADMIN"));
    
    ASSERT_TRUE(file.remove_access(id));
    ASSERT_TRUE(catalog.remove_access(id));
    
    std::cout << "After delete" << std::endl;
    std::cout << "Look what in file" << std::endl;
    file.show_access();
    std::cout << "Look what in catalog" << std::endl;
    catalog.show_access();
    
    std::cout << "Try again" << std::endl;
    ASSERT_FALSE(file.remove_access(id));
    ASSERT_FALSE(catalog.remove_access(id));
}

TEST(OpenFile, ProtectedOpen){
    Desp_sys s;
    Descatalog catalog = *s.get_root();
    Desfile file("file");
    
    Basic_description * ptr = &file;
    
    ID buf("file");
    catalog.insert(buf, ptr);
    
    std::string push = "Hello world!";
    file.write_file(push);
    
    catalog.crypt_file(buf);
    
    bool flag;
    map<ID, Basic_description *>::const_iterator p = catalog.find(buf, flag);
    ProtectedDesfile * pfile = dynamic_cast<ProtectedDesfile *>(p->second);
    
    std::cout << "Before -> " << *pfile << std::endl;
    
    pfile->open();
    
    std::cout << "After -> " << *pfile << std::endl;
    
    pfile->close_file();
}

