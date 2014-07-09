#ifndef BASE_HPP
#define BASE_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>

#define TEST(msg) std::cout << "TEST: " << msg << std::endl;
#define ERROR(msg) std::cout << "ERROR: " << msg << std::endl;

#define HOME_DIR "/home/carlshiles/bin"
#define DAT_FILE ".storm_data"
#define DAT_PATH HOME_DIR + "/" + DAT_FILE

#endif
