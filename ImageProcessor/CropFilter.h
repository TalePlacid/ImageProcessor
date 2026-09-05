#pragma once

/**
 * @file CropFilter.h
 * @brief 이미지를 크기에 맞게 자른다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

namespace ip {

	
/**
 * @brief 이미지를 크기에 맞게 자르는 필터 클래스.
 */
class CropFilter : public FilterBase {
public:
	CropFilter(int x, int y, int width, int height);
	virtual ~CropFilter() = default;
	CropFilter(const CropFilter& source) = default;
	CropFilter& operator=(const CropFilter& source) = default;
private:
	/**
	 * @brief 자르는 사이즈에 맞게 결과 이미지 버퍼를 생성한다.
	 */
	virtual ImageBuffer CreateResultBuffer(const ImageBuffer& source);
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);
private:
	int m_x; ///< 자르기 기준 x좌표
	int m_y; ///< 자르기 기준 y좌표
	int m_width; ///< 너비
	int m_height; ///< 높이
};

} // namespace ip
