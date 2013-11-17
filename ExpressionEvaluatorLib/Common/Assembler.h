#ifndef Assembler_h__
#define Assembler_h__

#include "..\Typedefs.h"

class Assembler
{
	ExpressionBytes _data;

	template<typename T>
	void Write(const T &data)
	{
		auto bytesCount = sizeof(T);

		auto bytes = reinterpret_cast<const Byte *>(&data);

		for(size_t i = 0; i < bytesCount; ++i)
		{
			_data.emplace_back(bytes[i]);
		}
	}

public:
	//FLD QWORD PTR DS:[value]
	//Push value to FPU stack
	Assembler &Load(double *value);

	//FSTP QWORD PTR DS:[dest]
	//Pop value from FPU stack to dest
	Assembler &Store(double *dest);

	//FSTP QWORD PTR SS:[ESP+offset]
	//Pop value from FPU stack to [ESP+offset]
	Assembler &StoreToStack(size_t offset);

	//FSTP ST
	//Pop value from FPU stack
	Assembler &Pop();

	//FFREE ST(registerNumber)
	//Mark ST register as free (register number should be in [1-7]
	Assembler &Free(Byte registerNumber);

	//MOV EAX, [address]
	//call EAX
	//Call function with address [address]
	Assembler &Call(void *address);

	//SUB ESP, bytesCount
	//Allocate memory in stack
	Assembler &AllocateStack(size_t bytesCount);

	//ADD ESP, bytesCount
	//Free memory in stack
	Assembler &FreeStack(size_t bytesCount);

	//FADD QWORD PTR DS:[operand2]
	//Add st(0) and operand2 and store result into st(0)
	Assembler &Add(double* operand2);

	//FSUB QWORD PTR DS:[operand2]
	//Subtract operand2 from st(0) and store result into st(0)
	Assembler &Sub(double* operand2);

	//FDIV QWORD PTR DS:[operand2]
	//Divide st(0) on operand2 and store result into st(0)
	Assembler &Div(double* operand2);

	//FDIV ST(0), ST(1)
	//Divide st(1) on st(0) and store result into st(0)
	Assembler &Div();

	//FDIVR ST(0), ST(1)
	//Divide st(0) on st(1) and store result into st(0)
	Assembler &DivR();
	
	//FPREM
	//Compute partial remainder of st(0) divided at st(1) and store result into st(0)
	Assembler &Mod();

	//FMUL QWORD PTR DS:[operand2]
	//Multiply st(1) and operand2 and store result into st(0)
	Assembler &Mul(double* operand2);

	//FCOS
	//Compute cosine at st(0) radian and store result into st(0)
	Assembler &Cos();

	//FSIN
	//Compute sine at st(0) radian and store result into st(0)
	Assembler &Sin();

	//FTAN
	//Compute tangent at st(0) radian and store result into st(1) and 1.0 into st(0)
	Assembler &Tan();

	//FCHS
	//Negate st(0) and store result into st(0)
	Assembler &Neg();

	//FABS
	//Compute modulus of st(0) and store result into st(0)
	Assembler &Abs();

	//FSQRT
	//Compute square root of st(0) and store result into st(0)
	Assembler &Sqrt();

	//Returns ExpressionBytes of command sequence passed into Assembler
	inline ExpressionBytes GetData() const
	{
		return _data;
	}
};

#endif // Assembler_h__
