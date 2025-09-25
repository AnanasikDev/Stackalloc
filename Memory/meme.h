#pragma once

#include <stdio.h>

constexpr short SIZE = 1024;
constexpr short MAX_CHUNKS = 512;
constexpr short INVALID = ((short)-1);

class Chunk {
public:
	short address = -1; // max value
	short size = -1;
	Chunk* prev = 0;
	Chunk* next = 0;
	short index = -1;

	Chunk() = default;
	Chunk(short _address, short _size, Chunk* _prev, Chunk* _next) : address(_address), size(_size), prev(_prev), next(_next)  {
	}
	~Chunk() {
		address = -1;
		size = -1;
	}

	void Set(short _address, short _size, Chunk* _prev, Chunk* _next, short _index) {
		address = _address;
		size = _size;
		prev = _prev;
		next = _next;
		index = _index;
		printf("Chunk allocated at %d with size %d\n", address, size);
	}

	void Reset(){
		address = INVALID;
		size = INVALID;
		index = INVALID;
		prev = nullptr;
		next = nullptr;
	}
};

class Heap {
public:
	unsigned char heap[SIZE];
	Chunk chunks[MAX_CHUNKS];
	Chunk* head;
	short chunkindex = 0;
	short freedChunkIndieces[MAX_CHUNKS];
	short freedChunkNum = 0;

	void* Alloc(short length);
	void ForceAlloc(short length, short address, Chunk* prev, Chunk* next);
	void Free(Chunk& block);
	void Free(void* ptr);
	void DisplayHeap(short from, short to) const;
	void DisplayChunks() const;
};