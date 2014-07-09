#include "guts.hpp"

namespace guts
{
    Node::Node(Node* p): _parent(p)
    {if (p != NULL) p->before(this);}

    Node::~Node()
    {
	for (Node* n : children)
	{delete n; TEST("deleteing");}
    }

    void Node::swap(node* a, node* b)
    {
/******
       Makes a child of b, b child of this
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

    int Node::find(node* n)
    {//Checks its nodes, but doesn't check it itself
	unsigned i;
	for (i=0; i<children.size(); i++)
	    if (n == children[i])
		return i;
	return -1;
    }

    File_Ball::File_Ball(std::string p, std::string n) 
	: Node(), _dir(p), _name(n)
    {
	if(opendir(p.c_str()) == NULL)
	{
	    ERROR("Directory " << p << " was not found.");
	    return;
	}

	struct stat info;
	
	if (stat(path().c_str(), &info) == 0)
	{
	    if (S_ISDIR(info.st_mode))
		load_folder();
	    else
		load_file();
	}
	else //Making a new one
	    create();
    }

    Note::Note(std::string n, std::string dir) : Node(p), _name(n);
    Org_Bot::Org_Bot(): Node

    Note::Note(std::string n, Note* p) : Node(p), _name(n)
    {
	if (p != NULL)
	{
	    p->make_parent(); //may already be parent, then line will do nada
	    dir = p->path();
	}
	else
	    ERROR("Creating note with NULL parent. (Must give parent or directory)");
    }

    Note::make_parent()
    {//Ignores request if already parent
	if (! is_parent())
	{
	    system(("rm "+path()).c_str());
	    system(("mkdir "+path()).c_str());
//	    Note* nt = new Note("note.a", this);
//	    nt->msg = msg;
// I'd like to do this without creating a new Note
	}
    }
}
