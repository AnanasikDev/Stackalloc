#include <iostream>
#include "meme.h"

Heap ram;

int main() {

	int* ints = (int*)ram.Alloc(3 * sizeof(int));
	{
		ints[0] = 0x44314341; // 1144079169 <- D1CA
		ints[1] = 0x52525546; // 1381127494 <- RRUF
		ints[2] = 0x574F5759; // 1464817497 <- WOWY
	}
	ram.DisplayChunks();
	//ram.DisplayHeap(0, 40);
	char* const string = (char*)ram.Alloc(13);
	{
		string[0] = 'H'; string[1] = 'e';
		string[2] = 'l';
		string[3] = 'l';
		string[4] = 'o';
		string[5] = ' ';
		string[6] = 'w';
		string[7] = 'o';
		string[8] = 'r';
		string[9] = 'l';
		string[10] = 'd';
		string[11] = '\n';
		string[12] = '\0';
	}
	ram.DisplayChunks();
	//ram.Free(string);
	//ram.DisplayHeap(0, 40);
	printf(string);
	char* const other = (char*)ram.Alloc(5);
	{
		other[0] = '7';
		other[1] = '7';
		other[2] = '7';
		other[3] = '7';
		other[4] = '7';
	}
	ram.DisplayChunks();
	//ram.DisplayHeap(0, 40);
	ram.Free(other);
	ram.Free(ints);
	ram.DisplayChunks();
	ram.Free(string);
	ram.DisplayChunks();

	
	{
		int in;
		std::cin >> in;
	}
	
	return 0;
}