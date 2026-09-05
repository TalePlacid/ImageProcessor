#pragma once

/**
* @file VerticalFlipFilter.h
* @brief 이미지를 상하 반전한다.
*/

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지를 상하 반전하는 클래스
 */
class VerticalFlipFilter : public FilterBase {
public:
	VerticalFlipFilter() = default;
	virtual ~VerticalFlipFilter() = default;
	VerticalFlipFilter(const VerticalFlipFilter& source) = default;
	VerticalFlipFilter& operator=(const VerticalFlipFilter& source) = default;
private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
};

} // namespace ip
