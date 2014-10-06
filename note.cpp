#include "note.hpp"

namespace note {

    Note::Note (file_ops::File_Obj* f)
	: _file(f), _ok(true)
    {
	if(f==NULL) 
	{_ok = false; ERROR("Bad file object");}
    }

    Note::~Note()
    {
	if (_file != NULL)
	    delete _file;
    }

//This is the constructor for making a brand new note
//Therefore we will have to create the file.
    Simple_Note::Simple_Note(std::string name, Parent_Note* p, std::string msg)
	: Note(new file_ops::Text(p->file()->get_path()+"/"+name)),
	  family::Child(p),  _edited(false), _msg(msg)
    {
	file()->create();
	file()->append(msg);
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
	    file_ops::File_Obj* fo = file_ops::search(file()->get_path()+"/"+str);
	    file_ops::Folder* fld = dynamic_cast<file_ops::Folder*>(fo);

	    if (fld != NULL)
		new Parent_Note(fld, this);
	    else
		new Simple_Note((file_ops::Text*)fo, this);
	}
    }

    void Parent_Note::save()
    {
	if (_parent_note != NULL)
	    _parent_note->save();
	 
	for (Child* n : _children)
	    ((Note*)n)->save();
    }

    void Parent_Note::add(Note* n)
    {before((Child*)n);}

    void Parent_Note::spawn(std::string message, std::string name)
    {
	if (name == "") name = name_it();
	TEST("were here to work on naming it");
	//_children.push_back(new Simple_Note(name, this, message));
	new Simple_Note(name, this, message);
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
		name += ch+'a';
		f -= nc;
	    }
	    f = _fert++;
	    dest = name;
	} while (file_ops::exists(dest));

	TEST("dest: "<<dest);
	return dest;
    }

//Core function for org_bot's next function 
    Note* Parent_Note::where_at()
    {
	Note* n;
	bool gotten = false;
	while (! gotten)
	{
	    if (_at < 0) _at=0;
	    if (_at >= size())
	    {
		_at = 0;
		if (_parent == NULL)
		    return NULL;
		else
		    return ((Parent_Note *)_parent)->where_at();
	    }
	    else 
	    {
		n = dynamic_cast<Note *>(_children[_at]);
		if (file_ops::get_filename(n->get_path())  != "note.a")
		    gotten = true;
		_at++;
	    }
	}
	return n;
    }

    Parent_Note* Parent_Note::transform(Simple_Note* s)
    {
//Get all needed info from s
	s->remove();
	std::string msg = s->get_msg();
	std::string name = file_ops::get_filename(s->get_path());

//Now remove s from vecctor of children & delete it
	pop(find(s));
	delete s;

///Already adds transformed note to parent's children vector
	return new Parent_Note(name, this, msg);
    }

}
