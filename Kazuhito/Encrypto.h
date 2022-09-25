#pragma once
#include <vector>

class Encrypto
{
public:
	static std::vector <unsigned char> decrypt(std::vector <unsigned char>, std::vector <int>);
	static std::vector <unsigned char> encrypt(std::vector <unsigned char>, std::vector <int>);
};

