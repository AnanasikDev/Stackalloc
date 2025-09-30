#include "meme.h"
#include <iostream>

void* Heap::Alloc(DOUBLE_WORD length) {
	Chunk* chk = head;
	DOUBLE_WORD adr{ Chunk::metasize };

	if (head == nullptr) {
		ForceAlloc(length, adr, nullptr, nullptr);
		return (void*)& data[adr];
	}

	while (chk) {
			
		Chunk* const prev = chk; // prev and chk are valid
		adr = chk->address + chk->size + Chunk::metasize;
		chk = &chunks[chk->nextIndex];
		if (chk == head || !chk) { // no next chunk, nextIndex == 0 - last chunk
			if (adr + length < SIZE) {
				ForceAlloc(length, adr, prev, chk);
				return (void*)&data[adr];
			}
			else {
				printf("Last chunk is too close to the end of the heap\n");
				return (void*)0;
			}
		}

		if (adr + length <= chk->address) {
			ForceAlloc(length, adr, prev, chk);
			return (void*)&data[adr];
		}

	}
	printf("No valid memory chunk found for allocation\n");
	return (void*)0;
}

void Heap::ForceAlloc(DOUBLE_WORD length, DOUBLE_WORD address, Chunk* prev, Chunk* next) {
	DOUBLE_WORD index = 0;
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
	Chunk* chk = &chunks[index];
	chk->Set(address, length, chk->nextIndex, index);
	if (prev) SetMeta(chk, prev != nullptr ? prev : chk);
	
	// TODO: save a pointer to the chunk in the metadata (on the heap itself)

	if (head == nullptr) {
		head = chk;
	}
	if (prev) prev->nextIndex = chk->index;
}

void Heap::Free(Chunk* block) {
	
	if (!head || block->size <= 0 || block->address < 0 || block->address >= SIZE) return;

	// push index to freed stack
	freedChunkIndieces[freedChunkNum] = block->index;
	freedChunkNum++;

	printf("%d bytes are freed at address %d\n", block->size, block->address);
	
	// reset chunk
	if (head == block) head = Next(block);
	Chunk* const prev = GetPrev(block);
	if (prev)  = Next(block);
	else { // first chunk
		if (Next(&block)) head = Next(block);
		else head = nullptr;
	}

	block->Reset();
}

void Heap::Free(void* ptr) {
	
	//Chunk* chk = (Chunk*)((BYTE*)ptr - Chunk::metasize);
	
	BYTE* hdr = reinterpret_cast<BYTE*>(ptr) - Chunk::metasize;
	Chunk* chk = reinterpret_cast<Chunk*>(	hdr);
	if (head != chk) {
		chk = Next(chk);
	}
	if (!chk) printf("CHUNK IS NULL\n");
	Free(*chk);

	//Chunk* chk{ head };
	//while (chk) {
	//	if (&data[chk->address] == ptr) {
	//		Free(*chk);
	//		return;
	//	}
	//	chk = chk->next;
	//}
}

void Heap::DisplayHeap(DOUBLE_WORD from, DOUBLE_WORD to) const {
	printf("[");
	for (DOUBLE_WORD i = from; i < to; i++) {
		char c = data[i];
		if (c == '\0') c = '#';
		if (c == '\n') c = '\\';
		if (c == '\t') c = '\\';
		printf("%c", c);
	}
	printf("]\n");
}

void Heap::DisplayChunks() const {
	Chunk* chk = head;
	DOUBLE_WORD lastadr{ 0 };
	DOUBLE_WORD lastsize{ 0 };
	if (!chk || chk->size == INVALID) {
		printf("No allocated chunks\n");
		return;
	}
	while (chk) {
		if (chk->size == 0 || chk->size == INVALID) continue;

		for (DOUBLE_WORD i{ lastadr + lastsize }; i < chk->address; i++) {
			printf("#");
		}

		for (DOUBLE_WORD i{ 0 }; i < chk->size; i++) {
			printf("%d", chk->index);
		}
		lastsize = chk->size;
		lastadr = chk->address;

		chk = chk->next;
	}
	printf("\n");
}

void* Heap::SetMeta(const Chunk* const chk, Chunk* const prev) {
	BYTE* ptr = data + chk->address - Chunk::metasize;
	Chunk** dest = reinterpret_cast<Chunk**>(ptr);
	*dest = prev;
	return ptr;
}

Chunk* const Heap::GetPrev(const Chunk* const chk) const {
	const BYTE* ptr = data + chk->address - Chunk::metasize;
	return (Chunk* const)(*ptr);
}

Chunk* Heap::At(WORD index) {
	return &chunks[index];
}

Chunk* Heap::Next(Chunk* chk) {
	return At(chk->nextIndex);
}