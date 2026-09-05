#pragma once

/**
* @file Logger.h
* @brief 로그 파일을 생성하고 기록한다.
*/


#include <chrono>
#include <fstream>
#include <string>

namespace ip {

/**
 * @brief 로그파일 입출력 전담 클래스.
 */
class Logger {
public:
	/**
	 * @brief 로그 파일을 생성한다.
	 * @throws LogError 파일을 열 수 없는 경우.
	 */
	Logger(std::string path);
	~Logger() = default;
	Logger(const Logger& source) = delete;
	Logger& operator=(const Logger& source) = delete;

	/**
	 * @brief 로그를 작성한다.
	 *
	 * 로그 내용:
	 *     - 필터 및 옵션명
	 *     - 처리 시간
	 *     - 성공/실패 여부
	 */
	void Write(std::string filterParameters,
		std::chrono::microseconds processingTime, bool isSucceeded);

private:
	std::ofstream m_file; // 로그 파일 스트림
};

} // namespace ip
