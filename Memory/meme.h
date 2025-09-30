#pragma once

#include <stdio.h>

using FOUR_WORD = long long int;
using DOUBLE_WORD = int;
using WORD = short;
using BYTE = unsigned char;

constexpr DOUBLE_WORD SIZE = 1024;
constexpr WORD MAX_CHUNKS = 512;
constexpr DOUBLE_WORD INVALID = ((unsigned)0);

class Chunk {
public:
	static constexpr DOUBLE_WORD metasize = sizeof(void*);

	DOUBLE_WORD address = INVALID; // max value
	DOUBLE_WORD size	= INVALID;
	WORD nextIndex		= INVALID;
	WORD index			= INVALID;

	void Set(DOUBLE_WORD _address, DOUBLE_WORD _size, WORD _nextIndex, DOUBLE_WORD _index) {
		address = _address;
		size = _size;
		nextIndex = _nextIndex;
		index = _index;
		printf("Chunk allocated at %d with size %d\n", address, size);
	}

	void Reset(){
		address		= INVALID;
		size		= INVALID;
		index		= INVALID;
		nextIndex	= INVALID;
	}
};

class Heap {
public:
	BYTE data[SIZE];
	Chunk chunks[MAX_CHUNKS];
	Chunk* head;
	DOUBLE_WORD chunkindex = 0;
	DOUBLE_WORD freedChunkIndieces[MAX_CHUNKS];
	DOUBLE_WORD freedChunkNum = 0;

	void* Alloc(DOUBLE_WORD length);
	void ForceAlloc(DOUBLE_WORD length, DOUBLE_WORD address, Chunk* prev, Chunk* next);
	void Free(Chunk* block);
	void Free(void* ptr);
	void DisplayHeap(DOUBLE_WORD from, DOUBLE_WORD to) const;
	void DisplayChunks() const;

private:
	void* SetMeta(const Chunk* const chk, Chunk* const prev);
	Chunk* const GetPrev(const Chunk* const chk) const;
	Chunk* At(WORD index);
	Chunk* Next(Chunk* chk);
};