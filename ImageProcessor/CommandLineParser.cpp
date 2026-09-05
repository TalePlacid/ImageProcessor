/**
 * @file CommandLineParser.cpp
 */

#include "CommandLineParser.h"
#include "Exceptions.h"

#include <iostream>
#include <string>
#include <stdexcept> // std::stoi 예외 처리

namespace ip {

namespace {
    /// argv 의 다음 인자를 안전하게 가져온다.
    std::string nextArg(int argc, char* argv[], int& i, const std::string& flag) {
        if (i + 1 >= argc) {
            throw ArgumentError(flag + ": missing value");
        }
        return argv[++i];
    }
} // anonymous namespace

ProgramOptions CommandLineParser::parse(int argc, char* argv[]) {
    ProgramOptions options;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg == "--input" || arg == "-i") {
            options.inputPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--output" || arg == "-o") {
            options.outputPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--filter" || arg == "-f") {
            options.filterName = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--pipeline" || arg == "-p") {
            options.filterName = "pipeline " + nextArg(argc, argv, i, arg);
        }
        else if (arg == "--thread" || arg == "-t") {
            options.threadCount = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--log" || arg == "-l") {
            options.logPath = nextArg(argc, argv, i, arg);
        }
        else if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            std::exit(0);
        }
        else {
            throw ArgumentError("Unknown option: " + arg);
        }
    }

    // 필수 인자 검증
    if (options.inputPath.empty()) {
        throw ArgumentError("--input is required");
    }
    if (options.outputPath.empty()) {
        throw ArgumentError("--output is required");
    }
    if (options.filterName.empty()) {
        throw ArgumentError("--filter or --pipeline is required");
    }

    // 선택 인자 검증
    try {
        int threadCount = std::stoi(options.threadCount);

        if (threadCount <= 0) {
            throw ArgumentError("--thread must be greater than 0");
        }
    }
    catch (const std::invalid_argument&) {
        throw ArgumentError("--thread must be an integer");
    }
    catch (const std::out_of_range&) {
        throw ArgumentError("--thread must be an integer");
    }

    return options;
}

void CommandLineParser::printUsage(const std::string& exeName) {
    std::cout
        << "Usage:\n"
        << "  " << exeName << " --input <path> --output <path> --filter <name>\n\n"
        << "Options:\n"
        << "  -i, --input   <path>   Input BMP file (24-bit, uncompressed)\n"
        << "  -o, --output  <path>   Output BMP file\n"
        << "  -f, --filter  <name>   Filter to apply (e.g. grayscale, blur, threshold:128)\n"
        << "  -p, --pipeline <filters>  Filters to apply (e.g. \"grayscale,blur,threshold:128\")\n"
        << "  -t, --thread  <count>  Worker thread count (default: 1)\n"
        << "  -l, --log     <path>   Append processing result to a log file\n"
        << "  -h, --help             Show this message\n\n"
        << "Examples:\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -f grayscale\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -f blur -t 4\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -f threshold:128 -l log.txt\n"
        << "  " << exeName << " -i input.bmp -o result.bmp -p \"grayscale,blur,threshold:128\"\n";
}

} // namespace ip
