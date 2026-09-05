#pragma once

/**
 * @file HistogramPrinter.h
 * @brief 히스토그램 표와 분포 그래프를 출력한다.
 */

#include <cstddef> // std::size_t

namespace ip {

/**
 * @brief 히스토그램 표와 분포 그래프를 출력하는 클래스.
 */
class HistogramPrinter {
public:
	HistogramPrinter() = delete; //인스턴스 생성 금지, 정적 메소드만 지원.

	/**
	 * @brief raw 히스토그램 표를 출력한다.
	 */
	static void PrintTable(const std::size_t (&red)[256], 
		const std::size_t (&green)[256],
		const std::size_t (&blue)[256],
		const std::size_t (&luma)[256]);

	/**
	 * @brief 히스토그램 시각화에 쓰일 축척을 구한다.
	 */
	static std::size_t CalculateScale(const std::size_t (&red)[256],
		const std::size_t (&green)[256],
		const std::size_t (&blue)[256],
		const std::size_t (&luma)[256]);

	/**
	 * @brief 히스토그램 시각화 그래프를 출력한다.
	 */
	static void PrintDistributionGraph(const char* title,
		const std::size_t (&histogram)[256], std::size_t scaleMaximum);
};

} // namespace ip
