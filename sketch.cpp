#include "sketch.hpp"

namespace core {

    Child::Child(Parent* p): _parent(p)
    {if (p != NULL) p->before(this);}

    Parent::~Parent()
    {
	for (Child* c : _children)
	{delete c; TEST("deleting");}
    }

    int Parent::find(Child* c)
    {//Checks its nodes, but doesn't check it itself
	unsigned i;
	for (i=0; i<_children.size(); i++)
	    if (c == _children[i])
		return i;
	return -1;
    }

    void Parent::swap(Child* a, Parent* b)
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
	    _children.erase(_children.begin()+i);
	    b->before(a);
	    before(b); //*this->before(b)
	}
	else ERROR("node not found for swap");
    }

}
