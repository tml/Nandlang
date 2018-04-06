#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include <memory>
#include "debug.h"

/// Special identifier used for ignoring parts of a function's output
extern const std::string ignoreIdentifier;

class State;

/// An expression. An expression has inputs and outputs.
class Expression : public Debuggable {
public:
    virtual void resolve(State&) const = 0;
    virtual uint64_t getInputNum(State&) const = 0;
    virtual uint64_t getOutputNum(State&) const = 0;
    /// Check the expression to ensure consistency and integrity.
    /// Throws an exception on failure.
    virtual void check(State&) const = 0;
};

typedef std::unique_ptr<Expression> ExpressionPtr;

size_t countOutputs(State& state, const std::vector<ExpressionPtr>& expressions);
void checkExpressions(State& state, const std::vector<ExpressionPtr>& expressions);

/// A NAND expression. NANDS two values together
class ExpressionNand : public Expression {
    ExpressionPtr m_left;
    ExpressionPtr m_right;
public:
    ExpressionNand(ExpressionPtr&&, ExpressionPtr&&);
    void resolve(State&) const override;
    uint64_t getInputNum(State&) const override;
    uint64_t getOutputNum(State&) const override;
    void check(State&) const override;
};

/// A function expression. Calls a function when evaluated
class ExpressionFunction : public Expression {
    std::string m_functionName;
    std::vector<ExpressionPtr> m_arguments;
public:
    ExpressionFunction(const std::string&, std::vector<ExpressionPtr>&&);
    void resolve(State&) const override;
    uint64_t getInputNum(State&) const override;
    uint64_t getOutputNum(State&) const override;
    void check(State&) const override;
};

/// A variable expression. Represents a variable
class ExpressionVariable : public Expression {
    std::string m_name;
public:
    ExpressionVariable(const std::string&);
    void resolve(State&) const override;
    uint64_t getInputNum(State&) const override;
    uint64_t getOutputNum(State&) const override;
    void check(State&) const override;
};

/// A literal expression
class ExpressionLiteral : public Expression {
    bool m_value;
public:
    ExpressionLiteral(bool);
    void resolve(State&) const override;
    uint64_t getInputNum(State&) const override;
    uint64_t getOutputNum(State&) const override;
    void check(State&) const override;
};
