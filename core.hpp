#ifndef CORE_HPP
#define CORE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

#define TEST(msg) std::cout << "TEST: " << msg << std::endl;
#define ERROR(msg) std::cout << "ERROR: " << msg << std::endl;

#define HOME_DIR "/home/carlshiles/bin"

namespace core 
{
    class node
    {

    protected:
	
	node* parent;

	std::vector<node*> children;

	int find(node* n);

	void swap(node* a, node* b);

    public:

	node(node* n = NULL): parent(n) 
	{if (parent != NULL) parent->before(this);}

	inline
	void after(node* n)
	{
	    if (parent != NULL)
		parent->swap(this, n);
	    else 
		n->before(this);
	}

	inline
	void before(node* n)
	{children.push_back(n);}

    };

    class note : public node
    {
    protected:
	std::string name, msg, dir;

	bool edited;

	friend std::istream& operator>>(std::istream& is, note& anote);

    public:

	note(std::string n, std::string m, node* p);

	inline
	std::string path()
	{
	    if (isParent())
		return name
	    return dir + "/" + name;
	}

	bool save();

	inline void clear() {msg="";}

	inline void listen() {std::cin >> *this; edited = true;}

	friend 
	std::ostream& operator<<(std::ostream& os, const note& anote);

	inline bool is_parent()
	{return children.size() > 0;}

	void make_parent()
	{
	    edited = true;
	    dir += "/"+name;
	    name = "note.a";
	    system(("mkdir "+dir).c_str());
	    save(); 
	}
	
	bool add(note* n)
	{
	    edited = true;
	    before(n);
	    if (! is_parent())
		make_parent();
	}
    };

    class OrgBot : public note
    {
    public:
	OrgBot();
	bool read_loop();
	bool load(std::string path);
	void   print_all();
	bool add(std::string name, std::string msg, node* parent);
    private:	
	bool read_loop(std::string dir_name);
    };

}

#endif
