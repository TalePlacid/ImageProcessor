/**
 * @file GrayscaleFilter.cpp
 */

#include "GrayscaleFilter.h"
#include "LumaCalculator.h"

namespace ip {

void GrayscaleFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 시작줄부터 끝줄까지 반복한다.
	for (int y = begin; y < end; y++) {
		const uint8_t* sourceRow = source.rowPtr(y);
		uint8_t* resultRow = result.rowPtr(y);

		// 1.1. 너비만큼 반복한다.
		for (int x = 0; x < source.width(); x++) {
			// 1.1.1. 그레이값을 구한다.
			const int index = x * ImageBuffer::CHANNELS;
			const int blue = static_cast<int>(sourceRow[index]);
			const int green = static_cast<int>(sourceRow[index + 1]);
			const int red = static_cast<int>(sourceRow[index + 2]);
			const uint8_t grayValue = static_cast<uint8_t>(LumaCalculator::Calculate(red, green, blue));

			// 1.1.2. 결과 이미지에 넣는다.
			resultRow[index] = grayValue;
			resultRow[index + 1] = grayValue;
			resultRow[index + 2] = grayValue;
		}
	}
}

} // namespace ip
