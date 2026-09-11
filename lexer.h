#ifndef MISH_LEXER_H
#define MISH_LEXER_H
#include <cstdint>
#include <string_view>

enum TokenKind {
    // 0-9
    Number,
    // <a-0-9-z>, <A-0-9-Z>
    Identifier,
    // =
    Assign,
    // +
    Add,
    // +=
    AddAssign,
    // ++
    Adds,
    // -
    Sub,
    // -=
    SubAssign,
    // --
    Subs,
    // *
    Mul,
    // *=
    MulAssign,
    // /
    Div,
    // /=
    DivAssign,
    // ;
    Semicolon,
    // :
    Colon,
    // .
    Period,
    // {
    OpenBody,
    // }
    CloseBody,
    // (
    OpenParen,
    // )
    CloseParen,
    EOF,
};

struct Span {
    uint64_t start;
    uint64_t end;
};

struct Token {
    TokenKind kind;
    Span span;
};

class Lexer {
public:
    Lexer(std::string_view source);
private:
    uint64_t m_current;
    uint64_t m_line;
    uint64_t m_col;
    std::string_view m_source;
};


#endif //MISH_LEXER_H
