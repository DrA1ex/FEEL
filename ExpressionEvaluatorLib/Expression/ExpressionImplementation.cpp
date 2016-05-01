#include <algorithm>
#include <mutex>
#include <stack>

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "ExpressionImplementation.h"
#include "../Typedefs.h"
#include "../Operators/Unary/Base/UnaryOperatorBase.h"
#include "../Operators/Binary/Base/BinaryOperatorBase.h"
#include "../Helpers.h"

static ValueType __pi = M_PI;
static ValueType __e = M_E;

ExpressionImplementation::ExpressionImplementation(const std::string& expression) : _expression(expression)
{
	if (!_initialized)
	{
		std::call_once(_initFlag, []
		               {
			               Init();
		               });
		_initialized = true;
	}

	_parameters["__pi"] = nullptr;
	_parameters["__e"] = nullptr;

	auto lexemes = ParseExpression();
	PrepareExpression(lexemes);

	CompileExpression();

	auto handle = GetCurrentProcess();
	DWORD oldProtect;
	VirtualProtectEx(handle, _compiledExpressionBytes.data(), _compiledExpressionBytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect);
}

void ExpressionImplementation::CompileExpression() const
{
	std::stack<ValueType*> stack;

	//We need addresses in one memory block, which CPU will can load in cache
	//It's will improve performance.
	//We allocate memory for vector, because otherwise it may reallocate memory and addresses will be invalid
	//We count constants (we store them in memory) and operations (we store operation result in memory too)
	_memory.reserve(std::count_if(_tokens.begin(), _tokens.end(),
	                              [](Token token)
	                              {
		                              auto type = token.GetType();
		                              return type == Token::Constant || type == Token::Operation;
	                              }));

	_parametersMemory.reserve(_parameters.size());

	_parametersMemory.emplace_back(__pi);
	_parameters["__pi"] = &_parametersMemory.back();
	_parametersMemory.emplace_back(__e);
	_parameters["__e"] = &_parametersMemory.back();

	Assembler()
		.PushRegister(GeneralAsmRegisters::EAX)
		.InitFPU()
		.WriteTo(_compiledExpressionBytes);

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
				ValueType* &paramPtr = _parameters[token.GetVariableName()];
				if(paramPtr == nullptr)
				{
					_parametersMemory.emplace_back(NAN);
					paramPtr = &_parametersMemory.back();
				}

				stack.emplace(paramPtr);
			}
			break;

		case Token::Operation:
			{
				_memory.emplace_back(NAN);
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

	Assembler()
		.PopRegister(GeneralAsmRegisters::EAX)
		.Ret()
		.WriteTo(_compiledExpressionBytes);
}

ValueType ExpressionImplementation::Execute() const
{
	auto code = reinterpret_cast<void(*)()>(_compiledExpressionBytes.data());

	code();

	return _memory.size() != 0 ? _memory.back() : *_parameters.at(_tokens.back().GetVariableName());
}
