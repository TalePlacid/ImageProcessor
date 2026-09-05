#pragma once

/**
 * @file GrayscaleFilter.h
 * @brief 이미지를 그레이스케일로 변환한다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지를 그레이스케일로 변환하는 필터 클래스.
 * 
 * 밝기값 계산은 LumaCalculator에게 위임.
 */
class GrayscaleFilter : public FilterBase {
public:
	GrayscaleFilter() = default;
	virtual ~GrayscaleFilter() = default;
	GrayscaleFilter(const GrayscaleFilter& source) = default;
	GrayscaleFilter& operator=(const GrayscaleFilter& source) = default;

private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
};

} // namespace ip
