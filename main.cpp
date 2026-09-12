#include <print>
#include <filesystem>
#include <CLI/CLI.hpp>

#include "lexer.hpp"

int main() {
    std::filesystem::path path = std::filesystem::absolute("..\\test.mish");
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return 1;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();

    std::string source = buffer.str();

    Lexer lex(source);
    auto tokens = lex.tokenize();
    if (!tokens.has_value()) return 1;


}
