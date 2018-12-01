//
//  BASIC_DESCRIPTION.hpp
//  FILE_SYSTEM
//
//  Created by Артём on 13/11/2018.
//  Copyright © 2018 Ерошев Артём. All rights reserved.
//

#ifndef BASIC_DESCRIPTION_hpp
#define BASIC_DESCRIPTION_hpp

#include "STREAM.hpp"
#include <ctime>
#include <map>
#include <vector>
extern string current_user;
extern string current_location;
extern std::fstream sys;
extern Desstream main_s;
extern Desstream temp;
extern Desstream sym;

using namespace std;

    //parent's absract class for classes "Descatalog" and "Desfile"
    class Basic_description{
    protected:
        //size object - file or directory
        int size;
        //table access to object. Containing id user and level privileges
        map<const string, const string> access_user;
        //way to object
        string location;
        //name object
        string name;
        virtual std::ostream & print(std::ostream &) const = 0;
    public:
        void set_acess(const string&, const string&);
        string & set_location(const string &);
        int & set_size(int &);
 
        bool insert_access(const string &, const string &);
        
        const string & get_name(){return name;}
        
        virtual Basic_description * clone() const = 0;
        
        virtual ~Basic_description(){};
    };

    //Class description directory. Include in itself struct catalog - table containing file and subdirectory
    class Descatalog: public Basic_description{
    private:
        //adress shift on disk(file)
        std::ios::pos_type virtual_adress;
        //table containing file and subdirectory
        map <const string, Basic_description *> struct_catalog;
        //print info table
        virtual std::ostream & print(std::ostream &) const;
    public:
        Descatalog(const string &name):virtual_adress(sys.tellg()){location = current_location; this->insert_access(current_user, "rw"); size = sizeof(*this); this->name = name;}
        
        //Descatalog(const string &, const string &, const string &, const string &);
        Descatalog(const Descatalog &);
        
        ~Descatalog();
        
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        
        Descatalog& operator = (const Descatalog &);
        
        bool insert(const string &, const Basic_description *);
        
        bool remove(const string &);
        
        bool replace(const string &, const Basic_description *);
        
        Basic_description & view(const string &);
        
        Descatalog * next(const string &);
        //function add object - file or catalog
        Descatalog * add_object(const string &);
        
        //function open file
        
        //function delete object - file or catalog
        
        Descatalog * delete_catalog(const string &);
        Descatalog * delete_file(const string &);

        //Des search(const string &) const;
        
        friend std::ostream & operator << (std::ostream &flow, const Descatalog &object){return object.print(flow);}
    };
    //Description file
    class Desfile: public Basic_description{
    protected:
        //time last changes
        tm * timeinfo;
        //id owner file
        string master;
        //pointer to connected data stream
        Desstream * ptr_stream;
        //shift in data stream
        std::ios::pos_type shift_stream;
        //print info file
        virtual std::ostream & print(std::ostream &) const;
    public:
        Desfile(const string &name):master(current_user){ptr_stream = &main_s; shift_stream = main_s.open_stream_for_file(shift_stream); time_t t = time(0); timeinfo = localtime(&t);location = current_location; this->insert_access(current_user, "rw"); size = sizeof(*this);this->name = name;};
        //Desfile(const string &, const string &, const string &, const string &);//to do
        
        virtual Desfile * clone() const {
            return new Desfile(*this);
        }
        
        void get_info() const;
        void change_acess();
        
        //-----------------------------------------------------
        int open_file() const;
        void close_file() const;
        void write_file();
        friend std::ostream & operator << (std::ostream &flow, Desfile &object){return object.print(flow);}
        //----------------------------------------------------
    };

class ProtectedDesfile: public Desfile{
private:
    map <const string, const string> table_users_access;
    virtual std::ostream & print(std::ostream &) const;
public:
    bool insert_user(const string &, const string &);
    bool remove_user(const string &);
    
    friend std::ostream & operator << (std::ostream &flow, ProtectedDesfile &object){return object.print(flow);}
};

const std::string Sh[] = {"1. Catalog", "2. File", "0. Quit"};
const int NumSh = sizeof(Sh) / sizeof(Sh[0]);

int Answer(const std::string *, int);

const std::string Choice = "Make your choice",
Msg = "You are wrong; repeate please";



#endif /* BASIC_DESCRIPTION_hpp */
