#ifndef GUTS_HPP
#define GUTS_HPP

#include "base.hpp"

namespace guts
{
    class Node
    {
    public:
	Node(Node* parent = NULL);

	inline void after(Node* n)
	{
	    if (parent != NULL)
		parent->swap(this, n);
	    else 
		n->before(this);
	}

	inline void before(Node* n)
	{children.push_back(n);}

	inline bool is_parent()
	{return children.size() > 0;}

	virtual ~Node();

    protected:
	Node* _parent;

	std::vector<Node*> _children;

	int find(Node* n);

	void swap(Node* a, Node* b);
    };

    class File_Ball : public Node
    {
/*****
      Must be able to be a folder or not
      Should have purely virtual path() function
Should be able to create, load, edit save
 */
    public:
	File_Ball(std::string path, std::string name);
	
	File_Ball(Node* parent);

    protected:
	std::string _dir, _name;

	inline std::string path()
	{return dir + "/" + name;}
    };
    
    class Note : public Node
    {
    public:
//Notes must either have a parent or a directory path
	Note(std::string name, std::string dir);

	Note(std::string name, Node* parent);

	inline std::string path()
	{return dir + "/" + name;}

    protected:
/*******
	name - primary identifier, doesn't change
	msg - simply the message the notes is carrying
	dir - the directory the note is in. doesn't change when made fldr
*/	
	std::string _name, _msg, _dir;
	
	friend std::istream& operator>>(std::istream& is, Note& note);

	void make_parent();
	
    };

    class Org_Bot : public Node
    {
    public:
	Org_Bot();
    private:
    }
};

#endif
