#include <iostream>
#include "Encrypto.h"


std::vector <unsigned char> Encrypto::decrypt(std::vector <unsigned char> indata, std::vector <int> key) {
	std::vector <unsigned char> outdata;
	for (int i = 0; i < indata.size(); i++) {
		outdata.push_back(indata[i] ^ key[i % key.size()]);
	}
	return outdata;
}

std::vector <unsigned char> Encrypto::encrypt(std::vector <unsigned char> indata, std::vector <int> key) {
	std::vector <unsigned char> outdata;
	for (int i = 0; i < indata.size(); i++) {
		//std::cout << i << std::endl;
		outdata.push_back(indata[i] ^ key[i % key.size()]);
	}
	return outdata;
}
