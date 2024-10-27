#pragma once

#include<concepts>
#include<stdexcept>
#include<map>
#include<set>
#include<vector>
#include<string>


namespace MathTeXlib::Logic
{
	
	class Language
	{
		
		protected:
			class Object
			{
				public:
					enum class ObjectType
					{
						INVALID,
						CONSTANT,
						VARIABLE,
						FUNCTION,
						RELATION,
						CONNECTIVE,
						QUANTIFIER
					};
					Object(std::string name, ObjectType typeOfObject) : Name{ name }, TypeOfObject { typeOfObject } {}
					std::string GetName() const { return Name; }
					ObjectType GetType() { return TypeOfObject; }

				private:
					std::string Name;
					ObjectType TypeOfObject;
			};

			class Constant : public MathTeXlib::Logic::Language::Object
			{
				public:
					Constant() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID } {}
					Constant(std::string name) : MathTeXlib::Logic::Language::Object{ name, ObjectType::CONSTANT } {}
			};

			class Variable : public MathTeXlib::Logic::Language::Object
			{
				public:
					Variable(std::string name) : MathTeXlib::Logic::Language::Object { name, ObjectType::VARIABLE } {}
					Variable() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID } {}
			};

			class Function : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Function() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID }, Size { 0 } {}
					Function(std::string name, unsigned int size) : Size { size },
						MathTeXlib::Logic::Language::Object { name, ObjectType::FUNCTION } {}
					unsigned int GetSize() const { return Size; }
			};


			class Term
			{
				private:
					std::map<std::string, MathTeXlib::Logic::Language::Variable> Variables;
					MathTeXlib::Logic::Language::Object Value;
					std::vector<Term> Arguments;
				public:
					Term(MathTeXlib::Logic::Language::Variable value) : Value {value} 
						{ Variables[value.GetName()] = value; }
					Term(MathTeXlib::Logic::Language::Constant value) : Value(value) {}
					Term(MathTeXlib::Logic::Language::Function value, std::vector<Term> arguments); 
					
					std::string GetName() const { return Value.GetName(); }
					Term Substitute(Term const& newValue, Term const& oldValue, 
						MathTeXlib::Logic::Language const& language) const;

					bool IsClosed() const { return Variables.size() == 0; }
					std::map<std::string, MathTeXlib::Logic::Language::Variable> GetVariables () { return Variables; }
					bool operator==(Term const& rhs) const;
			};

			class Relation : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Relation() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID }, Size { 0 } {}
					Relation(std::string name, unsigned int size) : Size { size },
						MathTeXlib::Logic::Language::Object { name, ObjectType::RELATION } {}
					unsigned int GetSize() const { return Size; }
			};

			class Connective : public MathTeXlib::Logic::Language::Object
			{
				private:
					unsigned int Size;
				public:
					Connective() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID }, Size { 0 } {}
					Connective(std::string name, unsigned int size) : Size { size },
						MathTeXlib::Logic::Language::Object { name, ObjectType::CONNECTIVE } {}
					unsigned int GetSize() const { return Size; }
			};

			class Quantifier : public MathTeXlib::Logic::Language::Object
			{
				public:
					Quantifier() : MathTeXlib::Logic::Language::Object { "", ObjectType::INVALID } {}
					Quantifier(std::string name) : MathTeXlib::Logic::Language::Object { name, ObjectType::QUANTIFIER } {}
			};
		
			void AddConstant(MathTeXlib::Logic::Language::Constant constant) { AddObject(constant, Constants); }
			void AddFunction(MathTeXlib::Logic::Language::Function function) { AddObject(function, Functions); }
			void AddRelation(MathTeXlib::Logic::Language::Relation relation) { AddObject(relation, Relations); }
			void AddConnective(MathTeXlib::Logic::Language::Connective connective) { AddObject(connective, Connectives); }
			void AddQuantifier(MathTeXlib::Logic::Language::Quantifier quantifier) { AddObject(quantifier, Quantifiers); }

		private:
			std::set<std::string> Names;
			std::map<std::string, MathTeXlib::Logic::Language::Constant> Constants;
			std::map<std::string, MathTeXlib::Logic::Language::Variable> Variables;
			std::map<std::string, MathTeXlib::Logic::Language::Function> Functions;
			std::map<std::string, MathTeXlib::Logic::Language::Relation> Relations;
			std::map<std::string, MathTeXlib::Logic::Language::Connective> Connectives;
			std::map<std::string, MathTeXlib::Logic::Language::Quantifier> Quantifiers;
			template<typename T> 
			void AddObject(T object, std::map<std::string, T> collection ) requires std::is_base_of_v<Object, T>;

		public:
			MathTeXlib::Logic::Language::Constant GetConstant(std::string const& name) const;
			MathTeXlib::Logic::Language::Variable GetVariable(std::string const& name);
			MathTeXlib::Logic::Language::Function GetFunction(std::string const& name) const;
			MathTeXlib::Logic::Language::Relation GetRelation(std::string const& name) const;
			MathTeXlib::Logic::Language::Connective GetConnective(std::string const& name) const;
			MathTeXlib::Logic::Language::Quantifier GetQuantifier(std::string const& name) const;
	};
}
