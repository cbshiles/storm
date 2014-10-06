#include "base.hpp"


std::string get_filename(std::string path)
{
    int i, sz = path.length();
    bool st = false;
    for (i=sz-1; i>=0; i--)
    {
	if (path[i] == '/')
	    return path.substr(i+1);
    }
    return path;
}

int main()
{
    TEST (get_filename("/user/deeds/deed1.png"));
}
