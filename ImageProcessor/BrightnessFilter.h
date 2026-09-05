#pragma once

/**
 * @file BrightnessFilter.h
 * @brief 이미지 밝기를 변환한다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지 밝기를 변환하는 클래스
 * 
 * 픽셀 색 범위(0~255)를 넘어가는 경우 절삭된다.
 */
class BrightnessFilter : public FilterBase {
public:
	BrightnessFilter(int offset);
	virtual ~BrightnessFilter() = default;
	BrightnessFilter(const BrightnessFilter& source) = default;
	BrightnessFilter& operator=(const BrightnessFilter& source) = default;
private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
private:
	int m_offset; ///< 밝기 변화량
};

} // namespace ip
