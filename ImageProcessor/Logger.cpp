/**
 * @file Logger.cpp
 */

#include "Logger.h"
#include "Exceptions.h"

#include <iomanip>
#include <ios>

namespace ip {

Logger::Logger(std::string path) {
	if (path.empty()) {
		throw LogError("log path is empty");
	}
	
	m_file.open(path, std::ios::out | std::ios::app);
	if (!m_file.is_open()) {
		throw LogError("failed to open log file: " + path);
	}
}

void Logger::Write(std::string filterParameters,
	std::chrono::microseconds processingTime, bool isSucceeded)
{
	if (m_file.is_open()) {
		std::string status = "FAILURE";
		if (isSucceeded)
		{
			status = "SUCCESS";
		}

		m_file << "filter=" << std::quoted(filterParameters)
			<< " processing_time_microseconds=" << processingTime.count()
			<< " status=" << status << '\n';
		m_file.flush();
	}
}

} // namespace ip
