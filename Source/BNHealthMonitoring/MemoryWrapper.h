#pragma once

class MemoryWrapper
{
private:
	static bool s_initialized;
	static MemoryWrapper* s_instance;
	const int memory_size = 5000;
	MemoryWrapper();
public:
	static MemoryWrapper* getInstance();
	char* mem_seg;
	~MemoryWrapper();
};
