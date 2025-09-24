#pragma once

#include <stdio.h>

using BYTE	= unsigned char;
using WORD	= unsigned int;
using PTR	= void*;

constexpr WORD SIZE = 1024;
constexpr WORD MAX_CHUNKS = 512;

class Chunk {
public:
	WORD address = -1; // max value
	WORD size = -1;
	Chunk* prev = 0;
	Chunk* next = 0;
	WORD index = -1;

	Chunk() = default;
	Chunk(WORD _address, WORD _size, Chunk* _prev, Chunk* _next) : address(_address), size(_size), prev(_prev), next(_next)  {
	}
	~Chunk() {
		address = -1;
		size = -1;
	}

	void Set(WORD _address, WORD _size, Chunk* _prev, Chunk* _next, WORD _index) {
		address = _address;
		size = _size;
		prev = _prev;
		next = _next;
		index = _index;
		printf("Chunk allocated at %d with size %d\n", address, size);
	}
};

class Heap {
public:
	BYTE heap[SIZE];
	Chunk chunks[MAX_CHUNKS];
	Chunk* head;
	WORD chunkindex = 0;
	WORD freedChunkIndieces[MAX_CHUNKS];
	WORD freedChunkNum = 0;

	PTR Alloc(WORD length);
	void ForceAlloc(WORD length, WORD address, Chunk* prev, Chunk* next);
	void Free(Chunk& block);
	void Free(PTR ptr);
	void DisplayHeap(WORD from, WORD to) const;
	void DisplayChunks() const;
};