#include "error.hpp"

#include <print>

ErrorLogger::ErrorLogger(std::string_view source)
:   m_source(source)
{}

void ErrorLogger::addError(Error err) {
    m_errors.emplace_back(err);
}

bool ErrorLogger::dump() {
    if (m_errors.empty()) return false;

    for (auto& error : m_errors) {
        std::print("\033[1;31merror:\033[0m {} ", error.message);
        switch (error.group) {
            case ErrorGroup::LexerErrorKind:
                std::println("(E0{})", static_cast<int>(error.kind.lex));
                break;
        }

        uint64_t line = 0;
        for (uint64_t i = 0; i < error.span->start; ++i) {
            if (i >= m_source.size()) break;
            char c = m_source[i];
            if (c == '\n') ++line;
        }

        uint64_t lineStart = error.span->start;
        while (lineStart > 0) {
            if (m_source[lineStart] == '\n') break;
            --lineStart;
        }

        uint64_t lineEnd = error.span->end;
        while (lineEnd < m_source.size()) {
            if (m_source[lineEnd] == '\n') break;
            ++lineEnd;
        }

        std::string_view span = m_source.substr(lineStart, lineEnd);
        std::println("{}", span);
    }

    return true;
}