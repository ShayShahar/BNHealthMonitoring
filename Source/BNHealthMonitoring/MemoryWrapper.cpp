#include "MemoryWrapper.h"

bool MemoryWrapper::s_initialized = false;
MemoryWrapper* MemoryWrapper::s_instance = nullptr;

MemoryWrapper::MemoryWrapper()
{
	mem_seg = new char[memory_size];
}

MemoryWrapper* MemoryWrapper::getInstance()
{
	if (!s_initialized)
	{
		s_instance = new MemoryWrapper();
		s_initialized = true;
		return s_instance;
	}
	else
	{
		return s_instance;
	}
}

MemoryWrapper::~MemoryWrapper()
{
	s_initialized = false;
}
