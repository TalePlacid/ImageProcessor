/**
 * @file PipelineFilter.cpp
 */

#include "PipelineFilter.h"

#include <utility>

namespace ip {

void PipelineFilter::Add(std::unique_ptr<FilterBase> filter) {
	this->filters.push_back(std::move(filter));
}

void PipelineFilter::Apply(ImageBuffer& image, int threadCount) {
	for (std::size_t i = 0; i < this->filters.size(); i++) {
		this->filters[i]->Apply(image, threadCount);
	}
}

} // namespace ip
