#ifndef NOTE_HPP
#define NOTE_HPP

#include "file_ops.hpp"
#include "family.hpp"

namespace note {

//transform function

/*
Test automatic naming thing

write command interpreter
tokenizer

 */
    class Note
    {
    public:

	Note (file_ops::File_Obj* f)
	    : _file(f)
	{

	    if(f==NULL) ERROR("Bad file object");
	}

	virtual ~Note()
	{
	    TEST("DSDS");
	    TEST("ITS!: "<<_file->get_path());
	    //delete _file;
	    TEST("bout now?");
	}
	
	inline void create()
	{_file->create();}

	inline void remove()
	{_file->remove();}

	virtual void clear() = 0;

	virtual void save() = 0;

	virtual void set_msg(std::string) = 0;

	virtual std::string get_msg() = 0;

    protected:
	file_ops::File_Obj* _file;


    };

    class Parent_Note;

    class Simple_Note : public Note, public family::Child
    {
    public:
	Simple_Note(std::string name, Parent_Note* parent, std::string message = "");

	Simple_Note(file_ops::Text* load_file, Parent_Note* p);

	virtual void clear()
	{
	    file()->overwrite("");
	}

	virtual void save()
	{
	    if (_edited)
		file()->overwrite(_msg);
	}

	inline file_ops::Text* file()
	{return (file_ops::Text*)_file;}

	virtual void set_msg(std::string s)
	{ _msg = s;}

	virtual std::string get_msg()
	{ return _msg;}

    protected:
	bool _edited;

	std::string _msg;
    };


    class Parent_Note : public Note, public family::Parent
    {
    public:
	Parent_Note(std::string name, Parent_Note* p, std::string msg);

	Parent_Note(file_ops::Folder* load_file, Parent_Note* p);

	virtual ~Parent_Note();

	virtual void save()
	{
	    if (_parent_note != NULL)
		_parent_note->save();
	 
	    for (Child* n : _children)
		((Note*)n)->save();
	}

	virtual void clear()
	{
	    file()->clear();
	}

	void add(Note*);

	void spawn(std::string name = "", std::string message = "");

	std::string name_it();

	inline file_ops::Folder* file()
	{return (file_ops::Folder*)_file;}

	virtual void set_msg(std::string s)
	{_parent_note->set_msg(s);}

	virtual std::string get_msg()
	{ return _parent_note->get_msg(); }

	std::string name_it(Note*);

    protected:
	Simple_Note* _parent_note;
	
	static std::string parent_text;

	char _fert = 0;
    };

}

#endif
