#ifndef ORG_BOT_HPP
#define ORG_BOT_HPP

#include "note.hpp"

#define HOME_DIR std::string("/home/carlshiles/bin")
#define DAT_FILE ".storm_data"
#define DAT_PATH HOME_DIR + "/" + DAT_FILE

namespace note {

    class Org_Bot : public Parent_Note
    {
    public:
	Org_Bot();

//	void listen();


    private:
//	void command_parser();
    };

}

#endif
