#ifndef MISH_LEXER_H
#define MISH_LEXER_H
#include <cstdint>
#include <optional>
#include <string_view>
#include <unordered_map>
#include <vector>

enum TokenKind {
    // 0-9
    Number,
    // <a-0-9-z>, <A-0-9-Z>
    Identifier,
    KwLet,
    KwFn,
    // =
    Assign,
    // ==
    Equal,
    // +
    Add,
    // +=
    AddAssign,
    // ++
    Increment,
    // -
    Sub,
    // -=
    SubAssign,
    // --
    Decrement,
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
    explicit Lexer(std::string_view source);

    std::vector<Token> tokenize();
private:
    uint64_t m_current;
    uint64_t m_line;
    uint64_t m_col;
    std::string_view m_source;

    std::optional<Token> matchSingle(char curr, uint64_t start);
    std::optional<Token> matchDouble(char curr, char next, uint64_t start);

    std::optional<char> advance();
    std::optional<char> next();
    std::optional<char> peek();
    bool isAtEnd();

    std::unordered_map<std::string_view, TokenKind> m_keywords = {
        { "let", KwLet },
        { "fn", KwFn },
    };
};

#endif //MISH_LEXER_H
