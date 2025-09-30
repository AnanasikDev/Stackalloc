#include <iostream>
#include "meme.h"

Heap ram;

int main() {

	char* ptr1 = (char*)ram.Alloc(3 * sizeof(char));
	ptr1[0] = 'K';
	ptr1[1] = 'E';

	char* ptr2 = (char*)ram.Alloc(5 * sizeof(char));
	ptr2[0] = '1';
	ptr2[1] = '2';
	ptr2[2] = '3';
	ptr2[3] = '4';
	ptr2[4] = '5';

	char* ptr3 = (char*)ram.Alloc(4 * sizeof(char));
	ptr3[0] = 'U';
	ptr3[1] = 'T';
	ptr3[2] = 'F';
	ptr3[3] = '8';

	ram.DisplayChunks();
	ram.DisplayHeap(0, 40);

	ram.Free(ptr2);


	ram.DisplayChunks();
	ram.DisplayHeap(0, 40);

	{
		int in;
		std::cin >> in;
	}
	
	return 0;
}