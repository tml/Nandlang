#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <iostream>
#include "debug.h"

/// Represents a particular symbol type.
enum class Symbol {
    LITERAL, COMMA, BLOCK, IOSEP, PARENTHESIS, IDENTIFIER, ASSIGN,
    FUNCTION, WHILE, IF, VAR, LINESEP, NAND, INDEX, ELSE, NONE
};

/// Maps single character symbols to Symbol values
extern const std::map<char, Symbol> symbolMap;
/// Maps keyword identifiers to Symbol values
extern const std::map<std::string, Symbol> keywordMap;
/// Symbols that are contained within this map are blocks which can contain
/// other symbols. For example, Parentheses can contain symbols, e.g. (a, b, c)
extern const std::map<Symbol, char> symbolBlocks;

class Token;
/// A type that represents a block of tokens. Useful in case I want to change
/// the collection type to something else.
typedef std::deque<Token> TokenBlock;

/// Represents a Token. A Token is a symbol that potentially has an associated
/// value. For example, an IDENTIFIER symbol also has a string, and a LITERAL
/// symbol has a boolean value.
class Token : public Debuggable {
    Symbol m_symbol;
    std::string m_identifier; // for Identifier symbols
    bool m_value;             // for Literal symbols
    TokenBlock m_block;       // Used for enclosing symbols, e.g. braces
    size_t m_index;           // Used for index symbol
public:
    Token(Symbol, const DebugInfo&);
    Token(Symbol, bool, const DebugInfo&);
    Token(Symbol, std::string, const DebugInfo&);
    Token(Symbol, TokenBlock, const DebugInfo&);
    Token(Symbol, size_t, const DebugInfo&);
    /// Get the symbol
    Symbol getSymbol() const;
    /// Get this token's identifier
    const std::string& getIdentifier() const;
    /// Get this token's literal value.
    bool getValue() const;
    /// Get index
    size_t getIndex() const;
    /// Get this token's block
    const TokenBlock& getBlock() const;
    /// Get a mutable reference to the token block
    TokenBlock takeBlock();
    /// Set identifier
    void setIdentifier(const std::string&);
    /// Set literal value
    void setValue(bool);
};

std::ostream& operator<<(std::ostream&, const Symbol&);
std::ostream& operator<<(std::ostream&, const Token&);

/// Print out the given token block
void printBlock(const TokenBlock& block);
