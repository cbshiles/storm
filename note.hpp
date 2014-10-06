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
	Note (file_ops::File_Obj*);

	virtual ~Note();
	
	inline void create()
	{_file->create();}

	inline void remove()
	{_file->remove();}

	virtual void clear() = 0;

	virtual void save() = 0;

	virtual void set_msg(std::string) = 0;

	virtual std::string get_msg() = 0;

	inline std::string get_path()
	{return _file->get_path();}

	virtual Note* get_parent() = 0;

    protected:
	file_ops::File_Obj* _file;

	bool _ok;
    };

    class Parent_Note;

    class Simple_Note : public Note, public family::Child
    {
    public:
//This is the constructor for making a brand new note
//Therefore we will have to create the file.
	Simple_Note(std::string name, Parent_Note* parent, std::string message = "");

//Load constructor
	Simple_Note(file_ops::Text* load_file, Parent_Note* p);

	virtual void clear()
	{file()->overwrite("");}

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
	{return _msg;}

	Parent_Note* transform(Simple_Note* s);

	virtual Note* get_parent()
	{
	    Note* n = dynamic_cast<Note*>(_parent);
	    if (n==NULL)
		return this;
	    else
		return n;
	}

    protected:
	bool _edited;

	std::string _msg;
    };


    class Parent_Note : public Note, public family::Parent
    {
    public:
//Creation constructor
	Parent_Note(std::string name, Parent_Note* p, std::string msg);

//Load constructor
	Parent_Note(file_ops::Folder* load_file, Parent_Note* p);

	virtual ~Parent_Note()
	{}

	virtual void save();


	virtual void clear()
	{file()->clear();}

	void add(Note*);

	void spawn(std::string message, std::string name = "");

	std::string name_it();

	inline file_ops::Folder* file()
	{return (file_ops::Folder*)_file;}

	virtual void set_msg(std::string s)
	{_parent_note->set_msg(s);}

	virtual std::string get_msg()
	{return _parent_note->get_msg(); }

	std::string name_it(Note*);

	Note* where_at();

	virtual Note* get_parent()
	{
	    Note* n = dynamic_cast<Note*>(_parent);
	    if (n==NULL)
		return this;
	    else
		return n;
	}

	int _at = 0;

    protected:
	static std::string parent_text;

	Simple_Note* _parent_note;

	char _fert = 0;

	Parent_Note* transform(Simple_Note*);


    };



}

#endif
