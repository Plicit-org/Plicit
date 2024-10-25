#include<string>
#include<stdexcept>
#include<vector>
#include "Language.h"

namespace MathTeXlib::Logic
{
	MathTeXlib::Logic::Language::Constant Language::GetConstant(std::string const& name) const
	{
		if(Constants.contains(name) == true) return Constants.at(name);
		throw std::invalid_argument("Unknown constant " + name);
	}

	MathTeXlib::Logic::Language::Variable Language::GetVariable(std::string const& name)
	{
		if(Variables.contains(name) == true) return Variables.at(name);
		if(Names.contains(name) == true) throw std::invalid_argument("Invalid variable name there is already an object named " + name);
		Names.insert(name);
		Variable addVariable { name };
		Variables[name] = addVariable;
		return addVariable;
	}
	
	MathTeXlib::Logic::Language::Function Language::GetFunction(std::string const& name) const
	{
		if(Functions.contains(name) == true) return Functions.at(name);
		throw std::invalid_argument("Unknown function " + name);
	}

	MathTeXlib::Logic::Language::Relation Language::GetRelation(std::string const& name) const
	{
		if(Relations.contains(name) == true) return Relations.at(name);
		throw std::invalid_argument("Unknown relation " + name);
	}
	
	void Language::AddConstant(MathTeXlib::Logic::Language::Constant constant)
	{
		if(Names.contains(constant.GetName()) == true)
		{
			throw std::invalid_argument("Invalid constant name " + constant.GetName() + 
				" there is already an object in this language with this name.");
		}
		else
		{
			Names.insert(constant.GetName());
			Constants[constant.GetName()] = constant;
		}
	}

	void Language::AddFunction(MathTeXlib::Logic::Language::Function function)
	{
		if(Names.contains(function.GetName()) == true)
		{
			throw std::invalid_argument("Invalid function name " + function.GetName() + 
				" there is already an object in this language with this name.");
		}
		else
		{
			Names.insert(function.GetName());
			Functions[function.GetName()] = function;
		}
	}

	void Language::AddRelation(MathTeXlib::Logic::Language::Relation relation)
	{
		if(Names.contains(relation.GetName()) == true)
		{
			throw std::invalid_argument("Invalid relation name " + relation.GetName() + 
				" there is already an object in this language with this name.");
		}
		else
		{
			Names.insert(relation.GetName());
			Relations[relation.GetName()] = relation;
		}
	}

	Language::Term::Term(MathTeXlib::Logic::Language::Function value, 
		std::vector<Term> arguments) : Value { value }, Arguments { arguments }
	{
		if (value.GetSize() != Arguments.size())
		{
			std::string errmsg = "Invalid number of arguments for function " + 
				value.GetName() + ", got " + std::to_string(Arguments.size()) + 
				" arguments, expected " + std::to_string(value.GetSize()) + " arguments.";
			throw std::length_error(errmsg);
		}
		for(Term term : Arguments)
		{
			Variables.merge(term.GetVariables());
		}

	}

	Language::Term Language::Term::Substitute(Language::Term const& newValue, Language::Term const& oldValue,
		MathTeXlib::Logic::Language const& language) const
	{
		if ((*this) == oldValue) return newValue;
		if (Arguments.size() == 0) return *this;
		std::vector<Term> arguments;
		for(Language::Term term : Arguments)
		{
			arguments.push_back(term.Substitute(newValue, oldValue, language));
		}
		return Term { language.GetFunction(Value.GetName()), arguments};
	}

	bool Language::Term::operator==(Term const& rhs) const
	{
		bool ret = false;
		if (Value.GetName() == rhs.Value.GetName())
		{
			ret = true;
			ret = ret && (Arguments == rhs.Arguments);
		}
		return ret;
	}
}
