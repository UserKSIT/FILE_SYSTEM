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
    int residue = info.size() % block;
    int quant;
    char * next = new char[4];
    int tmp;
    std::ios::pos_type prev;
    string cur;
    
    if (residue < block){
        //sys.seekg(residue);
        sys.write(info.substr(0, block - residue).c_str(), block - residue);
    }
        quant = (info.size() - (block - residue)) / block;
        for (int i = 0; i <= quant; i++){
            prev = sys.tellp();
            sys.seekp(std::ios::end);
            cur = sys.tellp();
            sys.seekp(prev);
            sys.write(cur.c_str(), 4);
            sys.seekp(std::ios::end);
            
            sys.write(info.substr((info.size() - (block - residue)) - i * 508, (info.size() - (block - residue)) - 508 * (i + 1)).c_str(), 508);
        }
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
        flow << buf << std::endl;
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }
    sys.read(buf, residue);
    flow << buf << std::endl;
    
    delete [] buf;
    delete [] next;
    return flow;
}
//резервация места при добавлении файла
std::ios::pos_type & Desstream::open_stream_for_file(std::ios::pos_type &shift){
    sys.seekg(std::ios::end);
    shift = sys.tellg() - virtual_adress;
    sys.write(0, 512);
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
