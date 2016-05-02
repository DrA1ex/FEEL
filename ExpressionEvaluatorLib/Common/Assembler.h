#ifndef Assembler_h__
#define Assembler_h__

#include "../Typedefs.h"

enum class GeneralAsmRegisters : uint8_t
{
	EAX = 0,
	ECX,
	EDX,
	EBX,
	ESP,
	EBP,
	ESI,
	EDI
};

class Assembler
{
	ExpressionBytes _data;

	template<typename T>
	void Write(const T &data)
	{
		auto bytesCount = sizeof(T);

		auto bytes = reinterpret_cast<const Byte *>(&data);

		for(uint32_t i = 0; i < bytesCount; ++i)
		{
			_data.emplace_back(bytes[i]);
		}
	}

	template<typename Arg1,typename... Data>
	void Write(Arg1 arg1, Data... args)
	{
		Write(arg1);
		Write(args...);
	}

public:
	void WriteTo(ExpressionBytes& dst) const;
	Assembler &Write(const Assembler &a);

	//FLD QWORD PTR DS:[value]
	//Push value to FPU stack
	Assembler &Load(double *value);

	//FLDZ
	//Push zero to FPU stack
	Assembler &LoadZero();

	//FLD1
	//Push one to FPU stack
	Assembler &LoadOne();

	//FSTP QWORD PTR DS:[dest]
	//Pop value from FPU stack to dest
	Assembler &Store(double *dest);

	//FSTP QWORD PTR SS:[ESP+offset]
	//Pop value from FPU stack to [ESP+offset]
	Assembler &StoreToStack(uint32_t offset);

	//FSTP ST
	//Pop value from FPU stack
	Assembler &Pop();

	//FFREE ST(registerNumber)
	//Mark ST register as free (register number should be in [1-7]
	Assembler &Free(Byte registerNumber);

	//MOV <DST>, <SRC>
	//Moves data from SRC to DST
	Assembler &Mov(GeneralAsmRegisters dst, GeneralAsmRegisters src);
	Assembler &Mov(GeneralAsmRegisters dst, uint32_t src);
	Assembler &Mov(double *dst, GeneralAsmRegisters src);

	//AND <DST>, <DATA>
	//Apply AND to DST and DATA and store result into DST
	Assembler &And(GeneralAsmRegisters dst, uint32_t data);

	//MOV EAX, [address]
	//CALL EAX
	//Call function with address [address]
	Assembler &Call(void *address);

	//CALL <REGISTER>
	Assembler &Call(GeneralAsmRegisters reg);

	//SUB ESP, bytesCount
	//Allocate memory in stack
	Assembler &AllocateStack(uint32_t bytesCount);

	//ADD ESP, bytesCount
	//Free memory in stack
	Assembler &FreeStack(uint32_t bytesCount);

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

	//RET
	//Return from proc
	Assembler &Ret();

	//PUSH <REGISTER>
	//Push register to stack)
	Assembler &PushRegister(GeneralAsmRegisters reg);

	//POP <REGISTER>
	//Pop register from stack (register number should be in [0-7])
	Assembler &PopRegister(GeneralAsmRegisters reg);

	//FINIT
	//Init FPU
	Assembler &InitFPU();

	//FSAVE
	//Save FPU to [ESP]
	Assembler &SaveFPU();

	//FRSTORE 
	//Load FPU from [ESP]
	Assembler &RestoreFPU();

	//FCOMI
	//Compare two values: st(0) and st(N)
	Assembler &Compare(Byte registerNumber = 1);

	//FCOMIP
	//Compare two values and pop: st(0) and st(N)
	Assembler &CompareAndPop(Byte registerNumber = 1);

	//JMP NEAR
	Assembler &Jmp(int8_t offset);

	//JMP NEAR if (not) Z (Zero flag)
	Assembler JE(int8_t offset);
	Assembler JNE(int8_t offset);

	//JMP NEAR if C (Carry flag)
	Assembler JL(int8_t offset);

	//JMP NEAR if not C and not Z
	Assembler JG(int8_t offset);

	//JMP NEAR if greather or equal (flag Z or not C)
	Assembler JGE(int8_t offset);

	//JMP NEAR if less or equal (flag Z or C)
	Assembler JLE(int8_t offset);

	//Returns ExpressionBytes of command sequence passed into Assembler
	inline ExpressionBytes GetData() const
	{
		return _data;
	}

	inline  size_t Size() const
	{
		return _data.size();
	}
};

#endif // Assembler_h__
