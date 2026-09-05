/**
 * @file VerticalFlipFilter.cpp
 */

#include "VerticalFlipFilter.h"

namespace ip {

void VerticalFlipFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 첫 줄부터 끝 줄까지 반복한다.
	for (int targetY = begin; targetY < end; targetY++) {
		// 1.1. 상하 반전된 y좌표를 찾는다.
		int sourceY = source.height() - 1 - targetY;
		const uint8_t* sourceRow = source.rowPtr(sourceY);
		uint8_t* resultRow = result.rowPtr(targetY);

		// 1.2. 줄 너비만큼, 결과 이미지에 넣는다.
		for (int i = 0; i < source.rowStride(); i++) {
			resultRow[i] = sourceRow[i];
		}
	}
}

} // namespace ip
