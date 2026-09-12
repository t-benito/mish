#ifndef MISH_ERROR_HPP
#define MISH_ERROR_HPP
#include <functional>
#include <string_view>
#include "lexer.hpp"

enum class LexerErrorKind: int {
    UnexpectedCharacter,
    UnknownCompKeyword,
};

enum class ErrorGroup {
    LexerErrorKind,
};

struct Error {
    std::string_view message;
    ErrorGroup group;
    union {
        LexerErrorKind lex;
    } kind;
    Span* span;
};

class ErrorLogger {
public:
    explicit ErrorLogger(std::string_view source);

    void addError(Error err);

    bool dump();

private:
    std::string_view m_source;
    std::vector<Error> m_errors;
};

#endif //MISH_ERROR_HPP
