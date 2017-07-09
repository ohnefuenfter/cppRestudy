// cppRestudy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <typeinfo>
#include <iostream>
#include <map>
#include "StateBroker.h"

using namespace std;

class SubState1 : public ISubroutineState1 {
	int var1;
	std::string var2;

public:
	int getVar1() const {
		return var1;
	}

	std::string getVar2() const {
		return var2;
	}

	void setVar1(int v1) { var1 = v1; }
	void setVar2(std::string& v) { var2 = v; }	
};

std::ostream& operator << (std::ostream& stream, ISubroutineState& state)
{
	stream << "Writing state" << std::endl;
	stream << state.getVar1() << std::endl;
	return stream;
}

std::ostream& operator << (std::ostream& stream, SubState1& state)
{
	stream << state.getVar1() << std::endl;
	stream << state.getVar2().c_str() << std::endl;
	return stream;
}

class ISubroutine {
public:
	virtual void Execute() = 0;	
};

StateBroker* stateBroker;

class Sub1Class : public ISubroutine {
public:
	void Execute()
	{
		if (stateBroker == NULL)
		{
			std::cout << "Sub1 called" << std::endl;
		}
		else {
			ISubroutineState1* ss1 = stateBroker->get<ISubroutineState1>();
			std::cout << "Sub1 with state called" << std::endl;
			ss1->setVar1(1);
			ss1->setVar2(std::string("State is changed by Sub1Class"));
			std::cout << *static_cast<SubState1*>(ss1) << std::endl;
		}
	}
};

class Sub2Class : public ISubroutine {
public:
	void Execute()
	{
		if (stateBroker == NULL)
		{
			std::cout << "Sub2 called" << std::endl;
		}
		else {
			ISubroutineState* ss1 = stateBroker->get<ISubroutineState>();
			std::cout << "Sub2 with state called" << std::endl;
			ss1->setVar1(2);
			std::cout << *static_cast<SubState1*>(ss1) << std::endl;
		}
	}
};

class Sub3Class : public ISubroutine {
public:
	void Execute()
	{
		if (stateBroker == NULL)
		{
		std::cout << "Sub3 called" << std::endl;
		}
		else {
			ISubroutineState1* ss1 = stateBroker->get<ISubroutineState1>();
			std::cout << "Sub3 with state called" << std::endl;
			ss1->setVar1(3);
			ss1->setVar2(std::string("State is changed by Sub3Class"));
			std::cout << *static_cast<SubState1*>(ss1) << std::endl;
		}
	}

};

class Algo {
private:
	Sub1Class* sub1;
	Sub2Class* sub2;
	Sub3Class* sub3;
	
public:
	Algo(Sub1Class* s1, Sub2Class* s2, Sub3Class* s3) : sub1(s1), sub2(s2), sub3(s3){}

	void Execute()
	{
		sub1->Execute();
		sub2->Execute();
		sub3->Execute();
	}
};

int main()
{
	Sub1Class s1;
	Sub2Class s2;
	Sub3Class s3;

	std::cout << "Stateless algorithm" << std::endl;
		Algo mainAlgo(&s1, &s2, &s3);
	mainAlgo.Execute();

	stateBroker = new StateBroker();
	SubState1* state = new SubState1();
	stateBroker->bind<ISubroutineState>(state);
	stateBroker->bind<ISubroutineState1>(state);

	std::cout << "Statefull algorithm" << std::endl;
	Algo statefulAlgo(&s1, &s2, &s3);
	statefulAlgo.Execute();

	int readch;

    std::cin >> readch;

	delete state;
	delete stateBroker;

    return 0;
}
