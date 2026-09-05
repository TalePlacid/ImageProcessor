#pragma once

/**
 * @file ConvolutionKernels.h
 * @brief 3x3 합성곱 필터에 쓰이는 커널을 정의한다.
 */

#include <array>

namespace ip::kernel {

static constexpr int KERNEL_SIZE = 3; ///< 커널 행렬 크기
static constexpr int KERNEL_RADIUS = KERNEL_SIZE / 2; ///< 커널 반경

using KernelRow = std::array<double, KERNEL_SIZE>;
using Kernel3x3 = std::array<KernelRow, KERNEL_SIZE>;

/**
 * @brief 흐림 효과 커널
 */
inline constexpr Kernel3x3 BLUR{
	KernelRow{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
	KernelRow{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0},
	KernelRow{1.0 / 9.0, 1.0 / 9.0, 1.0 / 9.0}
};

/**
 * @brief 선명 효과 커널
 */
inline constexpr Kernel3x3 SHARPEN{
	KernelRow{0.0, -1.0, 0.0},
	KernelRow{-1.0, 5.0, -1.0},
	KernelRow{0.0, -1.0, 0.0}
};

} // namespace ip::kernel