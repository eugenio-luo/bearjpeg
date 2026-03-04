#pragma once

#include <string>
#include <expected>
#include <span>
#include <vector>

struct ArgOptions {
private:
    std::optional<std::string_view> ao_input;
    std::optional<std::string_view> ao_output;
    bool                            ao_help = false;

public:
    std::string_view getInput(void)  const { return ao_input.value_or(""); }
    std::string_view getOutput(void) const { return ao_output.value_or(""); }
    bool             getHelp(void)   const { return ao_help; }

    void             setInput(std::string_view s)  { ao_input = std::make_optional<std::string_view>(s); }
    void             setOutput(std::string_view s) { ao_output = std::make_optional<std::string_view>(s); }
    void             setHelp(bool b)               { ao_help = b; }
};

std::expected<ArgOptions, std::string> parseOptions(const std::span<const char * const> args);
void printError(std::string_view error);
void printHelp(void);
