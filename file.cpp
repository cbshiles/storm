#include "file.hpp"

File_Org::File_Org(std::string p)
    : _path(p)
{
    if (exists)
	load();
    else
	create();
}

int main()
{
    File_Org fo((DAT_PATH).c_str());
    TEST(fo.exists());
}
