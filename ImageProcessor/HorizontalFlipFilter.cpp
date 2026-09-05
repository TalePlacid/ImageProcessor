/**
 * @file HorizontalFlipFilter.cpp
 */

#include "HorizontalFlipFilter.h"

namespace ip {

void HorizontalFlipFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 첫 줄부터 끝 줄까지 반복한다.
	for (int y = begin; y < end; y++) {
		const uint8_t* sourceRow = source.rowPtr(y);
		uint8_t* resultRow = result.rowPtr(y);

		// 1.1. 너비만큼 반복한다.
		for (int targetX = 0; targetX < source.width(); targetX++) {
			// 1.1.1. 좌우 반전된 위치를 찾는다.
			int sourceX = source.width() - 1 - targetX;

			// 1.1.2. 결과 이미지에 넣는다.
			for (int channel = 0; channel < ImageBuffer::CHANNELS; channel++) {
				int sourceIndex = sourceX * ImageBuffer::CHANNELS + channel;
				int targetIndex = targetX * ImageBuffer::CHANNELS + channel;
				resultRow[targetIndex] = sourceRow[sourceIndex];
			}
		}
	}
}

} // namespace ip
