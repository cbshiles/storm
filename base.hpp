#ifndef BASE_HPP
#define BASE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <cstdlib>
#include <algorithm>

#define TEST(msg) std::cout << "TEST: " << msg << std::endl;
#define ERROR(msg) std::cout << "ERROR: " << msg << std::endl;

/* move this shit
#define HOME_DIR std::string("/home/carlshiles/bin")
#define DAT_FILE ".storm_data"
#define DAT_PATH HOME_DIR + "/" + DAT_FILE
*/

#endif
