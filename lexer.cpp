#include "lexer.h"

#include <cctype>

Lexer::Lexer(std::string_view source)
:   m_current(0),
    m_line(0),
    m_col(0),
    m_source(source)
{}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        uint64_t start = m_current;

        auto curr = advance();
        if (!curr.has_value()) break;

        auto next = peek();
        if (next.has_value()) {
            auto token = matchDouble(*curr, *next, start);
            if (token.has_value()) {
                tokens.emplace_back(*token);
                continue;
            }
        }
        auto token = matchSingle(*curr, start);
        if (token.has_value()) {
            tokens.emplace_back(*token);
            continue;
        }
        if ( std::isdigit(*curr) ) {
            while (!isAtEnd()) {
                auto next = advance();
                if (
                    !next.has_value()
                    or !std::isdigit(*next)
                    ) break;
            }
            Span span = { start, m_current };
            Token token = { Number, span };
            tokens.push_back(token);
            continue;
        }
        if ( std::isalpha(*curr) ) {
            while (!isAtEnd()) {
                auto next = advance();
                if (!next.has_value()
                    or !std::isalpha(*next)
                    ) break;
            }
            Span span = { start, m_current };
            std::string_view str = m_source.substr(start, m_current);
            TokenKind kind = [str, this]() -> TokenKind {
                if (m_keywords.contains(str)) {
                    return m_keywords[str];
                }
                return Identifier;
            }();
            Token token = { kind, span };
            tokens.push_back(token);
        }
        // TODO: Error handling here
    }
    return tokens;
}

std::optional<Token> Lexer::matchSingle(char curr, uint64_t start) {
    auto kind = [curr]() -> std::optional<TokenKind> {
        switch (curr) {
            case '=': return Assign;
            case '+': return Add;
            case '-': return Sub;
            case '*': return Mul;
            case '/': return Div;

            case ':': return Colon;
            case ';': return Semicolon;

            case '{': return OpenBody;
            case '}': return CloseBody;

            case '(': return OpenParen;
            case ')': return CloseParen;

            default: return std::nullopt;
        }
    }();
    if (kind.has_value()) {
        return Token{ *kind, {start, m_current} };
    }
    return std::nullopt;
}

constexpr uint16_t pack2(char c1, char c2) {
    return static_cast<uint16_t>(c1) << 8 | c2;
}

std::optional<Token> Lexer::matchDouble(char curr, char next, uint64_t start) {
    auto kind = [curr, next]() -> std::optional<TokenKind> {
        uint16_t comb = pack2(curr, next);
        switch (comb) {
            case pack2('=', '='): return Equal;

            case pack2('+', '='): return AddAssign;
            case pack2('+', '+'): return Increment;

            case pack2('-', '='): return SubAssign;
            case pack2('-', '-'): return Decrement;

            case pack2('*', '='): return MulAssign;
            case pack2('/', '='): return DivAssign;

            default: return std::nullopt;
        }
    }();
    if (kind.has_value()) {
        advance();
        return Token{ *kind, {start, m_current} };
    }
    return std::nullopt;
}

std::optional<char> Lexer::advance() {
    if (isAtEnd()) return std::nullopt;
    char c = m_source[m_current];
    m_current++;
    m_col++;
    if (c == '\n') {
        m_line++;
        m_col = 0;
    }
    return c;
}

std::optional<char> Lexer::next() {
    if (m_current + 1 >= m_source.size()) return std::nullopt;
    return m_source[m_current + 1];
}

std::optional<char> Lexer::peek() {
    if (isAtEnd()) return std::nullopt;
    return m_source[m_current];
}

bool Lexer::isAtEnd() {
    return m_current >= m_source.size();
}
