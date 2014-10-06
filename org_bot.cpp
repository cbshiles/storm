#include "org_bot.hpp"

namespace note {

    Org_Bot::Org_Bot()
	: Parent_Note(new file_ops::Folder(DAT_PATH), NULL),
	  _state(Refresh), _cursor(this) 
    {}

    void Org_Bot::listen()
    {
	std::string cmd;
	while (_state != Exit)
	{
	    if (_state == Refresh)
		update();
	    std::getline(std::cin, cmd);
	    _state = command_parser(cmd);
	}
    }

//Depth-first traversal of nodes
    void Org_Bot::next()
    {
	Parent_Note* pn = dynamic_cast<Parent_Note*>(_cursor);
	if(pn == NULL) //If _cursor is not a parent node
	{
	    Simple_Note* sn = dynamic_cast<Simple_Note*>(_cursor);
	    if (sn->_parent != NULL)
		pn = dynamic_cast<Parent_Note*>(sn->_parent);
	    else
	    {_cursor = this; return;}
	}	
	Note* nt = pn->where_at();
	_cursor = (nt == NULL)? this : nt;
    }

    void Org_Bot::update()
    {//Remember to put this back in
	//system("clear");
	TEST("path: " << _cursor->get_path());
	TEST("message: " << _cursor->get_msg());
    }

    State Org_Bot::command_parser(std::string cmd)
    {
	int i, wst, l = cmd.length();
	bool inword = false;
	tool::LList<std::string> words;

//Read command
	for (i=wst=0; i<l; i++)
	{
	    if (isspace(cmd[i]) && inword)
	    {
		inword = false;
		words.add_back(cmd.substr(wst, i-wst));
	    }
	    else if (! inword)
	    {
		wst = i;
		inword = true;
	    }
	}
	if (inword)
	    words.add_back(cmd.substr(wst, l-wst));

	if (words.front() == "exit")
	    return Exit;
	else if (words.front() == "next")
	{next(); return Refresh;}
	else if(words.front() == "up")
	{
	    _cursor = _cursor->get_parent();
	    return Refresh;
	}

	else if (words.front() == "new")
	{//need reset and atEnd() method for LList (we're good afaik)

	    Parent_Note* pn = dynamic_cast<Parent_Note*>(_cursor);

	    int s = words.size();
	    if(s >= 2)
	    {
		std::string msg = words.next(2);
		for(i=2;i<s;i++)
		    msg += " " + words.next();

		if(pn != NULL) //If _cursor is a parent node
		{
		    TEST(msg);
		    if (msg != "new")
		    {pn->spawn(msg); TEST("made it");}
		    return Refresh;
		}
		else
		{
//    transform, then add
		}
	    }
	}


	else if (words.front() == "del") //deletes what _cursor is pointing to
	{
	    if (_cursor != this)
	    {
		_cursor->remove(); //Remove from file system

                //move cursor next
		Note* cs = _cursor;
		next();
		TEST(_cursor->get_path());

		//Remove _cursor from its parent's list of children
		Parent_Note* pn = dynamic_cast<Parent_Note*>(cs->get_parent());
		pn->pop(pn->find(dynamic_cast<Child*>(cs))); 
		pn->_at--; //Account for note disappearing
		
		return Refresh;
	    }
	    else
		TEST("Sorry, cannot delete OrgBot.");
	}

/*
else if (words.front() == "")
	{

	}
*/
	else
	    return Good;
    }
}

int main(int argc, char* argv[])
{
    note::Org_Bot steve;
    steve.listen();

//Broken list shit (wat?)
}
