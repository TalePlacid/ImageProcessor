/**
 * @file HistogramFilter.cpp
 */

#include "HistogramFilter.h"
#include "HistogramPrinter.h"
#include "LumaCalculator.h"

namespace ip {

void HistogramFilter::ProcessRange(const ImageBuffer& source, ImageBuffer&, int begin, int end) {
	constexpr int PIXEL_MAX = HISTOGRAM_SIZE - 1;
	std::size_t localRedPixels[HISTOGRAM_SIZE]{0, };
	std::size_t localGreenPixels[HISTOGRAM_SIZE]{0, };
	std::size_t localBluePixels[HISTOGRAM_SIZE]{0, };
	std::size_t localLumaValues[HISTOGRAM_SIZE]{0, };

	// 1. 첫 줄부터 마지막 줄까지 반복한다.
	for (int y = begin; y < end; y++) {
		const uint8_t* row = source.rowPtr(y);

		// 1.1. 너비만큼 반복한다.
		for (int x = 0; x < source.width(); x++) {
			// 1.1.1. rgb 히스토그램에 적는다.
			const int index = x * ImageBuffer::CHANNELS;
			const int blue = static_cast<int>(row[index]);
			const int green = static_cast<int>(row[index + 1]);
			const int red = static_cast<int>(row[index + 2]);

			localBluePixels[blue]++;
			localGreenPixels[green]++;
			localRedPixels[red]++;

			// 1.1.2. 밝기를 계산해 히스토그램에 적는다.
			int luma = LumaCalculator::Calculate(red, green, blue);

			if (luma < 0) {
				luma = 0;
			}
			else if (luma > PIXEL_MAX) {
				luma = PIXEL_MAX;
			}

			localLumaValues[luma]++;
		}
	}

	// 2. 지역 히스토그램을 결과 히스토그램에 넣는다.
	std::lock_guard<std::mutex> lock(this->histogramMutex);
	for (int i = 0; i < HISTOGRAM_SIZE; i++) {
		this->m_redPixels[i] += localRedPixels[i];
		this->m_greenPixels[i] += localGreenPixels[i];
		this->m_bluePixels[i] += localBluePixels[i];
		this->m_lumaValues[i] += localLumaValues[i];
	}
}

void HistogramFilter::Output(ImageBuffer&, ImageBuffer&) {
	// 1. raw 히스토그램 표를 출력한다.
	HistogramPrinter::PrintTable(this->m_redPixels, this->m_greenPixels,
		this->m_bluePixels,this->m_lumaValues);

	// 2. 시각화에 사용할 축척을 구한다.
	std::size_t scaleMaximum = HistogramPrinter::CalculateScale(this->m_redPixels,
		this->m_greenPixels,this->m_bluePixels,this->m_lumaValues);

	// 3. 시각화 그래프들을 출력한다.
	HistogramPrinter::PrintDistributionGraph("적색", this->m_redPixels, scaleMaximum);
	HistogramPrinter::PrintDistributionGraph("녹색", this->m_greenPixels, scaleMaximum);
	HistogramPrinter::PrintDistributionGraph("청색", this->m_bluePixels, scaleMaximum);
	HistogramPrinter::PrintDistributionGraph("밝기", this->m_lumaValues, scaleMaximum);
}

} // namespace ip
