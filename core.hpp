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
	std::string name, msg;

	bool edited;

	friend std::istream& operator>>(std::istream& is, note& anote);

    public:

	note(std::string n, std::string m, node* p);

	bool save();

	inline void clear() {msg="";}

	inline void listen() {std::cin >> *this; edited = true;}

	friend 
	std::ostream& operator<<(std::ostream& os, const note& anote);
	
    };

    class OrgBot //make it a node
    {
    public:
	OrgBot();
	bool read_loop();
	bool load(std::string path);
	static const std::string data_dir;
	void 	print_all();
    private:	
	bool read_loop(std::string dir_name);
	std::vector<note*> notes;
    };

}

#endif
