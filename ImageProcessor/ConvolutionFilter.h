#pragma once

/**
 * @file ConvolutionFilter.h
 * @brief 이미지를 커널을 이용해 3x3 합성곱 변환한다.
 * 
 * 지원 커널 종류
 *     - BLUR : 흐림 효과
 *     - SHARPEN : 선명 효과
 */

#include "ImageBuffer.h"
#include "FilterBase.h"
#include "ConvolutionKernels.h"

namespace ip {

/**
 * @brief 3x3 합성곱을 수행하는 필터 클래스
 */
class ConvolutionFilter : public FilterBase {
public:
	ConvolutionFilter(kernel::Kernel3x3 kernel);
	virtual ~ConvolutionFilter() = default;
	ConvolutionFilter(const ConvolutionFilter& source) = default;
	ConvolutionFilter& operator=(const ConvolutionFilter& source) = default;
private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
private:
	kernel::Kernel3x3 kernel; ///< 효과 커널
};

} // namespace ip
