#pragma once
#include <cstdint>

class KazuhitoBoard
{
public:
	bool passes_check();
	void insert_value(int row, int column, uint8_t value);
	uint8_t get_val(int row, int column);
	bool insert_into_all_empty(uint8_t* board, int num);
	void get_flattened(uint8_t* values);
	KazuhitoBoard();
	~KazuhitoBoard();

private:
	uint8_t board[9][9] = { 
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0,0}
	};

	
};

