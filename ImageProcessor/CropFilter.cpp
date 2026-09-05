/**
 * @file CropFilter.cpp
 */

#include "Exceptions.h"
#include "CropFilter.h"

namespace ip {

CropFilter::CropFilter(int x, int y, int width, int height) {
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}

ImageBuffer CropFilter::CreateResultBuffer(const ImageBuffer& source) {
	if (m_x < 0 || m_y < 0
		|| m_width <= 0 || m_height <= 0
		|| m_x >= source.width() || m_y >= source.height()
		|| m_width > source.width() - m_x
		|| m_height > source.height() - m_y) {
		throw FilterError("crop rectangle is out of range");
	}

	return ImageBuffer(m_width, m_height);
}

void CropFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 첫줄부터 끝줄까지 반복한다.
	for (int targetY = begin; targetY < end; targetY++) {
		const uint8_t* sourceRow = source.rowPtr(m_y + targetY);
		uint8_t* targetRow = result.rowPtr(targetY);

		// 2. 결과 이미지 버퍼의 너비만큼 반복한다.
		for (int targetX = 0; targetX < m_width; targetX++) {
			int sourceX = m_x + targetX;
			
			// 2.1. 결과 이미지 버퍼에 넣는다.
			for (int channel = 0; channel < ImageBuffer::CHANNELS; channel++) {
				int sourceIndex = sourceX * ImageBuffer::CHANNELS + channel;
				int targetIndex = targetX * ImageBuffer::CHANNELS + channel;

				targetRow[targetIndex] = sourceRow[sourceIndex];
			}
		}
	}
}

} // namespace ip
