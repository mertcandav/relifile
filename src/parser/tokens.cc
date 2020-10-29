#include "../../include/parser/tokens.hh"

std::string parser::tokens::inlineComment = "#";
std::string parser::tokens::lBrace = "{";
std::string parser::tokens::rBrace = "}";
std::string parser::tokens::lBrackets = "(";
std::string parser::tokens::rBrackets = ")";
std::string parser::tokens::varDefOperator = "=";
std::string parser::tokens::varConcatOperator = ":=";
std::string parser::tokens::varCallOperator = "$";
std::string parser::tokens::workflowDefine = "workflow";
std::string parser::tokens::workDefine = "work";
std::string parser::tokens::escapeSequenceOperator = "\\";
