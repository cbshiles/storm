#ifndef FILE_OPS_HPP
#define FILE_OPS_HPP

#include "base.hpp"

/*
make read_all (for Text)
 */

class File_Obj
{//Unix exclusive
public:
    File_Obj(std::string path): _path(path){}

    virtual void create()=0;

    virtual void remove()=0;

    //virtual void save()=0;

protected:
    std::string _path;

    bool _edited;
};

class Folder : public File_Obj
{
public:
    Folder(std::string path);

    virtual void create();

    virtual void remove();

    std::vector<std::string> list_files();
};

class Text : public File_Obj
{
public:
    Text(std::string path);

    virtual void create();

    virtual void remove();

    std::string read_all();
};

File_Obj* search(std::string path);

#endif
