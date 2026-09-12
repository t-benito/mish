#ifndef MISH_PARSER_HPP
#define MISH_PARSER_HPP
#include <memory>

#include "lexer.hpp"

struct Node;

enum class Tag {
    BinaryOpAdd,
    BinaryOpSub,
    BinaryOpMul,
    BinaryOpDiv,

    UnaryOpNegate,
    UnaryOpNot,
    UnaryOpAddrOf,
    UnaryOpDeref,

    Assign,
    AddAssign,
    SubAssign,
    MulAssign,
    DivAssign,

    VarDeclaration,
};

union Data {
    struct BinaryOp {
        Node* lhs;
        Node* rhs;
    };

    struct UnaryOp {
        Node* target;
        Node* value;
    };

    struct VarDeclaration {
        char* name;
        Node* value;
    };
};

struct Node {
    Tag tag;
    Data data;
    Span span;
};

class Parser {
public:
    Parser(std::vector<Token>& tokens);

    std::vector<Node>& parse();
private:
    std::vector<Token> m_tokens;

    uint64_t m_current;

    std::unique_ptr<Node> parseStmt(Token* token);
    std::unique_ptr<Node> parseExpr(Token* token);

    Token* advance();
    Token* match(TokenKind expected);
    Token* peek();
    Token* next();

    bool isAtEnd();
};

#endif //MISH_PARSER_HPP
