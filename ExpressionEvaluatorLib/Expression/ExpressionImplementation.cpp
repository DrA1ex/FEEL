#include <algorithm>
#include <mutex>
#include <stack>

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "ExpressionImplementation.h"
#include "..\Typedefs.h"
#include "..\Operators\Unary\Base\UnaryOperatorBase.h"
#include "..\Operators\Binary\Base\BinaryOperatorBase.h"
#include "..\Helpers.h"

ExpressionImplementation::ExpressionImplementation(const std::string &expression) : _expression(expression)
{
	if (!_initialized)
	{
		std::call_once(_initFlag, []
		               {
			               Init();
		               });
		_initialized = true;
	}

	_parameters["pi"] = M_PI;
	_parameters["e"] = M_E;

	CompileExpression();

	auto handle = GetCurrentProcess();
	DWORD oldProtect;
	VirtualProtectEx(handle, _compiledExpressionBytes.data(), _compiledExpressionBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
}

void ExpressionImplementation::CompileExpression() const
{
	auto lexemes = ParseExpression();
	_tokens = ConvertToPrefixNotation(lexemes);
	std::stack<ValueType*> stack;

	//We need addresses in one memory block, which CPU will can load in cache
	//It's will improve performance.
	//We allocate memory for vector, because otherwise it will reallocate memory and addresses will be invalid
	//We count variables (we store it in memory) and operations (we store operation result in memory too)
	_memory.reserve(std::count_if(_tokens.begin(), _tokens.end(),
	                              [](Token token)
	                              {
		                              auto type = token.GetType();
		                              return type == Token::Constant || type == Token::Operation;
	                              }));

	_compiledExpressionBytes.emplace_back(0x50); //push eax

	for (auto it = _tokens.begin(); it != _tokens.end(); ++it)
	{
		const Token& token = *it;

		switch (token.GetType())
		{
		case Token::Constant:
			{
				_memory.emplace_back(token.GetConstant());
				stack.emplace(&_memory.back());
			}
			break;

		case Token::Variable:
			{
				ValueType* paramPtr = const_cast<ValueType*>(&_parameters.at(token.GetVariableName()));
				stack.emplace(paramPtr);
			}
			break;

		case Token::Operation:
			{
				_memory.emplace_back(double());
				ValueType& resultRef = _memory.back();
				const OperatorBase& operation = token.GetOperation();
				ExpressionBytes operationBytes;

				switch (token.GetOperation().Type())
				{
				case OperatorBase::Unary:
					{
						auto operand = pop(stack);
						const UnaryOperatorBase& unaryOp = static_cast<const UnaryOperatorBase&>(operation);

						operationBytes = unaryOp.GetBytes(operand, &resultRef);
					}
					break;

				case OperatorBase::Binary:
					{
						auto operand2 = pop(stack);
						auto operand1 = pop(stack);
						const BinaryOperatorBase& binaryOp = static_cast<const BinaryOperatorBase&>(operation);

						operationBytes = binaryOp.GetBytes(operand1, operand2, &resultRef);
					}
					break;
				}

				_compiledExpressionBytes.insert(_compiledExpressionBytes.end(), operationBytes.begin(), operationBytes.end());
				stack.emplace(&resultRef);
			}
			break;
		}
	}

	//stack should store only result pointer at end
	if (stack.size() != 1)
		throw std::runtime_error("Stack disbalanced! Expression is wrong.");

	_compiledExpressionBytes.emplace_back(0x58); //pop eax
	_compiledExpressionBytes.emplace_back(0xC3); //ret
}

ValueType ExpressionImplementation::Execute() const
{
	auto code = reinterpret_cast<void(*)()>(_compiledExpressionBytes.data());

	code();

	return _memory.size() != 0 ? _memory.back() : _parameters[_tokens.back().GetVariableName()];
}
