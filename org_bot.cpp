#include "org_bot.hpp"

namespace note {

    Org_Bot::Org_Bot()
	: Parent_Note(new file_ops::Folder(DAT_PATH), NULL)
    {

	

    }

}

int main(int argc, char* argv[])
{
    note::Org_Bot steve;
    TEST("Z"<<steve.get_msg());
}
