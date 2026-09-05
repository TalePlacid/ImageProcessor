/**
 * @file main.cpp
 * @brief ImageProcessor 진입점 — 지원자가 작성해야 할 파일입니다.
 *
 * BMP 입출력과 커맨드라인 파싱은 제공된 코드가 처리합니다.
 * 본 과제에서 작성해야 할 것은 단 하나입니다:
 *
 *     ▶ 이미지 처리 필터 2개 이상 구현 + main 의 TODO 위치에 연결
 *
 * 또한 일관된 컨벤션과 예외 처리, 메모리 안정성도 함께 평가됩니다.
 */

#include "BmpParser.h"
#include "CommandLineParser.h"
#include "ImageBuffer.h"
#include "Exceptions.h"

#include <iostream>
#include <memory> // unique_pointer
#include <chrono>

// TODO: 본인이 구현한 필터 헤더를 include 하세요.
#include "FilterBase.h"
#include "FilterFactory.h"
#include "Logger.h"

int main(int argc, char* argv[]) {
    try {
        // ── CLI 인자 파싱 (제공된 코드) ─────────────────────────
        const ip::ProgramOptions options = ip::CommandLineParser::parse(argc, argv);

        // ── BMP 로드 (제공된 코드) ──────────────────────────────
        ip::ImageBuffer image = ip::BmpParser::loadFromFile(options.inputPath);
        std::cout << "Loaded: " << image.width() << " x " << image.height() << "\n";

        std::unique_ptr<ip::Logger> logger = nullptr;
        if (!options.logPath.empty()) {
            logger = std::make_unique<ip::Logger>(options.logPath);
        }

        // ───────────────────────────────────────────────────────
        // TODO: options.filterName 에 따라 적절한 필터를 생성하고        
        //       image 에 적용하세요.
        //        
        //   ※ 가산점 항목:
        //     - 추상 클래스(FilterBase) 기반 다형성 설계
        //     - 필터 파이프라인 체인 (CLI 옵션 확장 필요)
        //     - 멀티쓰레드 처리
        //     - 로그 파일 출력 (CLI 옵션 확장 필요)
        // ───────────────────────────────────────────────────────

        // ↓ 여기에 필터 적용 코드를 작성하세요.
        std::chrono::steady_clock::time_point filterStart
            = std::chrono::steady_clock::now();
        try {
            // 필터 생성
            std::unique_ptr<ip::FilterBase> filter =
                ip::FilterFactory::Create(options.filterName);

            // 필터 적용
            filter->Apply(image, std::stoi(options.threadCount));
        }
        catch (...) { // 중도 에러시 예외 처리
            std::chrono::microseconds processingTime
                = std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::steady_clock::now() - filterStart);

            // 실패 로그 작성
            if (logger != nullptr) {
                logger->Write(options.filterName, processingTime, false);
            }

            // 에러 메시지 재전달
            throw;
        }

        // 성공 로그 작성
        std::chrono::microseconds processingTime
            = std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::steady_clock::now() - filterStart);
        if (logger != nullptr) {
            logger->Write(options.filterName, processingTime, true);
        }

        // ── BMP 저장 (제공된 코드) ──────────────────────────────
        ip::BmpParser::saveToFile(options.outputPath, image);
        std::cout << "Saved:  " << options.outputPath << "\n";
        return 0;
    }
    catch (const ip::LogError& e) {
        std::cerr << e.what() << std::endl;
        return 5;
    }
    catch (const ip::ArgumentError& e) {
        std::cerr << e.what() << "\n\n";
        ip::CommandLineParser::printUsage(argc > 0 ? argv[0] : "ImageProcessor");
        return 4;
    }
    catch (const ip::BmpParseError& e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch (const ip::FilterError& e) {
        std::cerr << e.what() << std::endl;
        return 3;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}
