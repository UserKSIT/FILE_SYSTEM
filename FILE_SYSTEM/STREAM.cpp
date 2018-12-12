//
//  STREAM.cpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#include "STREAM.hpp"

using namespace std;
//редактирование
bool Desstream::push_stream(const string &info, const std::ios::pos_type &shift, int &size){// to do
    if (info.size() == 0)
        return false;
    
    long int edge = virtual_adress + shift;
    
    sys.seekp(0, std::ios::beg);
    sys.seekp(edge);
    
    int residue_block = size % block;
    
    long int prev = 0;
    long int cur = 0;
    long int quant = info.size() / block;
    
    int extra = 2147483647;

    if (size == 0){
        int i;
            for (i = 0; i < quant; i++){
                //sys.write(info.substr(508*i, 508*(i + 1)).c_str(), 508);
                sys << info.substr(508*i, 508*(i + 1));
                
                prev = sys.tellp();
                //sys.write("0", 4);
                sys << extra;
                sys.seekp(0, std::ios::end);
                cur = sys.tellp();
                sys.seekp(prev);
                sys << cur;
                sys.seekp(0, std::ios::end);
            }
            //sys.write(info.substr(508*i, info.size()).c_str(), info.size());
        sys << info.substr(508*i, info.size());
    }
    else{
        int k = 1;
        long int jump = 0;
        while(size - k * 508 > 508){
            edge += 508;
            sys.seekp(edge);
            jump = sys.tellp();
            edge += jump;
            sys.seekp(edge);
            k++;
        }
        edge += residue_block;
        sys.seekp(edge);
        
        if (info.size() <= 508 - residue_block){
            sys << info;
            size += info.size();
            return true;
        }
        sys.write(info.substr(0, block - residue_block).c_str(), block - residue_block);
        long int ruf = block - residue_block;
        
        int i;
        for (i = 0; i < quant; i++){
                prev = sys.tellp();
                //sys.write("0", 4);
                sys << extra;
                sys.seekp(0, std::ios::end);
                cur = sys.tellp();
                sys.seekp(prev);
     
                sys << cur;
                sys.seekp(0, std::ios::end);
                    
                //sys.write(info.substr(info.size() - ruf - i * 508, info.size() - ruf - 508 * (i + 1)).c_str(), 508);
            sys << info.substr(info.size() - ruf - i * 508, info.size() - ruf - 508 * (i + 1));
            }
        int non_empty = 0;
        for (int i = 0; i < 512; i++)
            sys << non_empty;
        //sys.write(info.substr(info.size() - ruf - i * 508, info.size()).c_str(), info.size());
        sys << info.substr(info.size() - ruf - i * 508, info.size());
    }
    size += info.size();
    return true;
}
//удаление информации
bool Desstream::delete_info(const std::ios::pos_type &shift, int &size){
    if (size == 0)
        return false;
    
    sys.seekp(0, std::ios::beg);
    sys.seekg(virtual_adress + shift);
    int quant = size / block;
    int residue = size % block;
    char * next = new char[4];
    char empty = 0;
    int tmp;
    
    for (int i = 0; i < quant; i++){
        for (int j = 0; j < block; j++)
            sys << empty;
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }
    for (int j = 0; j < residue; j++)
        sys << empty;
    delete [] next;
    return true;
}
//вывод информации
std::string Desstream::return_info(const std::ios::pos_type &shift, const int &size) const {
    std::cout << "Shift in return info " << shift << std::endl;
    std::ostringstream out;
    sys.seekg(0, std::ios::beg);
    sys.seekg(virtual_adress + shift);
    int quant = size / block;
    int residue = size % block;
    
    char * buf = new char[block];
    char * next = new char[4];
    int tmp;
    
    for(int i = 0; i < quant; i++){
        sys.read(buf, block);
        
        out << buf;
        
        sys.read(next, 4);
        tmp = Input(next, 4);
        sys.seekg(tmp);
    }

    sys.read(buf, residue);
    out << buf;
    
    delete [] buf;
    delete [] next;
    return out.str();
}
//резервация места при добавлении файла
std::ios::pos_type & Desstream::open_stream_for_file(std::ios::pos_type &shift){
    sys.seekp(0, std::ios::end);
    std::cout << "OPEM STREAM!" << std::endl;
    std::cout << sys.tellp() << std::endl;
    shift = sys.tellp() - virtual_adress;
    std::cout << shift << std::endl;
    int non_empty = 0;
    for (int i = 0; i < 512; i++)
        sys << non_empty;
   
    return shift;
}

//конструктор
Desstream::Desstream(const string &name):name(name){// добавить резервирование?
    sys.seekg(0, std::ios::end);
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
    sys.seekg(0, std::ios::end);
    virtual_adress = sys.tellg();
}




