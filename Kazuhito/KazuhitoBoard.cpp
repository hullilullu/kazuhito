#include <iostream>
#include "KazuhitoBoard.h"

//evauate if one row passes the Kazuhito encryption check
bool evaluate_row(uint8_t row[9]) {
	bool present[9] = { false,false,false,false,
			false,false,false,false,false };
	for (int i = 0; i < 9; i++) {
		if (row[i] < 10 && row[i] > 0) {
			
			present[row[i] - 1] = true;
		}
	}


	for (int i = 0; i < 9; i++) {
		if (present[i] == false) {
			return false;
		}
	}

	return true;
}

//makes column into row for evaluation with row check function
void column_to_row(uint8_t row[9], uint8_t board[9][9], int column_index) {
	for (int i = 0; i < 9; i++) {
		row[i] = board[i][column_index];
	}
}

//makes box into row for evaluation with row check function
void box_to_row(uint8_t row[9], uint8_t board[9][9], int box_index) {
	for (int i = 0; i < 9; i++) {
		int x = 3 * (box_index / 3) + i / 3;
		int y = 3 * (box_index % 3) + (i % 3);
		row[i] = board[x][y];
	}
}

bool KazuhitoBoard::passes_check() {

	//checks rows
	for (int i = 0; i < 9; i++) {
		//check rows
		if (!evaluate_row(KazuhitoBoard::board[i])) {
			return false;
		}
		//check columns
		uint8_t row[9] = { 0,0,0,0,0,0,0,0,0 };
		column_to_row(row, KazuhitoBoard::board, i);

		if (!evaluate_row(row)) {
			return false;
		}
		//check squares
		uint8_t boxrow[9] = { 0,0,0,0,0,0,0,0,0 };
		box_to_row(boxrow, KazuhitoBoard::board, i);
		if (!evaluate_row(boxrow)) {
			return false;
		}


	}

	return true;
}

void KazuhitoBoard::insert_value(int row, int column, uint8_t value) {
	if (row < 9 && column < 9 && row > -1 && column > -1) {
		KazuhitoBoard::board[row][column] = value;
	}
}

//finds all empty slots in a board and inserts an array of 8bit ints into all of them in order
bool KazuhitoBoard::insert_into_all_empty(uint8_t *values, int num) {
	int inserted_counter = 0;
	int num_empty_counter = 0;
	if (num > 9 * 9) return false;
	for (int i = 0; i < 81; i++) {
		if (KazuhitoBoard::board[i % 9][i / 9] == 0) {
			if (inserted_counter < num) {
				KazuhitoBoard::board[i % 9][i / 9] = values[inserted_counter];
				inserted_counter += 1;
				
			}
			num_empty_counter += 1;
		}
	}
	if (num_empty_counter != num) {
		return false;
	}

	return true;

}

void KazuhitoBoard::get_flattened(uint8_t* values) {
	for (int i = 0; i < 81; i++) {
		values[i] = KazuhitoBoard::board[i % 9][i / 9];
	}
}

uint8_t KazuhitoBoard::get_val(int row, int column) {
	return KazuhitoBoard::board[row][column];
};

KazuhitoBoard::KazuhitoBoard() {

}

KazuhitoBoard::~KazuhitoBoard() {

}