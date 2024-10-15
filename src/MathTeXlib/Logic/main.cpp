#include<iostream>
#include "LogicFalse.h"
#include "LogicTrue.h"
#include "LogicUnknown.h"
#include "Predicate.h"
#include "State.h"

int main(void)
{
	MathTeXlib::Logic::LogicTrue trueValue {};
	MathTeXlib::Logic::LogicFalse falseValue {};
	MathTeXlib::Logic::LogicUnknown unknownValue {};
	
	std::cout<<"Checking trueValue: "<<trueValue.Evaluate()<<"\n";
	std::cout<<"Checking falseValue: "<<falseValue.Evaluate()<<"\n";
	std::cout<<"Checking unknowValue: "<<unknownValue.Evaluate()<<"\n";
	std::cout<<"\n";
	std::cout<<"Checking !trueValue: "<<(!trueValue).Evaluate()<<"\n";
	std::cout<<"Checking !falseValue: "<<(!falseValue).Evaluate()<<"\n";
	std::cout<<"Checking !unknowValue: "<<(!unknownValue).Evaluate()<<"\n";
	std::cout<<"\n";
	std::cout<<"Checking trueValue    | trueValue: "<<(trueValue|trueValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   | trueValue: "<<(falseValue|trueValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue | trueValue: " <<(unknownValue|trueValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    | falseValue: "<<(trueValue|falseValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   | falseValue: "<<(falseValue|falseValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue | falseValue: " <<(unknownValue|falseValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    | unknownValue: "<<(trueValue|unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   | unknownValue: "<<(falseValue|unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue | unknownValue: " <<(unknownValue|unknownValue).Evaluate()<<"\n";
	std::cout<<"\n";
	std::cout<<"Checking trueValue    & trueValue: "<<(trueValue&trueValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   & trueValue: "<<(falseValue&trueValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue & trueValue: " <<(unknownValue&trueValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    & falseValue: "<<(trueValue&falseValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   & falseValue: "<<(falseValue&falseValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue & falseValue: " <<(unknownValue&falseValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    & unknownValue: "<<(trueValue&unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   & unknownValue: "<<(falseValue&unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue & unknownValue: " <<(unknownValue&unknownValue).Evaluate()<<"\n";
	std::cout<<"\n";
	std::cout<<"Checking trueValue    >> trueValue: "<<(trueValue>>trueValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   >> trueValue: "<<(falseValue>>trueValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue >> trueValue: " <<(unknownValue>>trueValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    >> falseValue: "<<(trueValue>>falseValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   >> falseValue: "<<(falseValue>>falseValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue >> falseValue: " <<(unknownValue>>falseValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    >> unknownValue: "<<(trueValue>>unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   >> unknownValue: "<<(falseValue>>unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue >> unknownValue: " <<(unknownValue>>unknownValue).Evaluate()<<"\n";
	std::cout<<"\n";
	std::cout<<"Checking trueValue    << trueValue: "<<(trueValue<<trueValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   << trueValue: "<<(falseValue<<trueValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue << trueValue: " <<(unknownValue<<trueValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    << falseValue: "<<(trueValue<<falseValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   << falseValue: "<<(falseValue<<falseValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue << falseValue: " <<(unknownValue<<falseValue).Evaluate()<<"\n";
	std::cout<<"Checking trueValue    << unknownValue: "<<(trueValue<<unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking falseValue   << unknownValue: "<<(falseValue<<unknownValue).Evaluate()<<"\n";
	std::cout<<"Checking unknownValue << unknownValue: " <<(unknownValue<<unknownValue).Evaluate()<<"\n";

	
	return 0;
}
