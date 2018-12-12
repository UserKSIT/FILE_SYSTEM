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
#include "USER.hpp"
#include "Crypt.hpp"
#include <ctime>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include "Crypt.hpp"


extern string current_user;
extern string current_location;
extern std::fstream sys;
extern int tag;
extern Desstream main_s;
extern Desstream temp;
extern Desstream sym;



extern int quantity_file;
extern int quantity_catalog;

using namespace std;
struct ID{
    //name object
    string name;
    //way to object
    string location;
    //adress shift on disk(file)
    long int virtual_adress;
    
    ID(const string name = ""):name(name){ location = current_location; sys.seekg(0, std::ios::end);virtual_adress = sys.tellg();}
    
    bool empty() const {if (name == ""){return true;} else {return false;}}
    bool clear() {name = ""; location = ""; virtual_adress = 0; return true;}
    
    const string get_name() const {return name;}
     void set_location(const string &loc) {location = loc;}
    
    bool operator < (const ID object) const
    {
        return name < object.name;
    }
    
    bool operator == (const ID object) const
    {
        return name == object.name;
    }
};

    //parent's absract class for classes "Descatalog" and "Desfile"
    class Basic_description{
    protected:
        //name object
        std::string name;
        //size object - file or directory
        int size;
        //table access to object. Containing id user and level privileges
        map<const string, const string> access_user;
        //print data object
        virtual std::ostream & print(std::ostream &) const = 0;
    public:
       
        int & set_size(int &sz) {size = sz; return size;}
        
        Basic_description& operator = (const Basic_description &);
 
        bool insert_access(const string &, const string &);
        bool remove_access(const string &);
        std::string check_access(const string &) const;
        bool change_access(const string &, const string &);
        std::string show_access() const;
        
        
        
        virtual Basic_description * clone() const = 0;
        virtual std::string get_status() const = 0;
        virtual int open() = 0;
        virtual bool close_file() = 0;
        
        
       
        virtual std::string get_master() const = 0;
    
        virtual void write_file(const string &) = 0;
        friend std::ostream & operator << (std::ostream &flow, const Basic_description &object){return object.print(flow);}
        virtual ~Basic_description(){};
        
        virtual std::ostream & write(std::ostream&) = 0;
        virtual std::istream & read(std::istream&) = 0;
        friend std::istream& operator >> (std::istream&, map<const string, const string> &);
    };

    //Class description directory. Include in itself struct catalog - table containing file and subdirectory
    class Descatalog: public Basic_description{
    private:
        //table containing file and subdirectory
        map <ID, Basic_description *> struct_catalog;
        //print info table
        virtual std::ostream & print(std::ostream &) const;
        //pointer to parent directory
        Descatalog * parent;
    public:
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //base constructor catalog
        Descatalog(const string & name = "no name"): parent(nullptr){if (current_user != "" && current_user != "ADMIN"){insert_access(current_user, "rw");} insert_access("ADMIN", "rw");size = sizeof(*this); this->name = name;}
        
        //copy constructor
        Descatalog(const Descatalog &);
        Descatalog& operator = (const Descatalog &);
        
        //release map
        ~Descatalog();
        
        //make clone for insert in struct catalog
        virtual Descatalog * clone() const {
            return new Descatalog(*this);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //function for filling catalog
        //function add object - file or catalog. In this place user make choice - file or catalog will be insert
        Descatalog * add_object(const string &);
        //insert file or catalog
        bool insert(ID &, const Basic_description *);
        
        //delete object in catalog (file or catalog)
        bool remove(ID &);
        
        //change object in catalog
        bool replace(ID &, const Basic_description *);
        
        //change name object
        bool change_name(const string &, const ID &);
        
        //function for make secure file
        bool crypt_file(ID &);
        bool decrypt_file(ID &);
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //move in tree catalog
        Descatalog * next(ID &);
        Descatalog * back();
        Descatalog & set_parent(Descatalog *);
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //find object in map catalog
        map <ID, Basic_description *>::const_iterator find(ID &, bool &) const;
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //return info about file
        virtual std::string get_status() const;
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        Basic_description * open_file(ID &, int &);
        //function put and extract object. It necessary for copy and moving object
        bool pull_in_buffer(ID &, ID &, Basic_description *&);
        bool extract_out_buffer(ID &, Basic_description *&);
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //print content catalog
        friend std::ostream & operator << (std::ostream &flow, const Descatalog &object){return object.print(flow);}
        
        //input? Check necessary
        friend std::istream& operator >> (std::istream&, Descatalog &);
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //check
        virtual std::string get_master() const {return check_access(current_user);}
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //waste (because catalog and file inherit from "Basic_description"
        virtual std::ostream & write(std::ostream&);
        virtual std::istream & read(std::istream&);
        virtual void write_file(const string &) {return;}
        virtual bool close_file(){return false;}
        virtual int open(){return 0;}
        //std::ostream& write(std::ostream& ostr, Descatalog const& pr);
        //std::istream& read(std::istream& istr, Descatalog const& pr);
        //---------------------------------------------------------------------------------------------------------------------------------------------------
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
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //constructor file (it doesn't have data stream).
        Desfile(const string & name = "no name"):master(current_user){ptr_stream = &main_s; shift_stream = 0; time_t t = time(0); timeinfo = localtime(&t); if (current_user != "" && current_user != "ADMIN"){insert_access(current_user, "rw");} insert_access("ADMIN", "rw");size = 0; this->name = name;};
        
        //copy constructor in this place open data stream
        Desfile(const Desfile &);
        Desfile& operator = (const Desfile &);
        
        //make clone for insert in struct catalog
        virtual Desfile * clone() const {
            return new Desfile(*this);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //support function for stream (check necessary)
        Desfile & open_stream();
        Desstream * get_stream() const {return ptr_stream;}
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        bool delete_info(){if (ptr_stream->delete_info(shift_stream, size)){return true;}else{return false;}}
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //get function
        //return info about file
        virtual std::string get_status() const;
        virtual std::string get_master() const {return master;}
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //base function for work with file
        virtual int open();
        virtual bool close_file();
        virtual void write_file(const string &);
        
        //return data contain in stream
        friend std::ostream & operator << (std::ostream &flow, Desfile &object){return object.print(flow);}
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        
        //---------------------------------------------------------------------------------------------------------------------------------------------------
        //waste function (check necessary)
        virtual std::ostream & write(std::ostream&);
        virtual std::istream & read(std::istream&);
        std::istream & read_time (std::istream &, tm * );
        friend std::ostream & operator << (std::ostream &, tm * );
        //---------------------------------------------------------------------------------------------------------------------------------------------------
    };

class ProtectedDesfile: public Desfile{
private:
    map<const string, const string> table_users_access;
    long int reserve_shift;
    virtual std::ostream & print(std::ostream &) const;
public:
    ProtectedDesfile(const string &name = "", const string key = ""): Desfile(name), reserve_shift(0){this->insert_user(current_user, key);ptr_stream = &sym;}
    
    virtual ProtectedDesfile * clone() const {
        return new ProtectedDesfile(*this);
    }
    
    bool insert_user(const string &, const string &);
    bool remove_user(const string &);
    void show_table();
    
    virtual std::string get_master() const {return master;}
    
    bool replace_user(const string &, const string &);
    
    std::string get_key();
    void set_key(const string &);
    
    
    virtual bool close_file();
    virtual int open();
    
    bool decrypt();
    
    virtual std::string get_status() const;
    
    //work with file
    virtual std::ostream & write(std::ostream&);
    virtual std::istream & read(std::istream&);
    
    virtual void write_file(const string &);
    
    friend std::ostream& operator << (std::ostream&, set<const string> &);
    
    //print data file
    friend std::ostream & operator << (std::ostream &flow, ProtectedDesfile &object){return object.print(flow);}
};



std::istream& read_access_user(std::istream&, map<const string, const string> &);
std::istream& read_table_access_pf(std::istream&, map<const string, int> &);
std::istream& read_struct_catalog(std::istream&, map<ID, Basic_description *> &);



const std::string Sh[] = {"1. Catalog", "2. File", "0. Quit"};
const std::string Mode[] = {"1. Read", "2. Write", "3. Read and write", "0. Quit"};
const int NumSh = sizeof(Sh) / sizeof(Sh[0]);
const int NumMode = sizeof(Mode) / sizeof(Mode[0]);

int Answer(const std::string *, int);

const std::string Choice = "Make your choice",
Msg = "You are wrong; repeate please";


bool check_master(const string&);



#endif /* BASIC_DESCRIPTION_hpp */
