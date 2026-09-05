#pragma once

/**
 * @file ThresholdFilter.h
 * @brief 이미지를 이진화한다.
 * 
 * 임계값과 동일하면 흰색으로 처리한다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지를 이진화하는 클래스
 */
class ThresholdFilter : public FilterBase {
public:
	ThresholdFilter(int threshold);
	virtual ~ThresholdFilter() = default;
	ThresholdFilter(const ThresholdFilter& source) = default;
	ThresholdFilter& operator=(const ThresholdFilter& source) = default;
private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
private:
	int m_threshold; ///< 임계값
};

} // namespace ip
