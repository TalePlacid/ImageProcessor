/**
 * @file LumaCalculator.cpp
 */

#include "LumaCalculator.h"

namespace ip {

int LumaCalculator::Calculate(int red, int green, int blue) {
	int luma = static_cast<int>((red * RED_LUMA_WEIGHT) + (green * GREEN_LUMA_WEIGHT)
		+ (blue * BLUE_LUMA_WEIGHT) + 0.5); //반올림

	return luma;
}

} // namespace ip