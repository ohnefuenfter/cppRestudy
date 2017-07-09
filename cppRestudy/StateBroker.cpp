#include "stdafx.h"
#include "StateBroker.h"

StateBroker::StateBroker()
{
	storage = new std::map<const char*, ISubroutineState*>();
}

StateBroker::~StateBroker()
{
	delete storage;
}

