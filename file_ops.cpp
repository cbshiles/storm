#include "file_ops.hpp"

namespace file_ops {

    Folder::Folder(std::string p)
	: File_Obj(p)
    {

    }

    Text::Text(std::string p)
	: File_Obj(p)
    {

    }


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
	File_Obj* ret = NULL;

	struct stat info;

	if 	(stat(p.c_str(), &info) == 0)
	{
	    if (S_ISDIR(info.st_mode))
		ret = new Folder(p);
	    else
		ret = new Text(p);
	}

	return ret;
    }

}
    int main()
    {
	file_ops::File_Obj* tst = file_ops::search("test/a");
	TEST(((file_ops::Text*)tst)->read_all());
    }

/*
  File_Obj* poo = search("../storm/poop");
  if (poo == NULL)
  {
  poo = new Text("../storm/poop");
  poo->create();
  }
*/

/*  
    for (std::string str : file()->list_files())
    TEST(str);
*/
