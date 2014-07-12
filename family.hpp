#ifndef FAM_HPP
#define FAM_HPP

#include "base.hpp"

namespace family {

    class Parent;

    class Child
    {
    public:
	Child(Parent* parent = NULL);

	virtual ~Child();

    protected:
	Parent* _parent;
    };

    class Parent : public Child
    {
    public:
	Parent(Parent* p): Child(p) {}

	inline void after(Parent* n)
	{
	    if (_parent != NULL)
		_parent->swap(this, n);
	    else 
		n->before(this);
	}

	inline void before(Child* n)
	{_children.push_back(n);}

	virtual ~Parent();

    protected:
	std::vector<Child*> _children;

	int find(Child* n);

	void swap(Child* a, Parent* b);
    };

}

#endif
