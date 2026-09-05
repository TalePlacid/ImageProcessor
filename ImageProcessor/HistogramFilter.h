#pragma once

/**
* @file HistogramFilter.h
* @brief 히스토그램을 분석한다.
* 
* 분석한 값을 콘솔에 출력한다.
* 출력 내용
*     - rgb, luma raw 값 테이블
*     - 적색 분포 시각화 그래프
*     - 녹색 분포 시각화 그래프
*     - 청색 분포 시각화 그래프
*     - luma 분포 시각화 그래프
*/

#include "ImageBuffer.h"
#include "FilterBase.h"

#include <cstddef>
#include <mutex>

namespace ip {

/**
 * @brief 히스토그램을 분석하는 클래스.
 */
class HistogramFilter : public FilterBase {
public:
	HistogramFilter() = default;
	virtual ~HistogramFilter() = default;
	HistogramFilter(const HistogramFilter& source) = default;
	HistogramFilter& operator=(const HistogramFilter& source) = default;

protected:
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
	/**
	 * @brief 히스토그램 분석 결과를 콘솔에 출력한다.
	 * 
	 * 그래프 시각화는 HistogramPrinter에 위임한다.
	 */
	virtual void Output(ImageBuffer& image, ImageBuffer& result);

private:
	static constexpr int PIXEL_MAX = 255; ///< 색 최대값
	static constexpr int HISTOGRAM_SIZE = PIXEL_MAX + 1; ///< 히스토그램 크기
	std::size_t m_redPixels[HISTOGRAM_SIZE]{0, }; ///< 적색 히스토그램
	std::size_t m_greenPixels[HISTOGRAM_SIZE]{0, }; ///< 녹색 히스토그램
	std::size_t m_bluePixels[HISTOGRAM_SIZE]{0, }; ///< 청색 히스토그램
	std::size_t m_lumaValues[HISTOGRAM_SIZE]{0, }; ///< 밝기 히스토그램
	std::mutex histogramMutex; ///< 멀티쓰레딩을 위한 임계 영역
};

} // namespace ip
