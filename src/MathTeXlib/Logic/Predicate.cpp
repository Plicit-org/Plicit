#include <functional>
#include "Predicate.h"

namespace MathTeXlib::Logic
{
	bool Predicate::Evaluate() const
	{ 
		return EvaluationFunction();
	}
			
	Predicate const& Predicate::operator|(Predicate const& righthand) 
	{
		std::function<bool()> oldEvaluationFunction = EvaluationFunction;
		EvaluationFunction = std::function<bool()> { [oldEvaluationFunction,righthand]() {return oldEvaluationFunction() || righthand.EvaluationFunction();}};
		return *this;
	}
	
	Predicate const& Predicate::operator&(Predicate const& righthand) 
	{
		std::function<bool()> oldEvaluationFunction = EvaluationFunction;
		EvaluationFunction = std::function<bool()>{[oldEvaluationFunction,righthand](){return oldEvaluationFunction() && righthand.EvaluationFunction();}};
		return *this;
	}
}
