#include "meme.h"
#include <iostream>

PTR Heap::Alloc(WORD length) {
	Chunk* chk = head;
	WORD adr{ 0 };

	if (head == nullptr) {
		ForceAlloc(length, 0, nullptr, nullptr);
		return (PTR)& heap[adr];
	}

	while (chk) {
		
		Chunk* prev = chk;
		adr = chk->address + chk->size;
		chk = chk->next;
		if (!chk) { // last chunk
			if (adr + length < SIZE) {
				ForceAlloc(length, adr, prev, chk);
				return (PTR)&heap[adr];
			}
			else {
				printf("Last chunk is too close to the end of the heap\n");
				return (PTR)0;
			}
		}

		if (adr + length <= chk->address) {
			ForceAlloc(length, adr, prev, chk);
			return (PTR)&heap[adr];
		}

	}
	printf("No valid memory chunk found for allocation\n");
	return (PTR)0;
}

void Heap::ForceAlloc(WORD length, WORD address, Chunk* prev, Chunk* next) {
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
		head = block.next;
	}
	block.address = -1;
	block.size = -1;
	block.index = -1;
	block.prev = nullptr;
	block.next = nullptr;
}

void Heap::Free(PTR ptr) {
	for (int i{ 0 }; i < MAX_CHUNKS; i++) {
		if (&heap[chunks[i].address] == ptr) {
			Free(chunks[i]);
			break;
		}
	}
}

void Heap::DisplayHeap(WORD from, WORD to) const {
	printf("[");
	for (WORD i = from; i < to; i++) {
		printf("%c", heap[i] == '\0' ? '#' : heap[i]);
	}
	printf("]\n");
}

void Heap::DisplayChunks() const {
	Chunk* chk = head;
	WORD lastadr{ 0 };
	WORD lastsize{ 0 };
	while (chk) {
		if (chk->size == 0 || chk->size == (WORD)-1) continue;

		for (WORD i{ lastadr + lastsize }; i < chk->address; i++) {
			printf("#");
		}

		for (WORD i{ 0 }; i < chk->size; i++) {
			printf("%d", chk->index);
		}
		lastsize = chk->size;
		lastadr = chk->address;

		chk = chk->next;
	}
	printf("\n");
}