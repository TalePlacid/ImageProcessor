#pragma once

/**
 * @file FilterBase.h
 * @brief 필터 공통 인터페이스를 제공한다.
 */

#include "ImageBuffer.h"

#include <exception> // std::exception_ptr
#include <memory>    // std::unique_ptr
#include <mutex>     // std::mutex
#include <vector>    // std::vector

namespace ip {

/**
 * @brief 필터 공통 인터페이스를 담당하는 클래스
 */
class FilterBase {
public:
	FilterBase() = default;
	virtual ~FilterBase() = 0;
	FilterBase(const FilterBase& source) = default;
	FilterBase& operator=(const FilterBase& source) = default;

	/**
	 * @brief 파이프라인 필터에 단일 필터를 추가한다.
	 */
	virtual void Add(std::unique_ptr<FilterBase> filter);

	/**
	 * @brief 필터를 적용한다.
	 *
	 * 파이프라인 필터의 경우, 속한 필터를 연속실행한다.
	 */
	virtual void Apply(ImageBuffer& image, int threadCount);

private:
	/*
	 * @brief 결과물 이미지 버퍼를 만든다.
	 */
	virtual ImageBuffer CreateResultBuffer(const ImageBuffer& source);

	/*
	 * @brief 전체 처리 범위를 쓰레드 수만큼 나누어 각 범위 크기를 반환한다.
	 */
	std::vector<int> DivideProcessingRange(const ImageBuffer& result, int threadCount);

	/*
	 * @brief 이미지 범위를 처리한다.
	 */
	virtual void ProcessRange(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end);

	/*
	 * @brief 작업 쓰레드에서 이미지 범위를 처리한다.
	 */
	void RunWorker(const ImageBuffer& source, ImageBuffer& result,
		int begin, int end, std::exception_ptr& workerException,
		std::mutex& exceptionMutex);

	/*
	 * @brief 결과물을 출력한다.
	 *
	 * 필터의 경우, 결과물 버퍼로 교체한다.
	 * 히스토그램분석의 경우, 콘솔 출력한다.
	 */
	virtual void Output(ImageBuffer& image, ImageBuffer& result);
};

} //namespace ip
