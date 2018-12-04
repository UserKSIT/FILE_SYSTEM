//
//  STREAM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "STREAM.hpp"
//стоит ли менять на string?
using namespace std;
//редактирование
bool Desstream::push_stream(const string &info, const std::ios::pos_type &shift, int &size){// to do
    bool res = true;
    if (info.size() == 0)
        return res;
    
    
    int edge = virtual_adress + shift;
    edge += size;
    sys.seekg(edge);
    int residue_block = size % block;
    std::ios::pos_type prev = 0;
    string cur;
    int quant = 0;

    
    int dif = 0;
    if (size == 0){
        quant = info.size() / block;
        if (quant > 0)
            for (int i = 0; i <= quant; i++){
                sys.write(info.substr(508*i, 508*(i + 1)).c_str(), 508);
                
                prev = sys.tellp();
                sys.seekp(std::ios::end);
                cur = sys.tellp();
                sys.seekp(prev);
                sys.write(cur.c_str(), 4);
                sys.seekp(std::ios::end);
            }
        else
            sys.write(info.substr(0, 508).c_str(), 508);
    }
    else{
        if (residue_block != 0){
            sys.write(info.substr(0, block - residue_block).c_str(), block - residue_block);
            dif = 1;
            
            int check = (info.size() - dif*(block - residue_block));
            if ( check > 0){
                quant = check / block;
                for (int i = 0; i <= quant; i++){
                    prev = sys.tellp();
                    sys.seekp(std::ios::end);
                    cur = sys.tellp();
                    sys.seekp(prev);
                    sys.write(cur.c_str(), 4);
                    sys.seekp(std::ios::end);
                    
                    sys.write(info.substr((info.size() - dif*(block - residue_block)) - i * 508, (info.size() - dif*(block - residue_block)) - 508 * (i + 1)).c_str(), 508);
                }
            }
        }
    }


    size += info.size() + 1;
    return res;
}
//удаление информации
bool Desstream::delete_info(const std::ios::pos_type &shift, int &size){
    sys.seekg(virtual_adress + shift);
    int quant = size / block;
    char * next = new char[4];
    int tmp;
    
    for (int i = 0; i < quant; i++){
        sys.write(0, block);
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }
    delete [] next;
    return true;
}
//вывод информации
std::ostream & Desstream::return_info(std::ostream &flow, const std::ios::pos_type &shift, const int &size) const {
    sys.seekg(virtual_adress + shift);
    int quant = size / block;
    int residue = size % block;
    
    char * buf = new char[block];
    char * next = new char[4];
    int tmp;
    
    for(int i = 0; i < quant; i++){
        sys.read(buf, block);
        
        for (int i = 0; i < block; i++)
            flow << buf[i];
        flow << std::endl;
        
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }

    sys.read(buf, residue);
    for (int i = 0; i < residue; i++)
        flow << buf[i];
    flow << std::endl;
    
    delete [] buf;
    delete [] next;
    return flow;
}

char * Desstream::return_info(const std::ios::pos_type &shift, const int &size) const {
    sys.seekg(virtual_adress + shift);
    int quant = size / block;
    int residue = size % block;
    
    char * buf = new char[size];
    char * next = new char[4];
    int tmp;
    
    for(int i = 0; i < quant; i++){
        for(int __i = i * block; __i < (i + 1) * block; __i++)
            sys >> buf[__i];
 
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }
    
    sys.read(buf, residue);
    for (int i = (quant - 1) * block; i < ((quant - 1) * block + residue); i++)
        sys >> buf[i];
    
    delete [] next;
    return buf;
}
//резервация места при добавлении файла
std::ios::pos_type & Desstream::open_stream_for_file(std::ios::pos_type &shift){
    sys.seekg(std::ios::end);
    shift = sys.tellg() - virtual_adress;
    sys.write("0", 512);
    return shift;
}

//конструктор
Desstream::Desstream(const string &name):name(name){// добавить резервирование?
    sys.seekg(std::ios::end);
    virtual_adress = sys.tellg();
}

int Input( char *s, size_t n )
{
    size_t i = 0;
    char c;
    
    while (i < n && (c = std::getchar()) != EOF &&  c != '\n')
    {
        s[i++] = c;
    }
    
    if ( n != 0 ) s[i == n ? n-1 : i] = '\0';
    
    return std::atoi(s);
}

void Desstream::init_stream(const string &name)
{
    this->name = name;
    sys.seekg(std::ios::end);
    virtual_adress = sys.tellg();
}

