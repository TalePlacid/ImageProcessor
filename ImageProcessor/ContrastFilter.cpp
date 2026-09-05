/**
 * @file ContrastFilter.cpp
 */

#include "ContrastFilter.h"

namespace ip {

ContrastFilter::ContrastFilter(int amount) {
	m_amount = amount;
}

void ContrastFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 변화율을 구한다.
	double factor = 1.0 + (m_amount / 100.0);
	if (factor < 0.0) { //색 반전 방어
		factor = 0.0;
	}

	// 2. 첫 줄부터 끝 줄까지 반복한다.
	for (int y = begin; y < end; y++) {
		const uint8_t* sourceRow = source.rowPtr(y);
		uint8_t* resultRow = result.rowPtr(y);

		// 2.1. 너비만큼 반복한다.
		for (int i = 0; i < source.rowStride(); i++) {
			// 2.1.1. 변화량을 적용한다.
			const int channelValue = static_cast<int>(sourceRow[i]);
			int adjustedValue = static_cast<int>(
				(channelValue - MIDDLE) * factor + MIDDLE
			);

			// 2.1.2. 색 범위를 넘어섰다면, 절삭한다.
			if (adjustedValue > 255) {
				adjustedValue = 255;
			}
			else if (adjustedValue < 0) {
				adjustedValue = 0;
			}

			// 2.1.3. 결과 이미지에 넣는다.
			resultRow[i] = static_cast<uint8_t>(adjustedValue);
		}
	}
}

} // namespace ip
