#include "core.hpp"

/* TO-DO

Make a way to add notes
Add all of your to-dos into the system
command-like interface
seperate name from path (make path() fucntion, which concats name and dir)

//Later: make nested notes workable. Thing you'll need:
     //once a note's children vector is > 0, delete this notes folder
     //and put it in a newly made directory for this note
     //the note will save itself in this directory with a standard name, note.a
     //all of its children will also save in this directory
     //will also have to turn back into a file after last child removed (not really)(unless you mean note.a)

     //Remember: You have before AND after function for all your nodes.
     //You can swap their order quite easily.
*/

/*
Don't get rid of this file!
Still have edited variable information in here
still unofficial hub
 */

namespace core
{

    void node::swap(node* a, node* b)
    {
/* Makes a child of b, b child of this
   Prerequistes:
   a needsys to already be a child of this node,
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
	    else //Can't find file, make a new one with msg from input
		listen();
	}
    }

    bool note::save()
    {
	if (edited)
	{
	    std::ofstream _file;
	    _file.open(path().c_str());
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

    OrgBot::OrgBot() : note(std::string(HOME_DIR)+"/.storm_data", "This is OrgBot")
    {
	TEST("yo "<< HOME_DIR);
	makeParent();
    }

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
    {return read_loop(path());}

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
	children.push_back(new note(path));
	return true;
    }

    void OrgBot::print_all()
    {
//Make the cast a funcction, but leave this here
//Mjust first determine my pattern of use
	for (node* n : children)
	    TEST(*((note *)n));
    }

    bool OrgBot::add(std::string name, std::string msg = "", node* p = NULL)
    {
	note* gnu = new note(name, msg, p);
	if (p == NULL) //Has no parent node, added directly to OrgBot
	    children.push_back(gnu);
	gnu->save();
    }
}
    int main()
    {
	core::OrgBot n;
	n.read_loop();
	n.add("new shit");
	n.print_all();
    }
