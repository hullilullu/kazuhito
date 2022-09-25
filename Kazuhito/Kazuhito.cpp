// Kazuhito.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Small program for decrypting files using the "Kazuhito" encryption system
// takes an encrypted file, its associated key, and your input with the correct code to 
// decrypt it back

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <conio.h>
#include "KazuhitoBoard.h"
#include "FileReado.h"
#include "Encrypto.h"



int main()
{
    std::cout << "NINJA CRYPT" << std::endl;
    std::cout << "TYPE IN FILE TO DECRYPT:" << std::endl;
    std::string filepath = "";
    std::cin >> filepath;
    std::cout << "TYPE IN PATH TO KEY FILE" << std::endl;
    std::string filekeypath = "";
    std::cin >> filekeypath;
    std::cout << "TYPE IN YOUR KEY:" << std::endl;
    KazuhitoBoard kazuhitoboard = KazuhitoBoard();

    std::vector<unsigned char> keydata = readFile(filekeypath.c_str());

    if (keydata.size() != 81) {
        std::cout << "corrupt key file" << std::endl;

        _getch();
        return 1;
    }

    uint8_t* keyarr = (uint8_t*)malloc(81 * sizeof(uint8_t));
    for (int i = 0; i < keydata.size(); i++) {
        
        keyarr[i] = (uint8_t) keydata.at(i);

    }
    kazuhitoboard.insert_into_all_empty(keyarr, 81);

    free(keyarr);

    std::string::size_type idx;

    //this section possibly found online (until end of if statement)
    idx = filepath.rfind('.');
    std::string filename = filepath;
    std::string extension = "";

    if (idx != std::string::npos)
    {
        extension = filepath.substr(idx + 1);
        filename = filepath.substr(0, idx);
    }

    //get users key for matching with associated ninjakey file
    std::vector <int> user_input;
    std::string passcode = "";
    int len = 0;
    std::cin >> passcode;
    for (auto& chr : passcode) {
        if (isdigit(chr)) {
            user_input.push_back(chr - 48);
            len += 1;
        }
    }

    //preps array for function call
    uint8_t* dynamic = (uint8_t*)malloc(len * sizeof(uint8_t));
    for (int i = 0; i < user_input.size(); i++) {
        dynamic[i] = (uint8_t) user_input.at(i);
    }
    kazuhitoboard.insert_into_all_empty(dynamic, len);

    free(dynamic);

    //gets kazuhito board as a series of numbers to walk through for encryption
    uint8_t* key = (uint8_t*) malloc(81 * sizeof(uint8_t));
    kazuhitoboard.get_flattened(key);
    std::vector<int> integer_key;
    for (int i = 0; i < 81; i++) {
        integer_key.push_back((int)key[i]);
    }

    free(key);

    if (!kazuhitoboard.passes_check()) {
        std::cout << "invalid key" << std::endl;
        _getch();
        return 1;
    }

    std::vector<unsigned char> encrypted_raw_data = readFile(filepath.c_str());

    std::vector<unsigned char> decrypted_data = Encrypto::encrypt(encrypted_raw_data, integer_key);
    std::cout << "decrypted the data" << std::endl;
    std::string zip = ".zip";
    writeFile(  (filename + zip).c_str(), decrypted_data);

    _getch();
    return 0;
}

