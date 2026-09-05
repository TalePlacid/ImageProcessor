/**
 * @file ThresholdFilter.cpp
 */

#include "ThresholdFilter.h"
#include "LumaCalculator.h"

namespace ip {

ThresholdFilter::ThresholdFilter(int threshold) {
	m_threshold = threshold;
}

void ThresholdFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 첫 줄부터 끝 줄까지 반복한다.
	for (int y = begin; y < end; y++) {
		const uint8_t* sourceRow = source.rowPtr(y);
		uint8_t* resultRow = result.rowPtr(y);

		// 1.1. 너비만큼 반복한다.
		for (int x = 0; x < source.width(); x++) {
			// 1.1.1. 픽셀의 밝기값을 구한다.
			const int index = x * ImageBuffer::CHANNELS;
			const int blue = static_cast<int>(sourceRow[index]);
			const int green = static_cast<int>(sourceRow[index + 1]);
			const int red = static_cast<int>(sourceRow[index + 2]);
			const int luma = LumaCalculator::Calculate(red, green, blue);
			
			// 1.1.2. 임계값에 따라, 색을 정한다.
			uint8_t channelValue = 255;
			if (luma < m_threshold){
				channelValue = 0;
			}

			// 1.1.3. 결과 이미지에 넣는다.
			resultRow[index] = channelValue;
			resultRow[index + 1] = channelValue;
			resultRow[index + 2] = channelValue;
		}
	}
}

} // namespace ip
