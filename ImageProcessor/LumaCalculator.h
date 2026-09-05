#pragma once

/**
 * @file LumaCalculator.h
 * @brief 밝기값을 계산한다.
 */

namespace ip {

/**
 * @brief RGB 가중치에 따라 밝기값을 계산하는 클래스
 */
class LumaCalculator {
public:
	LumaCalculator() = delete; // 인스턴스화 금지 (정적 메서드만 제공)

	static int Calculate(int red, int green, int blue);
private:
	static constexpr double RED_LUMA_WEIGHT = 0.299; ///< 적색 가중치
	static constexpr double GREEN_LUMA_WEIGHT = 0.587; ///< 녹색 가중치
	static constexpr double BLUE_LUMA_WEIGHT = 0.114; ///< 청색 가중치
};

} // namespace ip