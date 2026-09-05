#pragma once

/**
 * @file ResizeFilter.h
 * @brief 이미지 크기를 변환한다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

/**
 * @brief 이미지 크기를 변환하는 필터 클래스
 */
class ResizeFilter : public FilterBase {
public:
	ResizeFilter(int width, int height);
	virtual ~ResizeFilter() = default;
	ResizeFilter(const ResizeFilter& source) = default;
	ResizeFilter& operator=(const ResizeFilter& source) = default;
private:
	/**
	 * @brief 변환할 크기로 결과 이미지 버퍼를 생성한다.
	 */
	virtual ImageBuffer CreateResultBuffer(const ImageBuffer& source);

	/*
	 * @brief 이미지를 변환한다.
	 * 
	 * 좌표 변환은 픽셀의 중앙을 기준으로한다.
	 * 양선형 보간 방식을 사용한다.
	 */
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
private:
	int m_width; ///< 변환 너비
	int m_height; ///< 변환 높이
};

} // namespace ip
