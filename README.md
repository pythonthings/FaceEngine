# LUNA SDK python bindings

Welcome to the **Beta** of PythonBindings for VisionLabs LUNA SDK.
Thank you all for participating of Beta Test.
With all of your feedback and suggestions you can help us to create very useful feature - calling methods of LUNA SDK through python.

In pythonBindings there are some supplementary materials you may find useful.
Look into *cmake/* folder for a CMake find script for the SDK. You are not forced to use
CMake but we advise for it.

Currently we support Linux, Jetson and Windows.

Note, that the SDK is officially supported on RedHat
Linux families (RHEL, CentOS, Fedora). 

**Python version**
PythonBindings were tested with python 3.4, 3.5 and python 3.6.
Other versions may work as well(2.7 and higher), **x64**. 

Only basic methods and classes of LUNA SDK were binded.

**On Unix (Linux, Ubuntu 18, Jetson)**
* GCC 4.8.5 or higher
* A compiler with C++11 support
* CMake >= 3.6
* numpy for python

**On Windows**
* We support only windows x64
* A compiler with C++11 support
* CMake >= 3.6
* Bindings were tested only with "Visual Studio 14 2015".
* numpy for python

## Building on Linux, Jetson
From source files of pythonBindings generated a shared library `FaceEngine*.so`.
This library can be installed in system or used without installing.
 
You should do such steps:

1. Download LUNA SDK.

2. Choose directory with pythonBindings within LUNA SDK.

```bash
cd pythonBindings
```
3. **For library building and installing, only for Linux**:

```bash
$ python3 setup.py install 
```
Library `FaceEngine*.so` will be generated and installed in system.  

to uninstall it:

```bash
$ pip uninstall FaceEngine 
```
Possible you'll need **sudo rights** or use python3 and pip3.

3. **For library building without installing**:

If you want to **build from source files by CMake without installing**:

```bash
$ mkdir build
$ cd build
$ cmake .. -DFSDK_ROOT=<path_to_LUNA_SDK>
$ cmake --build . --config Release
```

If you want to point not default version of python or custom path to LUNA SDK you can write 

**Example building command (from FSDK_ROOT/pythonBindings/build):**
for `python 3.6` for example:

```bash
$ cmake .. -DFSDK_ROOT=<FSDK_path> -DCMAKE_INSTALL_PREFIX=./install -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python3.6
-DPYTHON_LIBRARY=$(python-config --prefix)/lib/libpython3.6.lib -DPYTHON_INCLUDE_DIR=$(python-config --prefix)/include/python3.6
```
**Example of building command (from FSDK_ROOT/pythonBindings/build):**
for python 2.7 for example:

```bash
$ cmake .. -DFSDK_ROOT=<FSDK_path> -DCMAKE_INSTALL_PREFIX=./install -DPYTHON_EXECUTABLE:FILEPATH=/usr/bin/python
-DPYTHON_LIBRARY=$(python-config --prefix)/lib/libpython2.7.lib -DPYTHON_INCLUDE_DIR=$(python-config --prefix)/include/python2.7
```

## Building on Windows

1. Download LUNA SDK.

2. Choose directory with pythonBindings within LUNA SDK.

```cmd
cd pythonBindings
```
Possible you'll need **system administrator rights**.

3. **For library building without installing in system**:

Default python.
```cmd
$ mkdir build
$ cd build
$ cmake -G "Visual Studio 14 2015 Win64" ../ -DFSDK_ROOT=../../ -DCMAKE_BUILD_TYPE=Release 
$ cmake --build . --config Release
$ copy ..\..\bin\vs2015\x64\*.dll release
```

If you want to point version of python or custom path to LUNA SDK you can write

```cmd
$ mkdir build
$ cd build
$ cmake -G "Visual Studio 14 2015 Win64" ../ -DFSDK_ROOT=../../ -DCMAKE_BUILD_TYPE=Release -DPYTHON_EXECUTABLE:FILEPATH=<path_to_python.exe> -DPYTHON_LIBRARY=<path_to_file_python.lib>
$ cmake --build . --config Release
$ copy ..\..\bin\vs2015\x64\*.dll release
```

**Some advises for windows:**
* We support only Windows x64.
* Install Visual Studio with tools for C++ building
* You can use developer terminal built-in in Visual Studio.
* Please use `python x64`
* Please do not forget to copy all `*.dll` from `luna_sdk_path\bin` to `pythonBindings\build\release` or set your own enviroment paths.
* Usual path for built FaceEngine.lib is `pythonBindings\build\release`, but it can be different, please verify your VisualStudio settings.
* Please verify slash `/` or backslash `\` is supported in your windows terminal.

## Usage on Linux
 
### if library FaceEngine*.so was installed by setup.py

**run a script**:

```bash
$ python3 your_script.py
```

**usage example**

```python
import FaceEngine as f
faceEnginePtr = f.createFaceEngine("data", "data/faceengine.conf")
```

### if library FaceEngine*.so was generated by CMake without installing

If FaceEngine*.so was built from sources by CMake pass the path to directory with FaceEngine*.so and add it to system paths:

**run a script**:

```bash
$ python3 your_script.py <path to dir with FaceEngine*.so>
```
**usage example**

```python
import sys
sys.path.append(sys.argv[1])
import FaceEngine as fe
```

Other usage examples could be found in `pythonBindings/tests` and `pythonBindings/examples`.

### Running tests on Linux

From `FSDK_ROOT`:

```bash
$ python3 pythonBindings/tests/test_image.py --bind-path pythonBindings/build
$ python3 pythonBindings/tests/test_rect.py --bind-path pythonBindings/build
$ python3 pythonBindings/tests/test_estimators.py --bind-path pythonBindings/build
$ python3 pythonBindings/tests/test_index.py --bind-path pythonBindings/build # only for service platforms, not for Jetson
$ python3 pythonBindings/tests/test_descriptor.py --bind-path pythonBindings/build
$ python3 pythonBindings/tests/test_detector.py --bind-path pythonBindings/build
$ python3 pythonBindings/tests/test_liveness.py --bind-path pythonBindings/build
```
### Running examples on Linux
Note: data folder must be at \<LUNA_SDK_root\>/data on Linux.
From `FSDK_ROOT`:

```
# Extracting, Matching, this example only for full version (not for front-edition) of LUNS SDK
$ python3 pythonBindings/examples/example_extractor_matcher.py pythonBindings/build testData/photo_2017-03-30_14-47-43_p.ppm testData/warp1.ppm testData/warp2.ppm

# Detecting, Landmarks, Estimating (Attributes, Quality, Eyes, Head pose and so on)
$ python3 pythonBindings/examples/example_estimators.py pythonBindings/build testData/photo_2017-03-30_14-47-43_p.ppm
 
# Detecting and warping
$ python3 pythonBindings/examples/example_detector_warper.py pythonBindings/build testData/photo_2017-03-30_14-47-43_p.ppm

# Index building, only for service platforms, not for Jetson
$ python3 pythonBindings/examples/example_index.py pythonBindings/build testData/emotions1.ppm testData testData/imageListIndex.txt 0.3
```
**usage of FaceEngine, example**

```python
import FaceEngine as fe
faceEnginePtr = fe.createFaceEngine("data", "data/faceengine.conf")
```

## Usage on Windows**

Pass the path to directory with FaceEngine.lib and add it to system paths.

**run a script**:

```cmd
$ python3 your_script.py <path to FaceEngine*.lib>
```
**usage example**

```python
import sys
sys.path.append(sys.argv[1])
import FaceEngine as fe
```
### Running tests on Windows

Please verify path with built FaceEngine.lib for your version of python. Usual path is `pythonBindings/build/release`.

```cmd
$ python3 pythonBindings/examples/example_estimators.py pythonBindings/build/release testData/photo_2017-03-30_14-47-43_p.ppm
$ python3 pythonBindings/examples/example_detector_warper.py pythonBindings/build/release testData/photo_2017-03-30_14-47-43_p.ppm
$ python3 pythonBindings/examples/example_extractor_matcher.py pythonBindings/build/release testData/photo_2017-03-30_14-47-43_p.ppm testData/warp1.ppm testData/warp2.ppm
$ python3 pythonBindings/examples/example_index.py pythonBindings/build/release testData/emotions1.ppm testData testData/imageListIndex.txt 0.3
```
### Running examples on Windows
Please verify path with built FaceEngine.lib for your version of python. Usual path is `pythonBindings/build/release`.

```cmd
$ python3 pythonBindings/tests/test_image.py --bind-path pythonBindings/build/release
$ python3 pythonBindings/tests/test_rect.py --bind-path pythonBindings/build/release
$ python3 pythonBindings/tests/test_estimators.py --bind-path pythonBindings/build/release
$ python3 pythonBindings/tests/test_index.py --bind-path pythonBindings/build/release
$ python3 pythonBindings/tests/test_descriptor.py --bind-path pythonBindings/build/release
$ python3 pythonBindings/tests/test_detector.py --bind-path pythonBindings/build/release
$ python3 pythonBindings/tests/test_liveness.py --bind-path pythonBindings/build/release
```

## About pybind11
PythonBindings use pybind11. pybind11 is a lightweight header-only library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code. Its goals and syntax are similar to the excellent Boost.Python library by David Abrahams: to minimize boilerplate code in traditional extension modules by inferring type information using compile-time introspection. Think of this library as a tiny self-contained version of Boost.Python with everything stripped away that isn't relevant for binding generation. Without comments, the core header files only require ~4K lines of code and depend on Python (2.7 or 3.x) and the C++ standard library. This compact implementation was possible thanks to some of the new C++11 language features (specifically: tuples, lambda functions and variadic templates). Since its creation, this library has grown beyond Boost.Python in many ways, leading to dramatically simpler binding code in many common situations.

Tutorial and reference documentation is provided at [doc](http://pybind11.readthedocs.org/en/master). A PDF version of the manual is available [here](https://media.readthedocs.org/pdf/pybind11/master/pybind11.pdf).

## pybind11 license

pybind11 is provided under a BSD-style license that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.

## Examples of code
As described befor first you need to create main object of FaceEngine:

```python
# if FaceEngine was not installed pass path to directory with FaceEngine*.so and add it to system paths
sys.path.append(sys.argv[1])
import FaceEngine as fe

```
Using of basic methods you can see in examples or tests. More detailed information about methods and classes you can see in `src/FaceEngine.cpp`.

```
py::class_<fsdk::IEthnicityEstimatorPtr>(f, "IEthnicityEstimatorPtr")
.def("estimate",[](
	const fsdk::IEthnicityEstimatorPtr& est,
	const fsdk::Image &warp) {
		fsdk::EthnicityEstimation out;
		fsdk::Result<fsdk::FSDKError> err = est->estimate(warp, out);
		if (err.isOk())
			return py::cast(out);
		else
			return py::cast(FSDKErrorResult(err)); })
		;
```

Here you can see class `fsdk::IEthnicityEstimatorPtr`, method `estimate`, its specification. You should pass image warp, the result will be `ethnicityEstimation` struct or error. 
How to use this from python, see `example.py`:

```python
import FaceEngine as fe
faceEngine = fe.createFaceEngine("data", "data/faceengine.conf")
image = fe.Image()
image.load("testData/Warp1.ppm")
ethnicityEstimator = faceEngine.createEthnicityEstimator()
ethnicity_result = ethnicityEstimator.estimate(image)
print("Ethnicity estimation result {0}".format(ethnicity_result))
```

### Creating of basic objects

```python
config = fe.createSettingsProvider("data/faceengine.conf")
attributeEstimator = faceEngine.createAttributeEstimator()
qualityEstimator = faceEngine.createQualityEstimator()
ethnicityEstimator = faceEngine.createEthnicityEstimator()
blackWhiteEstimator = faceEngine.createBlackWhiteEstimator()
smileEstimator = faceEngine.createSmileEstimator()
detector = faceEngine.createDetector(fe.FACE_DET_V1)
warper = faceEngine.createWarper()
descriptor = faceEngine.createDescriptor()
descriptorExtractor = faceEngine.createExtractor()
```
and so on.

### Landmarks

Landmarks are special classes binded to python. They are similar on python lists. It is possible to use some standard python built-in functions for them: `__len__`, `__getitem__`. The method `__setitem__` is used only for testing purposes. The length of definity type of landmarks is always fixed. For example len(landmarks5) is 5.

```python
for i in range(len(landmarks)):
        print(landmarks[i])
```

### Arrays

In some cases C++ arrays are casted to python lists.
For example:

```
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
            const uint32_t size = err.getValue();
            auto detectionResultPyList = py::list(size);
            for (uint32_t i = 0; i < size; ++i) {
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
```

**usage example**
```python
    detector = faceEngine.createDetector(fe.FACE_DET_V1)
    max_detections = 3
    print("Image for detection: ", _image_det.getHeight(), _image_det.getWidth(), _image_det.isValid())
    detector_result = detector.detect(_image_det, _image_det.getRect(), max_detections)
    print("detector result = ", detector_result)
    print("Detections: ")
    for i, item in enumerate(detector_result, 1):
        print(i, item)
```

### Enums
```c++
py::enum_<fsdk::Format::Type>(f, "FormatType")
	.value("Unknown", fsdk::Format::Unknown)
	.value("B8G8R8X8", fsdk::Format::B8G8R8X8)
	.value("R8G8B8X8", fsdk::Format::R8G8B8X8)
	.value("B8G8R8", fsdk::Format::B8G8R8)
	.value("R8G8B8", fsdk::Format::R8G8B8)
	.value("R8", fsdk::Format::R8)
	.value("R16", fsdk::Format::R16)
		;
```
**usage example**
```python
print(fe.FormatType.R8)
```

### SettingsProvider
SettingsProvider has quite difficult structure. 
Usage example you can see in `example_detector_warper.py`

```python
    config = fe.createSettingsProvider("data/faceengine.conf")
    config_path = config.getDefaultPath()
    print("Config settings: DefaultPath {0}".format(config_path))
    config.setValue("system", "verboseLogging", fe.SettingsProviderValue(value))
    faceEngine.setSettingsProvider(config)
    val = config.getValue("system", "verboseLogging")
    print("Config settings: \"system\", \"verboseLogging\" = {0}".format(val.asInt()))

```


