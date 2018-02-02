#include <vector>
#include "Interpreter.hpp"

// Blog: http://blog.csdn.net/fengbingchun/article/details/37325051

AbstractExpression_1::AbstractExpression_1()
{

}

AbstractExpression_1::~AbstractExpression_1()
{

}

void AbstractExpression_1::Interpret(const Context_1& c)
{

}

TerminalExpression_1::TerminalExpression_1(const std::string& statement)
{
	this->_statement = statement;
}

TerminalExpression_1::~TerminalExpression_1()
{

}

void TerminalExpression_1::Interpret(const Context_1& c)
{
	std::cout << this->_statement << "TerminalExpression" << std::endl;
}

NonterminalExpression_1::NonterminalExpression_1(AbstractExpression_1* expression, int times)
{
	this->_expression = expression;
	this->_times = times;
}

NonterminalExpression_1::~NonterminalExpression_1()
{

}

void NonterminalExpression_1::Interpret(const Context_1& c)
{
	for (int i = 0; i < _times; i++)
		this->_expression->Interpret(c);
}


int test_Interpreter1()
{
	Context* context = new Context();
	std::vector<AbstractExpression*> express;
	express.push_back(new Expression());
	express.push_back(new NonterminalExpression());
	express.push_back(new NonterminalExpression());

	std::vector<AbstractExpression*>::iterator p = express.begin();
	while (p != express.end()) {
		(*p)->Interpret(context);
		p++;
	}

	/*result
		ÖÕ¶Ë½âÊÍÆ÷
		·ÇÖÕ¶Ë½âÊÍÆ÷
		·ÇÖÕ¶Ë½âÊÍÆ÷
	*/

	return 0;
}

int test_Interpreter2()
{
	Context_1* c = new Context_1();
	AbstractExpression_1* te = new TerminalExpression_1("hello");
	AbstractExpression_1* nte = new NonterminalExpression_1(te, 2);
	nte->Interpret(*c);

	/*result
		helloTerminalExpression
		helloTerminalExpression
	*/

	return 0;
}
