#pragma once

/**
 * @file FilterOptionParser.h
 * @brief 필터 옵션을 파싱한다.
 *
 * 파이프라인을 필터 집합으로 다룬다.
 */

#include <string>
#include <vector>

namespace ip {

class FilterOptionParser {
public:
	FilterOptionParser() = delete; //인스턴스화 금지 (정적 메서드만 제공)
	
	/**
	 * @brief 필터 이름을 파싱한다.
	 * 
	 * 먼저 pipeline인지 확인한 뒤에 단일 필터인지 판별한다.
	 */
	static std::string ParseFilterName(std::string filterText);

	/**
	 * @brief 파이프라인에 속하는 단일 필터들을 파싱한다.
	 * @param filterText "pipeline \"grayscale, blur, brightness:30\"" 형식의 문자열.
	 * 각 필터는 ','로 구분한다.
	 */
	static std::vector<std::string> ParsePipelineFilters(std::string filterText);

	/**
	 * @brief 필터의 매개변수들을 파싱한다.
	 * @param filterText "crop:0,0,200,400" 형식의 문자열.
	 * 각 매개변수는 ':'로 구분한다.
	 */
	static std::vector<std::string> ParseFilterParameters(std::string filterText);

	/**
	 * @brief 매개변수 문자열을 정수로 파싱한다.
	 * @throws FilterError 정수가 아닌 경우.
	 */
	static int ParseInt(std::string parameterText);
};

} //namespace ip
