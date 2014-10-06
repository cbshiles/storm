#ifndef ORG_BOT_HPP
#define ORG_BOT_HPP

#include "note.hpp"
#include "tools.hpp"

#define HOME_DIR std::string("/home/brenan/bin")
#define DAT_FILE ".storm_data"
#define DAT_PATH HOME_DIR + "/" + DAT_FILE

namespace note {

/*
Needs to be able to cycle through all the notes
Needs to have a _cursor to keep track of current positiion
Needs to be able to create new simple notes
Should be all thats needed for a beginning
Up and working ASAP

cursor starts at this
needs to display info of current cursor
bot print out cursor's message each time
bot's message is a greeting w/ a list of commands

re-group after skeleton is working
 */

    enum State {Good, Exit, Refresh};

    class Org_Bot : public Parent_Note
    {
    public:
	Org_Bot();

	void listen();

///Depth-first traversal of nodes
	void next();

///Update display
	void update();

    private:
	State command_parser(std::string command);

	State _state;

	Note* _cursor;
    };

}

#endif
