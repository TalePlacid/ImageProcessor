/**
 * @file ConvolutionFilter.cpp 
 */

#include "ConvolutionFilter.h"

namespace ip {

ConvolutionFilter::ConvolutionFilter(kernel::Kernel3x3 kernel)
	: kernel(kernel) {

}

void ConvolutionFilter::ProcessRange(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end) {
	// 1. 첫 줄부터 끝 줄까지 반복한다.
	for (int pixelY = begin; pixelY < end; pixelY++) {
		// 1.1. 너비만큼 반복한다.
		for (int pixelX = 0; pixelX < source.width(); pixelX++) {
			// 1.1.1. 채널 수만큼 반복한다.
			for (int channel = 0; channel < ImageBuffer::CHANNELS; channel++) {
				// 1.1.1.1. 합성곱 연산한다.
				double sum = 0;
				for (int kernelY = 0; kernelY < kernel::KERNEL_SIZE; kernelY++) {
					for (int kernelX = 0; kernelX < kernel::KERNEL_SIZE; kernelX++) {
						// 연산할 위치를 구한다.
						int sourceY = pixelY + kernelY - kernel::KERNEL_RADIUS;
						int sourceX = pixelX + kernelX - kernel::KERNEL_RADIUS;

						// 위치가 가장자리이면, 가장 가까운 위치값을 복사한다.
						if (sourceY < 0) {
							sourceY = 0;
						}
						else if (sourceY >= source.height()) {
							sourceY = source.height() - 1;
						}

						if (sourceX < 0) {
							sourceX = 0;
						}
						else if (sourceX >= source.width()) {
							sourceX = source.width() - 1;
						}

						// 원본 이미지 스트림에서의 위치를 찾아 계산한다.
						int streamIndex = sourceX * ImageBuffer::CHANNELS + channel;
						sum += source.rowPtr(sourceY)[streamIndex] * this->kernel[kernelY][kernelX];
					}
				}
				
				// 1.1.1.2. 합성곱 결과가 색 범위를 넘어서면, 절삭한다.
				if (sum < 0.0) {
					sum = 0.0;
				}
				else if (sum > 255.0) {
					sum = 255.0;
				}

				// 1.1.1.3. 결과 이미지 스트림에 넣는다.
				int outStreamIndex = pixelX * source.CHANNELS + channel;
				result.rowPtr(pixelY)[outStreamIndex] = static_cast<uint8_t>(sum + 0.5);
			}
		}
	}
}

} // namespace ip
