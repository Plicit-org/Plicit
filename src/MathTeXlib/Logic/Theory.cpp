#include<vector>
#include<stdexcept>
#include<string>
#include<vector>
#include "Theory.h"


namespace MathTeXlib::Logic
{
	Theory::Formula::Formula(MathTeXlib::Logic::Language::Relation const& relation, 
		std::vector<MathTeXlib::Logic::Language::Term> arguments) : MainPart { relation }, Terms { arguments }
	{
		if (relation.GetSize() != arguments.size())
		{
			std::string errmsg = "Invalid number of arguments for relation " + relation.GetName() + ", got " +
				std::to_string(arguments.size()) + " arguments, expected " + std::to_string(relation.GetSize()) +
				" arguments.";
			throw std::length_error(errmsg);
		}
		for(MathTeXlib::Logic::Language::Term term : Terms)
		{
			FreeVariables.merge(term.GetVariables());
		}
	}

	Theory::Formula::Formula(MathTeXlib::Logic::Language::Quantifier const& quantifier, 
		MathTeXlib::Logic::Language::Variable const& variable, Formula formula) : MainPart { quantifier }, 
		Subject { variable }
	{
		if (formula.GetBoundVariables().contains(variable.GetName()) == true)
		{
			std::string errmsg = "The variable " + variable.GetName() + " is already bound by a quantifier.";
			throw std::logic_error(errmsg);
		}
		if(formula.GetFreeVariables().contains(variable.GetName()) == false)
		{
			std::string errmsg = "The formula does not contain the variable " + variable.GetName() + 
				" therefore it cannot be bound by a quantifier.";
			throw std::logic_error(errmsg);
		}
		FreeVariables.merge(formula.GetFreeVariables());
		BoundVariables.merge(formula.GetBoundVariables());
		FreeVariables.erase(variable.GetName());
		BoundVariables[variable.GetName()] = variable;
	}

	Theory::Formula::Formula(MathTeXlib::Logic::Language::Connective const& connective, std::vector<Formula> formulas) : 
		MainPart { connective }, Formulas { formulas }
	{
		if(connective.GetSize() != formulas.size())
		{
			throw std::length_error("Invalid number of arguments for connective " + connective.GetName() +
				" arguments, got " + std::to_string(formulas.size()) + " arguments, expected " + 
				std::to_string(connective.GetSize()) + " arguments.");
		}
		for(Formula formula : Formulas)
		{
			FreeVariables.merge(formula.GetFreeVariables());
			BoundVariables.merge(formula.GetBoundVariables());
		}
		std::vector<std::string> conflicts;
		for(auto [key, value] : FreeVariables)
		{
			if(BoundVariables.contains(key) == true) conflicts.push_back(key);
		}
		if(conflicts.size()>0)
		{
			std::string errmsg = "The following variable(s) would be free and bound in the resulting formula: ";
			for(std::string variable : conflicts)
			{
				errmsg += variable + ", ";
			}
			throw std::logic_error(errmsg);
		}
	}

	void Theory::AddAxiom(Formula const& axiom, std::string const& name)
	{
		if(axiom.IsClosed() == false)
		{
			std::string errmsg = "An axiom must be a closed formula, this formula has free variables.";
			throw std::logic_error(errmsg);
		}
		if(Axioms.contains(name)==true)
		{
			std::string errmsg = "This theory already has an axiom named " + name + ".";
			throw std::invalid_argument(errmsg);
		}
		Axioms[name] = axiom;
	}
}
