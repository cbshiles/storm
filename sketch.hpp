
#class Parent;
#include "base.hpp"

class Child
{
protected:
    Parent* _parent;
};

class Parent : public Child
{
public:
    Parent(Parent* parent = NULL);

	inline void after(Parent* n)
	{
	    if (_parent != NULL)
		_parent->swap(this, n);
	    else 
		n->before(this);
	}

	inline void before(Child* n)
	{_children.push_back(n);}

protected:
	Node* _parent;

	std::vector<Child*> _children;

	int find(Child* n);

	void swap(Child* a, Child* b);
}
