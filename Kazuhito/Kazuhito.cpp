// Kazuhito.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
        //printf("%d", keyarr[i]);
        //std::cout << keyarr[i];
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
    else
    {
        // No extension found
    }
    //

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

    uint8_t* dynamic = (uint8_t*)malloc(len * sizeof(uint8_t));
    for (int i = 0; i < user_input.size(); i++) {
        dynamic[i] = (uint8_t) user_input.at(i);
    }
    kazuhitoboard.insert_into_all_empty(dynamic, len);

    free(dynamic);

    uint8_t* key = (uint8_t*) malloc(81 * sizeof(uint8_t));
    kazuhitoboard.get_flattened(key);
    std::vector<int> integer_key;
    for (int i = 0; i < 81; i++) {
        integer_key.push_back((int)key[i]);
    }

    free(key);

    if (kazuhitoboard.passes_check()) {
    }
    else {
        std::cout << "invalid key" << std::endl;

        _getch();
        return 1;
    }

    //std::vector<unsigned char> raw_data = readFile(filepath.c_str());
    /*
    std::vector<unsigned char> encrypted_data = Encrypto::encrypt(raw_data, integer_key);
    //std::vector<unsigned char>().swap(raw_data);
    std::cout << "encrypted the data" << std::endl;
    std::string ninja = ".ninja";
    std::string encrypted_file = filename + ninja;
    writeFile( encrypted_file.c_str(), encrypted_data);
    */
    std::vector<unsigned char> encrypted_raw_data = readFile(filepath.c_str());

    std::vector<unsigned char> decrypted_data = Encrypto::encrypt(encrypted_raw_data, integer_key);
    std::cout << "decrypted the data" << std::endl;
    std::string zip = ".zip";
    writeFile(  (filename + zip).c_str(), decrypted_data);
    /*
    if (raw_data.size() != decrypted_data.size()) {
        std::cout << "different size for decrypted!" << raw_data.size() - decrypted_data.size() << std::endl;
        return 1;
    }

    std::cout << "identical size" << std::endl;

    for (int i = 0; i < raw_data.size(); i++) {
        if (raw_data[i] != decrypted_data[i]) {
            std::cout << "different at index" << i << std::endl;
            return 1;
        }
    }

    std::cout << "identical data" << std::endl;

    std::cout << " " << std::endl;
    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            std::cout << (int) kazuhitoboard.get_val(row, col);
        }
        std::cout << "" << std::endl;
    }
    std::cout << "  " << std::endl;
    */



    _getch();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
