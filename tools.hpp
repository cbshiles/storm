#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "base.hpp"


namespace tool {

    template<typename T>
    struct LNode
    {
	LNode(T val, LNode<T>* next = NULL)
	    :_next(next), _val(val) {}
	T _val;
	LNode<T>* _next;
    };

    template<typename T>
    class LList
    {
    public:
//Create empty list
	LList()
	    : _size(0) {}

	~LList()
	{
	    while (! empty())
		rm_front();
	}

	void add_front(T val)
	{
	    if (empty())
		_beg = _end = new LNode<T>(val);
	    else
		_beg = new LNode<T>(val, _beg);
	    _size++;
	}

	void add_back(T val)
	{
	    if (empty())
		_beg = _end = _pnt = new LNode<T>(val);
	    else
	    {
		_end->_next = new LNode<T>(val);
		_end = _end->_next;
	    }

	    _size++;
	}

///Preferred method of deletion
	void rm_front()
	{ 
	    if (empty()) return;
	    LNode<T>* new_beg = _beg->_next;
	    delete _beg;
	    _beg = new_beg;
	    _size--;
	}

	void rm(int i)
	{
	    if (empty() || i < 0 || i >= _size)
	    {
		ERROR("Invalid index");
		return;
	    }
	    if (i==0)
		rm_front();
	    bool chopped = false;
	    if (i == _size-1)
		chopped = true;

	    LNode<T> *prev, *goner = _beg;
	    while(i-- > 0)
	    {
		prev = goner;
		goner = goner->_next;
	    }
	    prev->_next = goner->_next;
	    if (chopped)
		_end = prev;
	    delete goner;
	    _size--;
	}

	inline bool empty()
	{return _size == 0;}

	inline T front()
	{return _beg->_val;}

	inline T back()
	{return _end->_val;}

	inline int size()
	{return _size;}

	inline bool atEnd()
	{return _end == _pnt;}

	inline void reset()
	{
	    _pnt = _beg;
	}

	T next(int x = 1)
	{T ans;
	    int i; for (i=0; i<x; i++)
		   {
		       ans = _pnt->_val;
		       if (atEnd()) break;
		       _pnt = _pnt->_next;
		   }
	    return ans;
	}

    protected:
	int _size;

	LNode<T> *_beg, *_end, *_pnt;

    };

}

#endif

