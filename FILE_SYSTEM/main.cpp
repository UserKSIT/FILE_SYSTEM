//
//  main.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 12/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "gtest/gtest.h"
//#include <string>
#include "DESCRIPTION_SYSTEM.hpp"
#include "Library_Template.hpp"
//#include "INTERFACE.hpp"
fstream sys;

string current_user;
string current_location;

int tag = 0;

Desstream main_s("MAIN");
Desstream temp("TEMP");
Desstream sym("SYMKEY");

int quantity_file;
int quantity_catalog;


const std::string Names[] = { "Unknown", "Circle", "Rectangle" };
const std::string Menu_Catalog[] = { "1. Add a object", "2. Find a object",
    "3. Delete a object", "4. Show all", "5. Open file", "6. Next catalog", "7. Back", "0. End work" };
const std::string Menu_File_1[] = { "1. Show info", "0. Close file"};
const std::string Menu_File_2[] = {"1. Write info", "0. Close file"};
const std::string Menu_File_3[] = {"1. Write info", "2. Read info", "0. Close file"};

const std::string Menu_start[] = {"1. Start work", "2. Change table users","0. Quit programm"};

//const std::string Choice = "Make your choice";
//const std::string Msg = "You are wrong; repeate please";

int Answer(const std::string alt[], int n);

int Add(Descatalog *);
int Find(Descatalog*);
int Remove(Descatalog *);
int ShowAll(Descatalog *);
int OpenF(Descatalog *);
int NextC(Descatalog *);
int BackC(Descatalog *);

int Write(Desfile *);
int Read(Desfile *);

int Work(Desp_sys &);
int Change_Table(Desp_sys &);

char *Get_String(void);

int(*Funcs[])(Descatalog *) = { nullptr, Add, Find, Remove, ShowAll, OpenF, NextC, BackC};

int(*Funcs_file1[])(Desfile *) = {nullptr, Read};
int(*Funcs_file2[])(Desfile *) = {nullptr, Write};
int(*Funcs_file3[])(Desfile *) = {nullptr, Write, Read};

int(*Func_work[])(Desp_sys &) = { nullptr, Work, Change_Table};

const int NumWork = sizeof(Menu_start)/sizeof(Menu_start[0]);

const int NumCatalog = sizeof(Menu_Catalog)/sizeof(Menu_Catalog[0]);

const int NumFile1 = sizeof(Funcs_file1)/sizeof(Funcs_file1[0]);
const int NumFile2 = sizeof(Funcs_file2)/sizeof(Funcs_file2[0]);
const int NumFile3 = sizeof(Funcs_file3)/sizeof(Funcs_file3[0]);

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
        switch (ltmp::GET_NUM(choice, 2)) {
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
            default:
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
    std::cout << *object;
    
    std::cout.clear();
    
    return 0;
}

int Add(Descatalog *view)
{
    string id;
    std::cout << "Enter name object" << std::endl;
    std::cin >> id;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a name was entered");
    view->add_object(id);
    
    return 0;
}
int Find(Descatalog *view)
{
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a shape name was entered");
    view->find(name);
    
    return 0;
}
int Remove(Descatalog*view)
{
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    if (view->remove(name))
        std::cout << "Ok" << std::endl;
    else
        std::cout << "The object with Name \"" << name << "\" is absent in container"
        << std::endl;
    return 0;
}
int ShowAll(Descatalog *view){
    std::cout << *view;
    return 0;
}

int NextC(Descatalog *view){
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    view = view->next(name);
    if (view != nullptr)
        std::cout << "Ok" << std::endl;
    else
        std::cout << "The object with Name \"" << name << "\" is absent in container"
        << std::endl;
    
    return 0;
}

int OpenF(Descatalog *view){
    std::string name;
    std::cout << "Enter a object name: --> ";
    std::cin >> name;
    if (!std::cin.good())
        throw std::invalid_argument("Error when a object name was entered");
    int res;
    Basic_description * Bptr = view->open_file(name, res);
    int ind;
    if (res > 0){
        Desfile * ptr = dynamic_cast<Desfile *>(Bptr);
        if (res == 1){
            while (ind = Answer(Menu_File_1, NumFile1))
                Funcs_file1[ind](ptr);
            return 0;
        }
        if (res == 2){
            while (ind = Answer(Menu_File_2, NumFile2))
                Funcs_file2[ind](ptr);
            return 0;
        }
        if (res == 3){
            while (ind = Answer(Menu_File_3, NumFile3))
                Funcs_file3[ind](ptr);
            return 0;
        }
    }
    return 0;
}

int BackC(Descatalog *view){
    view = view->back();
    if(view != nullptr)
        std::cout << "Ok" << std::endl;
    else
        std::cout << "This is a root" << std::endl;
    return 0;
}

char *Get_String(void)
{
    char *ptr = (char *)malloc(sizeof(char) * 1);
    if (ptr == NULL)
        return ptr;
    
    char buf[81];
    int n, len = 0;
    *ptr = '\0';
    do{
        n = scanf("%80[^\n]", buf);
    
        if(n < 0)
        {
            free(ptr);
            ptr = NULL;
            continue;
        }
        
        if(n == 0)
            scanf("%*c");
        else
        {
            len += strlen(buf);
            ptr = (char *)realloc(ptr, len + 1);
            
            if (ptr == NULL)
                return ptr;
            
            strcat(ptr, buf);
        }
    } while(n > 0);
    
    return ptr;
}

int main(int argc, char * argv[]) {
    sys.open("/Programms C++/FILE_SYSTEM/FILE_SYSTEM/FILE_SYSTEM.bin", std::ios::in | std::ios::out | std::ios::binary);
    if (sys.is_open())
        std::cout << "File is open\n";
    else
        std::cout << "Fuck you nigga\n";
    /*
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();*/
    
    
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
    Desfile object("Nigga");
    istringstream flow;
    string info;
    std::cout << "Input info" << std::endl;
    //flow >> info;
    getline(cin, info);
    //std::cin >> info;
    for (int i = 0; i < 1024; i++)
        object.write_file(info);
    
    std::cout << "Look -> ";
    std::cout << object << std::endl;
}

//to do
//нормальный ввод строки с пробелами
//нормальный дотсуп если rw
//начало работы
//переделать считывание в поток
