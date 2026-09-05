/**
 * @file BrightnessFilter.cpp
 */

#include "BrightnessFilter.h"

namespace ip {

BrightnessFilter::BrightnessFilter(int offset) {
	m_offset = offset;
}

void BrightnessFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 첫 줄부터 끝 줄까지 반복한다.
	for (int y = begin; y < end; y++) {
		const uint8_t* sourceRow = source.rowPtr(y);
		uint8_t* resultRow = result.rowPtr(y);

		// 1.1. 너비만큼 반복한다.
		for (int i = 0; i < source.rowStride(); i++) {
			// 1.1.1. 채널값을 구한다.
			int channelValue = static_cast<int>(sourceRow[i]) + m_offset;

			// 1.1.2. 범위를 벗어났다면, 절삭한다.
			if (channelValue > 255) {
				channelValue = 255;
			}
			else if (channelValue < 0) {
				channelValue = 0;
			}

			// 1.1.3. 채널값을 결과 이미지에 넣는다.
			resultRow[i] = static_cast<uint8_t>(channelValue);
		}
	}
}

} // namespace ip
