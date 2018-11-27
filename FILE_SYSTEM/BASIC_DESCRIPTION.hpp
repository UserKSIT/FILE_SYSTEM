//
//  BASIC_DESCRIPTION.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef BASIC_DESCRIPTION_hpp
#define BASIC_DESCRIPTION_hpp

#include "USER.hpp"
#include "STREAM.hpp"
#include "DESCRIPTION_SYSTEM.hpp"
#include <ctime>
#include <map>
#include <vector>
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
        map<const string, const string> access_user;
        
        //virtual std::ostream & print(std::ostream &) const = 0;
    public:
        void set_indentity(const string&, const string&);
        
        virtual Basic_description * clone() const = 0;
        
        virtual ~Basic_description(){};
    };
    
    class Descatalog: public Basic_description{
    private:
        int virtual_adress;
        map <Id, Basic_description *> struct_catalog;
        Desp_sys * ptr;
        //virtual std::ostream & print(std::ostream &) const;
    public:
        friend class Level_access;
        
        Descatalog(const string &, const string &, const string &, const string &, Desp_sys *);
        Descatalog(const Descatalog &);
        
        ~Descatalog();
        
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        
        Descatalog& operator = (const Descatalog &);
        
        bool insert(const Id &, const Basic_description *);
        
        bool remove(const Id &);
        
        bool replace(const Id &, const Basic_description *);
        //function add object - file or catalog
        Descatalog & add_file(const Basic_description &);
        Descatalog & add_catalog();
        
        //function open file
        
        
        //function delete object - file or catalog
        
        int deleta_catalog(const Basic_description &);

        Basic_description & search(const string &) const;
        
        void exibition() const;
        //friend std::ostream & operator << (std::ostream &flow, const Descatalog &object){return object.print(flow);}
    };
    
    class Desfile: public Basic_description{
    protected:
        tm * timeinfo;
        string master;
        Desstream ptr_stream;
        //virtual std::ostream & print(std::ostream &) const;
    public:
       Desfile(const string &, const string &, const string &, const string &);
        Desfile(const Desfile &);
        
        
        virtual Desfile * clone() const {
            return new Desfile(*this);
        }
        
        void get_info() const;
        void change_acess();
        
        //-----------------------------------------------------
        int open_file() const;
        void close_file() const;
        void write_file();
        bool delete_file();
        //friend std::ostream & operator << (std::ostream &flow, Desfile &object){return object.print(flow);}
        //----------------------------------------------------
    };



#endif /* BASIC_DESCRIPTION_hpp */
