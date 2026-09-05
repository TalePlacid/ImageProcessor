/*
 * @file FilterBase.cpp
 */

#include "FilterBase.h"
#include "Exceptions.h"

#include <thread>     // std::thread
#include <functional> // std::cref, std::ref

namespace ip {

namespace {

/*
 * @brief 쓰레드 종료를 대기한다.
 */
void JoinThreads(std::vector<std::thread>& threads) {
	for (std::size_t i = 0; i < threads.size(); i++) {
		if (threads[i].joinable()) {
			threads[i].join();
		}
	}
}

} // anonymous namespace

FilterBase::~FilterBase() = default;

void FilterBase::Add(std::unique_ptr<FilterBase>) {
	throw FilterError("filter does not support child filters");
}

void FilterBase::Apply(ImageBuffer& image, int threadCount) {
	const ImageBuffer& source = image;

	// 1. 결과물 버퍼를 생성한다.
	ImageBuffer result = CreateResultBuffer(source);

	// 2. 쓰레드 수만큼 범위를 나눈다.
	const std::vector<int> rangeSizes =
		DivideProcessingRange(result, threadCount);
	const int workerCount = static_cast<int>(rangeSizes.size());

	// 3. 단일 처리이면, 메인 쓰레드에서 처리한다.
	if (workerCount == 1) {
		ProcessRange(source, result, 0, rangeSizes[0]);
	}
	else { // 4. 병렬 처리이면,
		
		std::vector<std::thread> threads;
		threads.reserve(workerCount);
		std::exception_ptr workerException;
		std::mutex exceptionMutex;
		int begin = 0;

		try {
			// 4.1. 쓰레드 수만큼 반복한다.
			for (int i = 0; i < workerCount; i++) {
				int currentRangeSize = rangeSizes[i];
				int end = begin + currentRangeSize;

				// 4.1.1. 쓰레드를 생성한다. 
				threads.emplace_back(&FilterBase::RunWorker, this,
					std::cref(source), std::ref(result), begin, end,
					std::ref(workerException), std::ref(exceptionMutex));

				begin = end;
			}
		}
		catch (...) {
			// 예외 발생시에도 생성된 쓰레드 대기.
			JoinThreads(threads);
			throw;
		}

		// 쓰레드 종료 대기
		JoinThreads(threads);
		if (workerException != nullptr) {
			std::rethrow_exception(workerException);
		}
	}

	//5. 결과물을 출력한다.
	Output(image, result);
}

ImageBuffer FilterBase::CreateResultBuffer(const ImageBuffer& source) {
	return source;
}

std::vector<int> FilterBase::DivideProcessingRange(const ImageBuffer& result, 
	int threadCount) {
	std::vector<int> rangeSizes;

	if (threadCount <= 0) {
		throw FilterError("thread count must be greater than 0");
	}

	int totalRangeSize = result.height();
	if (totalRangeSize <= 0) {
		throw FilterError("filter range size must be greater than 0");
	}

	int workerCount = threadCount;
	if (totalRangeSize < threadCount)
	{
		workerCount = totalRangeSize;
	}
	int baseRangeSize = totalRangeSize / workerCount;
	int remainingRange = totalRangeSize % workerCount;
	rangeSizes.reserve(workerCount);

	for (int i = 0; i < workerCount; i++) {
		int extraRangeSize = 0;
		if (i < remainingRange) {
			extraRangeSize = 1;
		}
		
		int currentRangeSize = baseRangeSize + extraRangeSize;
		
		rangeSizes.push_back(currentRangeSize);
	}

	return rangeSizes;
}

void FilterBase::ProcessRange(const ImageBuffer&, ImageBuffer&, int, int) {
	throw FilterError("filter does not support processing range");
}

void FilterBase::RunWorker(const ImageBuffer& source, ImageBuffer& result,
	int begin, int end, std::exception_ptr& workerException,
	std::mutex& exceptionMutex) {
	try {
		ProcessRange(source, result, begin, end);
	}
	catch (...) {
		std::lock_guard<std::mutex> lock(exceptionMutex);
		if (workerException == nullptr) {
			workerException = std::current_exception();
		}
	}
}

void FilterBase::Output(ImageBuffer& image, ImageBuffer& result) {
	image = result;
}

} // namespace ip
