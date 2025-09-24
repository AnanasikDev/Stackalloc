#include "meme.h"
#include <iostream>

void* Heap::Alloc(short length) {
	Chunk* chk = head;
	short adr{ 0 };

	if (head == nullptr) {
		ForceAlloc(length, 0, nullptr, nullptr);
		return (void*)& heap[adr];
	}

	while (chk) {
			
		Chunk* const prev = chk; // prev and chk are valid
		adr = chk->address + chk->size;
		chk = chk->next;
		if (!chk) { // last chunk
			if (adr + length < SIZE) {
				ForceAlloc(length, adr, prev, chk);
				return (void*)&heap[adr];
			}
			else {
				printf("Last chunk is too close to the end of the heap\n");
				return (void*)0;
			}
		}

		if (adr + length <= chk->address) {
			ForceAlloc(length, adr, prev, chk);
			return (void*)&heap[adr];
		}

	}
	printf("No valid memory chunk found for allocation\n");
	return (void*)0;
}

void Heap::ForceAlloc(short length, short address, Chunk* prev, Chunk* next) {
	int index = 0;
	if (freedChunkNum > 0) {
		--freedChunkNum;
		index = freedChunkIndieces[freedChunkNum];
	}
	else if (chunkindex < MAX_CHUNKS) index = chunkindex++;
	else {
		for (; index < MAX_CHUNKS; ++index) {
			if (chunks[index].address >= SIZE) {
				break;
			}
		}
	}
	chunks[index].Set(address, length, prev, next, index);
	if (prev) prev->next = &chunks[index];
	if (head == nullptr) {
		head = &chunks[index];
	}
	else {
		head[address].next = &chunks[index];
	}
}

void Heap::Free(Chunk& block) {
	
	if (!head || block.size <= 0 || block.address < 0 || block.address >= SIZE) return;

	// push index to freed stack
	freedChunkIndieces[freedChunkNum] = block.index;
	freedChunkNum++;

	printf("%d bytes are freed at address %d\n", block.size, block.address);
	
	// reset chunk
	if (block.prev) block.prev->next = block.next;
	else {
		if (block.next) head = block.next;
		head = nullptr;
	}
	block.address = INVALID;
	block.size = INVALID;
	block.index = INVALID;
	block.prev = nullptr;
	block.next = nullptr;
}

void Heap::Free(void* ptr) {
	for (int i{ 0 }; i < MAX_CHUNKS; i++) {
		if (&heap[chunks[i].address] == ptr) {
			Free(chunks[i]);
			break;
		}
	}
}

void Heap::DisplayHeap(short from, short to) const {
	printf("[");
	for (short i = from; i < to; i++) {
		char c = heap[i];
		if (c == '\0') c = '#';
		if (c == '\n') c = '\\';
		if (c == '\t') c = '\\';
		printf("%c", c);
	}
	printf("]\n");
}

void Heap::DisplayChunks() const {
	Chunk* chk = head;
	short lastadr{ 0 };
	short lastsize{ 0 };
	if (!chk || chk->size == INVALID) {
		printf("No allocated chunks\n");
		return;
	}
	while (chk) {
		if (chk->size == 0 || chk->size == INVALID) continue;

		for (short i{ lastadr + lastsize }; i < chk->address; i++) {
			printf("#");
		}

		for (short i{ 0 }; i < chk->size; i++) {
			printf("%d", chk->index);
		}
		lastsize = chk->size;
		lastadr = chk->address;

		chk = chk->next;
	}
	printf("\n");
}