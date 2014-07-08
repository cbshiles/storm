#include <string>
#include <iostream>
#include <fstream>


#define TEST(msg) std::cout << "TEST: " << msg << std::endl;
#define ERROR(msg) std::cout << "ERROR: " << msg << std::endl;

/*
Want to create a program that keeps track of days, 
Want to create a program that keeps notes.
Giant to-do to-do
keeps track of time on a daily basis
 */

namespace core 
{
    class note
    {
	std::string name, msg;
	bool edited;
    public:
//Creating new note
	note(std::string n, std::string m):
	    name(n), msg(m), edited(true) {}

//Loading note from the disk
	note(std::string n):
	    name(n), msg(""), edited(false)
	{
	    std::ifstream _file(name.c_str());
	    std::string str;
	    if (_file.is_open())
	    {
		while (! _file.eof())
		{
		    std::getline(_file, str);
		    msg += str;
		}
	    }
	    else ERROR("Opening file: " << name);
	}

	std::string read() {return msg;}

	void write() //Can call for all
	{
	    if (edited)
	    {
	    std::ofstream _file;
	    _file.open(name.c_str());
	    _file << msg << std::endl;
	    _file.close();
	    }
	}
    };
}

int main(int argc, char** argv)
{
    core::note firstt("firstt");
    TEST(firstt.read());

    core::note second("2", "second message");
    second.write();
    return 1;
}
