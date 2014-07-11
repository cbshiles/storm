#ifndef FILE_OPS_HPP
#define FILE_OPS_HPP

#include "base.hpp"

namespace file_ops {

    class File_Obj
    {//Unix exclusive
    public:
	File_Obj(std::string path)
	    : _path(path)
	{}

	virtual void create()=0;

	virtual void remove()=0;

	inline std::string get_path()
	{return _path;}

    protected:
	std::string _path;


    };

    class Folder : public File_Obj
    {
    public:
	Folder(std::string path);

	virtual void create();

	void clear();

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

	void overwrite(std::string);

	void append(std::string);

    protected:
	std::ifstream is;
	std::ofstream os;

    };

    bool exists(std::string path);

    File_Obj* search(std::string path);

}

#endif
