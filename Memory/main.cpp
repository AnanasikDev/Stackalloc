#include <iostream>
#include "meme.h"

Heap ram;

int main() {

	int* ints = (int*)ram.Alloc(5 * sizeof(int));
	ints[0] = 0x6FAAFFFF;
	ints[1] = 7123;
	ints[2] = 600;
	ints[3] = 934;
	ints[4] = 55;
	ram.DisplayChunks();
	ram.DisplayHeap(0, 40);
	printf("%d\n", ints[0]);
	printf("%d\n", ints[1]);
	printf("%d\n", ints[2]);
	printf("%d\n", ints[3]);
	printf("%d\n", ints[4]);

	/*char* ptr1 = (char*)ram.Alloc(3);
	ptr1[0] = 'a';
	ptr1[1] = 'b';
	ptr1[2] = 'c';
	char* ptr2 = (char*)ram.Alloc(4);
	ptr2[0] = '4';
	ptr2[1] = '5';
	ptr2[2] = '6';
	ptr2[3] = '7';
	char* ptr3 = (char*)ram.Alloc(5);
	ptr3[0] = 'E';
	ptr3[1] = 'F';
	ptr3[2] = 'G';
	ptr3[3] = 'H';
	ptr3[4] = 'I';
	ram.DisplayChunks();
	ram.DisplayHeap(0, 20);
	ram.Free(ptr3);
	char* ptr4 = (char*)ram.Alloc(2);
	ptr4[0] = '_';
	ptr4[1] = '=';
	ram.DisplayHeap(0, 20);
	ram.Free(ptr1);
	void* ptr5 = ram.Alloc(10);
	ram.Alloc(50);
	ram.Free(ptr5);
	ram.Alloc(6);
	ram.DisplayChunks();
	ram.Alloc(4);
	ram.DisplayChunks();

	ram.Alloc(4);
	ram.DisplayChunks();

	std::cout << "Hello\n";*/

	int in;
	std::cin >> in;
	return 0;
}