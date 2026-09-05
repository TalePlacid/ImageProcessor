#pragma once

/**
* @file HorizontalFlipFilter.h
* @brief 이미지를 좌우 반전한다.
*/

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지를 좌우 반전하는 클래스
 */
class HorizontalFlipFilter : public FilterBase {
public:
	HorizontalFlipFilter() = default;
	virtual ~HorizontalFlipFilter() = default;
	HorizontalFlipFilter(const HorizontalFlipFilter& source) = default;
	HorizontalFlipFilter& operator=(const HorizontalFlipFilter& source) = default;
private:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
};

} // namespace ip
