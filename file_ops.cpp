#include "file_ops.hpp"

namespace file_ops {

    Folder::Folder(std::string p)
	: File_Obj(p)
    {}

    void Folder::create()
    {
	system(("mkdir "+_path).c_str());
    }

    void Folder::clear()
    {
	system(("rm -r "+_path+"/*").c_str());
    }

    void Folder::remove()
    {
	system(("rm -r "+_path).c_str());
    }

    std::vector<std::string> Folder::list_files()
    {
	std::vector<std::string> lzt;

	DIR *dir = opendir(_path.c_str());
	if(dir == NULL)
	{
	    ERROR("Directory " << _path << " was not found.");
	    return lzt;
	}

	struct dirent *entry;

	while ((entry = readdir(dir)) != NULL)
	{
	    std::string dname = entry->d_name;

	    if (!(dname == "." || dname == ".."))
		lzt.push_back(dname);
	}
    }

    Text::Text(std::string p)
	: File_Obj(p)
    {}

    void Text::create()
    {
	system(("touch "+_path).c_str());
    }

    void Text::remove()
    {
	system(("rm "+_path).c_str());
    }

    std::string Text::read_all()
    {

	std::string line, whole = "";
	is.open(_path);
	while (! is.eof())
	{
	    std::getline(is, line);
	    whole += line + '\n';
	}
	is.close();
	return whole;
    }

    void Text::overwrite(std::string str)
    {
	os.open(_path, std::ios::trunc);
	os << str;
	os.close();
    }

    void Text::append(std::string str)
    {
	os.open(_path, std::ios::app);
	os << str;
	os.close();
    }

    bool exists(std::string p)
    {
	struct stat info;
	return (stat(p.c_str(), &info) == 0);
    }

    File_Obj* search(std::string p)
    {
	struct stat info;

	if(stat(p.c_str(), &info) == 0) //File found
	{
	    if (S_ISDIR(info.st_mode))
		return new Folder(p);
	    else
		return new Text(p);
	}
	else return NULL;
    }

    std::string get_filename(std::string path)
    {
	int i, sz = path.length();
	for (i=sz-1; i>=0; i--)
	{
	    if (path[i] == '/')
		return path.substr(i+1);
		    }
	return path;
    }

}
