#pragma once

#include <string>
#include <expected>
#include <span>
#include <vector>

struct ArgOptions {
    static constexpr std::string INPUT_FILE_STR = "input=";
    static constexpr std::string OUTPUT_FILE_STR = "output=";
    static constexpr std::string HELP_STR = "help";

    std::vector<std::string_view> ao_unrecognized;

    std::optional<std::string_view> ao_input;
    std::optional<std::string_view> ao_output;
    std::optional<bool>             ao_help;

    std::expected<ArgOptions, std::string> valid(void);
};

std::expected<ArgOptions, std::string> parseOptions(const std::span<const char * const> args);
void printError(std::string_view error);
void printHelp(void);
