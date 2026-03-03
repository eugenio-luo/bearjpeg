#include <iostream>

#include "args.hpp"

int
main(int argc, const char *argv[])
{
    /* the first command arg is just the binary name */
    auto args = std::span{argv + 1, static_cast<size_t>(argc - 1)};
    std::expected<ArgOptions, std::string> options = parseOptions(args);
    if (!options) {
        printError(options.error());
        return 1;
    }

    if (options->ao_help.value_or(false)) {
        printHelp();
        return 0;
    }

    return 0;
}
