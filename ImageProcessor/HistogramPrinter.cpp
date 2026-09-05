/**
 * @file HistogramPrinter.cpp
 */

#include "HistogramPrinter.h"

#include <array>    // std::array
#include <iomanip>  // std::setfill, std::setw
#include <iostream> // std::cout

namespace ip {

namespace {

constexpr int HISTOGRAM_SIZE = 256; //히스토그램 크기
constexpr int BUCKET_SIZE = 16; // 바구니 수
constexpr int BUCKET_COUNT = HISTOGRAM_SIZE / BUCKET_SIZE; // 바구니 용량
constexpr int BAR_WIDTH = 40; // 막대 너비

/*
* @brief 범위 값들의 개수를 담는 구조체
*/
struct Bucket {
	int rangeStart;
	int rangeEnd;
	std::size_t count;
};

} // anonymous namespace

void HistogramPrinter::PrintTable(const std::size_t (&red)[256],
	const std::size_t (&green)[256], const std::size_t (&blue)[256],
	const std::size_t (&luma)[256]) {
	std::cout << "\n[Raw 히스토그램 표]\n";
	std::cout << std::right
		<< std::setw(7) << "Value"
		<< std::setw(12) << "Red"
		<< std::setw(12) << "Green"
		<< std::setw(12) << "Blue"
		<< std::setw(12) << "Luma"
		<< '\n';

	for (int value = 0; value < HISTOGRAM_SIZE; value++) {
		std::cout << std::setw(7) << value
			<< std::setw(12) << red[value]
			<< std::setw(12) << green[value]
			<< std::setw(12) << blue[value]
			<< std::setw(12) << luma[value]
			<< '\n';
	}
}

std::size_t HistogramPrinter::CalculateScale(const std::size_t (&red)[256],
	const std::size_t (&green)[256], const std::size_t (&blue)[256],
	const std::size_t (&luma)[256]) {
	std::array<Bucket, BUCKET_COUNT> redBuckets{};
	std::array<Bucket, BUCKET_COUNT> greenBuckets{};
	std::array<Bucket, BUCKET_COUNT> blueBuckets{};
	std::array<Bucket, BUCKET_COUNT> lumaBuckets{};
	for (int value = 0; value < HISTOGRAM_SIZE; value++) {
		const int bucketIndex = value / BUCKET_SIZE;
		redBuckets[bucketIndex].count += red[value];
		greenBuckets[bucketIndex].count += green[value];
		blueBuckets[bucketIndex].count += blue[value];
		lumaBuckets[bucketIndex].count += luma[value];
	}

	std::size_t scaleMaximum = 0;

	for (int bucket = 0; bucket < BUCKET_COUNT; bucket++) {
		if (redBuckets[bucket].count > scaleMaximum) {
			scaleMaximum = redBuckets[bucket].count;
		}
		if (greenBuckets[bucket].count > scaleMaximum) {
			scaleMaximum = greenBuckets[bucket].count;
		}
		if (blueBuckets[bucket].count > scaleMaximum) {
			scaleMaximum = blueBuckets[bucket].count;
		}
		if (lumaBuckets[bucket].count > scaleMaximum) {
			scaleMaximum = lumaBuckets[bucket].count;
		}
	}

	return scaleMaximum;
}

void HistogramPrinter::PrintDistributionGraph(const char* title,
	const std::size_t (&histogram)[256], std::size_t scaleMaximum) {
	std::array<Bucket, BUCKET_COUNT> buckets{};
	for (int bucket = 0; bucket < BUCKET_COUNT; bucket++) {
		buckets[bucket].rangeStart = bucket * BUCKET_SIZE;
		buckets[bucket].rangeEnd = buckets[bucket].rangeStart + BUCKET_SIZE - 1;
	}

	for (int value = 0; value < HISTOGRAM_SIZE; value++) {
		const int bucketIndex = value / BUCKET_SIZE;
		buckets[bucketIndex].count += histogram[value];
	}

	std::cout << '\n' << '[' << title << " 히스토그램 그래프]\n";
	for (int bucket = 0; bucket < BUCKET_COUNT; bucket++) {
		int barLength = 0;
		if (scaleMaximum > 0) {
			barLength = static_cast<int>(
				static_cast<double>(buckets[bucket].count) / scaleMaximum * BAR_WIDTH + 0.5
			);
		}

		std::cout << std::setfill('0')
			<< std::setw(3) << buckets[bucket].rangeStart << '-'
			<< std::setw(3) << buckets[bucket].rangeEnd
			<< std::setfill(' ') << " | ";
		for (int position = 0; position < BAR_WIDTH; position++) {
			if (position < barLength) {
				std::cout << '#';
			}
			else {
				std::cout << ' ';
			}
		}
		std::cout << " | " << buckets[bucket].count << '\n';
	}
}

} // namespace ip
