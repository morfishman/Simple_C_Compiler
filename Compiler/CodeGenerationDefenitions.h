#pragma once

/* ---------- Registers ---------- */
// The initial value of the register number for the different tree nodes
#define NO_REGISTER -1
// The number of registers the code generator uses
#define NUM_OF_REGISTERS 10
// The maximum length of register's name
#define REGISTER_NAME_LENGTH 8
// The registers used for code generation

#define ECX "ecx"
#define CL "cl"
#define CH "ch"

#define ESI "esi"

#define EDI "edi"

#define EBX "ebx"
#define BL "bl"
#define BH "bh"


// The registers used for some arithmetic operations (because they're the default result registers)
#define EAX "eax"
#define AL "al"
#define AH "ah"
#define EDX "edx"
#define DL "dl"
#define DH "dh"
/* ---------- Labels ---------- */
// The format of a label.
// Expecting label number for the %d.
#define LABEL_FORMAT "$$L%d"
// The maximum length of label's name
#define LABEL_NAME_LENGTH 8

/* ---------- Symbols Addresses ---------- */
// The format of an address in the data segment (global variables).
// Added $ at the start of the address to solve name collisions for global variables.
// Expecting the identifier name for the %s.
#define GLOBAL_ADDRESS_FORMAT "$%s"
// The format of an address on the stack (relative to ebp).
// Expecting the relative address off of ebp for the %d.
#define STACK_ADDRESS_FORMAT "[ebp + %d]"
// The maximum length of symbol address. It is equal to the maximum length of
// a token because the longest address that will be produced will be the length of
// a long identifier.
#define SYMBOL_ADDRESS_LENGTH 30
// The size of an entry in the stack of the program.
// For x86 the size of a stack entry is 4 bytes
#define STACK_ENTRY_BYTES 4
/* ---------- Instructions ---------- */
#define MOV "\tmov %s, %s\n"
#define XOR "\txor %s, %s\n"
#define PUSH "\tpush %s\n"
#define POP "\tpop %s\n"
#define CALL "\tcall %s\n"

// Control flow
#define CMP "\tcmp %s, %s\n"
#define LABEL "%s:\n"
#define JMP "\tjmp %s\n"
#define JE "\tje %s\n"
#define JNE "\tjne %s\n"
#define JG "\tjg %s\n"
#define JGE "\tjge %s\n"
#define JL "\tjl %s\n"
#define JNZ "\tjnz %s\n"
#define JLE "\tjle %s\n"
#define JC "\tjc %s\n"
#define JNC "\tjnc %s\n"
#define JAE "\tjae %s\n"
#define JBE "\tjbe %s\n"
#define LOOP "\tloop %s\n"

// Arithmetic
#define ADD "\tadd %s, %s\n"
#define SUB "\tsub %s, %s\n"
#define SBB "\tsbb %s, %s\n"
#define IMUL "\timul %s\n"
#define MUL "\tmul %s\n"
#define IDIV "\tidiv %s\n"
#define DIV "\tdiv %s\n"
#define NEG "\tneg %s\n"
#define INC "\tinc %s\n"
#define DEC "\tdec %s\n"
#define TEST "\ttest %s, %s\n"
#define AND "\tand %s, %s\n"
#define OR "\tor %s, %s\n"
#define SETZ "\tsetz %s\n"
#define NOT "\tnot %s\n"

/* ---------- Data types ---------- */
#define DB " db ?\n"
#define DD " dd ?\n"
