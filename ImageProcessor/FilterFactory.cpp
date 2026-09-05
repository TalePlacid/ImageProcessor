/**
 * @file FilterFactory.cpp
 */

#include "Exceptions.h"

#include "FilterFactory.h"
#include "FilterBase.h"
#include "FilterOptionParser.h"
#include "GrayscaleFilter.h"
#include "BrightnessFilter.h"
#include "ContrastFilter.h"
#include "ThresholdFilter.h"
#include "ConvolutionFilter.h"
#include "HistogramFilter.h"
#include "CropFilter.h"
#include "HorizontalFlipFilter.h"
#include "VerticalFlipFilter.h"
#include "ResizeFilter.h"
#include "PipelineFilter.h"

#include <vector>

namespace ip {

std::unique_ptr<FilterBase> FilterFactory::Create(std::string filterText) {
	std::unique_ptr<FilterBase> filter = nullptr;

	// 1. 필터 이름을 구분한다.
	const std::string filterName = FilterOptionParser::ParseFilterName(filterText);

	// 2. 파이프라인이면,
	if (filterName == "pipeline") {
		// 2.1 파이프라인 필터를 만든다.
		filter = std::make_unique<PipelineFilter>();

		// 2.2 파이프라인 필터에 필터들을 추가한다.
		const std::vector<std::string> pipelineFilters =
			FilterOptionParser::ParsePipelineFilters(filterText);

		for (std::size_t i = 0; i < pipelineFilters.size(); i++) {
			filter->Add(CreateSingleFilter(pipelineFilters[i]));
		}
	}
	else { 	// 2. 파이프라인 필터가 아니면, 단일 필터를 만든다.
		filter = CreateSingleFilter(filterText);
	}

	//3. 필터를 반환한다.
	return filter;
}

std::unique_ptr<FilterBase> FilterFactory::CreateSingleFilter(std::string filterText) {
	std::unique_ptr<FilterBase> filter = nullptr;

	// 1. 필터명과 매개변수들을 파싱한다.
	const std::string filterName = FilterOptionParser::ParseFilterName(filterText);
	const std::vector<std::string> parameters =
		FilterOptionParser::ParseFilterParameters(filterText);

	// 2. 필터명에 따라, 필터를 생성한다.
	if (filterName == "grayscale") {
		filter = std::make_unique<GrayscaleFilter>();
	}
	else if (filterName == "brightness") {
		if (parameters.size() != 1)
		{
			throw FilterError("brightness needs 1 parameter");
		}

		int offset = FilterOptionParser::ParseInt(parameters[0]);
		
		filter = std::make_unique<BrightnessFilter>(offset);
	}
	else if (filterName == "contrast") {
		if (parameters.size() != 1)
		{
			throw FilterError("contrast needs 1 parameter");
		}

		int amount = FilterOptionParser::ParseInt(parameters[0]);

		filter = std::make_unique<ContrastFilter>(amount);
	}
	else if (filterName == "threshold") {
		if (parameters.size() != 1)
		{
			throw FilterError("threshold needs 1 parameter");
		}

		int threshold = FilterOptionParser::ParseInt(parameters[0]);

		filter = std::make_unique<ThresholdFilter>(threshold);
	}
	else if (filterName == "blur") {
		filter = std::make_unique<ConvolutionFilter>(kernel::BLUR);
	}
	else if (filterName == "sharpen") {
		filter = std::make_unique<ConvolutionFilter>(kernel::SHARPEN);
	}
	else if (filterName == "histogram") {
		filter = std::make_unique<HistogramFilter>();
	}
	else if (filterName == "crop") {
		if (parameters.size() != 4)
		{
			throw FilterError("crop needs 4 parameters");
		}

		int x = FilterOptionParser::ParseInt(parameters[0]);
		int y = FilterOptionParser::ParseInt(parameters[1]);
		int width = FilterOptionParser::ParseInt(parameters[2]);
		int height = FilterOptionParser::ParseInt(parameters[3]);

		filter = std::make_unique<CropFilter>(x, y, width, height);
	}
	else if (filterName == "flip") {
		if (parameters.size() != 1)
		{
			throw FilterError("flip needs 1 parameter");
		}

		if (parameters[0] == "horizontal") {
			filter = std::make_unique<HorizontalFlipFilter>();
		}
		else if (parameters[0] == "vertical") {
			filter = std::make_unique<VerticalFlipFilter>();
		}
		else {
			throw FilterError("unknown flip direction");
		}
	}
	else if (filterName == "resize") {
		if (parameters.size() != 2)
		{
			throw FilterError("resize needs 2 parameters");
		}

		int width = FilterOptionParser::ParseInt(parameters[0]);
		int height = FilterOptionParser::ParseInt(parameters[1]);

		filter = std::make_unique<ResizeFilter>(width, height);
	}
	else {
		throw FilterError("Unknown filter: " + filterText);
	}

	// 3. 필터를 반환한다.
	return filter;
}

} // namespace ip
