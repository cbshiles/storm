#include "base.hpp"

class File_Org
{//Class representing some location in file system
public:
    File_Org(std::string path="");

    inline bool exists()
    {return std::ifstream(_path.c_str());}

    inline void create()
    {//Assume (! exist) == true
	_h.create();
	edited = true;
    }

    inline void load()
    {//Assume (exist) == true
	_h.load();
	edited = false;
    }

    virtual void save() = 0;
    virtual void remove() = 0;
    virtual void edit() = 0;

protected:
    std::string _path;

    bool edited;

};

class Helper
{
    virtual void create();

    virtual void remove();

    virtual void save();

    virtual void load();
};
