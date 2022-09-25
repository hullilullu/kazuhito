#pragma once
#include <vector>


std::vector<unsigned char> readFile(const char* filename);
int writeFile(const char* filename, std::vector<unsigned char> databytes);


