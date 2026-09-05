/**
 * @file ResizeFilter.cpp
 */

#include "ResizeFilter.h"
#include "Exceptions.h"

namespace ip {

ResizeFilter::ResizeFilter(int width, int height) {
	if (width <= 0 || height <= 0) {
		throw FilterError("resizing width and height must be positive");
	}

	m_width = width;
	m_height = height;
}

ImageBuffer ResizeFilter::CreateResultBuffer(const ImageBuffer& source) {
	return ImageBuffer(m_width, m_height);
}

void ResizeFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 배율을 구한다.
	double horizontalRatio = source.width() / (m_width * 1.0);
	double verticalRatio = source.height() / (m_height * 1.0);

	// 2. 목적지의 높이만큼 반복한다.
	for (int destinationY = begin; destinationY < end; destinationY++) {
		// 2.1. 원본 y좌표를 구한다.
		double sourceY = (destinationY + 0.5) * verticalRatio - 0.5;
		if (sourceY < 0) {
			sourceY = 0;
		}
		else if (sourceY > source.height() - 1) {
			sourceY = source.height() - 1;
		}

		// 2.2. 수직 보간 비율을 구한다.
		int topY = static_cast<int>(sourceY);
		int bottomY = topY + 1;
		if (bottomY >= source.height()) {
			bottomY = source.height() - 1;
		}

		double deltaY = sourceY - topY;
		const uint8_t* topRow = source.rowPtr(topY);
		const uint8_t* bottomRow = source.rowPtr(bottomY);
		uint8_t* destinationRow = result.rowPtr(destinationY);

		// 2.3. 목적지의 너비만큼 반복한다.
		for (int destinationX = 0; destinationX < m_width; destinationX++) {
			//2.3.1. 원본 x좌표를 찾는다.
			double sourceX = (destinationX + 0.5) * horizontalRatio - 0.5;
			if (sourceX < 0) {
				sourceX = 0;
			}
			else if (sourceX > source.width() - 1) {
				sourceX = source.width() - 1;
			}

			// 2.2.2. 수평 보간 비율을 구한다.
			int leftX = static_cast<int>(sourceX);
			int rightX = leftX + 1;
			if (rightX >= source.width()) {
				rightX = source.width() - 1;
			}

			double deltaX = sourceX - leftX;

			// 2.2.3. 보간한 값을 결과 이미지 버퍼에 넣는다.
			for (int channel = 0; channel < ImageBuffer::CHANNELS; channel++) {
				int leftIndex = leftX * ImageBuffer::CHANNELS + channel;
				int rightIndex = rightX * ImageBuffer::CHANNELS + channel;
				int destinationIndex = destinationX * ImageBuffer::CHANNELS + channel;

				double topValue = topRow[leftIndex] * (1 - deltaX)
					+ topRow[rightIndex] * deltaX;
				double bottomValue = bottomRow[leftIndex] * (1 - deltaX)
					+ bottomRow[rightIndex] * deltaX;
				double resizedValue = topValue * (1 - deltaY)
					+ bottomValue * deltaY;

				destinationRow[destinationIndex] = static_cast<uint8_t>(resizedValue + 0.5);
			}
		}
	}
}

} // namespace ip
