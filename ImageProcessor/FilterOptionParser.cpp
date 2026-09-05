#include "Exceptions.h"
#include "FilterOptionParser.h"

namespace ip {

namespace {

const std::string PIPELINE_PREFIX = "pipeline ";

/*
 * @brief 구분자로 파싱한다.
 */
std::vector<std::string> Split(std::string text, char separator, std::string emptyError) {
	// 1. 마지막 구분자전까지 파싱한다.
	std::vector<std::string> values;
	std::string::size_type valueStart = 0;
	std::string::size_type separatorPosition = text.find(separator);
	while (separatorPosition != std::string::npos) {
		std::string value = text.substr(valueStart, separatorPosition - valueStart);
		if (value.empty()) {
			throw FilterError(emptyError);
		}

		values.push_back(value);
		valueStart = separatorPosition + 1;
		separatorPosition = text.find(separator, valueStart);
	}

	// 2. 마지막 값을 넣는다.
	std::string value = text.substr(valueStart);
	if (value.empty()) {
		throw FilterError(emptyError);
	}

	values.push_back(value);

	// 3. 값들을 반환한다.
	return values;
}

} // anonymous namespace

std::string FilterOptionParser::ParseFilterName(std::string filterText) {
	std::string filterName;

	// 1. pipeline으로 시작하면, 파이프라인 필터명을 적는다.
	if (filterText.compare(0, PIPELINE_PREFIX.size(), PIPELINE_PREFIX) == 0) {
		filterName = "pipeline";
	}
	else { // 2. pipeline으로 시작하지 않으면, 단일 필터명을 적는다.
		const std::string::size_type parameterStart = filterText.find(':');
		filterName = filterText.substr(0, parameterStart);
	}

	if (filterName.empty()) {
		throw FilterError("filter name is empty");
	}

	// 3. 필터명을 반환한다.
	return filterName;
}

std::vector<std::string> FilterOptionParser::ParsePipelineFilters(std::string filterText) {
	std::vector<std::string> pipelineFilters;

	if (filterText.compare(0, PIPELINE_PREFIX.size(), PIPELINE_PREFIX) != 0) {
		throw FilterError("invalid pipeline format");
	}

	// 1. 파이프라인에 속하는 필터들을 파싱한다.
	std::string pipelineText = filterText.substr(PIPELINE_PREFIX.size());
	pipelineFilters = Split(pipelineText, ',', "pipeline filter is empty");

	// 2. 파이프라인에 속하는 필터들을 반환한다.
	return pipelineFilters;
}

std::vector<std::string> FilterOptionParser::ParseFilterParameters(std::string filterText) {
	// 1. 필터 매개변수들을 파싱한다.
	std::vector<std::string> parameters;
	const std::string::size_type parameterStart = filterText.find(':');

	if (parameterStart != std::string::npos) {
		parameters = Split(filterText.substr(parameterStart + 1), ':', "filter parameter is empty");
	}

	// 2. 필터 매개변수들을 반환한다.
	return parameters;
}

int FilterOptionParser::ParseInt(std::string parameterText) {
	int integerParameter;
	
	try {
		integerParameter = std::stoi(parameterText);
	}
	catch (const std::invalid_argument&) {
		throw FilterError("parameter must be a number");
	}
	catch (const std::out_of_range&) {
		throw FilterError("parameter must be a number");
	}

	return integerParameter;
}

} //namespace ip
