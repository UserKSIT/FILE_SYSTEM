//
//  BASIC_DESCRIPTION.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef BASIC_DESCRIPTION_hpp
#define BASIC_DESCRIPTION_hpp

#include <stdio.h>
#include <fstream>
#include "USER.hpp"
#include "STREAM.hpp"
#include <ctime>
//#include "DESCRIPTION_SYSTEM.hpp"

using namespace std;


    struct Id{
        string name;
        string location;
        Id (const string &name = "", const string &location = ""): name(name), location(location){}
    };
    
    class Basic_description{
    protected:
        int size;
        Level_access access_users;
        Id identity;
    public:
        //Basic_description();
        
        void set_indentity(const string&, const string&);
        virtual Basic_description * clone() const = 0;
        //virtual Basic_description &operator =(const Basic_description&) = 0;
        //virtual Basic_description &operator =(Basic_description &&) = 0;
        
        virtual ~Basic_description(){};
        
        
        
    };
    
    class Descatalog: public Basic_description{
    private:
        int virtual_adress;
        map <Id, Basic_description *> struct_catalog;
        //Basic_description * struct_catalog;
        int opp;
        int quant;
    public:
        friend class Level_access;
        
        Descatalog(const string &, const string &, const string &, const string &);
        Descatalog(const Descatalog &);
        
        ~Descatalog(){delete [] struct_catalog;}
        
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        //virtual void set_indentity(const string&, const string&);
        
        //function add object - file or catalog
        Descatalog & add_file(const Basic_description &);
        Descatalog & add_catalog();
        
        //function open file
        
        
        //function delete object - file or catalog
        
        int deleta_catalog(const Basic_description &);

        Basic_description & search(const string &) const;
        
        void exibition() const;
        friend std::ostream & operator << (std::ostream &flow, const Descatalog &object);//virtual?
        
        //virtual Descatalog &operator =(const Descatalog&);
        //virtual Descatalog &operator =(Descatalog &&);
        
        
    };
    
    class Desfile: public Basic_description{
    protected:
        tm * timeinfo;
        string master;
        Desstream * ptr_stream;
    public:
        Desfile(const string &, const string &, const string &, const string &);
        Desfile(const Desfile &);
        
        
        virtual Desfile * clone() const {
            return new Desfile(*this);
        }
        
        //virtual void set_indentity(const string &, const string &);
        
        
        
        //virtual Desfile &operator =(const Desfile&);
        //virtual Desfile &operator =(Desfile &&);
        
        void get_info() const;
        void change_acess();
        
        //-----------------------------------------------------
        
        
        int open_file() const;
        void close_file() const;
        void write_file();
        bool delete_file();
        friend std::ostream & operator << (std::ostream &flow,  Desfile  &object);//read file
        //----------------------------------------------------
    };
    


#endif /* BASIC_DESCRIPTION_hpp */
