#include<iostream>
#include "LogicFalse.h"
#include "LogicTrue.h"
#include "Predicate.h"

int main(void)
{
	MathTeXlib::Logic::LogicTrue test {};
	MathTeXlib::Logic::LogicFalse test2 {};
	std::cout<<test.Evaluate()<<"\n";
	std::cout<<test2.Evaluate()<<"\n";
	MathTeXlib::Logic::Predicate test3 = test|test2;
	std::cout<<test3.Evaluate()<<"\n";
	std::cout<<(test&test2).Evaluate()<<"\n";
	return 0;
}
