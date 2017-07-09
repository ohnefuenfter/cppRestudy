#include <map>
#include <typeinfo>

#pragma once

class ISubroutineState {
public:
	ISubroutineState() = default;

	virtual int getVar1() const = 0;
	virtual void setVar1(int v1) = 0;
};

class ISubroutineState1 : public ISubroutineState {
public:

	virtual std::string getVar2() const = 0;
	virtual void setVar2(std::string& v2) = 0;
};

class StateBroker
{
	std::map<const char*, ISubroutineState*> *storage;
public:
	StateBroker();

	template <class S>
	void StateBroker::bind(S* state) {
		storage->emplace(typeid(S).name(), state);
	}

	template <class S>
	S* StateBroker::get() const {
		auto found = storage->find(typeid(S).name());
		if (found == storage->end()) return NULL;
		return (S*)found->second;
	}

	~StateBroker();
};

