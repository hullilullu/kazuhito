#include "FileReado.h"
#include<iostream>
#include <fstream>
#include <vector>
typedef unsigned char BYTE;

//curtesy the internet: stackoverflow user PLasty Grove
std::vector<unsigned char> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<unsigned char> fileData(fileSize);
    file.read((char*)&fileData[0], fileSize);
    return fileData;
}

//curtesy: the internet: https://www.tutorialspoint.com/writing-a-binary-file-in-cplusplus
int writeFile(const char* filename, std::vector<unsigned char> databytes) {
    std::cout << "write func" << std::endl;
    std::ofstream wf(filename, std::ios::out | std::ios::binary);
    if (!wf) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }
    std::cout << "file opened, start to write" << std::endl;
    for (auto chr : databytes) {
        wf.write((char *) &chr, 1);
    }
    std::cout << "done writing, closing" << std::endl;
    wf.close();
    if (!wf.good()) {
        std::cout << "Error occurred at writing time!" << std::endl;
        return 1;
    }
    return 0;
}