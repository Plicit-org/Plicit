#include <functional>
#include "Predicate.h"
#include "State.h"
#include <iostream>

namespace MathTeXlib::Logic
{
	State Predicate::Evaluate() const
	{ 
		return EvaluationFunction();
	}
			
	Predicate Predicate::operator|(Predicate const& righthand) const
	{
		std::function<State()> oldEvaluationFunction = EvaluationFunction;
		Predicate ret { std::function<State()> { [oldEvaluationFunction,righthand]() {return oldEvaluationFunction() || righthand.EvaluationFunction();}}};
		return ret;
	}
	
	Predicate Predicate::operator&(Predicate const& righthand) const
	{
		std::function<State()> oldEvaluationFunction = EvaluationFunction;
		Predicate ret{ std::function<State()>{[oldEvaluationFunction,righthand](){return oldEvaluationFunction() && righthand.EvaluationFunction();}}};
		return ret;
	}

	Predicate Predicate::operator!() const
	{
		std::function<State()> oldEvaluationFunction = EvaluationFunction;
		Predicate ret { std::function<State()>{[oldEvaluationFunction](){return !oldEvaluationFunction();}}};
		return ret;
	}

	Predicate Predicate::operator>>(Predicate const& righthand) const
	{
		std::function<State()> oldEvaluationFunction = EvaluationFunction;
		Predicate ret {std::function<State()>{[oldEvaluationFunction,righthand]()
			{return oldEvaluationFunction()>>righthand.EvaluationFunction(); }}};
		return ret;
	}

	Predicate Predicate::operator<<(Predicate const& righthand) const
	{
		std::function<State()> oldEvaluationFunction = EvaluationFunction;
		Predicate ret {std::function<State()>{[oldEvaluationFunction,righthand]()
			{return oldEvaluationFunction()<<righthand.EvaluationFunction(); }}};
		return ret;
	}

}
