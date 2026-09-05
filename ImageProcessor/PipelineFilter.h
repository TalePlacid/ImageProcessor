#pragma once

/**
 * @file PipelineFilter.h
 * @brief 여러 필터들로 이루어진 파이프라인을 실행한다.
 */

#include "ImageBuffer.h"
#include "FilterBase.h"

#include <memory>
#include <vector>

namespace ip {

/**
 * @brief 여러 필터들로 이루어진 파이프라인 클래스.
 */
class PipelineFilter : public FilterBase {
public:
	PipelineFilter() = default;
	virtual ~PipelineFilter() = default;
	PipelineFilter(const PipelineFilter& source) = delete;
	PipelineFilter& operator=(const PipelineFilter& source) = delete;

	/**
	 * @brief 파이프라인에 필터를 추가한다.
	 */
	virtual void Add(std::unique_ptr<FilterBase> filter);
	
	/**
	 * @brief 파이프라인에 필터들을 순차실행한다.
	 */
	virtual void Apply(ImageBuffer& image, int threadCount);
private:
	std::vector<std::unique_ptr<FilterBase>> filters; ///< 필터 배열
};

} // namespace ip
