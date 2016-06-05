#ifndef FBC_MESSY_TEST_INTERPRETER_HPP_
#define FBC_MESSY_TEST_INTERPRETER_HPP_

#include <iostream>
#include <string>

#include "Context.hpp"

class Context;

class AbstractExpression
{
public:
	virtual void Interpret(Context* context) = 0;
};

class Expression : public AbstractExpression
{
public:
	virtual void Interpret(Context* context)
	{
		std::cout << "ÖÕ¶Ë½âÊÍÆ÷" << std::endl;
	}
};

class NonterminalExpression : public AbstractExpression
{
public:
	virtual void Interpret(Context* context)
	{
		std::cout << "·ÇÖÕ¶Ë½âÊÍÆ÷" << std::endl;
	}
};

class Context
{
public:
	std::string input;
	std::string output;
};

// ============================================
class AbstractExpression_1
{
public:
	virtual ~AbstractExpression_1();
	virtual void Interpret(const Context_1& c);
protected:
	AbstractExpression_1();
private:
};

class TerminalExpression_1 : public AbstractExpression_1
{
public:
	TerminalExpression_1(const std::string& statement);
	~TerminalExpression_1();
	void Interpret(const Context_1& c);
protected:
private:
	std::string _statement;
};

class NonterminalExpression_1 : public AbstractExpression_1
{
public:
	NonterminalExpression_1(AbstractExpression_1* expression, int times);
	~NonterminalExpression_1();
	void Interpret(const Context_1& c);
protected:
private:
	AbstractExpression_1* _expression;
	int _times;
};

int test_Interpreter1();
int test_Interpreter2();

#endif // FBC_MESSY_TEST_INTERPRETER_HPP_
