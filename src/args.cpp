#include <print>
#include <ranges>
#include <algorithm>

#include "args.hpp"

static constexpr std::string_view INPUT_FILE_STR = "in=";
static constexpr std::string_view OUTPUT_FILE_STR = "out=";
static constexpr std::string_view HELP_STR = "-h";
static constexpr std::string_view HELP_OUTPUT = "help: bearjpeg in=file1.jpg out=file2.ppm\n";
static constexpr std::string_view ERROR_OUTPUT = "error: {0}\ntry bearjpeg -h\n";

using namespace std::string_view_literals;

static std::expected<ArgOptions, std::string>
validOptions(const ArgOptions& options, const std::vector<std::string_view>& unrecognized)
{
    if (!unrecognized.empty()) {
        auto chars = unrecognized | std::views::join_with(", "sv);
        return std::unexpected("unrecognized options: " + std::string(chars.begin(), chars.end()));
    }

    if (options.getHelp()) {
        return options;
    }

    if (options.getInput() == "") {
        return std::unexpected("missing input file");
    } else if (options.getOutput() == "") {
        return std::unexpected("missing output file");
    }

    return options;
}

static void
parseArg(ArgOptions& options, std::vector<std::string_view>& unrecognized, std::string_view arg)
{
    if (arg.starts_with(INPUT_FILE_STR)) {
        options.setInput(arg.substr(INPUT_FILE_STR.size()));
    } else if (arg.starts_with(OUTPUT_FILE_STR)) {
        options.setOutput(arg.substr(OUTPUT_FILE_STR.size()));
    } else if (arg == HELP_STR) {
        options.setHelp(true);
    } else {
        unrecognized.push_back(arg);
    }
}

std::expected<ArgOptions, std::string>
parseOptions(const std::span<const char * const> args)
{
    ArgOptions options;
    std::vector<std::string_view> unrecognized;

    std::ranges::for_each(args, [&options, &unrecognized](const auto arg){ parseArg(options, unrecognized, arg); });

    return validOptions(options, unrecognized);
}

void
printError(const std::string_view error)
{
    std::print(ERROR_OUTPUT, error);
}

void
printHelp(void)
{
    std::print(HELP_OUTPUT);
}
