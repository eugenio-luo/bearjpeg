#include <print>
#include <ranges>
#include <algorithm>

#include "args.hpp"

using namespace std::string_view_literals;

std::expected<ArgOptions, std::string>
ArgOptions::valid(void)
{
    if (!ao_unrecognized.empty()) {
        auto chars = ao_unrecognized | std::views::join_with(", "sv);
        return std::unexpected("unrecognized options: " + std::string(chars.begin(), chars.end()));
    }

    if (ao_help.value_or(false)) {
        return *this;
    }

    if (!ao_input) {
        return std::unexpected("missing input file");
    } else if (!ao_output) {
        return std::unexpected("missing output file");
    }

    return *this;
}

static void
parseArg(ArgOptions& options, std::string_view arg)
{
    if (arg.starts_with(options.INPUT_FILE_STR)) {
        options.ao_input = arg.substr(options.INPUT_FILE_STR.size());
    } else if (arg.starts_with(options.OUTPUT_FILE_STR)) {
        options.ao_output = arg.substr(options.OUTPUT_FILE_STR.size());
    } else if (arg == options.HELP_STR) {
        options.ao_help = true;
    } else {
        options.ao_unrecognized.push_back(arg);
    }
}

std::expected<ArgOptions, std::string>
parseOptions(const std::span<const char * const> args)
{
    ArgOptions options;
    std::ranges::for_each(args, [&options](const auto arg){ parseArg(options, arg); });

    return options.valid();
}

void
printError(std::string_view error)
{
    std::print("error: {0}\ntry bearjpeg help\n", error);
}

void
printHelp(void)
{
    std::print("help: bearjpeg input=file1.jpg output=file2.ppm\n");
}
