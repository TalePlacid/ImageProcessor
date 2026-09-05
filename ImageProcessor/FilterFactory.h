#pragma once

/**
 * @file FilterFactory.h
 * @brief 필터를 생성한다.
 */

#include "ImageBuffer.h"
#include <string>
#include <memory>

namespace ip {

class FilterBase;

/**
 * @brief 필터 생성을 담당하는 클래스
 */

class FilterFactory {
public:
	FilterFactory() = delete; // 인스턴스화 금지 (정적 메서드만 제공)

	/**
	 * @brief 필터를 생성한다.
	 */
	static std::unique_ptr<FilterBase> Create(std::string filterText);
private:
	// 단일 필터 생성 메소드
	static std::unique_ptr<FilterBase> CreateSingleFilter(std::string filterText);
};

} //namespace ip
