#include "parser.hpp"

Parser::Parser(std::vector<Token>& tokens)
:   m_tokens(tokens),
    m_current(0)
{}

std::vector<Node> &Parser::parse() {
    std::vector<Node> ast;

    while (!isAtEnd()) {
        Token* token = advance();
        std::unique_ptr<Node> stmt = parseStmt(token);

        if (stmt == nullptr) {
            // error handling.... synchronization here
        }

    }
}

std::unique_ptr<Node> Parser::parseStmt(Token *token) {
    switch (token->kind) {
        case TokenKind::KwLet:
            break;
        default: return nullptr;
    }
}

std::unique_ptr<Node> Parser::parseExpr(Token *token) {

}

Token* Parser::advance() {
    if (isAtEnd()) return nullptr;
    Token* token = &m_tokens[m_current];
    m_current++;
    return token;
}

Token *Parser::match(TokenKind expected) {
    Token* token = advance();

    if (token == nullptr) return nullptr;
    if (token->kind != expected) return nullptr;

    return token;
}

Token *Parser::next() {
    if (m_current + 1 >= m_tokens.size()) return nullptr;
    return &m_tokens[m_current + 1];
}

Token *Parser::peek() {
    if (isAtEnd()) return nullptr;
    return &m_tokens[m_current];
}

bool Parser::isAtEnd() {
    return m_current >= m_tokens.size();
}
