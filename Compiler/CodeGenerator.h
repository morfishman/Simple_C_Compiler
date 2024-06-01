//#pragma once
//#include <stdio.h>
//#include <stdbool.h>
//#include "CodeGenerationDefenitions.h"
//#include "ParserTree.h"
//#include "SymbalTable.h"
//#include "Token.h"
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <cstdarg>
//
//
///* ---------- Classes ---------- */
//class Register {
//public:
//	std::string BIT32;
//	std::string HBIT8;
//	std::string LBIT8;
//	bool BIT8;
//	bool ARITMATIC;
//	bool inuse;
//public:
//	Register(std::string BIT32, std::string HBIT8, std::string LBIT8, bool BIT8, bool ARITMATIC)
//		: BIT32(BIT32), HBIT8(""), LBIT8(""), BIT8(BIT8), inuse(false), ARITMATIC(ARITMATIC) {
//
//		if (!HBIT8.empty()) {
//			this->HBIT8 = HBIT8;
//			this->LBIT8 = LBIT8;
//		}
//	}
//	std::string* GetName() {
//		return &BIT32;
//	}
//
//	bool InUse() {
//		return inuse;
//	}
//
//	void EndInUse() {
//		 inuse = false;
//	}
//	void SetInUse() {
//		inuse = true;
//	}
//
//};
//// Struct of the code generator
//class Code_Generator
//{
//private:
//	std::vector<Register*>* registers; // Array of registers to be used in the 
//	FILE* destFile;// A pointer to the output file for the 
//	ParseTreeNode* ast;
//	SymbalTable* symbalTable;
//	int functions_wrote;
//	int temp;
//public:
//	Code_Generator(ParseTreeNode* ast, SymbalTable* symbalTable): 
//		registers(new std::vector<Register*>()) 
//		,destFile(nullptr) , ast(ast)
//		, symbalTable(symbalTable),functions_wrote(2),
//	temp(0){}
//
//	bool init() {
//		errno_t err = fopen_s(&destFile, "output.txt", "w");
//		if (err != 0) {
//			// Handle error, for example:
//			perror("Error opening file");
//			return 1;
//		}
//		Register* r = new Register(EDI, "", "", false, false);
//		registers->push_back(r);
//		registers->push_back(new Register(ESI, "", "", false, false));
//		registers->push_back(new Register(EBX, BH, BL, true, false));
//		registers->push_back(new Register(ECX, CH, CL, true, false));
//
//		registers->push_back(new Register(EAX, AH, AL, true, true));
//		registers->push_back(new Register(EDX, DH, DL, true, true));
//		
//
//
//
//		return true;
//	}
//
//	void push_all(int number) {
//		for (size_t i = 0; i < 6; i++)
//		{
//			if (i != number) {
//				generate_push(i);
//			}
//		}
//	}
//	void pop_all(int number) {
//		for (int i = 5; i >=0 ; i--)
//		{
//			if (i != number) {
//				generate_pop(i);
//			}
//		}
//	}
//
//	int register_alloc(bool low, bool aritmatic) {
//		for (size_t i = 0; i < registers->size(); i++)
//		{
//			if (!(*registers)[i]->InUse() && (*registers)[i]->ARITMATIC == aritmatic && ((low && (*registers)[i]->BIT8 == low) || !low)) {
//				(*registers)[i]->SetInUse();
//				return i;
//			}
//		}
//		return -1;
//	}
//
//	void register_free(int r)
//	{
//		if ((*registers)[r]->InUse())(*registers)[r]->EndInUse();
//	}
//
//	std::string* register_name(int r, bool size) {
//		if (size) {
//			return &((*registers)[r]->LBIT8);
//		}
//		return (*registers)[r]->GetName();
//	}
//
//
//	std::string* label_create()
//	{
//		// A static integer to create unique labels
//		static int label_num = 0;
//		// Create label
//		char buffer[LABEL_NAME_LENGTH];
//		snprintf(buffer, LABEL_NAME_LENGTH,LABEL_FORMAT, label_num);
//		// Increment static int for next label
//		label_num++;
//		// Allocate memory for the std::string object on the heap
//		std::string* label = new std::string(buffer);
//		// Return the pointer to the dynamically allocated std::string object
//		return label;
//	}
//
//	std::string symbol_address(GenericSymbal* entry) {
//		if (entry->address != nullptr)
//			return *(entry->address);
//		// Static string for the address (to prevent allocation each time we need a symbol)
//		static char address[SYMBOL_ADDRESS_LENGTH] = { 0 };
//		// - If the entry is global, just return the identifier
//		if (entry->scope->currentScope == 0)
//		{
//			sprintf_s(address, SYMBOL_ADDRESS_LENGTH, GLOBAL_ADDRESS_FORMAT, entry->name);
//			entry->address = new std::string(address);
//			return *(entry->address);
//		}
//
//		int bp_offset = (entry->scope->used_space);
//		// Create the computed stack address for the symbol
//		if (*(entry->type) == TokenType::CHAR)
//			sprintf_s(address, SYMBOL_ADDRESS_LENGTH, "byte ptr " STACK_ADDRESS_FORMAT, bp_offset);
//		else
//			sprintf_s(address, SYMBOL_ADDRESS_LENGTH, "dword ptr " STACK_ADDRESS_FORMAT, bp_offset);
//		// Return the computed address
//		entry->address = new std::string(address);
//		return *(entry->address);
//	}
//
//	void output(const char* format, ...)
//	{
//		va_list args; // Declare a va_list type variable
//		va_start(args, format); // Initialize the va_list with the ...
//		vfprintf(destFile, format, args); // Forward ... to vfprintf
//		va_end(args); // Clean up the va_list
//	}
//
//
//	void output_data_segment()
//	{
//		std::vector<GenericSymbal*>* global_table = symbalTable->tokensInScope;
//		output(".data\n");
//		for (int i = 0; i < global_table->size(); i++)
//		{
//			Identifer* entry = dynamic_cast<Identifer*>((*global_table)[i]);
//			if (entry != nullptr) {
//				const char* format = "\t" GLOBAL_ADDRESS_FORMAT;
//				output(format , entry->name);
//				output(*(entry->type) == TokenType::CHAR ? DB : DD);
//			}
//			
//		}
//		output("\tbuffer db 0,0\n");
//		output("\tnew_line db 13, 10, 0, 0\n");
//	}
//
//
//	void generate() {
//		output("include \\masm32\\include\\masm32rt.inc\n");
//		output_data_segment();
//		output(".code\n");
//		generate_code(ast);
//		output("start:\n");
//		generate_call("main");
//		output("end start\n");
//	}
//
//	void generate_code(ParseTreeNode* treeNode) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				if (ntd->getType() == NonTerminal::PROGRAM) {
//					generate_code(ptn);
//				}
//				else {
//					generate_function(ptn);
//				}
//			}
//		}
//
//	}
//	void generate_function(ParseTreeNode* treeNode) {
//		Function* func = dynamic_cast<Function*>((*(symbalTable->tokensInScope))[functions_wrote]);
//		output(func->name.c_str());
//		output(" proc\n");
//		output("\tpush ebp\n");
//		output("\tmov ebp,esp\n");
//
//		int tempo = decl_params(func,(*(symbalTable->lowerScops))[symbalTable->scope_found]);
//		temp = tempo;
//		generate_scope((treeNode->getChildrens()[0]->getChildrens()[1]),(*(symbalTable->lowerScops))[symbalTable->scope_found]);
//		functions_wrote++;
//		symbalTable->scope_found++;
//
//		if (*(func->type) == TokenType::VOID) {
//			output("\tpop ebp\n");
//			output("\tret ");
//			if (temp - 4 != 0) {
//				output(std::to_string(temp - 4).c_str());
//			}
//			output("\n");
//		}
//		output(func->name.c_str());
//		output(" endp\n");
//	}
//
//	int decl_params(Function* f, SymbalTable* sTable) {
//		int counter = 0;
//		sTable->used_space += 4;
//		while(f->passedTypes!= nullptr && counter  < f->passedTypes->size())
//		{
//			Identifer* temp = dynamic_cast<Identifer*>((*(sTable->tokensInScope))[counter]);
//			if (temp != nullptr) {
//				code_generator_decl(sTable);
//				counter++;
//			}
//			symbol_address(temp);
//		}
//		return sTable->used_space;
//	}
//
//	void generate_scope(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				if (ntd->getType() == NonTerminal::STMT) {
//					generate_scope_stmt(ptn,sTable);
//				}
//				else {
//					generate_scope(ptn, sTable);
//				}
//			}
//		}
//	}
//
//	int generate_return(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		/// <summary>
//		/// check if its is exists in the symbal table
//		/// </summary>
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		int reg_return = COMPUTING_EXPRETION(*childrens[1], sTable);
//		if (reg_return ==-1) {
//			return -1;
//		}
//		output(MOV, EAX, register_name(reg_return, false)->c_str());
//		register_free(reg_return);
//		output("\tpop ebp\n");
//		output("\tret ");
//		if (temp - 4 != 0) {
//			output(std::to_string(temp - 4).c_str());
//		}
//		output("\n");
//		return 1;
//	}
//
//	void generate_scope_stmt(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				switch (ntd->getType())
//				{
//				case NonTerminal::LINE_STMT:
//					generate_line_stmt(ptn, sTable);
//					break;
//				case NonTerminal::CONTROL_STATEMENT:
//					CONTROL_STATEMENT(*ptn, *sTable);
//					break;
//				case NonTerminal::FUNC_CALL:
//					//here
//					push_all(-1);
//					FUNC_CALL(*ptn, *sTable, -1);
//					pop_all(-1);
//					break;
//
//				case NonTerminal::RETURN_STMT:
//					generate_return(*ptn, *sTable);
//					break;
//
//				default:
//					break;
//				}
//			}
//		}
//	}
//
//	//NEED FIX
//	void CONTROL_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		/// <summary>
//		/// check if its is exists in the symbal table
//		/// </summary>
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		SymbalTable* st;
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				switch (ntd->getType())
//				{
//				case NonTerminal::IF_STATEMENT:
//					st = ((*(sTable.lowerScops))[sTable.scope_found++]);
//					st->used_space = sTable.used_space;
//					gen_IF_STATEMENT(*ptn, *st);
//					break;
//
//				case NonTerminal::WHILE_STATEMENT:
//					st = ((*(sTable.lowerScops))[sTable.scope_found++]);
//					st->used_space = sTable.used_space;
//					gen_WHILE_STATEMENT(*ptn, *st);
//					break;
//
//				case NonTerminal::FOR_STATEMENT://kmokmolmklm
//					st = ((*(sTable.lowerScops))[sTable.scope_found++]);
//					st->used_space = sTable.used_space;
//					gen_FOR_STATEMENT(*ptn, *st );
//					break;
//
//				case NonTerminal::IF_ELSE_STATEMENT:
//					gen_IF_ELSE_STATEMENT(*ptn, sTable);
//					break;
//				default:
//					break;
//				}
//			}
//		}
//		return;
//	}
//
//	void gen_IF_ELSE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		SymbalTable* if_scope = ((*(sTable.lowerScops))[sTable.scope_found++]);
//		if_scope->used_space = sTable.used_space;
//		SymbalTable* else_scope = ((*(sTable.lowerScops))[sTable.scope_found++]);
//		else_scope->used_space = sTable.used_space;
//		ParseTreeNode* ptn1 = nullptr;
//		ParseTreeNode* scope_if = nullptr;
//		ParseTreeNode* scope_else = nullptr;
//		std::string* loop_lbl = label_create();
//		std::string* loop_lbl2 = label_create();
//		std::string* loop_exit = label_create();
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//					ptn1 = ptn;
//				}
//				else if (ntd->getType() == NonTerminal::SCOPE)
//				{
//					if (scope_if == nullptr) {
//						scope_if = ptn;
//					}
//					else {
//						scope_else = ptn;
//					}
//				}
//			}
//		}
//		output(loop_lbl->c_str());
//		output(":\n");
//		if (ptn1 != nullptr) {
//			int reg = CONTROL_EXP(*ptn1, *if_scope);
//			if (reg != -1)
//			{
//				generate_not(reg);
//				output(CMP, register_name(reg, false)->c_str(), "0");
//				output(JNE, loop_lbl2->c_str());
//				register_free(reg);
//			}
//		}
//		generate_scope(scope_if, if_scope);
//		output(JMP, loop_exit->c_str());
//
//		output(loop_lbl2->c_str());
//		output(":\n");
//		generate_scope(scope_else, else_scope);
//
//		output(loop_exit->c_str());
//		output(":\n");
//	}
//
//	void gen_IF_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		int total_size = sTable.used_space;
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//
//		ParseTreeNode* ptn1 = nullptr;
//		ParseTreeNode* scope = nullptr;
//		std::string* loop_lbl = label_create();
//		std::string* loop_exit = label_create();
//
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//					ptn1 = ptn;
//				}
//				else
//				{
//					scope = ptn;
//				}
//			}
//		}
//		output(loop_lbl->c_str());
//		output(":\n");
//		if (ptn1 != nullptr) {
//			int reg = CONTROL_EXP(*ptn1, sTable);
//			if (reg != -1)
//			{
//				generate_not(reg);
//				output(CMP, register_name(reg, false)->c_str(), "0");
//				output(JNE, loop_exit->c_str());
//				register_free(reg);
//			}
//		}
//		generate_scope(scope, &sTable);
//		output(loop_exit->c_str());
//		output(":\n");
//	}
//
//
//
//	void gen_WHILE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		int total_size = sTable.used_space;
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//
//		ParseTreeNode* ptn1 = nullptr;
//		ParseTreeNode* scope = nullptr;
//		std::string* loop_lbl = label_create();
//		std::string* loop_exit = label_create();
//
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//					ptn1 = ptn;
//				}
//				else
//				{
//					scope = ptn;
//				}
//			}
//		}
//		output(loop_lbl->c_str());
//		output(":\n");
//		if (ptn1 != nullptr) {
//			int reg = CONTROL_EXP(*ptn1, sTable);
//			if (reg != -1)
//			{
//				generate_not(reg);
//				output(CMP, register_name(reg, false)->c_str(), "0");
//				output(JNE, loop_exit->c_str());
//				register_free(reg);
//			}
//		}
//		generate_scope(scope, &sTable);
//		output(JMP, loop_lbl->c_str());
//		output(loop_exit->c_str());
//		output(":\n");
//	}
//
//
//
//	void gen_FOR_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		int total_size = sTable.used_space;
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		
//		ParseTreeNode * ptn1 = nullptr;
//		ParseTreeNode * ptn2 = nullptr;
//		ParseTreeNode * ptn3 = nullptr;
//		ParseTreeNode * scope = nullptr;
//		std::string* loop_lbl = label_create();
//		std::string* loop_exit = label_create();
//
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				if (ntd->getType() == NonTerminal::CONTROL_EXP) {
//					ptn3 = ptn;
//				}
//				else if (ntd->getType() == NonTerminal::FOR_EXP) {
//					if (ptn1 == nullptr)ptn1 = ptn;
//					else ptn2 = ptn;
//				}
//				else
//				{
//					scope = ptn;
//				}
//			}
//		}
//		if (ptn1 != nullptr) {
//			int reg = FOR_EXP(*ptn1, sTable);
//			if (reg != -1)
//			{
//				register_free(reg);
//			}
//		}
//		output(loop_lbl->c_str());
//		output(":\n");
//		if (ptn2 != nullptr) {
//			int reg = FOR_EXP(*ptn2, sTable);
//			if (reg != -1)
//			{
//				generate_not(reg);
//				output(CMP, register_name(reg, false)->c_str(), "0");
//				output(JNE, loop_exit->c_str());
//				register_free(reg);
//			}
//		}
//		generate_scope(scope, &sTable);
//		if (ptn3)
//		{
//			int reg = CONTROL_EXP(*ptn3, sTable);
//			if (reg != -1) {
//				register_free(reg);
//			}
//		}
//		output(JMP, loop_lbl->c_str());
//		output(loop_exit->c_str());
//		output(":\n");
//	}
//
//
//	int FOR_EXP(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		if (childrens.size() == 1) {
//			return -1;
//		}
//		return CONTROL_EXP(treeNode, sTable);
//	}
//
//
//	int CONTROL_EXP(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		/// <summary>
//		/// check if its is exists in the symbal table
//		/// </summary>
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		int reg = -1;
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				switch (ntd->getType())
//				{
//				case NonTerminal::ASSIGN:
//					ASSIGN(*ptn, sTable);
//					reg = 0;
//					break;
//
//				case NonTerminal::FUNC_CALL:
//					reg = register_alloc(false, false);
//					push_all(reg);
//					reg = FUNC_CALL(*ptn, sTable, reg);
//					pop_all(reg);
//					break;
//
//				case NonTerminal::VAL_CHANGE_TYPE:
//					reg = VAL_CHANGE_TYPE(*ptn, sTable);
//					break;
//				case NonTerminal::COMPUTING_EXPRETION:
//					reg = COMPUTING_EXPRETION(*ptn, sTable);
//					break;
//
//				case NonTerminal::TYPE_CONTROL_EXP:
//					if( reg != -1)
//						register_free(reg);
//					reg = CONTROL_EXP(*ptn, sTable);
//					break;
//				case NonTerminal::CONTROL_EXP:
//					if (reg != -1)
//						register_free(reg);
//					reg = CONTROL_EXP(*ptn, sTable);
//					break;
//				default:
//					break;
//				}
//			}
//		}
//		return reg;
//	}
//
//	void generate_line_stmt(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		int reg;
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				switch (ntd->getType())
//				{
//				case NonTerminal::ASSIGN:
//					ASSIGN(*ptn, *sTable);
//					break;
//
//				case NonTerminal::FUNC_CALL:
//					push_all(reg);
//					reg = FUNC_CALL(*ptn, *sTable, -1);
//					pop_all(reg);
//					register_free(reg);
//					break;
//
//				case NonTerminal::VAL_CHANGE_TYPE:
//					reg = VAL_CHANGE_TYPE(*ptn, *sTable);
//					register_free(reg);
//					break;
//
//				case NonTerminal::LINE_STMT:
//					generate_line_stmt(ptn, sTable);
//					break;
//				default:
//					break;
//				}
//			}
//		}
//	}
//
//
//	int VAL_CHANGE_TYPE(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		/// <summary>
//		/// check if its is exists in the symbal table
//		/// </summary>
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		if (childrens.size() == 1) {
//			int reg;
//			if (NonTerminalData* nonterminal = dynamic_cast<NonTerminalData*>(childrens[0]->getData())) {
//				switch (nonterminal->getType())
//				{
//				case NonTerminal::POST_ONARY_ARITMATIC:
//					reg = POST_ONARY_ARITMATICA(*(childrens[0]), sTable);
//					break;
//				case NonTerminal::PRE_ONARY_ARITMATIC:
//					reg = PRE_ONARY_ARITMATICA(*(childrens[0]), sTable);
//					break;
//				default:
//					break;
//				}
//				return reg;
//			}
//		}
//		else {
//			TokenType* leftType = nullptr;
//			TokenType* rightType = nullptr;
//			Token* identifiertoken = dynamic_cast<Token*>(childrens[0]->getData());
//			GenericSymbal* result = GetIdentifier(sTable, identifiertoken);	
//			leftType = result->type;
//
//			//computing expretion
//			NonTerminalData* rightNonterminal = dynamic_cast<NonTerminalData*>(childrens[2]->getData());
//			if (rightNonterminal == nullptr) {
//				return -1;
//			}
//			int reg = COMPUTING_EXPRETION(*childrens[2], sTable);
//			code_generator_mov_identifier_back(reg, result, *leftType);
//			return reg;
//		}
//
//	}
//
//
//
//	void ASSIGN(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		/// <summary>
//		/// check if its is exists in the symbal table
//		///          ASSIGN
//		///         /      \
//        /// DECLERATION  COMPUTING_EXPRETION
//		/// --------------------------------
//		///          ASSIGN
//		///         /      \
//        /// IDENTIFER  COMPUTING_EXPRETION
//		/// </summary>
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		TokenType* leftType = nullptr;
//		TokenType* rightType = nullptr;
//		GenericSymbal* result;
//		if (NonTerminalData* nonterminal = dynamic_cast<NonTerminalData*>(childrens[0]->getData())) {
//			 result = DECLERATION(*(childrens[0]), sTable);
//			 leftType = result->type;
//		}
//		else
//		{
//			Token* identifiertoken = dynamic_cast<Token*>(childrens[0]->getData());
//			result = GetIdentifier(sTable, identifiertoken);	
//			leftType = result->type;
//		}
//
//		//computing expretion
//		NonTerminalData* rightNonterminal = dynamic_cast<NonTerminalData*>(childrens[2]->getData());
//		if (rightNonterminal == nullptr) {
//			return;
//		}
//		int reg = COMPUTING_EXPRETION(*childrens[2], sTable);
//		code_generator_mov_identifier_back(reg, result, *leftType);
//		register_free(reg);
//	}
//
//	GenericSymbal* DECLERATION(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		/// <summary>
//		/// check if its is exists in the symbal table
//		/// 
//		///     DECLERATION:
//		///     /           \
//        /// Return_TYPE    identifer
//		/// </summary>
//
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		GenericSymbal* id = GetIdentifier(sTable, dynamic_cast<Token*>(childrens[1]->getData()));
//		code_generator_decl(&sTable);
//		return id;
//	}
//
//	void PASSED_PARAMS(ParseTreeNode& treeNode, SymbalTable& sTable, std::vector<TokenType*>* returnal) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		ParseTreeNode* ptn2 = nullptr;
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				TokenType* toAdd = nullptr;
//				switch (ntd->getType())
//				{
//
//				case NonTerminal::COMPUTING_EXPRETION:
//					toAdd = ptn->getType();
//					if (toAdd == nullptr) {
//						returnal = nullptr;
//						return;
//					}
//					ptn2 = ptn;
//					returnal->push_back(toAdd);
//					break;
//
//				case NonTerminal::PASS_PARAM:
//					PASSED_PARAMS(*ptn, sTable, returnal);
//					break;
//
//				default:
//					returnal = nullptr;
//					return;
//
//				}
//			}
//		}
//		if (ptn2 != nullptr) {
//			int reg = COMPUTING_EXPRETION(*ptn2, sTable);
//			generate_push(reg);
//			register_free(reg);
//		}
//	}
//
//	int FUNC_CALL(ParseTreeNode& treeNode, SymbalTable& sTable, int reg_number) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		//param vector
//		std::vector<TokenType*>* returnal = new std::vector<TokenType*>();
//		if (childrens.size() > 3) {
//			PASSED_PARAMS(*childrens[2], sTable, returnal);
//			if (returnal == nullptr) {
//				return false;
//			}
//		}
//		//
//		GenericSymbal* func = GetFunction(sTable, dynamic_cast<Token*>(childrens[0]->getData()), returnal);
//		if (func->name == "get_c") {
//			
//			output("\tpush eax\n");
//			output(XOR,EAX,EAX);
//			output("\tpush offset new_line+2\n");
//			output("\tcall StdOut\n");
//			output("\tpush 1\n");
//			output("\tpush offset buffer\n");
//			output("\tcall StdIn\n");
//			output("\tpush offset new_line+2\n");
//			output("\tcall StdOut\n");
//
//			output("\tmov al, byte ptr [buffer]\n");
//			output("\tsub al, '0' \n");
//			if (reg_number != -1) {
//				output(MOV, register_name(reg_number, false)->c_str(), EAX);
//			}
//			output("\tpop eax\n");
//			return reg_number;
//		}
//		else if (func->name == "print_c") {
//			output(POP, EDX);
//			output("\tpush eax\n");
//			output(MOV, EAX, EDX);
//			output(ADD, AL, "\'0\'");
//			output(MOV, "[buffer]", AL);
//			output(PUSH, "offset buffer");
//			output(CALL, "StdOut");
//			output("\tpush offset new_line\n");
//			output("\tcall StdOut\n");
//			output("\tpop eax\n");
//			return reg_number;
//		}
//		else {
//			if (*(func->type) == TokenType::VOID) {
//				return -1;
//			}
//			generate_call(func->name);
//			if (reg_number != -1) {
//				output(MOV, register_name(reg_number, false)->c_str(), EAX);
//			}
//			return reg_number;
//		}
//	}
//
//	GenericSymbal* GetFunction(SymbalTable& sTable, Token* token, std::vector<TokenType*>* passed_param) {
//		GenericSymbal* returnal = sTable.searchFunction(token, passed_param);
//		returnal = returnal == nullptr ? symbalTable->searchFunctionInLowerScopes(token, sTable.currentScope, passed_param) : returnal;
//		return returnal;
//	}
//
//	GenericSymbal* GetIdentifier(SymbalTable& sTable, Token* token) {
//		GenericSymbal* returnal = sTable.searchIdentifier(token->getValue());
//		returnal = returnal == nullptr ? symbalTable->searchIdentifierInLowerScopes(token->getValue(), sTable.currentScope) : returnal;
//		return returnal;
//	}
//
//	int COMPUTING_EXPRETION(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		int buffer = -1;
//		for (ParseTreeNode* ptn : childrens) {
//			NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//			if (ntd != nullptr) {
//				switch (ntd->getType())
//				{
//				case NonTerminal::ARITMATIC:
//					buffer = generate_aritmatic(ptn, &sTable);
//					break;
//				case NonTerminal::BOOL_EXPRETION:
//					buffer = generate_bool_expretion(ptn, &sTable);
//					break;
//				default:
//					break;
//				}
//
//			}
//		}
//		return buffer;
//	}
//
//	int generate_bool_expretion(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		if (childrens.size() == 1) {
//			return generate_bool_cmp(childrens[0], sTable);
//		}
//		bool and_sign = false;
//		int cmp1 = -1;
//		int cmp2 = -1;
//		for (ParseTreeNode* ptn : childrens) {
//			{
//			
//			
//				NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//				if (ntd != nullptr) {
//					TokenType* gs;
//					ParseTreeNode* child;
//					Token* t;
//					switch (ntd->getType())
//					{
//					case NonTerminal::BOOL_CMP:
//						if (cmp1 == -1) {
//							cmp1 = generate_bool_cmp(ptn, sTable);
//						}
//						else {
//							cmp2 = generate_bool_cmp(ptn, sTable);
//						}
//						break;
//					case NonTerminal::BOOLEAN_COMBO:
//						child = ptn->getChildrens()[0];
//						t = dynamic_cast<Token*>(child->getData());
//						if (TokenType::LOGICAL_AND == t->tokenType) {
//							and_sign = true;
//						}
//						break;
//					case NonTerminal::BOOL_EXPRETION:
//						if (cmp1 == -1) {
//							cmp1 = generate_bool_expretion(ptn, sTable);
//						}
//						else {
//							cmp2 = generate_bool_expretion(ptn, sTable);
//						}
//					default:
//						break;
//					}
//				}
//			}
//
//		}
//
//		if (and_sign) {
//			output(XOR, EAX, EAX);
//			output(TEST, register_name(cmp1, false)->c_str(), register_name(cmp1, false)->c_str());
//			output(SETZ, AL);
//			output(MOV, register_name(cmp1, false)->c_str(), EAX);
//			generate_not(cmp1);
//
//			output(XOR, EAX, EAX);
//			output(TEST, register_name(cmp2, false)->c_str(), register_name(cmp2, false)->c_str());
//			output(SETZ, AL);
//			output(MOV, register_name(cmp2, false)->c_str(), EAX);
//			generate_not(cmp2);
//
//			output(AND, register_name(cmp1, false)->c_str(), register_name(cmp2, false)->c_str());
//
//		}
//		else {
//			output(XOR, EAX, EAX);
//			output(TEST, register_name(cmp1, false)->c_str(), register_name(cmp1, false)->c_str());
//			output(SETZ, AL);
//			output(MOV, register_name(cmp1, false)->c_str(), EAX);
//			generate_not(cmp1);
//
//			output(XOR, EAX, EAX);
//			output(TEST, register_name(cmp2, false)->c_str(), register_name(cmp2, false)->c_str());
//			output(SETZ, AL);
//			output(MOV, register_name(cmp2, false)->c_str(), EAX);
//			generate_not(cmp2);
//
//			output(OR, register_name(cmp1, false)->c_str(), register_name(cmp2, false)->c_str());
//		}
//		register_free(cmp2);
//		return cmp1;
//
//	}
//
//
//	int generate_bool_cmp(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		if (childrens.size() == 1) {
//			return generate_expr(childrens[0], sTable);
//		}
//		int exp1=-1;
//		int exp2;
//		std::string cmp;
//		
//
//
//
//		for (ParseTreeNode* ptn : childrens) {
//			{
//				
//				NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//				if (ntd != nullptr) {
//					TokenType* gs;
//					ParseTreeNode* child;
//					Token* t;
//					switch (ntd->getType())
//					{
//					case NonTerminal::BOOL_CMP:
//						//error msg
//						break;
//					case NonTerminal::EXPR:
//						if (exp1 == -1) {
//							exp1 = generate_expr(ptn, sTable);
//						}
//						else {
//							exp2 = generate_expr(ptn, sTable);
//						}
//						break;
//					case NonTerminal::BOOLEAN_COMPERSION:
//						child = ptn->getChildrens()[0];
//						t = dynamic_cast<Token*>(child->getData());
//						if (TokenType::EQUAL == t->tokenType) {
//							cmp = JE;
//						}
//						else if (TokenType::NOT_EQUAL == t->tokenType) {
//							cmp = JNE;
//						}else if (TokenType::GREATER_THAN_OR_EQUAL == t->tokenType) {
//							cmp = JAE;
//						}else if (TokenType::LESS_THAN_OR_EQUAL == t->tokenType) {
//							cmp = JBE;
//						}
//					default:
//						break;
//					}
//				}
//
//			
//			}
//
//		}
//
//		std::string* lbl = label_create();
//		std::string* skip = label_create();
//		output(CMP, register_name(exp1, false)->c_str(), register_name(exp2, false)->c_str());
//		output(cmp.c_str(), lbl->c_str());
//		output(MOV, register_name(exp1, false)->c_str(), "0");
//		output(JMP,skip->c_str());
//		
//
//		output(lbl->c_str());
//		output(": \n");
//		output(MOV, register_name(exp1, false)->c_str(), "1");
//		output(skip->c_str());
//		output(": \n");
//
//		register_free(exp2);
//		return exp1;
//	}
//
//	int generate_expr(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		int ARITMATIC;
//		for (ParseTreeNode* ptn : childrens) {
//			{
//				NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//				if (ntd != nullptr) {
//					TokenType* gs;
//					switch (ntd->getType())
//					{
//					case NonTerminal::ARITMATIC:
//						ARITMATIC = generate_aritmatic(ptn, sTable);
//						break;
//					case NonTerminal::BOOL_EXPR:
//						ARITMATIC = generate_aritmatic(ptn, sTable);
//						generate_not(ARITMATIC);
//						break;
//					default:
//						break;
//					}
//				}
//				
//			}
//
//		}
//		return ARITMATIC;
//	}
//
//	void generate_not(int reg) {
//		output(XOR, EAX, EAX);
//		output(ADD, EAX, register_name(reg, false)->c_str());
//		output(SETZ, DL);
//		output(XOR, EAX, EAX);
//		output(MOV, AL, DL);
//		output(MOV,register_name(reg, false)->c_str(), EAX);
//	}
//
//	int generate_f(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		for (ParseTreeNode* ptn : childrens) {
//			{
//				if (Token* t = dynamic_cast<Token*>(ptn->getData())) {
//					GenericSymbal* gos;
//					int reg_num;
//					switch (t->getType())
//					{
//					case TokenType::IDENTIFIER:
//						gos = GetIdentifier(*sTable, t);
//						if (*(treeNode->getType()) == TokenType::INT) {
//							reg_num = register_alloc(false, false);
//						}
//						else {
//							reg_num = register_alloc(true, false);
//						}
//						code_generator_mov_identifier(reg_num, gos, *(treeNode->getType()));
//						return reg_num;
//					case TokenType::NUMERIC:
//						reg_num = register_alloc(false, false);
//						code_generator_mov_literal(reg_num, t);
//						return reg_num;
//					case TokenType::CHAR_LITTERAL:
//						reg_num = register_alloc(true, false);
//						code_generator_mov_literal(reg_num, t);
//						return reg_num;
//					case TokenType::LEFT_BRACKET:
//						break;
//					default:
//						break;
//					}
//				}
//				else {
//					int reg_number;
//					NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//					TokenType* gs;
//					switch (ntd->getType())
//					{
//					case NonTerminal::FUNC_CALL:
//						reg_number = register_alloc(false, false);
//						push_all(reg_number);
//						reg_number = FUNC_CALL(*ptn, *sTable, reg_number);
//						pop_all(reg_number);
//						return reg_number;
//					case NonTerminal::POST_ONARY_ARITMATIC:
//						return POST_ONARY_ARITMATICA(*ptn, *sTable);
//					case NonTerminal::PRE_ONARY_ARITMATIC:
//						return PRE_ONARY_ARITMATICA(*ptn, *sTable);
//					case NonTerminal::ARITMATIC:
//						return generate_aritmatic(ptn, sTable);
//					default:
//						break;
//					}
//
//				}
//			}
//
//		}
//	}
//	int POST_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		int reg = 0;
//		bool inc = false;
//		GenericSymbal* gs = nullptr;
//		if (!childrens.empty()) {
//			if (Token* t = dynamic_cast<Token*>(childrens[1]->getData())) {
//				Token* SIGN = dynamic_cast<Token*>(childrens[0]->getChildrens()[0]->getData());
//				gs = GetIdentifier(sTable, t);
//				int reg_num;
//				if (*(gs->type) == TokenType::INT) {
//					reg_num = register_alloc(false, false);
//				}
//				else {
//					reg_num = register_alloc(true, false);
//				}
//				reg = reg_num;
//		
//				
//				if (SIGN->getType() == TokenType::INCREMENT) {
//					inc = true;
//				}
//			
//			
//			}
//		}
//		code_generator_mov_identifier(reg, gs, *(gs->type));
//		if (inc) {
//			output(INC, register_name(reg, false)->c_str());
//			code_generator_mov_identifier_back(reg, gs, *(gs->type));
//		}
//		else {
//			output(DEC, register_name(reg, false)->c_str());
//			code_generator_mov_identifier_back(reg, gs, *(gs->type));
//		}
//		
//		return reg;
//	}
//	int PRE_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode.getChildrens();
//		int reg = 0;
//		bool inc = false;
//		GenericSymbal* gs = nullptr;
//		if (!childrens.empty()) {
//			if (Token* t = dynamic_cast<Token*>(childrens[0]->getData())) {
//				Token* SIGN = dynamic_cast<Token*>(childrens[1]->getChildrens()[0]->getData());
//				gs = GetIdentifier(sTable, t);
//				int reg_num;
//				if (*(gs->type) == TokenType::INT) {
//					reg_num = register_alloc(false, false);
//				}
//				else {
//					reg_num = register_alloc(true, false);
//				}
//				reg = reg_num;
//
//
//				if (SIGN->getType() == TokenType::INCREMENT) {
//					inc = true;
//				}
//
//
//			}
//		}
//		code_generator_mov_identifier(reg, gs, *(gs->type));
//		if (inc) {
//			output(INC, register_name(reg, false)->c_str());
//			code_generator_mov_identifier_back(reg, gs, *(gs->type));
//			output(DEC, register_name(reg, false)->c_str());
//		}
//		else {
//			output(DEC, register_name(reg, false)->c_str());
//			code_generator_mov_identifier_back(reg, gs, *(gs->type));
//			output(INC, register_name(reg, false)->c_str());
//		}
//		return reg;
//	}
//
//
//	int generate_aritmatic(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		int ARITMATIC = -1;
//		ParseTreeNode* aritmatic_ptn = nullptr;
//		int T = -1;
//		ParseTreeNode* t_ptn = nullptr;
//		
//		bool add = false;
//
//		
//		for (ParseTreeNode* ptn : childrens) {
//			{
//				if (Token* t = dynamic_cast<Token*>(ptn->getData())) {
//					GenericSymbal* gos;
//					switch (t->getType())
//					{
//					case TokenType::PLUS:
//						add = true;
//						break;
//					case TokenType::MINUS:
//						add = false;
//						break;
//					default:
//						break;
//					}
//				}
//				else {
//					NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//					TokenType* gs;
//					switch (ntd->getType())
//					{
//					case NonTerminal::ARITMATIC:
//						aritmatic_ptn = ptn;
//						break;
//					case NonTerminal::T:
//						t_ptn = ptn;
//						break;
//					default:
//						break;
//					}
//
//				}
//			}
//
//		}
//
//		if (aritmatic_ptn == nullptr) {
//			return generate_t(t_ptn, sTable);;
//		}
//		
//		if (aritmatic_ptn->getMaxDepgh() > t_ptn->getMaxDepgh()) {
//			ARITMATIC = generate_aritmatic(aritmatic_ptn, sTable);
//			T = generate_t(t_ptn, sTable);
//		}
//		else {
//			T = generate_t(t_ptn, sTable);
//			ARITMATIC = generate_aritmatic(aritmatic_ptn, sTable);
//		}
//		
//		
//		
//		if (add) {
//			generate_add(ARITMATIC, T);
//		}
//		else {
//			generate_sub(ARITMATIC, T);
//		}
//		register_free(T);
//		return ARITMATIC;
//	}
//
//	int generate_t(ParseTreeNode* treeNode, SymbalTable* sTable) {
//		std::vector<ParseTreeNode*> childrens = treeNode->getChildrens();
//		int T = -1;
//		ParseTreeNode* t_ptn = nullptr;
//		int F = -1;
//		ParseTreeNode* f_ptn = nullptr;
//		bool mul = false;
//		bool div = false;
//		bool  mod = false;
//		for (ParseTreeNode* ptn : childrens) {
//			{
//				if (Token* t = dynamic_cast<Token*>(ptn->getData())) {
//					GenericSymbal* gos;
//					switch (t->getType())
//					{
//					case TokenType::STAR:
//						mul = true;
//						break;
//					case TokenType::DIVIDE:
//						div = true;
//						break;
//					case TokenType::MODULO:
//						mod = true;
//						break;
//					default:
//						break;
//					}
//				}
//				else {
//					NonTerminalData* ntd = dynamic_cast<NonTerminalData*>(ptn->getData());
//					TokenType* gs;
//					switch (ntd->getType())
//					{
//					case NonTerminal::F:
//						f_ptn = ptn;
//						
//						break;
//					case NonTerminal::T:
//						t_ptn = ptn;
//						break;
//					default:
//						break;
//					}
//
//				}
//			}
//		}
//		if (t_ptn == nullptr) {
//			return generate_f(f_ptn,sTable);
//		}
//
//		if (f_ptn->getMaxDepgh() > t_ptn->getMaxDepgh()) {
//			F = generate_f(f_ptn, sTable);
//			T = generate_t(t_ptn, sTable);
//		}
//		else {
//			T = generate_t(t_ptn, sTable);
//			F = generate_f(f_ptn, sTable);
//		}
//
//
//		if (mul) {
//			generate_mul(T, F);
//		}
//		else if (div) {
//			generate_div(T, F);
//		}
//		else {
//			generate_mod(T, F);
//		}
//		register_free(F);
//		return T;
//	}
//
//	void generate_mul(int reg_one, int reg_two) {
//		
//		output(MOV, EAX, register_name(reg_one, false)->c_str());
//		output(XOR, EDX, EDX);
//		output(MUL, register_name(reg_two, false)->c_str());
//		output(MOV, register_name(reg_one, false)->c_str(), EAX);
//		
//	}
//	void generate_div(int reg_one, int reg_two) {
//	
//		output(MOV, EAX, register_name(reg_one, false)->c_str());
//		output(XOR, EDX, EDX);
//		output(DIV, register_name(reg_two, false)->c_str());
//		output(MOV, register_name(reg_one, false)->c_str(), EAX);
//		
//	}
//
//	void generate_mod(int reg_one, int reg_two) {
//	
//		output(MOV, EAX, register_name(reg_one, false)->c_str());
//		output(XOR, EDX, EDX);
//		output(DIV, register_name(reg_two, false)->c_str());
//		output(MOV, register_name(reg_one, false)->c_str(), EDX);
//		
//	}
//
//	void generate_add(int reg_one, int reg_two) {
//		output(ADD, register_name(reg_one, false)->c_str(), register_name(reg_two, false)->c_str());
//	}
//
//	void generate_sub(int reg_one, int reg_two) {
//		output(SUB, register_name(reg_one, false)->c_str(), register_name(reg_two, false)->c_str());
//	}
//
//	void generate_push(int reg) {
//		output(PUSH, register_name(reg, false)->c_str());
//	}
//	void generate_pop(int reg) {
//		output(POP, register_name(reg, false)->c_str());
//	}
//	void generate_call(std::string function_name) {
//		output(CALL, function_name.c_str());
//	}
//
//	void code_generator_decl(SymbalTable* sTable)
//	{
//		if (*((*(sTable->tokensInScope))[sTable->found++]->type) == TokenType::CHAR) {
//			sTable->used_space += 4;
//		}
//		else {
//			sTable->used_space += 4;
//		}
//		
//	}
//	
//	void code_generator_mov_literal(int register_number, Token* token)
//	{
//		if (token->getType() == TokenType::CHAR_LITTERAL) {
//			output(XOR, register_name(register_number, false)->c_str(), register_name(register_number, false)->c_str());
//			output(MOV, register_name(register_number, true)->c_str(),
//				("'" + token->getValue() + "'").c_str());
//		}
//		else {
//			output(MOV, register_name(register_number, false)->c_str(),
//				(token->getValue()).c_str());
//		}
//	}
//
//	void code_generator_mov_identifier(int register_number, GenericSymbal* identifier, TokenType type)
//	{
//		if (type == TokenType::CHAR)
//		{
//			output(XOR, register_name(register_number,false)->c_str(), register_name(register_number,false)->c_str());
//			// Mov the value to the lower byte of the register
//			output("\tmov %s, %s\n", register_name(register_number,true)->c_str(),
//				symbol_address(identifier).c_str());
//		}
//		// If the type of the identifier is not char (int)
//		else {
//			output(MOV, register_name(register_number,false)->c_str(),
//				symbol_address(identifier).c_str());
//		}
//	}
//
//	void code_generator_mov_identifier_back(int register_number, GenericSymbal* identifier, TokenType type)
//	{
//		if (type == TokenType::CHAR)
//		{
//			// Mov the value to the lower byte of the register
//			output("\tmov byte ptr %s, %s\n", symbol_address(identifier).c_str(),register_name(register_number, true)->c_str());
//		}
//		// If the type of the identifier is not char (int)
//		else {
//			output(MOV,symbol_address(identifier).c_str(), register_name(register_number, false)->c_str());
//		}
//	}
//
//};
//


#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdarg>
#include <vector>
#include <string>
#include "CodeGenerationDefenitions.h"
#include "ParserTree.h"
#include "SymbalTable.h"
#include "Token.h"

class Register {
public:
	std::string BIT32;
	std::string HBIT8;
	std::string LBIT8;
	bool BIT8;
	bool ARITMATIC;
	bool inuse;

public:
	Register(std::string BIT32, std::string HBIT8, std::string LBIT8, bool BIT8, bool ARITMATIC);
	std::string* GetName();
	bool InUse();
	void EndInUse();
	void SetInUse();
};

class Code_Generator {
private:
	std::vector<Register*>* registers;
	FILE* destFile;
	ParseTreeNode* ast;
	SymbalTable* symbalTable;
	int functions_wrote;
	int temp;
	int found_num;
	std::string* f_num_addr;
public:
	Code_Generator(ParseTreeNode* ast, SymbalTable* symbalTable);
	bool init(std::string* file_name);
	void push_all(int number);
	void setup_sp_down_by_num(SymbalTable* sTable, int number);
	void update_sp_up_by_number(SymbalTable* sTable, int number);
	void update_sp_down(SymbalTable* sTable);
	void setup_sp_down(SymbalTable* sTable,bool func);
	void update_sp_up(SymbalTable* sTable);
	void pop_all(int number);
	int register_alloc(bool low, bool aritmatic);
	void register_free(int r);
	std::string* register_name(int r, bool size);
	std::string* label_create();
	std::string symbol_address(GenericSymbal* entry);
	void output(const char* format, ...);
	void output_data_segment();
	void generate();
	void generate_code(ParseTreeNode* treeNode);
	void generate_function(ParseTreeNode* treeNode);
	int decl_params(Function* f, SymbalTable* sTable);
	void generate_scope(ParseTreeNode* treeNode, SymbalTable* sTable);
	int generate_return(ParseTreeNode& treeNode, SymbalTable& sTable);
	void generate_scope_stmt(ParseTreeNode* treeNode, SymbalTable* sTable);
	void CONTROL_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
	void gen_IF_ELSE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
	void gen_IF_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
	void gen_WHILE_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
	void gen_FOR_STATEMENT(ParseTreeNode& treeNode, SymbalTable& sTable);
	int FOR_EXP(ParseTreeNode& treeNode, SymbalTable& sTable);
	int CONTROL_EXP(ParseTreeNode& treeNode, SymbalTable& sTable);
	void generate_line_stmt(ParseTreeNode* treeNode, SymbalTable* sTable);
	int VAL_CHANGE_TYPE(ParseTreeNode& treeNode, SymbalTable& sTable);
	void ASSIGN(ParseTreeNode& treeNode, SymbalTable& sTable);
	GenericSymbal* DECLERATION(ParseTreeNode& treeNode, SymbalTable& sTable);
	void PASSED_PARAMS(ParseTreeNode& treeNode, SymbalTable& sTable, std::vector<TokenType*>* returnal);
	int FUNC_CALL(ParseTreeNode& treeNode, SymbalTable& sTable, int reg_number);
	GenericSymbal* GetFunction(SymbalTable& sTable, Token* token, std::vector<TokenType*>* passed_param);
	GenericSymbal* GetIdentifier(SymbalTable& sTable, Token* token);
	int COMPUTING_EXPRETION(ParseTreeNode& treeNode, SymbalTable& sTable);
	int generate_bool_expretion(ParseTreeNode* treeNode, SymbalTable* sTable);
	int generate_bool_cmp(ParseTreeNode* treeNode, SymbalTable* sTable);
	int generate_expr(ParseTreeNode* treeNode, SymbalTable* sTable);
	void generate_not(int reg);
	int generate_f(ParseTreeNode* treeNode, SymbalTable* sTable);
	int POST_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable);
	int PRE_ONARY_ARITMATICA(ParseTreeNode& treeNode, SymbalTable& sTable);
	int generate_aritmatic(ParseTreeNode* treeNode, SymbalTable* sTable);
	int generate_t(ParseTreeNode* treeNode, SymbalTable* sTable);
	void generate_mul(int reg_one, int reg_two);
	void generate_div(int reg_one, int reg_two);
	void generate_mod(int reg_one, int reg_two);
	void generate_add(int reg_one, int reg_two);
	void generate_sub(int reg_one, int reg_two);
	void generate_push(int reg);
	void generate_pop(int reg);
	void generate_call(std::string function_name);
	void code_generator_decl(SymbalTable* sTable);
	void code_generator_mov_literal(int register_number, Token* token);
	void code_generator_mov_identifier(int register_number, GenericSymbal* identifier, TokenType type);
	void code_generator_mov_identifier_back(int register_number, GenericSymbal* identifier, TokenType type);
};

