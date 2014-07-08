#include "core.hpp"

/* TO-DO

Make a way to add notes
Add all of your to-dos into the system
command-like interface
Make OrgBot a node (but not a note)
*/

namespace core
{

    void node::swap(node* a, node* b)
    {
/* Makes a child of b, b child of this
   Prerequistes:
   a needs to already be a child of this node,
   and b needs to not be
*/
	int i = find(a);
	if (i != -1)
	{
	    children.erase(children.begin()+i);
	    b->before(a);
	    before(b);  //*this->before(b)
	}
	else ERROR("node not found for swap");
    }

    int node::find(node* n)
    {//Checks its nodes, but doesn't check it itself
	unsigned i;
	for (i=0; i<children.size(); i++)
	    if (n == children[i])
		return i;
	return -1;
    }

    note::note(std::string n, std::string m = "", node* p = NULL):
	node(p), name(n), msg(m), edited(m != "")
    {
	if (! edited) //Try to load from disk
	{
	    std::ifstream _file(name.c_str());
	    if (_file.is_open()) 
		_file >> *this;
	    else
		listen();
	}
    }

    bool note::save()
    {
	if (edited)
	{
	    std::ofstream _file;
	    _file.open(name.c_str());
	    _file << *this;
	}
	return edited;
    }

    std::istream& operator>>(std::istream& is, note& anote)
    {//Appends to the message
	std::string str;
	while (! is.eof())
	{
	    std::getline(is, str);
	    anote.msg += str + '\n';
	}
	return is;
    }

    inline
    std::ostream& operator<<(std::ostream& os, const note& anote)
    {return os << anote.msg;}

    const std::string OrgBot::data_dir = "/home/carlshiles/bin/.storm_data";

    OrgBot::OrgBot() {}

    bool OrgBot::read_loop(std::string dir_name)
    {
	DIR *dir = opendir(dir_name.c_str());
	if(dir == NULL)
	{
	    ERROR("Directory " << dir_name << " was not found.");
	    return false;
	}

	struct dirent *entry;
	struct stat info;

	bool suc = true;

	while ((entry = readdir(dir)) != NULL)
	{
	    std::string dname = entry->d_name;

	    if (!(dname == "." || dname == ".."))
	    {
		std::string path = dir_name + "/" + dname;

		stat(path.c_str(), &info);

		if(S_ISDIR(info.st_mode))
		    suc &= read_loop(path);
		else 
		    suc &= load(path);
	    }
	}
	return suc;
    }

    inline
    bool OrgBot::read_loop()
    {return read_loop(data_dir);}

    bool OrgBot::load(std::string path)
    {
/*
	char xten;
	int s = path.size();
	if (path[s-2] == '.')
	    xten = path[s-1];
	else
	    xten = ' ';
*/
	notes.push_back(new note(path));
	return true;
    }

    void OrgBot::print_all()
    {
	for (note* n : notes)
	    TEST(*n);
    }
}
    int main()
    {
	core::OrgBot n;
	n.read_loop();
	n.print_all();
    }
