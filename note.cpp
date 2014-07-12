#include "note.hpp"

namespace note {

//This is the constructor for making a new note from the program
//Therefore we will have to create the file.
    Simple_Note::Simple_Note(std::string name, Parent_Note* p, std::string msg)
	: Note(new file_ops::Text(p->file()->get_path()+"/"+name)),
	  family::Child(p),  _edited(false), _msg(msg)
    {
	file()->create();
    }


//Load constructor
    Simple_Note::Simple_Note(file_ops::Text* load_file, Parent_Note* p)
	: Note(load_file), family::Child(p), _edited(false),
	  _msg(file()->read_all())
    {}

    std::string Parent_Note::parent_text = "note.a";

//Creation constructor
    Parent_Note::Parent_Note(std::string name, Parent_Note* p, std::string msg)
	: Note(new file_ops::Folder(p->file()->get_path()+"/"+name)),
	  family::Parent(p), _parent_note(new Simple_Note(parent_text, this, msg))
    {
	file()->create();
    }

//Load constructor
    Parent_Note::Parent_Note(file_ops::Folder* load_file, Parent_Note* p)
	: Note(load_file), family::Parent(p)
    {
	std::vector<std::string> babies = file()->list_files();



	std::vector<std::string>::iterator m  = std::find(babies.begin(), babies.end(), parent_text);

	if(m != babies.end())
	{
	    _parent_note = new Simple_Note
		(new file_ops::Text(file()->get_path()+"/"+parent_text), this);
	    babies.erase(m);
	}
	else _parent_note = NULL;

	for (std::string str : babies)
	{
	    TEST("load another one");
	    file_ops::File_Obj* fo = file_ops::search(file()->get_path()+"/"+str);
	    file_ops::Folder* fld = dynamic_cast<file_ops::Folder*>(fo);

	    if (fld != NULL)
		new Parent_Note(fld, this);
	    else
		new Simple_Note((file_ops::Text*)fo, this);
	}
    }

    Parent_Note::~Parent_Note()
    {
	_parent_note = NULL;
    }

    void Parent_Note::spawn(std::string name, std::string message)
    {
	if (name == "") name = name_it();
	_children.push_back(new Simple_Note(name, this, message));
    }

    void Parent_Note::add(Note* n)
    {
	before((Child*)n);
    }

    std::string Parent_Note::name_it()
    {
//Must be connected to the new, instead of load constructor
//Guaranteed to be a unique name
	int nc = 'z' - 'a' + 1;
	int f = _fert++;
	if (f > 127)
	{
	    ERROR("The node at " << file()->get_path() << " has created the max number of babies."); 
	    return "" ;
	}
	std::string name, dest; //destination
	bool uniq;
	do 
	{
	    name = "_";
	    while (f >= 0)
	    {
		char ch = f%nc;
		name += &ch;
		f -= nc;
	    }
	    f = _fert++;
	    dest = file()->get_path()+"/"+name;
	} while (file_ops::exists(dest));

	return dest;
    }

}

