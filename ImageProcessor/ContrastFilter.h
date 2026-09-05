#pragma once

/**
 * @file BrightnessFilter.h
 * @brief 이미지 대비를 변환한다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지 대비를 변환하는 클래스
 * 
 * 픽셀 색 범위(0~255)를 넘어가는 경우 절삭된다.
 */
class ContrastFilter : public FilterBase {
public:
	ContrastFilter(int amount);
	virtual ~ContrastFilter() = default;
	ContrastFilter(const ContrastFilter& source) = default;
	ContrastFilter& operator=(const ContrastFilter& source) = default;
private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
private:
	static constexpr int MIDDLE = 128; ///< 픽셀 중앙값
	int m_amount; ///< 대비 변화량
};

} // namespace ip
