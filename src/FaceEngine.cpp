#include <iostream>
#include <pybind11/pybind11.h>
#include <fsdk/FaceEngine.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/numpy.h>
#include "ErrorsAdapter.hpp"
#include "FaceEngineAdapter.hpp"
#include "SettingsProviderAdapter.hpp"
#include "helpers.hpp"


namespace py = pybind11;

PyIFaceEngine createPyFaceEnginePtr(const char* dataPath = nullptr, const char* configPath = nullptr) {
	return PyIFaceEngine(dataPath, configPath);
}


PyISettingsProvider createSettingsProviderPtr(const char* path) {
	return PyISettingsProvider(path);
}


PYBIND11_MAKE_OPAQUE(fsdk::Landmarks5);
PYBIND11_MAKE_OPAQUE(fsdk::Landmarks68);

PYBIND11_MODULE(FaceEngine, f) {
	
	f.doc() = R"pbdoc(

        Python wrapper for LUNA SDK usings pybind11
        -------------------------------------------

        .. currentmodule:: FaceEngine

        .. autosummary::
           :toctree: _generate

           	createFaceEngine
           	createSettingsProvider
           	loadImage
           	PyIFaceEngine
			PyIFaceEngine.createAttributeEstimator
			PyIFaceEngine.createQualityEstimator
			PyIFaceEngine.createEthnicityEstimator

			PyIFaceEngine.createHeadPoseEstimator
			PyIFaceEngine.createBlackWhiteEstimator
			PyIFaceEngine.createDepthEstimator
			PyIFaceEngine.createIREstimator
			PyIFaceEngine.createSmileEstimator
			PyIFaceEngine.createFaceFlowEstimator
			PyIFaceEngine.createEyeEstimator
			PyIFaceEngine.createEmotionsEstimator
			PyIFaceEngine.createGazeEstimator

			PyIFaceEngine.createDetector
			PyIFaceEngine.createWarper
			PyIFaceEngine.createDescriptor
			PyIFaceEngine.createDescriptorBatch
			PyIFaceEngine.createExtractor
			PyIFaceEngine.createMatcher
			PyIFaceEngine.setSettingsProvider
			PyIFaceEngine.createIndexBuilder
			PyIFaceEngine.loadDenseIndex
			PyIFaceEngine.loadDynamicIndex

			SettingsProviderValue
			SettingsProviderValue.__init__

			PyISettingsProvider.getDefaultPath
			PyISettingsProvider.load
			PyISettingsProvider.save
			PyISettingsProvider.clear
			PyISettingsProvider.isEmpty
			PyISettingsProvider.setValue
			PyISettingsProvider.getValue

			IQualityEstimatorPtr
			IQualityEstimatorPtr.estimate

			IAttributeEstimatorPtr
			IAttributeEstimatorPtr.estimate

			IEthnicityEstimator
			IEthnicityEstimator.estimate

			IDetector
			IDetector.detect

			IWarperPtr
			IWarperPtr.warp
			IWarperPtr.createTransformation

			IDescriptorPtr
			IDescriptorPtr.getModelVersion
			IDescriptorPtr.getDescriptorLength
			IDescriptorPtr.getDescriptor

			IDescriptorBatchPtr
			IDescriptorBatchPtr.add
			IDescriptorBatchPtr.removeFast
			IDescriptorBatchPtr.removeSlow
			IDescriptorBatchPtr.getMaxCount
			IDescriptorBatchPtr.getCount
			IDescriptorBatchPtr.getModelVersion
			IDescriptorBatchPtr.getDescriptorSize
			IDescriptorBatchPtr.getDescriptorSlow
			IDescriptorBatchPtr.getDescriptorFast

			DescriptorBatchError

			IDescriptorExtractorPtr
			IDescriptorExtractorPtr.extract
			IDescriptorExtractorPtr.extractFromWarpedImage
			IDescriptorExtractorPtr.extractFromWarpedImageBatch


			IDescriptorMatcherPtr
			IDescriptorMatcherPtr.match

			IHeadPoseEstimatorPtr
			IHeadPoseEstimatorPtr.estimate

			IBlackWhiteEstimatorPtr
			IBlackWhiteEstimatorPtr.estimate

			ILivenessDepthEstimatorPtr
			ILivenessDepthEstimatorPtr.estimate
			ILivenessDepthEstimatorPtr.setRange

			ILivenessIREstimatorPtr
			ILivenessIREstimatorPtr.estimate

			ISmileEstimatorPtr
			ISmileEstimatorPtr.estimate

			ILivenessFlowEstimatorPtr
			ILivenessFlowEstimatorPtr.estimate

			IEyeEstimatorPtr
			IEyeEstimatorPtr.estimate

			IEmotionsEstimatorPtr
			IEmotionsEstimatorPtr.estimate

			IGazeEstimatorPtr
			IGazeEstimatorPtr.estimate

			IIndexPtr
			IIndexPtr.search

			IDenseIndexPtr
			IDenseIndexPtr.search
			IDenseIndexPtr.size
			IDenseIndexPtr.descriptorByIndex
			IDenseIndexPtr.search

			IDynamicIndexPtr
			IDynamicIndexPtr.saveToDenseIndex
			IDynamicIndexPtr.saveToDynamicIndex
			IDynamicIndexPtr.search
			IDynamicIndexPtr.size
			IDynamicIndexPtr.descriptorByIndex
			IDynamicIndexPtr.appendDescriptor
			IDynamicIndexPtr.appendBatch
			IDynamicIndexPtr.removeDescriptor

			MatchingResult

			Landmarks5
			Landmarks5.__len__
			Landmarks5.__getitem__
			Landmarks5.__setitem__

			Landmarks68
			Landmarks68.__len__
			Landmarks68.__getitem__
			Landmarks68.__setitem__

			IrisLandmarks
			IrisLandmarks.__len__
			IrisLandmarks.__getitem__
			IrisLandmarks.__setitem__

			EyelidLandmarks
			EyelidLandmarks.__len__
			EyelidLandmarks.__getitem__
			EyelidLandmarks.__setitem__

			Vector2f
			Vector2f.__init__
			Vector2f.__repr__

			Vector2i
			Vector2i.__init__
			Vector2i.__repr__

			FSDKErrorResult
			DescriptorBatchResult
			ImageErrorResult
			SettingsProviderErrorResult
			FSDKErrorValueInt
			FSDKErrorValueFloat
			FSDKErrorValueMatching


			AttributeEstimation
			AttributeEstimation.__init__
			AttributeEstimation.__repr__
			Quality
			Quality.__init__
			Quality.getQuality

			EthnicityEstimation
			EthnicityEstimation.__init__
			EthnicityEstimation.__repr__
			EthnicityEstimation.getEthnicityScore
			EthnicityEstimation.getPredominantEthnicity

			HeadPoseEstimation
			HeadPoseEstimation.__init__
			HeadPoseEstimation.__repr__
			HeadPoseEstimation.getFrontalFaceType

			SmileEstimation
			SmileEstimation.__init__
			SmileEstimation.__repr__

			EyesEstimation
			EyesEstimation.__init__
			EyesEstimation.__repr__
			State
			EyeAttributes
			EyeAttributes.state
			EyeAttributes.iris
			EyeAttributes.eyelid

			EmotionsEstimation
			EmotionsEstimation.__init__
			EmotionsEstimation.__repr__
			EmotionsEstimation.getPredominantEmotion
			EmotionsEstimation.getEmotionScore

			Emotions

			GazeEstimation
			GazeEstimation.__init__
			GazeEstimation.__repr__
			GazeEstimation

			EyeAngles

			Ethnicity

			Transformation

			Detection

			FormatType

			Image
			Image.__init__
			Image.getWidth
			Image.getHeight
			Image.isValid
			Image.getFormat
			Image.getRect
			Image.getData
			Image.getChannelCount
			Image.getChannelStep
			Image.getBitDepth
			Image.getByteDepth
			Image.computePitch
			Image.isPadded
			Image.isBGR
			Image.isValidFormat
			Image.setData
			Image.save
			Image.load
			Image.getRect
			Image.loadFromMemory

			ImageType

			ImageError

			SettingsProviderError

			Rect

			ObjectDetectorClassType
			ObjectDetectorClassType.ODT_MTCNN
			ObjectDetectorClassType.ODT_COUNT

			FSDKError
			FrontalFaceType

			DepthRange
			DepthRange.__repr__
			loadImage
			EyeAngles

			IIndexPtr
			IIndexPtr.search
			
			IDenseIndexPtr
			IDenseIndexPtr.search
			IDenseIndexPtr.size
			IDenseIndexPtr.descriptorByIndex
			
			IDynamicIndexPtr
			IDynamicIndexPtr.saveToDenseIndex
			IDynamicIndexPtr.saveToDynamicIndex
			IDynamicIndexPtr.countOfIndexedDescriptors
			IDynamicIndexPtr.search
			IDynamicIndexPtr.size
			IDynamicIndexPtr.descriptorByIndex
			IDynamicIndexPtr.search
			IDynamicIndexPtr.appendDescriptor
			IDynamicIndexPtr.appendBatch
			IDynamicIndexPtr.removeDescriptor
			
			IIndexBuilderPtr
			IIndexBuilderPtr.buildIndex
			IIndexBuilderPtr.appendDescriptor
			IIndexBuilderPtr.appendBatch
			IIndexBuilderPtr.appendDescriptor
			IIndexBuilderPtr.removeDescriptor
			IIndexBuilderPtr.descriptorByIndex
			
    )pbdoc";
	
	enum class FaceEngineEdition {
		FrontEndEdition,
		CompleteEdition
	};
	
	py::enum_<fsdk::FaceEngineEdition>(f, "FaceEngineEdition", "Complete or FrontEdition version.\n")
		.value("FrontEndEdition", fsdk::FaceEngineEdition::FrontEndEdition)
		.value("CompleteEdition", fsdk::FaceEngineEdition::CompleteEdition)
		.export_values();
			;
	
	f.def("createFaceEngine", &createPyFaceEnginePtr, py::return_value_policy::take_ownership,
		  "Create FaceEngine", py::arg("dataPath") = nullptr, py::arg("configPath") = nullptr,
		  "Create the LUNA SDK root object\n"
		  "\tArgs:\n"
		  "\t\tparam1 (str): [optional] path to folder with FSDK data. Default: ./data (on windows), /opt/visionlabs/data (on linux)\n"
		  "\t\tparam2 (str): [optional] path to faceengine.conf file. Default: <dataPath>/faceengine.cong\n");
	
	f.def("createSettingsProvider", &createSettingsProviderPtr, py::return_value_policy::take_ownership,
		  "Create object SettingsProvider\n"
		  "\tArgs:\n"
		  "\t\tparam1 (str): configuration file path\n");
	
	py::class_<PyIFaceEngine>(f, "PyIFaceEngine", "Root LUNA SDK object interface\n")
		.def("getFaceEngineEdition", &PyIFaceEngine::getFaceEngineEdition,
			"Get LUNA SDK ditribution edition.\n"
			"\tReturns:\n"
			"\t\t(enum FaceEngineEdition) Edition of LUNA SDK instance. Posible values:\n"
			"\t\t\tCompleteEdition - full edition with all function.\n"
			"\t\t\tFrontEndEdition - short edition with excluded descriptor functions.\n"
			"\t\t\tExtractor, matcher, descriptor, batch and index cannot be created.")
		.def("createAttributeEstimator", &PyIFaceEngine::createAttributeEstimator, "Creates Attribute estimator\n")
		.def("createQualityEstimator", &PyIFaceEngine::createQualityEstimator, "Creates Quality estimator\n")
		.def("createEthnicityEstimator", &PyIFaceEngine::createEthnicityEstimator, "Creates Ethnicity estimator\n")
		
		.def("createHeadPoseEstimator", &PyIFaceEngine::createHeadPoseEstimator, "Creates Head pose estimator\n")
		.def("createBlackWhiteEstimator", &PyIFaceEngine::createBlackWhiteEstimator, "Creates Black/White estimator\n")
		.def("createDepthEstimator", &PyIFaceEngine::createDepthEstimator, "Creates Liveness Depth estimator\n")
		.def("createIREstimator", &PyIFaceEngine::createIREstimator, "Creates Liveness Infrared estimator\n")
		.def("createSmileEstimator", &PyIFaceEngine::createSmileEstimator, "Creates Smile estimator\n")
		.def("createFaceFlowEstimator", &PyIFaceEngine::createFaceFlowEstimator, "Creates Liveness flow estimator. \n"
			"Note: this estimator is required only for liveness detection purposes.\n")
		.def("createEyeEstimator", &PyIFaceEngine::createEyeEstimator, "Creates Eye estimator\n")
		.def("createEmotionsEstimator", &PyIFaceEngine::createEmotionsEstimator, "Creates Emotions estimator\n")
		.def("createGazeEstimator", &PyIFaceEngine::createGazeEstimator, "Creates Gaze estimator\n")
		
		.def("createDetector", &PyIFaceEngine::createDetector,
			 "Creates a detector of given type.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (enum ObjectDetectorClassType): fixed or random order of algorithm types\n")
		.def("createWarper", &PyIFaceEngine::createWarper, "Creates warper\n")
		.def("createDescriptor", &PyIFaceEngine::createDescriptor, "Creates Descriptor\n")
		.def("createDescriptorBatch", &PyIFaceEngine::createDescriptorBatch, py::arg("size"), py::arg("version") = 0,
			 "Creates Batch of descriptors\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int): amount of descriptors in batch\n"
			 "\t\tparam2 (str): descriptor version in batch. If 0 - use dafault version from config\n")
		
		.def("createExtractor", &PyIFaceEngine::createExtractor, "Creates descriptor extractor\n")
		.def("createMatcher", &PyIFaceEngine::createMatcher, "Creates descriptor matcher\n")
		
		// Index
		.def("createIndexBuilder", &PyIFaceEngine::createIndexBuilder, "Creates index builder.\n")
		
		.def("loadDenseIndex", [](
			 PyIFaceEngine& faceEngine,
			 const char* indexPath) {
				 fsdk::ResultValue<fsdk::FSDKError, fsdk::IDenseIndex*> res = faceEngine.loadDenseIndex(indexPath);
				 if (res.isOk())
					 return std::make_tuple(FSDKErrorResult(fsdk::makeResult(res.getError())), fsdk::acquire(res.getValue()));
				 else
					 return std::make_tuple(FSDKErrorResult(fsdk::makeResult(res.getError())), fsdk::IDenseIndexPtr());
			 },
			 "Loads dense index.\n"
			 "\t\t Only indexes saved as dense are to be loaded as dense.\n"
			 "\tArgs:\n"
			 "\t\t param1 (str): indexPath Path to index to be loaded.\n"
			 "\tReturns:\n"
			 "\t\t(tuple with FSDKErrorResult and dense index): error code FSDKErrorResult and output dense index.\n")
		
		.def("loadDynamicIndex", [](
			PyIFaceEngine& faceEngine,
			const char* indexPath) {
				fsdk::ResultValue<fsdk::FSDKError, fsdk::IDynamicIndex*> res = faceEngine.loadDynamicIndex(indexPath);
				if (res.isOk())
					return std::make_tuple(FSDKErrorResult(fsdk::makeResult(res.getError())), fsdk::acquire(res.getValue()));
				else
					return std::make_tuple(FSDKErrorResult(fsdk::makeResult(res.getError())), fsdk::IDynamicIndexPtr());
			},
			"Loads dynamic index.\n"
			"\t\t Only indexes saved as dynamic are to be loaded as dynamic.\n"
			"\tArgs:\n"
			"\t\t param1 (str): indexPath Path to index to be loaded.\n"
			"\tReturns:\n"
			"\t\t(tuple with FSDKErrorResult and dense index): error code FSDKErrorResult and output dynamic index.\n")
		
		.def("setSettingsProvider", &PyIFaceEngine::setSettingsProvider,
			"Sets settings provider\n"
			"\tArgs:\n"
			"\t\tparam1 (PyISettingsProvider): setting provider\n")
				; // FaceEngine
		
		// ISettingsProvider
		py::class_<PyISettingsProvider>(f, "PyISettingsProvider")
		.def("getDefaultPath", &PyISettingsProvider::getDefaultPath,
			"Get settings path this provider is bound to.\n"
			"\tThis is the same path that was given to load().\n"
			"\tReturns path string.\n")
		
		.def("load", &PyISettingsProvider::load,
			 "Load settings from given path.\n"
			 "if `path` is null, load from the default path; @see getDefaultPath().\n"
			 "\tReturns result with error code specified by ISettingsProvider\n")
		
		.def("save", &PyISettingsProvider::save,
			"Save settings values using the default path.\n"
			"Path may be null, in this case a path from getDefaultPath() will be used.\n"
			"\tReturns true if succeded, false otherwise.\n")
		
		.def("clear", &PyISettingsProvider::clear, "Clear settings.\n")
		
		.def("isEmpty", &PyISettingsProvider::isEmpty,
			"Check if there are loaded settings.\n"
			"Returns true if provider is empty.\n")
		
		.def("setValue", &PyISettingsProvider::setValue, "Set parameter value.\n"
		"Lookup parameter by key. Creates a parameter if it does not already exist.\n"
		"Sets settings provider\n"
		"\tArgs:\n"
		"\t\tparam1 (str): parameter section\n"
		"\t\tparam2 (str): parameter name\n"
		"\t\tparam3 (value): parameter value\n")
		
		.def("getValue", &PyISettingsProvider::getValue,
			 "Get parameter value. Lookup parameter by key. Return empty value if the parameters does not exist.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (str): parameter section\n"
			 "\t\tparam2 (str): parameter name\n")
			; // PyISettingsProvider
	
	py::class_<fsdk::ISettingsProvider::Value>(f, "SettingsProviderValue", "Configuration parameter value.\n")
		.def(py::init<>(), "Initialize an empty value. Value type will be set to `Undefined`")
		.def(py::init<int>(), "Initialize an integer value")
		.def(py::init<int, int>(), "Initialize a 2d integer value")
		.def(py::init<int, int, int>(), "Initialize a 3d integer value")
		.def(py::init<int, int, int, int>(), "Initialize a 4d integer value")
		.def(py::init<float>(), "Initialize a float value")
		.def(py::init<float, float>(), "Initialize a 2d float value")
		.def(py::init<float, float, float>(), "Initialize a 3d float value")
		.def(py::init<float, float, float, float>(), "Initialize a 4d float value")
		.def(py::init<const char*>(), "Initialize a string value. Note: only short strings (<15 chars) are supported.\n")
		.def(py::init<const fsdk::Rect&>(), "Initialize a rect value")
		.def(py::init<bool>(), "Initialize a bool value")
		
		.def("asFloat", &fsdk::ISettingsProvider::Value::asFloat, py::arg("defaultValue") = 0.f,
			 "Safely get a float. If actual value type is float, the value is returned; "
			 "if not a fallback value is returned"
			 "\tArgs:\n"
			 "\t\tparam1 (float): [optional] fallback value\n")
		
		.def("asBool", &fsdk::ISettingsProvider::Value::asBool, py::arg("defaultValue") = false,
			 "Safely get a boolean. If actual value type is convertible to bool, "
			 "the value is returned; if not a fallback value is returned.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (bool): [optional] fallback value\n")
		
		.def("asInt", &fsdk::ISettingsProvider::Value::asInt, py::arg("defaultValue") = 0,
			 "Safely get an integer. If actual value type is Int, the value is returned; "
			 "if not a fallback value is returned.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int): [optional] fallback value\n")
		
		.def("asString", &fsdk::ISettingsProvider::Value::asString, py::arg("defaultValue") = "",
			 "Safely get a string. If actual value type is String, the value is returned; "
			 "if not a fallback value is returned. Note: doesn't allocate or copy memory.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int): [optional] fallback value\n")
		
		.def("asRect", []( const fsdk::ISettingsProvider::Value& v) {
			return v.asRect(); })
		.def("asRect", [](
			 const fsdk::ISettingsProvider::Value& v, const fsdk::Rect& r) {
				 return v.asRect(r); },
			 "Safely get a Rect. If actual value type is convertible to Rect, the value is returned; "
			 "if not a fallback value is returned\n"
			 "\tArgs:\n"
			 "\t\tparam1 (rect): [optional] fallback value\n")
		
		.def("asPoint2f", [](
			const fsdk::ISettingsProvider::Value& v) {
			return v.asPoint2f(); })
		.def("asPoint2f", [](
			 const fsdk::ISettingsProvider::Value& v, const fsdk::Point2f& r) {
				 return v.asPoint2f(r); },
			 "Safely get a Point2f. If actual value type is convertible to Point2f, the value is returned; \n"
			 "\tif not a fallback value is returned.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Vector2f): [optional] fallback value\n")
		
		.def("asPoint2i", [](
			const fsdk::ISettingsProvider::Value& v) {
			return v.asPoint2i(); })
		.def("asPoint2i", [](
			 const fsdk::ISettingsProvider::Value& v, const fsdk::Point2i& r) {
				 return v.asPoint2i(r); },
			 "Safely get a Point2i. If actual value type is convertible to Point2i, the value is returned; \n"
			 "\tif not a fallback value is returned.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Vector2i): [optional] fallback value\n")
		
		.def("asSize", [](
			const fsdk::ISettingsProvider::Value& v) {
			return v.asSize(); })
		.def("asSize", [](
			 const fsdk::ISettingsProvider::Value& v, const fsdk::Size& s) {
				 return v.asSize(s); },
			 "Safely get a Size. If actual value type is convertible to Size, the value is returned;\n"
			 "\tif not a fallback value is returned.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Vector2i): [optional] fallback value\n")
			; // SettingsProviderValue
	
	py::class_<fsdk::IFaceEnginePtr>(f, "IFaceEnginePtr");
	
	// Index
	py::class_<fsdk::IIndexPtr>(f, "IIndexPtr", "Some data structure optimized for search queries.\n")
		.def("search", [](
			 const fsdk::IIndexPtr& indexPtr,
			 const fsdk::IDescriptorPtr reference,
			 const int maxResultsCount) {
				 std::vector<fsdk::SearchResult> searchResults(maxResultsCount);
				 fsdk::ResultValue<fsdk::FSDKError, int> err = indexPtr->search(
				 reference,
				 maxResultsCount,
				 searchResults.data());
				 if (err.isOk()) {
					 const uint32_t searchSize = err.getValue();
					 py::list searchResultsPyList(searchSize);
					 for (uint32_t i = 0; i < searchSize; ++i)
						 searchResultsPyList[i] = searchResults[i];
					 return std::make_tuple(FSDKErrorResult(err), searchResultsPyList);
				 } else {
					 return std::make_tuple(FSDKErrorResult(err), py::list());
				 }
			 },
			 "Search for descriptors with the shorter distance to passed descriptor.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (IDescriptorPtr): Descriptor to match against index.\n"
			 "\t\tparam2 (int): Maximum count of results. It is upper bound value, it\n"
			 "\t\t\еdoes not guarantee to return exactly this amount of results.\n"
			 "\tReturns:\n"
			 "\t\t(tuple of FSDKErrorResult and list of SearchResults): \n"
			 "\t\t\ttuple with FSDKErrorResult and list of SearchResults\n")
				;
	
	py::class_<fsdk::IDenseIndexPtr>(f, "IDenseIndexPtr", "Dense (read only) index.\n")
	
		.def("search", [](
			 const fsdk::IDenseIndexPtr& indexPtr,
			 const fsdk::IDescriptorPtr reference,
			 const int maxResultsCount) {
				 std::vector<fsdk::SearchResult> searchResults(maxResultsCount);
				 fsdk::ResultValue<fsdk::FSDKError, int> err = indexPtr->search(
				 reference,
				 maxResultsCount,
				 searchResults.data());
				 if (err.isOk()) {
					 const uint32_t searchSize = err.getValue();
					 py::list searchResultsPyList(searchSize);
					 for (uint32_t i = 0; i < searchSize; ++i)
						 searchResultsPyList[i] = searchResults[i];
					 return std::make_tuple(FSDKErrorResult(err), searchResultsPyList);
				 } else {
					 return std::make_tuple(FSDKErrorResult(err), py::list());
				 }
			 },
			 "Search for descriptors with the shorter distance to passed descriptor.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (IDescriptorPtr): Descriptor to match against index.\n"
			 "\t\tparam2 (int): Maximum count of results. It is upper bound value, it\n"
			 "\t\tdoes not guarantee to return exactly this amount of results.\n"
			 "\tReturns:\n"
			 "\t\t(tuple of FSDKErrorResult and list): tuple with FSDKErrorResult and list of SearchResults,\n")
		
		.def("size", [](
			const fsdk::IDenseIndexPtr& indexPtr) {
			return indexPtr->size();
		}, "Return size of internal storage. if not initialized, 0 is returned.\n")
		
		.def("descriptorByIndex", [](
			 const fsdk::IDenseIndexPtr& indexPtr,
			 const fsdk::DescriptorId index,
			 const fsdk::IDescriptorPtr& descriptorPtr) {
				 fsdk::Result<fsdk::FSDKError> err = indexPtr->descriptorByIndex(index, descriptorPtr);
				 if (err.isOk())
					 return std::make_tuple(FSDKErrorResult(err), descriptorPtr);
				 else
					 return std::make_tuple(FSDKErrorResult(err), fsdk::IDescriptorPtr());
			 },
			 "Requests descriptor data out of internal storage.\n"
			 "\t\tparam1 (index): Identification value of some descriptor. Might be received either\n"
			 "\t\t\tby using append() methods, or as output of search query. Must be less than size().\n"
			 "\t\tparam2 (descriptor): created descriptor object with correctly set\n"
			 "\t\t\еversion and length. Only changes data of passed descriptor.\n"
			 "\tReturns:\n"
			 "\t\t(tuple of FSDKErrorResult and descriptor):tuple with FSDKErrorResult and descriptor\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
			; // IDenseIndexPtr
		
	py::class_<fsdk::IDynamicIndexPtr>(f, "IDynamicIndexPtr", "Dynamic index")
		
		.def("saveToDenseIndex", [](const fsdk::IDynamicIndexPtr& dynamicIndex, const char* path) {
			fsdk::Result<fsdk::FSDKError> err = dynamicIndex->saveToDenseIndex(path);
			return FSDKErrorResult(err);
		}, "Saves index as dense. To load saved index use @see loadDenseIndex method.\n"
			 "\tDense index cannot be loaded as dynamic.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (str): Path to file to be created and filled with index data.\n"
			 "\t\tAny extension is acceptable.\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorResult): One of the error codes specified by FSDKErrorResult\n")
		
		.def("saveToDynamicIndex", [](const fsdk::IDynamicIndexPtr& indexPtr, const char* path) {
			fsdk::Result<fsdk::FSDKError> err = indexPtr->saveToDynamicIndex(path);
			return FSDKErrorResult(err);
		}, "Saves index as dynamic. To load saved index use @see loadDynamicIndex method.\n"
			 "\tDynamic index cannot be loaded as dense.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (str): Path to file to be created and filled with index data.\n"
			 "\t\tAny extension is acceptable.\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorResult): One of the error codes specified by FSDKErrorResult\n")
		
		.def("countOfIndexedDescriptors", [](const fsdk::IDynamicIndexPtr& dynamicIndex){
			return dynamicIndex->countOfIndexedDescriptors();
		}, "Returns count of indexed descriptors.\n"
			 "\t\t You may wonder why this method exists if we have size() method. The reason is that\n"
			 "\t\t removeDescriptor behaves differently on\n"
			 "\t\t IIndexBuild and IDynamicIndex. On builder it does actually erases\n"
			 "\t\t descriptor out of internal storage, but it does not erase it if used on\n"
			 "\t\t IDynamicIndex. The reason is that graph data structure relies on indexes\n"
			 "\t\t being constant, so removeDescriptor only removes it out of graph, so it is not\n"
			 "\t\t discoverable see search. So this methods returns actuall data\n"
			 "\t\t storage size minus count of removed descriptors.\n"
			"\tReturns:\n"
			 "\t\t(int): Count of indexed descriptors.\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("search", [](
			 const fsdk::IDynamicIndexPtr& indexPtr,
			 const fsdk::IDescriptorPtr reference,
			 const int maxResultsCount) {
				 std::vector<fsdk::SearchResult> searchResults(maxResultsCount);
				 fsdk::ResultValue<fsdk::FSDKError, int> err = indexPtr->search(
				 reference,
				 maxResultsCount,
				 searchResults.data());
				 if (err.isOk()) {
					 const uint32_t searchSize = err.getValue();
					 py::list searchResultsPyList(searchSize);
					 for (uint32_t i = 0; i < searchSize; ++i)
						 searchResultsPyList[i] = searchResults[i];
					 return std::make_tuple(FSDKErrorResult(err), searchResultsPyList);
				 } else {
					 return std::make_tuple(FSDKErrorResult(err), py::list());
				 }
			},
			"Search for descriptors with the shorter distance to passed descriptor.\n"
			"\tArgs:\n"
			"\t\tparam1 (IDescriptorPtr): Descriptor to match against index.\n"
			"\t\tparam2 (int): Maximum count of results. It is upper bound value, it\n"
			"\t\t\еdoes not guarantee to return exactly this amount of results.\n"
			"\tReturns:\n"
			"\t\t(tuple of FSDKErrorResult and list): \n"
			"\t\t\ttuple with FSDKErrorResult and list of SearchResults\n")
		
		.def("size", [](
			const fsdk::IDynamicIndexPtr& indexPtr) {
			return indexPtr->size();
		}, "Returns size of internal storage. If not initialized, 0 is returned.\n")
		
		.def("descriptorByIndex", [](
			 const fsdk::IDynamicIndexPtr& indexPtr,
			 const fsdk::DescriptorId index,
			 const fsdk::IDescriptorPtr& descriptorPtr) {
				 fsdk::Result<fsdk::FSDKError> err = indexPtr->descriptorByIndex(index, descriptorPtr);
				 if (err.isOk())
					 return std::make_tuple(FSDKErrorResult(err), descriptorPtr);
				 else
					 return std::make_tuple(FSDKErrorResult(err), fsdk::IDescriptorPtr());
			 },
			 "Requests descriptor data out of internal storage.\n"
			 "\t\tparam1 (index): Identification value of some descriptor. Might be received either\n"
			 "\t\t\tby using append methods, or as output of search query. Must be less than size().\n"
			 "\t\tparam2 (descriptor): created descriptor object with correctly set\n"
			 "\t\tversion and length. Only changes data of passed descriptor.\n"
			 "\tReturns:\n"
			 "\t\t(tuple of FSDKErrorResult and descriptor):tuple with FSDKErrorResult and descriptor\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("appendDescriptor", [](const fsdk::IDynamicIndexPtr& index, const fsdk::IDescriptorPtr batch) {
			fsdk::ResultValue<fsdk::FSDKError, fsdk::DescriptorId> err = index->appendDescriptor(batch);
			return FSDKErrorValueInt(err);
			},
			 "Appends descriptor to internal storage.\n"
			 "\t\tparam1 (descriptor): created descriptor with correct length, version and data\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueInt): One of the error codes specified by FSDKError and identification\n"
			 "\t\t\tof appended descriptor. Such identification might be used to query descriptor\n"
			 "\t\t\twith descriptorByIndex() or remove it from storage\n"
			 "\t\t\twith removeDescriptor()\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("appendBatch", [](
			 const fsdk::IDynamicIndexPtr& index,
			 const fsdk::IDescriptorBatchPtr batch) {
				 fsdk::ResultValue<fsdk::FSDKError, fsdk::DescriptorId> err = index->appendBatch(batch);
				 return FSDKErrorValueInt(err);
			 },
			 "Appends batch of descriptors to internal storage.\n"
			 "\t\tparam1 (batch): Batch of descriptors with correct length, version and data\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueInt): One of the error codes specified by FSDKError and identification\n"
			 "\t\tof appended descriptor. Other descriptors from batch are appended\n"
			 "\t\tsequentially in the same order as they are in the batch. Such identification\n"
			 "\t\t might be used to query descriptor with\n"
			 "\t\tdescriptorByIndex() or remove it from storage\n"
			 "\t\twith removeDescriptor().\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("removeDescriptor", [](const fsdk::IDynamicIndexPtr& dynamicIndex, const fsdk::DescriptorId id){
				 fsdk::Result<fsdk::FSDKError> err = dynamicIndex->removeDescriptor(id);
				 return FSDKErrorResult(err);
			 },
			 "Removes descriptor out of internal storage.\n"
			 "\t\tIf used on IDynamicIndex graph updates itself too.\n"
			 "\t\tIMPORTANT: If used on IDynamicIndex it will NOT actually erase\n"
			 "\t\tdescriptor with given index out of internal storage. Instead, it will\n"
			 "\t\tremove it out of graph, so it is not searchable.\n"
			 "\t\tIf used on @see IIndexBuilder, it WILL actually erase it. But beware:\n"
			 "\t\tif your storage is big enough performance might be very poor, because\n"
			 "\t\tdescriptors are stored sequentially in vector-like data structure, so every\n"
			 "\t\telement after erased will be moved.\n"
			 "\t\tparam1 (index): Identification of descriptors position in internal storage.\n"
			 "\t\tIs received by using append methods or search()\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueInt): One of the error codes specified by FSDKError\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
			; // IDynamicIndexPtr
	
	py::class_<fsdk::IIndexBuilderPtr>(f, "IIndexBuilderPtr")
	
		.def("buildIndex", [](const fsdk::IIndexBuilderPtr& indexBuilderPtr) {
			auto res = indexBuilderPtr->buildIndex();
			if (res.isOk())
				return std::make_tuple(FSDKErrorResult(fsdk::makeResult(res.getError())), fsdk::acquire(res.getValue()));
			else
				return std::make_tuple(FSDKErrorResult(fsdk::makeResult(res.getError())), fsdk::IDynamicIndexPtr());
		}, "Builds index with every descriptor appended. Blocks until completed.\n"
			 "\t\t Is very heavy method in terms of computing load.\n")
		
		.def("appendDescriptor", [](const fsdk::IIndexBuilderPtr& indexBuilderPtr, const fsdk::IDescriptorPtr batch){
				 fsdk::ResultValue<fsdk::FSDKError, fsdk::DescriptorId> err = indexBuilderPtr->appendDescriptor(batch);
				 return FSDKErrorValueInt(err);
			 },
			 "Appends descriptor to internal storage.\n"
			 "\t\tparam1 (descriptor): created descriptor with correct length, version and data\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueInt): One of the error codes specified by FSDKError and identification\n"
			 "\t\t\tof appended descriptor. Such identification might be used to query descriptor\n"
			 "\t\t\twith descriptorByIndex() or remove it from storage\n"
			 "\t\t\twith removeDescriptor()\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("appendBatch", [](
			 const fsdk::IIndexBuilderPtr& indexBuilderPtr,
			 const fsdk::IDescriptorBatchPtr batch) {
				 fsdk::ResultValue<fsdk::FSDKError, fsdk::DescriptorId> err = indexBuilderPtr->appendBatch(batch);
				 return FSDKErrorValueInt(err);
			 },
			 "Appends batch of descriptors to internal storage.\n"
			 "\t\tparam1 (batch): Batch of descriptors with correct length, version and data\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueInt): One of the error codes specified by FSDKError and identification\n"
			 "\t\t\tof appended descriptor. Other descriptors from batch are appended\n"
			 "\t\t\tsequentially in the same order as they are in the batch. Such identification\n"
			 "\t\t\tmight be used to query descriptor with\n"
			 "\t\t\tdescriptorByIndex() or remove it from storage\n"
			 "\t\t\twith removeDescriptor().\n"
			 "\t\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("removeDescriptor", [](const fsdk::IIndexBuilderPtr& indexBuilderPtr, const fsdk::DescriptorId index) {
				 fsdk::Result<fsdk::FSDKError> err = indexBuilderPtr->removeDescriptor(index);
				 return FSDKErrorResult(err);
			 },
			 "Removes descriptor out of internal storage.\n"
			 "If used on IDynamicIndex graph updates itself too.\n"
			 "\t\tIMPORTANT: If used on IDynamicIndex it will NOT actually erase\n"
			 "\t\tdescriptor with given index out of internal storage. Instead, it will\n"
			 "\t\tremove it out of graph, so it is not searchable.\n"
			 "\t\tIf used on @see IIndexBuilder, it WILL actually erase it. But beware:\n"
			 "\t\tif your storage is big enough performance might be very poor, because\n"
			 "\t\tdescriptors are stored sequentially in vector-like data structure, so every\n"
			 "\t\telement after erased will be moved.\n"
			 "\t\tparam1 (index): Identification of descriptors position in internal storage.\n"
			 "\t\tIs received by using append methods or search()\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueInt): One of the error codes specified by FSDKError"
			 "\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def("descriptorByIndex", [](
			 const fsdk::IIndexBuilderPtr& indexBuilderPtr,
			 const fsdk::DescriptorId index,
			 const fsdk::IDescriptorPtr& descriptorPtr) {
				 fsdk::Result<fsdk::FSDKError> err = indexBuilderPtr->descriptorByIndex(index, descriptorPtr);
			
				 if (err.isOk())
					 return std::make_tuple(FSDKErrorResult(err), descriptorPtr);
				 else
					 return std::make_tuple(FSDKErrorResult(err), fsdk::IDescriptorPtr());
			 },
			 "Requests descriptor data out of internal storage.\n"
			 "\t\tparam1 (index): Identification value of some descriptor. Might be received either\n"
			 "\t\t\tby using append methods, or as output of search query. Must be less than size().\n"
			 "\t\tparam2 (descriptor): created descriptor object with correctly set\n"
			 "\t\tversion and length. Only changes data of passed descriptor.\n"
			 "\tReturns:\n"
			 "\t\t(tuple of FSDKErrorResult and descriptor):tuple with FSDKErrorResult and descriptor\n"
			 "\t\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")

//		we do not need this now
//		.def("buildIndexAsync", [](const fsdk::IIndexBuilderPtr& indexBuilderPtr) {
//			auto res = indexBuilderPtr->buildIndex();
//			if (res.isOk())
//				return std::make_tuple(FSDKErrorResult(res), fsdk::acquire(res.getValue()));
//			else
//				return std::make_tuple(FSDKErrorResult(res), fsdk::IDynamicIndexPtr());
//		}, "")
			; // IIndexBuilderPtr
	
	py::class_<fsdk::IQualityEstimatorPtr>(f, "IQualityEstimatorPtr",
		"Image quality estimator interface.\n"
		"This estimator is designed to work with a person face image; you should pass a warped face detection image.\n"
		"Quality estimator detects the same attributes as all the other estimators:\n"
		"\tover/under exposure;\n"
		"\tblurriness;\n"
		"\tnatural/unnatural colors;\n")
	
		.def("estimate",[](
			 const fsdk::IQualityEstimatorPtr& est,
			 const fsdk::Image &warp) {
				 fsdk::Quality out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate the quality. If success returns quality output structure with quality params, else error code "
			 "(see FSDKErrorResult for details). \n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): image with warped face. Format must be R8G8B8"
			 "\tReturns:\n"
			 "\t\t(Quality): if success - output Quality,\n"
			 "\t\t(FSDKErrorResult): else error code FSDKErrorResult\n")
			;
	
	py::class_<fsdk::IAttributeEstimatorPtr>(f, "IAttributeEstimatorPtr",
		 "Face image attribute estimator interface. This estimator is designed to work with a person face image; \n"
		 "you should pass a warped face detection image. Estimated attributes are: \n"
		 "\tage;\n"
		 "\tgender;\n"
		 "\tglasses;\n")
	
		.def("estimate", [](
			 const fsdk::IAttributeEstimatorPtr& est,
			 const fsdk::Image &warp) {
				 fsdk::AttributeEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate the attributes. If success returns AttributeEstimation output structure with params, else error code.\n"
			 "\t\t(see FSDKErrorResult for details)\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): image with warped face. Format must be R8G8B8\n"
			 "\tReturns:\n"
			 "\t\t(AttributeEstimation): if success - AttributeEstimation,\n"
			 "\t\t(FSDKErrorResult): else error code FSDKErrorResult\n")
		;
		
		py::class_<fsdk::IEthnicityEstimatorPtr>(f, "IEthnicityEstimatorPtr",
			"Ethnicity estimator interface. This estimator is designed to work with a person face image; \n"
			"you should pass a warped face detection image obtained from IWarper. \n"
			"See EthnicityEstimation for output details")
		
		.def("estimate",[](
			 const fsdk::IEthnicityEstimatorPtr& est,
			 const fsdk::Image &warp) {
				 fsdk::EthnicityEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Ethnicity estimator interface. If success returns EthnicityEstimation structure with params, else error code. \n"
			 "See FSDKErrorResult for details. This estimator is designed to work with a person face image; \n"
			 "you should pass a warped face detection image obtained from IWarper\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): image with warped face. Format must be R8G8B8"
			 "\tReturns:\n"
			 "\t\t(EthnicityEstimation): if success - EthnicityEstimation,\n"
			 "\t\t(FSDKErrorResult): else error code FSDKErrorResult\n")
			;
	
	py::class_<fsdk::IDetectorPtr>(f, "IDetectorPtr", "Face detector interface")
	
		.def("detect",[](
			 const fsdk::IDetectorPtr& det,
			 const fsdk::Image& image,
			 const fsdk::Rect& rect,
			 uint32_t maxCount) {
				 std::vector<fsdk::Detection> detections(maxCount);
				 std::vector<fsdk::Landmarks5> landmarks(maxCount);
				 std::vector<fsdk::Landmarks68> landmarks68(maxCount);
				 fsdk::ResultValue<fsdk::FSDKError, int> err = det->detect(
				 image,
				 rect,
				 detections.data(),
				 landmarks.data(),
				 landmarks68.data(),
				 maxCount);
				 
				 if (err.isOk()) {
					 auto detectionResultPyList = py::list(err.getValue());
					 for (uint32_t i = 0; i < (uint32_t)err.getValue(); ++i) {
						 detectionResultPyList[i] = std::make_tuple(detections[i], landmarks[i], landmarks68[i]);
					 }
					 return std::make_tuple(FSDKErrorValueInt(err), detectionResultPyList);
				 } else {
					 return std::make_tuple(FSDKErrorValueInt(err), py::list());
				 }},
			 "Detect faces and landmarks on the image\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): input image. Format must be R8G8B8\n"
			 "\t\tparam2 (Rect): rect of interest inside of the image\n"
			 "\t\tparam3 (int): length of `detections` and `landmarks` arrays\n"
			 "\tReturns:\n"
			 "\t\t(tuple with FSDKErrorValueInt code and list of tuples): \n"
			 "\t\t\ttuple with FSDKErrorValueInt code and list of tuples from\n"
			 "\t\t\tDetection, Landmarks5, Landmarks68see FSDKErrorValueInt (see FSDKErrorValueInt)\n")
		
		.def("detect_light",[](
			 const fsdk::IDetectorPtr& det,
			 const fsdk::Image& image,
			 const fsdk::Rect& rect,
			 int maxCount) {
				 std::vector<fsdk::Detection> detections(maxCount);
				 fsdk::ResultValue<fsdk::FSDKError, int> err = det->detect(
				 image,
				 rect,
				 detections.data() ,
				 maxCount);
				
				if (err.isOk()) {
					auto detectionResultPyList = py::list(err.getValue());
					for (uint32_t i = 0; i < (uint32_t)err.getValue(); ++i) {
						detectionResultPyList[i] = detections[i];
					}
					return std::make_tuple(FSDKErrorValueInt(err), detectionResultPyList);
				} else {
					return std::make_tuple(FSDKErrorValueInt(err), py::list()); }},
			 "Detect faces and landmarks on the image\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): input image. Format must be R8G8B8\n"
			 "\t\tparam2 (Rect): rect of interest inside of the image\n"
			 "\t\tparam3 (int): length of `detections` array\n"
			 "\tReturns:\n"
			 "\t\t(tuple with FSDKErrorValueInt code and list of Detections): \n"
			 "\t\t\ttuple with FSDKErrorValueInt code and list of Detections (see FSDKErrorValueInt)\n")
		
		.def("detect5",[](
			 const fsdk::IDetectorPtr& det,
			 const fsdk::Image& image,
			 const fsdk::Rect& rect,
			 int maxCount) {
				 std::vector<fsdk::Detection> detections(maxCount);
				 std::vector<fsdk::Landmarks5> landmarks(maxCount);
				 fsdk::ResultValue<fsdk::FSDKError, int> err = det->detect(
				 image,
				 rect,
				 detections.data(),
				 landmarks.data(),
				 maxCount);
				 auto detectionResultPyList = py::list();
			
			
			if (err.isOk()) {
				auto detectionResultPyList = py::list(err.getValue());
				for (uint32_t i = 0; i < (uint32_t)err.getValue(); ++i)
					detectionResultPyList[i] = std::make_tuple(detections[i], landmarks[i]);
				
				return std::make_tuple(FSDKErrorValueInt(err), detectionResultPyList);
			} else
				return std::make_tuple(FSDKErrorValueInt(err), py::list()); },
			 
			 "Detect faces and landmarks on the image\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): input image. Format must be R8G8B8\n"
			 "\t\tparam2 (Rect): rect of interest inside of the image\n"
			 "\t\tparam3 (int): length of `detections` and `landmarks` arrays\n"
			 "\tReturns:\n"
			 "\t\t(tuple with FSDKErrorValueInt code and list of tuples): \n"
			 "\t\t\t tuple with FSDKErrorValueInt code and list of tuples from Detection, Landmarks5 (see FSDKErrorValueInt)\n")
			;
	
	py::class_<fsdk::IWarperPtr>(f, "IWarperPtr",
		"Face detection area warper interface.\n"
		"\tPerform affine transformations on an image to properly align depicted face for descriptor extraction.\n")
	
		.def("warp",[](
			 const fsdk::IWarperPtr& warper,
			 const fsdk::Image& image,
			 const fsdk::Transformation& transformation) {
				 fsdk::Image transformedImage;
				 fsdk::Result<fsdk::FSDKError> error = warper->warp(image, transformation, transformedImage);
				 if (error.isOk())
					 return py::cast(transformedImage);
				 else
					 return py::cast(FSDKErrorResult(error)); },
			 "Warp image\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): input image. Format must be R8G8B8\n"
			 "\t\tparam2 (Transformation): transformation data\n"
			 "\tReturns:\n"
			 "\t\t(Image): if success - output transformed image,\n"
			 "\t\t(FSDKErrorResult): else error code FSDKErrorResult\n")
		
		.def("warp",[](
			 const fsdk::IWarperPtr& warper,
			 const fsdk::Landmarks5& landmarks,
			 const fsdk::Transformation& transformation) {
				 fsdk::Landmarks5 transformedLandmarks5;
				 fsdk::Result<fsdk::FSDKError> error = warper->warp(
				 landmarks,
				 transformation,
				 transformedLandmarks5);
				 if (error.isOk())
					 return py::cast(transformedLandmarks5);
				 else
					 return py::cast(FSDKErrorResult(error)); },
			 "Warp landmarks of size 5\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Landmarks5): landmarks array of size 5\n"
			 "\t\tparam2 (Transformation): transformation data\n"
			 "\tReturns:\n"
			 "\t\t(Landmarks5): if success - output transformed image,\n"
			 "\t\t(FSDKErrorResult): else error code FSDKErrorResult\n")
		
		.def("warp",[](
			 const fsdk::IWarperPtr& warper,
			 const fsdk::Landmarks68& landmarks68,
			 const fsdk::Transformation& transformation) {
				 fsdk::Landmarks68 transformedLandmarks68;
				 fsdk::Result<fsdk::FSDKError> error = warper->warp(landmarks68,
																	transformation,
																	transformedLandmarks68);
				 if (error.isOk())
					 return py::cast(transformedLandmarks68);
				 else
					 return py::cast(FSDKErrorResult(error)); },
			 "Warp landmarks of size 68\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Landmarks68): landmarks array of size 68\n"
			 "\t\tparam2 (Transformation): transformation data\n"
			 "\tReturns:\n"
			 "\t\t(Landmarks68): if success - transformed landmarks of size 68,\n"
			 "\t\t(FSDKErrorResult): else -  error code FSDKErrorResult\n")
		
		.def("createTransformation",[](
			 const fsdk::IWarperPtr& warper,
			 const fsdk::Detection& detection,
			 const fsdk::Landmarks5& landmarks) {
				 return warper->createTransformation(detection, landmarks); },
			 "Create transformation data struct.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Detection): detection rect where landmarks are.\n"
			 "\t\tparam2 (Landmarks5): landmarks to calculate warping angles\n"
			 "\tReturns:\n"
			 "\t\t(Transformation): Transformation obj,\n")
			;
	
	// descriptor
	py::class_<fsdk::IDescriptorPtr>(f, "IDescriptorPtr", "Descriptor interface. Used for matching.\n")
	
		.def("getModelVersion",[]( const fsdk::IDescriptorPtr& desc) {
				 return desc->getModelVersion(); },
			 "Get algorithm model version this descriptor was created with.\n"
			 "\tReturns:\n"
			 "\t\t(int): Version as integral number.\n")
		
		.def("getDescriptorLength",[]( const fsdk::IDescriptorPtr& desc) {
				 return desc->getDescriptorLength(); },
			 "Return size of descriptor in bytes.\n"
			 "This method is thread safe.\n"
			 "\tReturns:\n"
			 "\t\t(int): size of descriptor in bytes.\n")
		
		.def("getDescriptor",[]( const fsdk::IDescriptorPtr& desc) {
				 const int size = 264;
				 std::vector<uint8_t>buffer(size, 0);
				 bool allocated = desc->getDescriptor(&buffer.front());
				 auto l = py::list(size);
				 int i = 0;
				 for (auto it = buffer.rbegin(); it != buffer.rend(); ++it) {
					 l[i] = *it;
					 ++i;
				 }
				 if (allocated)
					 return l;
				 else
					 return py::list(); },
			 "Copy descriptor data to python list.\n "
			 "\tThis method is thread safe"
			 "\tReturns:\n"
			 "\t\t(list): list of uint8_t if is ok (length of list is 264), empty list if ERROR")
		.def("load",[]( const fsdk::IDescriptorPtr& descriptor,
						const char* buffer,
						uint32_t bufferSize) {
			std::vector<uint8_t> descriptorExpectedSerial(bufferSize);
			memcpy(&descriptorExpectedSerial.front(), buffer, bufferSize);
			VectorArchive archiveDescriptor(descriptorExpectedSerial);
			fsdk::Result<fsdk::ISerializableObject::Error> err = descriptor->load(&archiveDescriptor);
			return SerializeErrorResult(err);
		}, "Load descriptor from buffer")
			; // descriptor
	
	py::enum_<fsdk::ISerializableObject::Error>(f, "SerializeError",
												"Serialization error codes.\n")
		.value("Ok", fsdk::ISerializableObject::Error::Ok)
		.value("Size", fsdk::ISerializableObject::Error::Size)
		.value("Signature", fsdk::ISerializableObject::Error::Signature)
		.value("ArchiveRead", fsdk::ISerializableObject::Error::ArchiveRead)
		.value("InputArchive", fsdk::ISerializableObject::Error::InputArchive)
		.value("ArchiveWrite", fsdk::ISerializableObject::Error::ArchiveWrite)
			; // error

//	Errors
	py::class_<SerializeErrorResult>(f, "SerializeErrorResult",
									 "Wrapper for ISerializableObject::Error that encapsulates an action result enumeration.\n"
									 "\tAn enum should specify a result code.\n")
		.def_readonly("isOk", &SerializeErrorResult::isOk)
		.def_readonly("isError", &SerializeErrorResult::isError)
		.def_readonly("serializeError", &SerializeErrorResult::serializeError)
		.def_readonly("what", &SerializeErrorResult::what)
		.def("__repr__",
			 [](const SerializeErrorResult &err) {
				 return "SerializeErrorResult: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", serializeError = " +
						fsdk::ErrorTraits<fsdk::ISerializableObject::Error>::toString(err.serializeError)
						+ ", what = " + err.what; })
			;

// DescriptorBatch
	py::class_<fsdk::IDescriptorBatchPtr>(f, "IDescriptorBatchPtr", "Descriptor batch interface. "
	"Used for matching large continuous sets of descriptors")
	
		.def("add",[] (
			 const fsdk::IDescriptorBatchPtr& descriptorBatchPtr,
			 const fsdk::IDescriptorPtr& desc) {
				 fsdk::Result<fsdk::IDescriptorBatch::Error> error = descriptorBatchPtr->add(desc);
				 return DescriptorBatchResult(error);
			 },
			 "Add a descriptor to the batch.\n"
			 "\tWhen adding the first descriptor to an empty batch, the initial internal parameters (like version,\n"
			 "\tetc) of the batch are set to correspond ones of the descriptor. This means that incompatible descriptors\n"
			 "\tadded later will be rejected. See getModelVersion() to check whether a descriptor can be added to the batch.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (IDescriptorPtr): descriptor to add. Descriptor data is copied and to internal reference is held,\n"
			 "\t\tthus it is safe to release the source descriptor object later.\n"
			 "\tReturns:\n"
			 "\t\t(DescriptorBatchResult): One of the error codes specified by DescriptorBatchError.\n")
		
		.def("removeFast",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr, const int index) {
				 fsdk::Result<fsdk::IDescriptorBatch::Error> error = descriptorBatchPtr->removeFast(index);
				 return DescriptorBatchResult(error); },
			 "Remove a descriptor from batch. \nRemove descriptor by swapping it with the last descriptor in batch.\n"
			 "\tThis preserves descriptor order.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int): descriptor index\n"
			 "\tReturns:\n"
			 "\t\t(DescriptorBatchResult): One of the error codes specified by DescriptorBatchError.\n")
		
		.def("removeSlow",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr, int index) {
				 if (index < 0 || index >= int(descriptorBatchPtr->getCount())) throw py::index_error();
				 fsdk::Result<fsdk::IDescriptorBatch::Error> error = descriptorBatchPtr->removeSlow(index);
				 return  DescriptorBatchResult(error);},
			 "Remove a descriptor from batch.\n"
			 "\tRemove descriptor by shifting all the following descriptors back. This preserves descriptor order.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int): descriptor index\n"
			 "\tReturns:\n"
			 "\t\t(DescriptorBatchResult): One of the error codes specified by DescriptorBatchError.\n" )
		
		.def("getMaxCount",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr) {
				 return descriptorBatchPtr->getMaxCount(); },
			 "Get maximum number of descriptors in this batch.\n"
			 "\tReturns:\n"
			 "\t\t(int): maximum number of descriptors in this batch.\n")
		
		.def("getCount",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr) {
				 return descriptorBatchPtr->getCount(); },
			 "Get actual number of descriptors in this batch.\n"
			 "\tReturns:\n"
			 "\t\t(int):actual number of descriptors in this batch.\n")
		
		.def("getModelVersion",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr) {
				 return descriptorBatchPtr->getModelVersion(); },
			 "Get algorithm model version the descriptors in this batch were created with.\n"
			 "This function only makes sense when there is at least one descriptor in the batch. It will return 0 if\n"
			 "the batch is empty.\n"
			 "\tReturns:\n"
			 "\t\t(int): Version as integral number.\n")
		
		.def("getDescriptorSize",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr) {
				 return descriptorBatchPtr->getDescriptorSize(); },
			 "Get length of one descriptor. Specified by version of descriptors in batch.\n"
			 "\tReturns:\n"
			 "\t\t(int): Length of one descriptor in batch.\n")
		
		.def("getDescriptorSlow",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr, int index) {
				 std::cout << "MSD = " << index << " " << descriptorBatchPtr->getCount() << std::endl;
				 if (index < 0 || index >= int(descriptorBatchPtr->getCount())) throw py::index_error();
				 return fsdk::acquire(descriptorBatchPtr->getDescriptorSlow(index)); },
			 "Create descriptor from batch by index with copying\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int):  index required descriptor in batch\n"
			 "\tReturns:\n"
			 "\t\t(IDescriptorPtr): valid object if succeeded.\n")
		
		.def("getDescriptorFast",[]( const fsdk::IDescriptorBatchPtr& descriptorBatchPtr, int index) {
				 if (index < 0 || index >= int(descriptorBatchPtr->getCount())) throw py::index_error();
				 return fsdk::acquire(descriptorBatchPtr->getDescriptorFast(index)); },
			 "Create descriptor from batch by index without copying\n"
			 "\tArgs:\n"
			 "\t\tparam1 (int):  index required descriptor in batch\n"
			 "\tReturns:\n"
			 "\t\t(IDescriptorPtr): valid object if succeeded.\n")
		
		.def("load",[](const fsdk::IDescriptorBatchPtr& descriptorBatchPtr,
					   const char* buffer,
					   uint32_t bufferSize) {
			std::vector<uint8_t> batchExpectedSerial(bufferSize);
			memcpy(&batchExpectedSerial.front(), buffer, bufferSize);
			VectorArchive archiveDescriptor(batchExpectedSerial);
			fsdk::Result<fsdk::ISerializableObject::Error> err = descriptorBatchPtr->load(&archiveDescriptor, bufferSize);
			return SerializeErrorResult(err);
			
		}, "Load descriptor from buffer")
			;
	
	py::enum_<fsdk::IDescriptorBatch::Error>(f, "DescriptorBatchError",
		"Descriptor batch error enumeration.\n"
		"\tUsed for descriptor batch related errors indication.\n")
		.value("Ok", fsdk::IDescriptorBatch::Error::Ok)
		.value("InvalidInput", fsdk::IDescriptorBatch::Error::InvalidInput)
		.value("BatchFull", fsdk::IDescriptorBatch::Error::BatchFull)
		.value("Incompatible", fsdk::IDescriptorBatch::Error::Incompatible)
		.value("Internal", fsdk::IDescriptorBatch::Error::Internal)
		.value("IoError", fsdk::IDescriptorBatch::Error::IoError)
		.value("OutOfRange", fsdk::IDescriptorBatch::Error::OutOfRange)
		;
	
	py::class_<fsdk::IDescriptorExtractorPtr>(f, "IDescriptorExtractorPtr",
		"Descriptor extractor interface.\n"
		"\tExtracts face descriptors from images. The descriptors can be later used for face matching.\n")
	
		.def("extract",[](
			 const fsdk::IDescriptorExtractorPtr& extractor,
			 fsdk::Image& image,
			 const fsdk::Detection& detection,
			 const fsdk::Landmarks5& landmarks,
			 const fsdk::IDescriptorPtr& descriptor) {
				 fsdk::ResultValue<fsdk::FSDKError, float> err = extractor->extract(image, detection,
																					landmarks, descriptor);
				 return py::cast(FSDKErrorValueFloat(err)); },
			 "Extract a face descriptor from an image.\n"
			 "\tThis method accepts arbitrary images that have size at least 250x250 pixels and R8G8B8 pixel format.\n"
			 "\tThe input image is warped internally using an assigned warper (@see IWarper). The descriptor extractor is\n"
			 "\tcreated with a proper warped assigned by default so no additional setup is required, unless this behaviour\n"
			 "\tis overriden with `defaultWarper` flag upon extractor creation.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image):  source image. Format must be R8G8B8\n"
			 "\t\tparam2 (Detection): face detection\n"
			 "\t\tparam3 (Landmarks5): face feature set\n"
			 "\t\tparam4 (IDescriptorPtr) [out]: descriptor to fill with data.\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueFloat): ResultValue with error code specified by FSDKError and score of descriptor normalized in range [0, 1]\n"
			 "\t\t\t1 - face on the input warp; 0 - garbage on the input detection.\n"
			 "\t\t\tScore is fake if extractor uses mobile net version of extraction model.\n"
			 "\t\tSee FSDKErrorValueFloat.\n")
		
		.def("extractFromWarpedImage",[](
			 const fsdk::IDescriptorExtractorPtr& extractor,
			 const fsdk::Image& image,
			 const fsdk::IDescriptorPtr& descriptor) {
				 fsdk::ResultValue<fsdk::FSDKError, float> err = extractor->extractFromWarpedImage(image, descriptor);
				 return py::cast(FSDKErrorValueFloat(err)); },
			 "Extract descriptor from a warped image.\n"
			 "\tThe input image should be warped; see IWarper.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (Image): image source warped image, should be a valid 250x250 image in R8G8B8 format.\n"
			 "\t\tparam2 (IDescriptorPtr) [out]: descriptor to fill with data\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueFloat): ResultValue with error code specified by FSDKError and score of descriptor normalized in range [0, 1]\n"
			 "\t\t\t1 - face on the input warp; 0 - garbage on the input detection.\n"
			 "\t\t\tScore is fake if extractor uses mobile net version of extraction model.\n"
			 "\t\tSee FSDKErrorValueFloat.\n")
		
		.def("extractFromWarpedImageBatch",[](
			 const fsdk::IDescriptorExtractorPtr& extractor,
			 py::list warpsBatchList,
			 const fsdk::IDescriptorBatchPtr& descriptorBatch,
			 const fsdk::IDescriptorPtr& aggregation,
			 uint32_t batchSize) {
				 std::vector<float> garbageScoreBatch(batchSize);
				 std::vector<fsdk::Image> warpsBatch(batchSize);
				 for (uint32_t i = 0; i < batchSize; ++i) {
					 warpsBatch[i] = warpsBatchList[i].cast<fsdk::Image>();
				 }
				 fsdk::Result<fsdk::FSDKError> err = extractor->extractFromWarpedImageBatch(
				 warpsBatch.data(),
				 descriptorBatch,
				 aggregation,
				 garbageScoreBatch.data(),
				 batchSize);
				 auto garbagePyList = py::list();
				 if (err.isOk()) {
					 for (uint32_t i = 0; i < batchSize; ++i) {
						 garbagePyList.append(garbageScoreBatch[i]);
					 }
					 return garbagePyList;
				 }
				 else {
					 garbagePyList.append(FSDKErrorResult(err));
					 return garbagePyList;
				 } },
			 "Extract batch of descriptors from a batch of images and perform aggregation.\n"
			 "\tThe input images should be warped; see IWarper.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (list):  input array of warped images, images should be in R8G8B8 format, "
			 "with size 250x250\n"
			 "\t\tparam2 (IDescriptorBatchPtr) [out]:  descriptorBatch descriptor batch to fill with data.\n"
			 "\t\tparam3 (IDescriptorPtr) [out]: descriptor with aggregation based on descriptor batch.\n"
			 "\t\tparam4 (int): size of the batch.\n"
			 "\tReturns:\n"
			 "\t\t(list): if OK - list of descriptor scores normalized in range [0, 1]\n"
			 "\t\t\t1 - face on the input warp; 0 - garbage on the input warp.\n"
			 "\t\t\tScore is fake if extractor uses mobile net version of extraction model.\n"
			 "\t\t(FSDKErrorResult): else - result with error code specified by FSDKError\n See FSDKErrorResult.\n")
		
		.def("extractFromWarpedImageBatch",[](
			 const fsdk::IDescriptorExtractorPtr& extractor,
			 py::list warpsBatchList,
			 const fsdk::IDescriptorBatchPtr& descriptorBatch,
			 uint32_t batchSize) {
				 std::vector<float> garbageScoreBatch(batchSize);
				 std::vector<fsdk::Image> warpsBatch(batchSize);
				 for (uint32_t i = 0; i < batchSize; ++i) {
					 warpsBatch[i] = warpsBatchList[i].cast<fsdk::Image>();
				 }
				 fsdk::Result<fsdk::FSDKError> err = extractor->extractFromWarpedImageBatch(
				 warpsBatch.data(),
				 descriptorBatch,
				 garbageScoreBatch.data(),
				 batchSize);
				 py::list garbagePyList;
				 if (err.isOk()) {
					 for (uint32_t i = 0; i < batchSize; ++i) {
						 garbagePyList.append(garbageScoreBatch[i]);
					 }
					 return garbagePyList;
				 }
				 else {
					 garbagePyList.append(FSDKErrorResult(err));
					 return garbagePyList; } },
			 "Extract batch of descriptors from a batch of images.\n"
			 "\tThe input images should be warped; see IWarperPtr.\n"
			 "\tArgs:\n"
			 "\t\tparam1 (list): input list of warped images.Images should be in R8G8B8 format , with size 250x250\n"
			 "\t\tparam2 (IDescriptorBatchPtr) [out]: \n"
			 "\t\tparam3 (int): size of the batch\n"
			 "\tReturns:\n"
			 "\t\t(list): if OK - list of descriptor scores normalized in range [0, 1]\n"
			 "\t\t\t1 - face on the input warp; 0 - garbage on the input warp.\n"
			 "\t\t\t Score is fake if extractor uses mobile net version of extraction model.\n"
			 "\t\t(FSDKErrorResult): else - result with error code specified by FSDKError\n See FSDKErrorResult.\n")
			;
	
	py::class_<fsdk::IDescriptorMatcherPtr>(f, "IDescriptorMatcherPtr",
		"Descriptor matcher interface.\n"
		"\tMatches descriptors 1:1 and 1:M (@see IDescriptor and IDescriptorBatch interfaces).\n"
		"\tAs a result of the matching process the calling site gets a MatchingResult "
		"(or several of them in case of 1:M\n"
		"\tmatching). The MatchingResult structure contains distance and similarity metrics.\n"
		"\t\n"
		"\tDistance is measured in abstract units and tends to 0 for similar descriptors "
		"and to infinity for different ones.\n"
		"\tSimilarity is the opposite metric and shows probability of two "
		"descriptors belonging to the same person; therfore\n"
		"\tit is normalized to [0..1] range")
		
		.def("match",[](
			 const fsdk::IDescriptorMatcherPtr& matcherPtr,
			 const fsdk::IDescriptorPtr& first,
			 const fsdk::IDescriptorPtr& second) {
				 fsdk::ResultValue<fsdk::FSDKError, fsdk::MatchingResult> err =
				 matcherPtr->match(first, second);
				 return FSDKErrorValueMatching(err); },
			 "Match descriptors 1:1.\n"
			 "\tArgs\n"
			 "\t\tparam1 (IDescriptorPtr): first descriptor\n"
			 "\t\tparam2 (IDescriptorPtr): second descriptor\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueMatching): Value with error code specified by FSDKError and matching result. "
			 "See FSDKErrorValueMatching.\n")
		
		.def("match",[](
			 const fsdk::IDescriptorMatcherPtr& matcherPtr,
			 const fsdk::IDescriptorPtr& reference,
			 const fsdk::IDescriptorBatchPtr& candidates) {
				 std::vector<fsdk::MatchingResult> results(candidates->getCount());
				 fsdk::Result<fsdk::FSDKError> err =
				 matcherPtr->match(reference, candidates, results.data());
				 auto resultsPyList = py::list();
				 if (err.isOk()) {
					 for (const auto& it: results) {
						 resultsPyList.append(it);
					 }
					 return resultsPyList;
				 }
				 else {
					 resultsPyList.append(FSDKErrorResult(err));
					 return resultsPyList; } },
			 "Match descriptors 1:M.\n"
			 "\tMatches a reference descriptor to a batch of candidate descriptors. "
			 "The results are layed out in the\n"
			 "\tsame order as the candidate descriptors in the batch.\n"
			 "\tArgs\n"
			 "\t\tparam1 (IDescriptorPtr): the reference descriptor\n"
			 "\t\tparam2 (IDescriptorPtr): the candidate descriptor batch to match with the reference\n"
			 "\tReturns:\n"
			 "\t\t(list): if OK - matchig result list.\n"
			 "\t\t\tLength of `results` must be at least the same as the length of the candidates batch.\n"
			 "\t\t\tIDescriptorBatchPtr::getMaxCount()\n"
			 "\t\t(FSDKErrorResult wrapped in list): else - result with error specified by FSDKErrorResult.\n")
			;

//	second part of estimators
	py::class_<fsdk::IHeadPoseEstimatorPtr>(f, "IHeadPoseEstimatorPtr",
		"Head pose angles estimator interface.\n"
		"\tThis estimator is designed to work with 68 landmark points extracted from photo using face detector;\n"
		"\tsee IDetector for details.\n"
		"\tdetails Estimated angles are:\n"
		"\t\tpitch;\n"
		"\t\tyaw;\n"
		"\t\troll.\n"
		"\tsee HeadPoseEstimation structure for details about how exactly the estimations are reported")
	
		.def("estimate",[](
		const fsdk::IHeadPoseEstimatorPtr& est,
		const fsdk::Landmarks68& landmarks68) {
			fsdk::HeadPoseEstimation out;
			fsdk::Result<fsdk::FSDKError> err = est->estimate(landmarks68, out);
			if (err.isOk())
				return py::cast(out);
			else
				return py::cast(FSDKErrorResult(err)); })
		.def("estimate",[](
			 const fsdk::IHeadPoseEstimatorPtr& est,
			 const fsdk::Image& image,
			 const fsdk::Detection& detection) {
				 fsdk::HeadPoseEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(image, detection, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate the angles.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): image source image. Format must be R8G8B8.\n"
			 "\t\tparam2 (Detection): detection.\n"
			 "\tReturns:\n"
			 "\t\t(HeadPoseEstimation): if OK - output estimation; see AngleEstimation.\n"
			 "\t\t(FSDKErrorResult): else - Result with error specified by FSDKErrorResult.\n")
			;
	
	py::class_<fsdk::Ref<fsdk::IBlackWhiteEstimator>>(f, "IBlackWhiteEstimatorPtr",
		  "Grayscale image estimator interface.\n"
		  "\tThis estimator is indifferent to image content and dimensions; you can pass both face crops (including\n"
		  "\twarped images) and full frames.\n")
	
		.def("estimate",[](
			 const fsdk::Ref<fsdk::IBlackWhiteEstimator>& est,
			 const fsdk::Image& image) {
				 bool outIsGrayscale;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(image, outIsGrayscale);
				 if (err.isOk())
					 return py::cast(outIsGrayscale);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Check if image is grayscale or colo.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): image source image. Format must be R8G8B8.\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorResult): estimation result; true if image is grayscale, false if not.\n")
			;
	
	py::class_<fsdk::ILivenessDepthEstimatorPtr>(f, "ILivenessDepthEstimatorPtr",
												 "Depth estimator interface.\n"
												 "\tThis estimator is designed for face analysis using depth map. It works with 16 bit depth map of face warp.\n"
												 "\tSee IWarper for details")
	
		.def("estimate",[](
			 const fsdk::ILivenessDepthEstimatorPtr& est,
			 const fsdk::Image& image) {
				 fsdk::ResultValue<fsdk::FSDKError, float> err = est->estimate(image);
			
				 return FSDKErrorValueFloat(err); },
			 "Check whether or not depth map corresponds to the real person.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): warped depth image with R16 format.\n"
			 "\tReturns:\n"
			 "\t\t(FSDKErrorValueFloat): ResultValue with error code and score of estimation.\n"
			 "\t\t\testimation score normalized between 0.0 and 1.0,\n"
			 "\t\t\twhere 1.0 equals to 100% confidence that person on image is alive, and 0.0 equals to 0%.\n")
		
		.def("setRange",[](
			 const fsdk::ILivenessDepthEstimatorPtr& est,
			 const fsdk::DepthRange& range) {
				 return est->setRange(range); },
			 "Set depth range for estimator.\n"
			 "\tArgs\n"
			 "\t\tparam1 (DepthRange): range see DepthRange.\n"
			 "\tReturns:\n"
			 "\t\t(bool): True - if range was set, otherwise - False.\n"
			 "\t\t\tif !range.isOk() range is not set.\n")
			;

// IREstimation
	py::class_<fsdk::IREstimation>(f, "IREstimation",
		"IR estimation output.\n"
		"\tThese values are produced by ILivenessIREstimator object.\n")
		.def(py::init<>())
		.def_readwrite("isReal", &fsdk::IREstimation::isReal, "\tbool answer, the real person or not")
		.def_readwrite("score", &fsdk::IREstimation::score, "\t score")
		.def("__repr__",
			 [](const fsdk::IREstimation &result) {
				 return "isReal = " + std::to_string(result.isReal)
						+ ", score = " + std::to_string(result.score); })
		;
	
	py::class_<fsdk::ILivenessIREstimatorPtr>(f, "ILivenessIREstimatorPtr",
		"Infra-red liveness estimator interface.\n"
		"\tThis estimator is designed for face analysis using infra red facial warp (8-bit 1 channel) image.\n"
		"\tIWarper for details.\n")
	
		.def("estimate",[](
			 const fsdk::ILivenessIREstimatorPtr& est,
			 const fsdk::Image& irWarp) {
				 fsdk::IREstimation irEstimation;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(irWarp, irEstimation);
				 if (err.isOk())
					 return py::cast(irEstimation);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Check whether or not infrared warp corresponds to the real person.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): irWarp infra red face warp\n"
			 "\tReturns:\n"
			 "\t\t(IREstimation): if OK - return irEstimation\n"
			 "\t\t\t(FSDKErrorResult): else - Error code.\n")
			;
	
	py::class_<fsdk::ISmileEstimatorPtr>(f, "ISmileEstimatorPtr",
		"Smile estimator interface.\n"
		"\tThis estimator is designed for smile/mouth/mouth overlap detection.\n"
		"\tIt works with warped image see IWarper for details.\n")
	
		.def("estimate",[](
			 const fsdk::ISmileEstimatorPtr& est,
			 const fsdk::Image& image) {
				 fsdk::SmileEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(image, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate SmileEstimation probabilities.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): face warped image.\n"
			 "\tReturns:\n"
			 "\t\t(SmileEstimation): if OK - estimation\n"
			 "\t\t(FSDKErrorResult): else - Error code.\n")
			;
	
	py::class_<fsdk::ILivenessFlowEstimatorPtr>(f, "ILivenessFlowEstimatorPtr",
		"\tLiveness flow estimator interface.\n"
		"\tThis estimator is designed for liveness detection. It works with 1 close-range face crop\n"
		"\tand 10 long-range face crops estimating correctness of optical flow between theese frames.\n"
		"\tRequired input images - 96x96 face warp central crops.\n"
		"\tsee IWarper for details.\n")
	
		.def("estimate",[](
			 const fsdk::ILivenessFlowEstimatorPtr& est,
			 const fsdk::Image& small,
			 std::vector<fsdk::Image> framesPyList) {
				 double score = 0.0;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(small, framesPyList.data(), framesPyList.size(), score);
				 if (err.isOk())
					 return py::cast(score);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Check if correct optical flow can be calculated from input images..\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): small face crop\n"
			 "\t\tparam2 (list): list with big face crops.\n"
			 "\tReturns:\n"
			 "\t\t(double): if OK - score.\n"
			 "\t\t(FSDKErrorResult): else - error code")
			;
	
	py::class_<fsdk::IEyeEstimatorPtr>(f, "IEyeEstimatorPtr",
		"Eye estimator interface.\n"
		"This estimator is designed to work with a person face image; you should pass a warped face detection image.\n"
		"Eye estimator detects:\n"
		"\teyes state;\n"
		"\tlandmarks describing iris.\n"
		"See EyesEstimation for output details.\n"
		"More detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
	
		.def("estimate",[](
			 const fsdk::IEyeEstimatorPtr& est,
			 const fsdk::Image& warp,
			 const fsdk::Landmarks5& landmarks5) {
				 fsdk::EyesEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, landmarks5, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate the attributes.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): warp source image. Format must be R8G8B8. Must be warped!\n"
			 "\t\tparam2 (Landmarks5): landmarks5 landmark of size 5 used to warp image, "
			 "must be in warped image coordinates. @see IWarper\n"
			 "\tReturns:\n"
			 "\t\t(EyesEstimation): if OK - return eye estimation\n"
			 "\t\t(FSDKErrorResult): else - Error code")
		
		.def("estimate",[](
			 const fsdk::IEyeEstimatorPtr& est,
			 const fsdk::Image& warp,
			 const fsdk::Landmarks68& landmarks68) {
				 fsdk::EyesEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, landmarks68, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate the attributes.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): warp source image. Format must be R8G8B8. Must be warped!\n"
			 "\t\tparam2 (Landmarks68): landmark of size 68 used to warp image, must be "
			 "in warped image coordinates.\n"
			 "\tReturns:\n"
			 "\t\t(EyesEstimation): if OK - return eye estimation"
			 "\t\t(FSDKErrorResult): else - Error code")
			;
	
	py::class_<fsdk::IEmotionsEstimatorPtr>(f, "IEmotionsEstimatorPtr",
		"Emotions estimator interface.\n"
		"\tThis estimator is designed to work with a person face image; y"
		"ou should pass a warped face detection image obtained from IWarper.\n"
		"\tsee IWarper for details.\n"
		"\tEmotions estimator detects set of emotions depiceted on given face.\n"
		"\tsee EmotionsEstimation for output details.\n")
		.def("estimate",[](
			 const fsdk::IEmotionsEstimatorPtr& est,
			 const fsdk::Image& warp) {
				 fsdk::EmotionsEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "\tEstimate the attributes.\n"
			 "\tArgs\n"
			 "\t\tparam1 (Image): warp source image. If format is not R8 it would be converted to R8. "
			 "Must be warped!\n"
			 "\tReturns:\n"
			 "\t\t(EmotionsEstimation): if OK - estimation of emotions. see EmotionsEstimation for details\n"
			 "\t\t(FSDKErrorResult): else - Error code")
			;
	
	py::class_<fsdk::IGazeEstimatorPtr>(f, "IGazeEstimatorPtr",
			"Gaze estimator interface.\n"
			"\tThis estimator is designed to work with 68 facial landmarks, HeadPoseEstimation\n"
			"\t(see IHeadPoseEstimator) and EyesEstimations of both eyes (@see IEyeEstimator).\n"
			"\tsee GazeEstimation structure for details about how exactly the estimations are reported.\n"
			"\tInput points should be relative to the same coordinate system. Best results are achieved\n"
			"\tif coordinate system is tied to image on which input data was retrieved.\n")
		.def("estimate",[](
			 const fsdk::IGazeEstimatorPtr& est,
			 const fsdk::HeadPoseEstimation& angles,
			 const fsdk::EyesEstimation& eyesEstimation) {
				 fsdk::GazeEstimation out;
				 fsdk::Result<fsdk::FSDKError> err = est->estimate(angles, eyesEstimation, out);
				 if (err.isOk())
					 return py::cast(out);
				 else
					 return py::cast(FSDKErrorResult(err)); },
			 "Estimate the eye angles.\n"
			 "\tArgs\n"
			 "\t\tparam1 (HeadPoseEstimation): HeadPoseEstimation calculated using landmarks68.\n"
			 "\t\tparam2 (EyesEstimation): EyesEstimation of eyes.\n"
			 "\tReturns:\n"
			 "\t\t(GazeEstimation): if OK - output estimation; @see GazeEstimation.\n"
			 "\t\t(FSDKErrorResult): else - error code")
			;
	
	py::class_<fsdk::MatchingResult>(f, "MatchingResult", "Result of descriptor matching.\n")
		.def(py::init<>(), "Initializes result to default values.\n")
		.def(py::init<float, float>(),
			 "Initializes result.\n"
			 "\tArgs\n"
			 "\t\tparam1 (float): distance value.\n"
			 "\t\tparam2 (float): similarity value.\n")
		.def_readwrite("distance", &fsdk::MatchingResult::distance)
		.def_readwrite("similarity", &fsdk::MatchingResult::similarity)
		.def("__repr__",
			 [](const fsdk::MatchingResult &result) {
				 return "distance = " + std::to_string(result.distance)
						+ ", similarity = " + std::to_string(result.similarity); })
			;
	
	py::class_<fsdk::SearchResult>(f, "SearchResult", "Result of index search.\n")
		.def(py::init<>(), "Default constructor.\n")
		.def(py::init<float, float, fsdk::DescriptorId>(),
			 "Construct structure with parameters.\n"
			 "\tArgs\n"
			 "\t\tparam1 (float): Distance between descriptors.\n"
			 "\t\tparam2 (float): Similarity between descriptors.\n"
			 "\t\tparam3 (int): Index of found descriptors in some storage.\n")
		.def_readwrite("distance", &fsdk::SearchResult::distance)
		.def_readwrite("similarity", &fsdk::SearchResult::similarity)
		.def_readwrite("index", &fsdk::SearchResult::index)
		.def("__repr__",
			 [](const fsdk::SearchResult &result) {
				 return "distance = " + std::to_string(result.distance)
						+ ", similarity = " + std::to_string(result.similarity)
						+ ", index = " + std::to_string(result.index); })
			;
	
	py::class_<fsdk::Landmarks5>(f, "Landmarks5",
		"Face landmarks, length is fixed and equal to5.\n"
		"\tMTCNN face detector is capable of face landmarks detection. "
		"\tLandmarks are special classes binded to python. \n"
		"\tThey are similar on python lists. It is possible to use some standard python built-in "
		"functions for them: \n"
		"\t`__len__`, `__getitem__`. The method `__setitem__` is used only for test and research "
		"purposes with class Vector2f. \n"
		"\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
	
		.def(py::init<>())
		.def("__len__", [](const fsdk::Landmarks5 &v) { return v.landmarkCount; },
			 "Called to implement the built-in function len(). Should return the length of the object, an integer >= 0.\n"
			 "\tExample: len(landmarks)")
		.def("__getitem__", [](const fsdk::Landmarks5 &s, size_t i) {
				 if (i >= s.landmarkCount) throw py::index_error();
				 return s.landmarks[i]; },
			 "Called to implement evaluation of self[key]. The accepted keys should be integers.\n "
			 "\tExample: lanmarks[3]")
		
		.def("__setitem__", [](fsdk::Landmarks5 &s, size_t i, fsdk::Vector2<float> v) {
				 if (i >= s.landmarkCount) throw py::index_error();
				 s.landmarks[i].x = v.x;
				 s.landmarks[i].y = v.y;
				 return s.landmarks[i];
			 },
			 "Called to implement assignment to self[key]. \n"
			 "\tThe method `__setitem__` is used only for test and research purposes with class Vector2f.\n "
			 "\tExample: lanmarks[i] = FaceEngine.Vector2f(10.0, 20.0)")
			; //Landmarks5
	
	py::class_<fsdk::Landmarks68>(f, "Landmarks68",
		"Face landmarks, length is fixed and equal to 68.\n"
		"\tMTCNN face detector is capable of face landmarks detection. "
		"\tLandmarks are special classes binded to python. \n"
		"\tThey are similar on python lists. It is possible to use some standard python "
		"built-in functions for them: \n"
		"\t`__len__`, `__getitem__`. The method `__setitem__` is used only for test and "
		"research purposes with class Vector2f. \n"
		"\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
	
		.def(py::init<>())
		.def("__len__", [](const fsdk::Landmarks68 &v) { return v.landmarkCount; },
			 "Called to implement the built-in function len(). Should return the length of the object, an integer >= 0.\n"
			 "\tExample: len(landmarks)")
		
		.def("__getitem__", [](const fsdk::Landmarks68 &s, size_t i) {
				 if (i >= s.landmarkCount) throw py::index_error();
				 return s.landmarks[i]; },
			 "Called to implement evaluation of self[key]. The accepted keys should be integers.\n "
			 "\tExample:lanmarks[3]")
		
		.def("__setitem__", [](fsdk::Landmarks68 &s, size_t i, fsdk::Vector2<float> v) {
			if (i >= s.landmarkCount) throw py::index_error();
			s.landmarks[i].x = v.x;
			s.landmarks[i].y = v.y;
			return s.landmarks[i];
		}, "Called to implement assignment to self[key]. \n"
			 "\tThe method `__setitem__` is used only for test and research purposes with class Vector2f.\n "
			 "\tExample: lanmarks[i] = FaceEngine.Vector2f(10.0, 20.0)")
		; //Landmarks68
	
	py::class_<fsdk::EyesEstimation::EyeAttributes::IrisLandmarks>(f, "IrisLandmarks",
			"Iris landmarks, length is fixed and equal to 32.\n"
			"\tMTCNN face detector is capable of face landmarks detection. "
			"\tLandmarks are special classes binded to python. \n"
			"\tThey are similar on python lists. It is possible to use some standard "
			"python built-in functions for them: \n"
			"\t`__len__`, `__getitem__`. The method `__setitem__` is used only for "
			"test and research purposes with class Vector2f. \n"
			"\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		
		.def(py::init<>())
		.def("__len__", [](const fsdk::EyesEstimation::EyeAttributes::IrisLandmarks &v)
			 { return fsdk::EyesEstimation::EyeAttributes::irisLandmarksCount; },
			 "Called to implement the built-in function len(). Should return the length of the object, an integer >= 0.\n"
			 "\tExample: len(landmarks)")
		
		.def("__getitem__", [](const fsdk::EyesEstimation::EyeAttributes::IrisLandmarks &l, size_t i) {
				 if (i >= fsdk::EyesEstimation::EyeAttributes::irisLandmarksCount) throw py::index_error();
				 return l.landmarks[i]; },
			 "Called to implement evaluation of self[key]. The accepted keys should be integers.\n "
			 "\tExample:lanmarks[3]")
		
		.def("__setitem__", [](fsdk::EyesEstimation::EyeAttributes::IrisLandmarks &s,
							   size_t i,
							   fsdk::Vector2<float> v) {
				 if (i >= fsdk::EyesEstimation::EyeAttributes::irisLandmarksCount) throw py::index_error();
				 s.landmarks[i].x = v.x;
				 s.landmarks[i].y = v.y;
				 return s.landmarks[i]; },
			 "Called to implement assignment to self[key]. \n"
			 "\tThe method `__setitem__` is used only for test and research purposes with class Vector2f.\n "
			 "\tExample: lanmarks[i] = FaceEngine.Vector2f(10.0, 20.0)")
			;   //IrisLandmarks
	
	py::class_<fsdk::EyesEstimation::EyeAttributes::EyelidLandmarks>(f, "EyelidLandmarks",
		"Eyelid landmarks, length is fixed and equal to 6.\n"
		"\tMTCNN face detector is capable of face landmarks detection. "
		"\tLandmarks are special classes binded to python. \n"
		"\tThey are similar on python lists. It is possible to use some standard "
		"python built-in functions for them: \n"
		"\t`__len__`, `__getitem__`. The method `__setitem__` "
		"is used only for test and research purposes with class Vector2f. \n"
		"\tMore detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
	
		.def(py::init<>())
		.def("__len__", [](const fsdk::EyesEstimation::EyeAttributes::EyelidLandmarks &v)
			 { return fsdk::EyesEstimation::EyeAttributes::eyelidLandmarksCount; },
			 "Called to implement the built-in function len(). Should return the length of the object, an integer >= 0.\n"
			 "\tExample: len(landmarks)")
		
		.def("__getitem__", [](const fsdk::EyesEstimation::EyeAttributes::EyelidLandmarks &l, size_t i) {
				 if (i >= fsdk::EyesEstimation::EyeAttributes::eyelidLandmarksCount) throw py::index_error();
				 return l.landmarks[i]; },
			 "Called to implement evaluation of self[key]. The accepted keys should be integers.\n "
			 "\tExample:lanmarks[3]")
		
		.def("__setitem__", [](fsdk::EyesEstimation::EyeAttributes::EyelidLandmarks &s,
							   size_t i,
							   fsdk::Vector2<float> v) {
				 if (i >= fsdk::EyesEstimation::EyeAttributes::eyelidLandmarksCount) throw py::index_error();
				 s.landmarks[i].x = v.x;
				 s.landmarks[i].y = v.y;
				 return s.landmarks[i];
			 },
			 "Called to implement assignment to self[key]. \n"
			 "\tThe method `__setitem__` is used only for test and research purposes with class Vector2f.\n "
			 "\tExample: lanmarks[i] = FaceEngine.Vector2f(10.0, 20.0)")
			; //EyelidLandmarks

// doc Template
//		"Te.\n"
//		"\tTe.\n"
//		"\tArgs\n"
//		"\t\tparam1 (t): te\n"
//		"\t\tparam2 (t): te\n"
//		"\tReturns:\n"
//		"\t\t(t): te"
// Vector2
	
	py::class_<fsdk::Vector2<float>>(f, "Vector2f", "Vector with 2 float values, x and y")
		.def(py::init<>())
		.def(py::init<float, float>())
		.def(py::init<const fsdk::Vector2<float>&>())
		.def(py::self != py::self)
		.def(py::self == py::self)
		.def_readwrite("x", &fsdk::Vector2<float>::x)
		.def_readwrite("y", &fsdk::Vector2<float>::y)
		.def("__repr__",
			 [](const fsdk::Vector2<float> &v) {
				 return "x = " + std::to_string(v.x) + ", y = " + std::to_string(v.y);
		 })
		;
	
	py::class_<fsdk::Vector2<int>>(f, "Vector2i", "Vector with 2 integer values, x and y")
		.def(py::init<>())
		.def(py::init<int, int>())
		.def(py::init<const fsdk::Vector2<int>&>())
		.def(py::self != py::self)
		.def(py::self == py::self)
		.def_readwrite("x", &fsdk::Vector2<int>::x)
		.def_readwrite("y", &fsdk::Vector2<int>::y)
		.def("__repr__",
			 [](const fsdk::Vector2<int> &v) {
				 return "x = " + std::to_string(v.x) + ", y = " + std::to_string(v.y);
			 })
		;

//	Errors
	py::class_<FSDKErrorResult>(f, "FSDKErrorResult",
		"Wrapper for FSDK::Error that encapsulates an action result enumeration.\n"
		"\tAn enum should specify a result code.\n")
		.def_readonly("isOk", &FSDKErrorResult::isOk)
		.def_readonly("isError", &FSDKErrorResult::isError)
		.def_readonly("FSDKError", &FSDKErrorResult::fsdkError)
		.def_readonly("what", &FSDKErrorResult::what)
		.def("__repr__",
			 [](const FSDKErrorResult &err) {
				 return "FSDKErrorResult: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", FSDKError = " + fsdk::ErrorTraits<fsdk::FSDKError >::toString(err.fsdkError)
						+ ", what = " + err.what; })
			;
	
	py::class_<DescriptorBatchResult>(f, "DescriptorBatchResult",
		"Wrapper for DescriptorBatch::Error that encapsulates an action result enumeration.\n"
		"\tAn enum should specify a result code.\n")
		.def_readonly("isOk", &DescriptorBatchResult::isOk)
		.def_readonly("isError", &DescriptorBatchResult::isError)
		.def_readonly("DescriptorBatchError", &DescriptorBatchResult::descriptorBatchError)
		.def_readonly("what", &DescriptorBatchResult::what)
		.def("__repr__",
			 [](const DescriptorBatchResult &err) {
				 return "DescriptorBatchResult: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", DescriptorBatchError = " +
						fsdk::ErrorTraits<fsdk::IDescriptorBatch::Error>::toString(err.descriptorBatchError)
						+ ", what = " + err.what; })
			;
	
	py::class_<ImageErrorResult>(f, "ImageErrorResult",
		 "Wrapper for Image::Error that encapsulates an action result enumeration.\n"
		 "\tAn enum should specify a result code.\n")
		.def_readonly("isOk", &ImageErrorResult::isOk)
		.def_readonly("isError", &ImageErrorResult::isError)
		.def_readonly("imageError", &ImageErrorResult::imageError)
		.def_readonly("what", &ImageErrorResult::what)
		.def("__repr__",
			 [](const ImageErrorResult &err) {
				 return "ImageErrorResult: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", imageError = " + fsdk::ErrorTraits<fsdk::Image::Error>::toString(err.imageError)
						+ ", what = " + err.what; })
			;
	
	py::class_<SettingsProviderResult>(f, "SettingsProviderErrorResult",
		"Wrapper for SettingsProvider::Error that encapsulates an action result enumeration.\n"
		"\ttAn enum should specify a result code.\n")
		.def_readonly("isOk", &SettingsProviderResult::isOk)
		.def_readonly("isError", &SettingsProviderResult::isError)
		.def_readonly("SettingsProviderResult", &SettingsProviderResult::settingsProviderError)
		.def_readonly("what", &SettingsProviderResult::what)
		.def("__repr__",
			 [](const SettingsProviderResult &err) {
				 return "SettingsProviderResult: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", SettingsProviderError = " +
						fsdk::ErrorTraits<fsdk::ISettingsProvider::Error>::
						toString(err.settingsProviderError)
						+ ", what = " + err.what; })
		;
	
	py::class_<FSDKErrorValueInt>(f, "FSDKErrorValueInt", "Wrapper for result to output some integer "
		"value aside the result.\n")
		.def_readonly("isOk", &FSDKErrorValueInt::isOk)
		.def_readonly("isError", &FSDKErrorValueInt::isError)
		.def_readonly("FSDKError", &FSDKErrorValueInt::fsdkError)
		.def_readonly("what", &FSDKErrorValueInt::what)
		.def_readonly("value", &FSDKErrorValueInt::value)
		.def("__repr__",
			 [](const FSDKErrorValueInt &err) {
				 return "FSDKErrorValueInt: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", FSDKError = " + fsdk::ErrorTraits<fsdk::FSDKError >::toString(err.fsdkError)
						+ ", value = " + std::to_string(err.value)
						+ ", what = " + err.what; })
			;
	
	py::class_<FSDKErrorValueFloat>(f, "FSDKErrorValueFloat",
		"Wrapper for result to output some "
		"float value aside the result.\n")
		.def_readonly("isOk", &FSDKErrorValueFloat::isOk)
		.def_readonly("isError", &FSDKErrorValueFloat::isError)
		.def_readonly("FSDKError", &FSDKErrorValueFloat::fsdkError)
		.def_readonly("what", &FSDKErrorValueFloat::what)
		.def_readonly("value", &FSDKErrorValueFloat::value)
		.def("__repr__",
			 [](const FSDKErrorValueFloat &err) {
				 return "FSDKErrorValueFloat: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", FSDKError = " + fsdk::ErrorTraits<fsdk::FSDKError >::toString(err.fsdkError)
						+ ", value = " + std::to_string(err.value)
						+ ", what = " + err.what;
			 })
		;
	
	py::class_<FSDKErrorValueMatching>(f, "FSDKErrorValueMatching", "Wrapper for result to output "
		"some Matching value (distance, similarity) aside the result.\n")
		.def_readonly("isOk", &FSDKErrorValueMatching::isOk)
		.def_readonly("isError", &FSDKErrorValueMatching::isError)
		.def_readonly("FSDKError", &FSDKErrorValueMatching::fsdkError)
		.def_readonly("what", &FSDKErrorValueMatching::what)
		.def_readonly("value", &FSDKErrorValueMatching::value)
		.def("__repr__",
			 [](const FSDKErrorValueMatching &err) {
				 return "FSDKErrorValueMatching: "
						"isOk = " + std::to_string(err.isOk)
						+ ", isError = " + std::to_string(err.isError)
						+ ", FSDKError = " + fsdk::ErrorTraits<fsdk::FSDKError >::toString(err.fsdkError)
						+ ", value: (distance = " + std::to_string(err.value.distance) +
						", similarity = " + std::to_string(err.value.similarity) + ")"
						+ ", what = " + err.what;
			 })
		;

// Attribute
	py::class_<fsdk::AttributeEstimation>(f, "AttributeEstimation",
		"Attribute estimation output.\n"
		"\tThese values are produced by IComplexEstimator object.\n"
		"\tEach estimation is given in normalized [0, 1] range. Parameter meanings:\n"
		"\t\tgender: 1 - male, 0 - female;\n"
		"\t\tglasses: 1 - person wears glasses, 0 - person doesn't wear glasses;\n"
		"\t\tage: estimated age (in years).\n")
		.def(py::init<>())
		.def_readwrite("gender", &fsdk::AttributeEstimation::gender)
		.def_readwrite("glasses", &fsdk::AttributeEstimation::glasses)
		.def_readwrite("age", &fsdk::AttributeEstimation::age)
		.def("__repr__",
			 [](const fsdk::AttributeEstimation &a) {
				 return "AttributeEstimation: "
						"gender = " + std::to_string(a.gender) +
						", glasses = " + std::to_string(a.glasses) +
						", age = " + std::to_string(a.age);
		 	})
			;

//	Quality
	py::class_<fsdk::Quality>(f, "Quality",
		"Quality estimation structure\n"
		"\tEach estimation is given in normalized [0, 1] range. Parameter meanings:\n"
		"\t\tlight: image overlighting degree. 1 - ok, 0 - overlighted;\n"
		"\t\tdark: image darkness degree. 1 - ok, 0 - to dark;\n"
		"\t\tgray: image grayness degree 1 - ok, 0 - to gray;\n"
		"\t\tblur: image blur degree. 1 - ok, 0 - to blured.\n")
		.def(py::init<>())
		.def_readwrite("light", &fsdk::Quality::light)
		.def_readwrite("dark", &fsdk::Quality::dark)
		.def_readwrite("gray", &fsdk::Quality::gray)
		.def_readwrite("blur", &fsdk::Quality::blur)
		.def("__repr__",
			 [](const fsdk::Quality &q) {
				 return "Quality: "
						"light = " + std::to_string(q.light)
						+ ", dark = " + std::to_string(q.dark)
						+ ", gray = " + std::to_string(q.gray)
						+ ", blur = " + std::to_string(q.blur);
			 })
		.def("getQuality", &fsdk::Quality::getQuality)
		;

//	Ethnicity
	py::class_<fsdk::EthnicityEstimation>(f, "EthnicityEstimation",
		"Ethnicity estimation structure.\n"
		"\tEach estimation is given in normalized [0, 1] range.\n")
		.def(py::init<>())
		.def_readwrite("africanAmerican", &fsdk::EthnicityEstimation::africanAmerican)
		.def_readwrite("indian", &fsdk::EthnicityEstimation::indian)
		.def_readwrite("asian", &fsdk::EthnicityEstimation::asian)
		.def_readwrite("caucasian", &fsdk::EthnicityEstimation::caucasian)
		.def("__repr__",
			 [](const fsdk::EthnicityEstimation &e) {
				 return "EthnicityEstimation: "
						"africanAmerican = " + std::to_string(e.africanAmerican)
						+ ", indian = " + std::to_string(e.indian)
						+ ", asian = " + std::to_string(e.asian)
						+ ", caucasian = " + std::to_string(e.caucasian);
			 })
		.def("getEthnicityScore", &fsdk::EthnicityEstimation::getEthnicityScore,
			 "Returns score of required ethnicity")
		.def("getPredominantEthnicity", &fsdk::EthnicityEstimation::getPredominantEthnicity,
			 "Returns ethnicity with greatest score"
			 "\tArgs:"
			 "\t\tparam1 (Ethnicity): ethnicity")
			;

//	HeadPose
	py::class_<fsdk::HeadPoseEstimation>(f, "HeadPoseEstimation",
		"Head pose estimation output.\n"
		"\tThese values are produced by IHeadPoseEstimator object.\n"
		"\tEach angle is measured in degrees and in [-180, 180] range.\n")
		.def(py::init<>())
		.def_readwrite("pitch", &fsdk::HeadPoseEstimation::pitch)
		.def_readwrite("yaw", &fsdk::HeadPoseEstimation::yaw)
		.def_readwrite("roll", &fsdk::HeadPoseEstimation::roll)
		.def("getFrontalFaceType", &fsdk::HeadPoseEstimation::getFrontalFaceType)
		.def("__repr__",
			 [](const fsdk::HeadPoseEstimation &h) {
				 return "HeadPoseEstimation: "
						"pitch = " + std::to_string(h.pitch)
						+ ", yaw = " + std::to_string(h.yaw)
						+ ", roll = " + std::to_string(h.roll);
			 })
			;
	
	py::enum_<fsdk::HeadPoseEstimation::FrontalFaceType>(f, "FrontalFaceType", py::arithmetic())
		.value("FrontalFace0", fsdk::HeadPoseEstimation::FrontalFace0)
		.value("FrontalFace1", fsdk::HeadPoseEstimation::FrontalFace1)
		.value("FrontalFace2", fsdk::HeadPoseEstimation::FrontalFace2)
			;
		
		py::class_<fsdk::DepthRange>(f, "DepthRange",
			 "Depth range configuration structure in millimeters.\n"
			 "\tSpecifies working range of distances for depth estimator.\n"
			 "\tAverage depth map value should belong to this range.\n"
			 "\tBy default configured for kinect depth sensor.\n")
		.def_readwrite("min", &fsdk::DepthRange::min)
		.def_readwrite("max", &fsdk::DepthRange::max)
		.def("isOk", &fsdk::DepthRange::isOk)
		.def("__repr__",
			 [](const fsdk::DepthRange &h) {
				 return "<DepthRange: "
						", min = " + std::to_string(h.min)
						+ ", max = " + std::to_string(h.max);
			 })
			;
	
	py::class_<fsdk::SmileEstimation>(f, "SmileEstimation")
		.def(py::init<>())
		.def_readwrite("mouth", &fsdk::SmileEstimation::mouth)
		.def_readwrite("smile", &fsdk::SmileEstimation::smile)
		.def_readwrite("occlusion", &fsdk::SmileEstimation::occlusion)
		.def("__repr__",
			 [](const fsdk::SmileEstimation &s) {
				 std::ostringstream mouth;
				 std::ostringstream smile;
				 std::ostringstream occlusion;
				 mouth << s.mouth;
				 smile << s.smile;
				 occlusion << s.occlusion;
				 return "SmileEstimation: "
						"mouth = " + mouth.str()
						+ ", smile = " + smile.str()
						+ ", occlusion = " + occlusion.str();
			 })
		;

// first of all for test
	f.def("loadImage", &loadImage, "used only for depth test");

// EyesEstimation
	py::class_<fsdk::EyesEstimation>(f, "EyesEstimation",
		"Eyes estimation output.\n"
		"\tThese values are produced by IEyeEstimator object.\n")
		.def(py::init<>())
		.def_readwrite("leftEye", &fsdk::EyesEstimation::leftEye)
		.def_readwrite("rightEye", &fsdk::EyesEstimation::rightEye)
		;
		py::enum_<fsdk::EyesEstimation::EyeAttributes::State>(f, "State", "Enumeration of possible eye states.\n")
		.value("Closed", fsdk::EyesEstimation::EyeAttributes::State::Closed, "Eye is closed.\n")
		.value("Open", fsdk::EyesEstimation::EyeAttributes::State::Open, "Eye is open.\n")
		.value("Occluded", fsdk::EyesEstimation::EyeAttributes::State::Occluded,
			   "Eye is blocked by something not transparent,\n"
			   "\tor landmark passed to estimator doesn't point to an eye.\n")
		;
		
		py::class_<fsdk::EyesEstimation::EyeAttributes>(f, "EyeAttributes", "Eyes attribute structure.\n")
	//		.def_property_readonly_static("irisLandmarksCount", [] (const fsdk::EyesEstimation::EyeAttributes& e)
	//			{return e.irisLandmarksCount; })
	//		.def_property_readonly_static("eyelidLandmarksCount", [] (const fsdk::EyesEstimation::EyeAttributes& e)
	//			{return e.eyelidLandmarksCount; })
		.def_readwrite("state", &fsdk::EyesEstimation::EyeAttributes::state)
		.def_readwrite("iris", &fsdk::EyesEstimation::EyeAttributes::iris)
		.def_readwrite("eyelid", &fsdk::EyesEstimation::EyeAttributes::eyelid)
		;

// Emotions
	py::class_<fsdk::EmotionsEstimation>(f, "EmotionsEstimation",
		"Emotions estimation structure.\n"
		"\tEach estimation is given in normalized [0, 1] range.\n")
		.def(py::init<>())
		.def_readwrite("anger", &fsdk::EmotionsEstimation::anger)
		.def_readwrite("disgust", &fsdk::EmotionsEstimation::disgust)
		.def_readwrite("fear", &fsdk::EmotionsEstimation::fear)
		.def_readwrite("happiness", &fsdk::EmotionsEstimation::happiness)
		.def_readwrite("sadness", &fsdk::EmotionsEstimation::sadness)
		.def_readwrite("surprise", &fsdk::EmotionsEstimation::surprise)
		.def_readwrite("neutral", &fsdk::EmotionsEstimation::neutral)
		.def("getPredominantEmotion", &fsdk::EmotionsEstimation::getPredominantEmotion,
			 "Returns emotion with greatest score")
		.def("getEmotionScore", &fsdk::EmotionsEstimation::getEmotionScore,
			 "Returns score of required emotion"
			 "\tArgs\n"
			 "\t\tparam1 (emotion): emotion\n")
		.def("__repr__",
			 [](const fsdk::EmotionsEstimation &e) {
				 return "EmotionsEstimation: "
						" anger = " + std::to_string(e.anger)
						+ ", disgust = " + std::to_string(e.disgust)
						+ ", fear = " + std::to_string(e.fear)
						+ ", happiness = " + std::to_string(e.happiness)
						+ ", sadness = " + std::to_string(e.sadness)
						+ ", surprise = " + std::to_string(e.surprise)
						+ ", neutral = " + std::to_string(e.neutral);
			 })
		; // Emotions
	
	py::enum_<fsdk::EmotionsEstimation::Emotions>(f, "Emotions", py::arithmetic(), "Emotions enum")
		.value("Anger", fsdk::EmotionsEstimation::Anger)
		.value("Disgust", fsdk::EmotionsEstimation::Disgust)
		.value("Fear", fsdk::EmotionsEstimation::Fear)
		.value("Happiness", fsdk::EmotionsEstimation::Happiness)
		.value("Sadness", fsdk::EmotionsEstimation::Sadness)
		.value("Surprise", fsdk::EmotionsEstimation::Surprise)
		.value("Neutral", fsdk::EmotionsEstimation::Neutral)
		.value("Count", fsdk::EmotionsEstimation::Count)
		;
	
	// Gaze
		py::class_<fsdk::GazeEstimation>(f, "GazeEstimation",
										 "Gaze estimation output.\n"
										 "\tThese values are produced by IGazeEstimatorPtr object.\n"
										 "\tEach angle is measured in degrees and in [-180, 180] range.\n")
		.def(py::init<>())
		.def_readwrite("leftEye", &fsdk::GazeEstimation::leftEye)
		.def_readwrite("rightEye", &fsdk::GazeEstimation::rightEye)
		.def("__repr__",
			 [](const fsdk::GazeEstimation &g) {
				 return "GazeEstimation: "
						"leftEye: yaw = " + std::to_string(g.leftEye.yaw) +
						", pitch = " + std::to_string(g.leftEye.pitch) +
						", rightEye: yaw = " + std::to_string(g.rightEye.yaw) +
						", pitch = " + std::to_string(g.rightEye.pitch);
			 })
		;
	
	py::class_<fsdk::GazeEstimation::EyeAngles>(f, "EyeAngles", "Eye angles.\n")
		.def_readwrite("yaw", &fsdk::GazeEstimation::EyeAngles::yaw)
		.def_readwrite("pitch", &fsdk::GazeEstimation::EyeAngles::pitch)
		.def("__repr__",
			 [](const fsdk::GazeEstimation::EyeAngles &e) {
				 return "EyeAngles: "
						"yaw = " + std::to_string(e.yaw)
						+ ", pitch = " + std::to_string(e.pitch);
			 })
		;

//	Ethnicity
	py::enum_<fsdk::EthnicityEstimation::Ethnicities>(f, "Ethnicity", "Ethnicity enum.\n")
		.value("AfricanAmerican", fsdk::EthnicityEstimation::AfricanAmerican)
		.value("Indian", fsdk::EthnicityEstimation::Indian)
		.value("Asian", fsdk::EthnicityEstimation::Asian)
		.value("Caucasian", fsdk::EthnicityEstimation::Caucasian)
		.value("Count", fsdk::EthnicityEstimation::Count)
		.export_values();
			;

//	Transformation
	py::class_<fsdk::Transformation>(f, "Transformation",
		 "Transformation data structure, used for warping.\n"
		 "\tUse this structure to perform image and landmarks transformations.\n"
		 "\tIf no circumstances should you create OR edit this structure by yourself")
		.def(py::init<>())
		.def_readwrite("angleDeg", &fsdk::Transformation::angleDeg)
		.def_readwrite("scale", &fsdk::Transformation::scale)
		.def_readwrite("centerP", &fsdk::Transformation::centerP)
		.def_readwrite("detectionTopLeft", &fsdk::Transformation::detectionTopLeft)
		.def("__repr__", [](const fsdk::Transformation &t) {
			return "Transformation: "
				   " angleDeg= " + std::to_string(t.angleDeg)
				   + ", scale = " + std::to_string(t.scale)
				   + ", centerP: x = " + std::to_string(t.centerP.x) + " y = " + std::to_string(t.centerP.y)
				   + ", detectionTopLeft: x = " + std::to_string(t.detectionTopLeft.x)
				   + " y = " + std::to_string(t.detectionTopLeft.y);
		})
			;
// Image type and format
	py::enum_<fsdk::Format::Type>(f, "FormatType", "Format type enumeration.\n")
		.value("Unknown", fsdk::Format::Unknown)
		.value("B8G8R8X8", fsdk::Format::B8G8R8X8)
		.value("R8G8B8X8", fsdk::Format::R8G8B8X8)
		.value("B8G8R8", fsdk::Format::B8G8R8)
		.value("R8G8B8", fsdk::Format::R8G8B8)
		.value("R8", fsdk::Format::R8)
	//		R16 is used for internal transformations for depth map and cannot be saved or downloaded
		.value("R16", fsdk::Format::R16,
			   "\tUsed for internal transformations for depth map and "
			   "cannot be saved or downloaded")
		;
	
	py::class_<fsdk::Image>(f, "Image",
		"Image objects\n"
		"More detailed description see in FaceEngineSDK_Handbook.pdf or source C++ interface.\n")
		.def(py::init<>())
		.def("getWidth", &fsdk::Image::getWidth)
		.def("getHeight", &fsdk::Image::getHeight)
		.def("isValid", &fsdk::Image::isValid)
		.def("getFormat", [](const fsdk::Image& image){
			fsdk::Format::Type type = fsdk::Format::Type(image.getFormat());
			return type;
		})
		
		.def("getRect", &fsdk::Image::getRect,
			 "Image rectangle.\n"
			 "\tResulting rectangle top left corner is always at (0, 0).\n")
		
		.def("getData", [](const fsdk::Image& image) {
			fsdk::Format type = fsdk::Format::Type(image.getFormat());
			int c = getChannelCount(type);
			const auto* const data_uint = image.getDataAs<uint8_t>();
			std::vector<uint8_t> data(data_uint, data_uint + image.getDataSize());
			std::vector<ssize_t> shape { image.getHeight(), image.getWidth(), c };
			auto ptr = data.data();
			return py::array(shape, ptr);
		}, "\tReturns image as numpy array.\n")
		
		.def("getChannelCount", [](const fsdk::Image& image) {
			fsdk::Format type = fsdk::Format::Type(image.getFormat());
			return getChannelCount(type);
		}, "\tReturns channel count.\n")
		.def("getChannelStep", [](const fsdk::Image& image) {
			return image.getFormat().getChannelStep();
		}, "\tGet channel step.Padding bytes are considered spare channels.\n")
		
		.def("getChannelSize", [](const fsdk::Image& image) {
			return image.getFormat().getChannelSize();
		})
		
		.def("getBitDepth", [](const fsdk::Image& image) {
			return image.getFormat().getBitDepth();
		})
		
		.def("getByteDepth", [](const fsdk::Image& image) {
			return image.getFormat().getByteDepth();
		})
		
		.def("computePitch", [](const fsdk::Image& image, int rowWidth) {
			return image.getFormat().computePitch(rowWidth);
		})
		
		.def("isPadded", [](const fsdk::Image& image) {
			return image.getFormat().isPadded();
		})
		
		.def("isBGR", [](const fsdk::Image& image) {
			return image.getFormat().isBGR();
		})
		
		.def("isValidFormat", [](const fsdk::Image& image) {
			return image.getFormat().isValid();
		}, "\tReturns true if image format is one of valid types, i.e. not Unknown.\n")
		
		.def("setData", [](fsdk::Image& image, py::array npImage) {
			auto size = npImage.shape();
			fsdk::Format type;
			if (size[2] == 3)
				type = fsdk::Format::R8G8B8;
			else if (size[2] == 1)
				type = fsdk::Format::R8;
			else
				throw py::cast_error("\nUnsupported types of image! Convert it to R8G8B8 or R8, or "
									 "point exact format as second parameter, example: "
									 "image.setData(numpy_array, FaceEngine.FormatType.R8G8B8X8)");
			image.set(size[1], size[0], type, npImage.data());
		}, "Set image by numpy array. Convert it to R8G8B8 or R8.\n")
		
		.def("setData", [](fsdk::Image& image, py::array npImage, fsdk::Format::Type type) {
			auto size = npImage.shape();
			image.set(size[1], size[0], fsdk::Format(type), npImage.data());
		}, "\n\tSet image by numpy array. Please point format. example: \n"
			 "\t\timage.setData(numpy_array, FaceEngine.FormatType.R8G8B8X8)")
		
		.def("save", [](const fsdk::Image& image, const char* path) {
			fsdk::Result<fsdk::Image::Error> error = image.save(path);
			return ImageErrorResult(error);
		})
		
		.def("save", [](const fsdk::Image& image,
						const char* path,
						const fsdk::Format::Type type) {
			fsdk::Result<fsdk::Image::Error> error = image.save(path, fsdk::Format(type));
			return ImageErrorResult(error);
		})
		.def("load",[](fsdk::Image& image, const char* path) {
			fsdk::Result<fsdk::Image::Error> error = image.load(path);
			return ImageErrorResult(error);
		})
		
		.def("load", [](fsdk::Image& image,
						const char* path,
						const fsdk::Format::Type type) {
			fsdk::Result<fsdk::Image::Error> error = image.load(path, fsdk::Format(type));
			return ImageErrorResult(error);
		})
		
		.def("loadFromMemory", [](fsdk::Image& image, const char* bytes, int sizeInBytes) {
			fsdk::Result<fsdk::Image::Error> error = image.loadFromMemory(bytes, sizeInBytes);
			return ImageErrorResult(error);
		})
		
		.def("loadFromMemory", [](
		fsdk::Image& image,
		const char* bytes,
		int sizeInBytes,
		const fsdk::Format::Type type) {
			fsdk::Result<fsdk::Image::Error> error = image.loadFromMemory(
			bytes,
			sizeInBytes,
			fsdk::Format(type));
			return ImageErrorResult(error);
		})
		;
	
	
	py::enum_<fsdk::Image::Type>(f, "ImageType",
		"Supported image types.\n")
		.value("BMP", fsdk::Image::Type::BMP)
		.value("JPG", fsdk::Image::Type::JPG)
		.value("PNG", fsdk::Image::Type::PNG)
		.value("PPM", fsdk::Image::Type::PPM)
		.value("TIFF", fsdk::Image::Type::TIFF)
		.value("Unknown", fsdk::Image::Type::Unknown)
		;
	
	py::enum_<fsdk::Image::Error>(f, "ImageError", "Image error codes.\n")
		.value("Ok", fsdk::Image::Error::Ok)
		.value("InvalidWidth", fsdk::Image::Error::InvalidWidth)
		.value("InvalidHeight", fsdk::Image::Error::InvalidHeight)
		.value("InvalidDataPtr", fsdk::Image::Error::InvalidDataPtr)
		.value("InvalidDataSize", fsdk::Image::Error::InvalidDataSize)
		.value("InvalidImage", fsdk::Image::Error::InvalidImage)
		.value("InvalidArchive", fsdk::Image::Error::InvalidArchive)
		.value("InvalidPath", fsdk::Image::Error::InvalidPath)
		.value("InvalidType", fsdk::Image::Error::InvalidType)
		.value("InvalidFormat", fsdk::Image::Error::InvalidFormat)
		.value("InvalidBitmap", fsdk::Image::Error::InvalidBitmap)
		.value("InvalidMemory", fsdk::Image::Error::InvalidMemory)
		.value("InvalidConversion", fsdk::Image::Error::InvalidConversion)
		.value("FailedToSave", fsdk::Image::Error::FailedToSave)
		.value("FailedToLoad", fsdk::Image::Error::FailedToLoad)
		.value("FailedToInitialize", fsdk::Image::Error::FailedToInitialize)
			;
	
	py::enum_<fsdk::ISettingsProvider::Error>(f, "SettingsProviderError",
		"Config parsing error codes.\n")
		.value("Ok", fsdk::ISettingsProvider::Error::Ok)
		.value("IOError", fsdk::ISettingsProvider::Error::IOError)
		.value("Memory", fsdk::ISettingsProvider::Error::Memory)
		.value("Internal", fsdk::ISettingsProvider::Error::Internal)
		.value("InvalidPi", fsdk::ISettingsProvider::Error::InvalidPi)
		.value("InvalidTag", fsdk::ISettingsProvider::Error::InvalidTag)
		.value("InvalidCdata", fsdk::ISettingsProvider::Error::InvalidCdata)
		.value("FileNotFound", fsdk::ISettingsProvider::Error::FileNotFound)
		.value("InvalidPcdata", fsdk::ISettingsProvider::Error::InvalidPcdata)
		.value("InvalidDocType", fsdk::ISettingsProvider::Error::InvalidDocType)
		.value("InvalidSettings", fsdk::ISettingsProvider::Error::InvalidSettings)
		.value("InvalidComment", fsdk::ISettingsProvider::Error::InvalidComment)
		.value("InvalidAttribute", fsdk::ISettingsProvider::Error::InvalidAttribute)
		.value("InvalidEndElement", fsdk::ISettingsProvider::Error::InvalidEndElement)
		.value("AppendInvalidRoot", fsdk::ISettingsProvider::Error::AppendInvalidRoot)
		.value("NoDocumentElement", fsdk::ISettingsProvider::Error::NoDocumentElement)
		.value("EndElementMismatch", fsdk::ISettingsProvider::Error::EndElementMismatch)
		.value("InvalidStartElement", fsdk::ISettingsProvider::Error::InvalidStartElement)
			;
	
	py::class_<fsdk::Detection>(f, "Detection",
		"Face detection.\n"
		"\tStores a detected face bounding box within a source image frame as well as detection confidence score.\n")
		.def(py::init<>())
		.def_readwrite("rect", &fsdk::Detection::rect, "Object bounding box")
		.def_readwrite("score", &fsdk::Detection::score, "Object detection score)")
		.def("isValid", &fsdk::Detection::isValid)
		.def("__repr__",
			 [](const fsdk::Detection &d) {
				 return "Detection: rect: x = " + std::to_string(d.rect.x) +
						", y = " + std::to_string(d.rect.y) +
						", width = " + std::to_string(d.rect.width) +
						", height = " + std::to_string(d.rect.height) +
						"; score = " + std::to_string(d.score) +
						"; isValid = " + std::to_string(d.isValid());
			 })
	
		;
	
	py::class_<fsdk::Rect>(f, "Rect", "Rectangle")
		.def(py::init<>())
		.def(py::init<int, int, int, int>())
		.def(py::init<fsdk::Vector2<int>, fsdk::Vector2<int>>())
		.def(py::init<const fsdk::Rect&>())
		.def(py::self != py::self)
		.def(py::self == py::self)
		.def_readwrite("x", &fsdk::Rect::x)
		.def_readwrite("y", &fsdk::Rect::y)
		.def_readwrite("width", &fsdk::Rect::width)
		.def_readwrite("height", &fsdk::Rect::height)
		.def_static("coords", &fsdk::Rect::coords)
		.def("size", &fsdk::Rect::size)
		.def("topLeft", &fsdk::Rect::topLeft)
		.def("center", &fsdk::Rect::center)
		.def("bottomRight", &fsdk::Rect::bottomRight)
		.def("top", &fsdk::Rect::top)
		.def("bottom", &fsdk::Rect::bottom)
		.def("left", &fsdk::Rect::left)
		.def("right", &fsdk::Rect::right)
		.def("set", &fsdk::Rect::set)
		.def("adjust", &fsdk::Rect::adjust)
		.def("adjusted", &fsdk::Rect::adjusted)
		.def("getArea", &fsdk::Rect::getArea)
		.def("inside", &fsdk::Rect::inside)
		.def("isValid", &fsdk::Rect::isValid)
		.def("__repr__",
			 [](const fsdk::Rect &r) {
				 return "x = " + std::to_string(r.x) +
						", y = " + std::to_string(r.y) +
						", width = " + std::to_string(r.width) +
						", height = " + std::to_string(r.height);
			 })
		;
	
	py::enum_<fsdk::ObjectDetectorClassType>(f, "ObjectDetectorClassType", py::arithmetic(), "Object detector type enumeration.\n")
		.value("ODT_MTCNN", fsdk::ODT_MTCNN, "MTCNN detector type")
		.value("ODT_MTCNN_MINI", fsdk::ODT_MTCNN_MINI, "ODT_MTCNN_MINI detector type")
		.value("ODT_COUNT", fsdk::ODT_COUNT, "Detector type count")
		.export_values();
			;
	
	py::enum_<fsdk::FSDKError>(f, "FSDKError", "Common SDK error codes.\n")
		.value("Ok", fsdk::FSDKError::Ok)
		.value("Internal", fsdk::FSDKError::Internal)
		.value("InvalidInput", fsdk::FSDKError::InvalidInput)
		.value("InvalidImage", fsdk::FSDKError::InvalidImage)
		
		.value("InvalidRect", fsdk::FSDKError::InvalidRect)
		.value("InvalidImageFormat", fsdk::FSDKError::InvalidImageFormat)
		.value("InvalidImageSize", fsdk::FSDKError::InvalidImageSize)
		.value("InvalidDetection", fsdk::FSDKError::InvalidDetection)
		.value("InvalidLandmarks5", fsdk::FSDKError::InvalidLandmarks5)
		.value("InvalidLandmarks68", fsdk::FSDKError::InvalidLandmarks68)
		.value("InvalidTransformation", fsdk::FSDKError::InvalidTransformation)
		.value("InvalidDescriptor", fsdk::FSDKError::InvalidDescriptor)
		.value("InvalidDescriptorBatch", fsdk::FSDKError::InvalidDescriptorBatch)
		.value("InvalidSettingsProvider", fsdk::FSDKError::InvalidSettingsProvider)
		
		.value("ModuleNotInitialized", fsdk::FSDKError::ModuleNotInitialized)
		.value("ModuleNotReady", fsdk::FSDKError::ModuleNotReady)
		.value("LicenseError", fsdk::FSDKError::LicenseError)
		
		.value("BufferIsNull", fsdk::FSDKError::BufferIsNull)
		.value("BufferIsFull", fsdk::FSDKError::BufferIsFull)
		.value("BufferIsEmpty", fsdk::FSDKError::BufferIsEmpty)
		.value("InvalidBufferSize", fsdk::FSDKError::InvalidBufferSize)
		
		.value("IncompatibleDescriptors", fsdk::FSDKError::IncompatibleDescriptors)
			;
}


