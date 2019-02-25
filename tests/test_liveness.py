import unittest
import argparse
import sys
import os
import logging
import struct

# if FaceEngine is not installed within the system, add the directory with FaceEngine*.so to system paths
parser = argparse.ArgumentParser()
parser.add_argument("-b", "--bind-path", type=str,
                    help="path to FaceEngine*.so file - binding of luna-sdk")

args = parser.parse_args()
path_to_binding = args.bind_path
print(path_to_binding)
if not os.path.isdir(path_to_binding):
    print("Directory with FaceEngine*.so was not found.")
    exit(1)


print("Directory {0} with python bindings of FaceEngine was included".format(path_to_binding))
print(sys.argv)

sys.path.append(path_to_binding)

# if FaceEngine is installed only this string of code is required for module importing
import FaceEngine as fe

# erase two first arguments for unittest argument parsing
del(sys.argv[1])
del(sys.argv[1])

faceEngine = fe.createFaceEngine("data", "data/faceengine.conf")

test_data_path = "testData"
dataPath = "data"

liveness_engine = fe.createLivenessEngine(faceEngine, "data")

def print_landmarks(landmarks, message=""):
    print(message)
    for i in range(len(landmarks)):
        print(landmarks[i])

print(liveness_engine)

config = fe.createSettingsProvider("data/faceengine.conf")
config_path = config.getDefaultPath()

liveness_engine.setSettingsProvider(config)
path = liveness_engine.getDataDirectory()
print("Path to data directory is: {0}".format(path))
liveness_engine.setDataDirectory(path)

print(fe.LA_PITCH_DOWN)
print(fe.LA_PITCH_UP)
print(fe.LA_YAW_LEFT)
print(fe.LA_YAW_RIGHT)
print(fe.LA_SMILE)
print(fe.LA_MOUTH)
print(fe.LA_EYEBROW)
print(fe.LA_EYE)
print(fe.LA_ZOOM)
print(fe.LA_INFRARED)
print(fe.LA_EYEBROW)
print(fe.LA_COUNT)

print(fe.CLA_DEPTH)
print(fe.CLA_COUNT)

print(fe.LSDKError.Ok)
print(fe.LSDKError.NotInitialized)
print(fe.LSDKError.NotReady)
print(fe.LSDKError.PreconditionFailed)
print(fe.LSDKError.Internal)
angles = fe.Angles()
angles.left = 10
angles.pitch = 20
angles.roll = 30
print("angles {0}, {1} {2}".format(angles.left, angles.pitch, angles.roll))
scores = fe.Scores()
scores.smile = 0.3
scores.mouth = 0.3
scores.eyebrow = 0.4
print("scores {0}, {1} {2}".format(scores.smile, scores.mouth, scores.eyebrow))
eye_states = fe.EyeStates()
eye_states.left = 0
eye_states.right = 1
print("eye_states {0}, {1} ".format(eye_states.left, eye_states.right))

liveness = liveness_engine.createLiveness(fe.LA_INFRARED)
complex_liveness = liveness_engine.createComplexLiveness(fe.CLA_DEPTH)
image = fe.Image()
image_path = test_data_path + "/image1.ppm"
err = image.load(image_path)
if err.isError:
    exit(-1)
err, success = liveness.update(image)
result_det, detection = liveness.getDetection()
if result_det:
    print(detection)
else:
    print("detection was not got")



result_warp, warp = liveness.getWarp()
print("result_warp success:", result_warp, warp.getWidth(), warp.getHeight())
result, landmarks68 = liveness.getLandmarks68()
print("landmarks68 success:", result)
result, landmarks5 = liveness.getLandmarks5()
print_landmarks(landmarks5, "landmarks5:")

print("landmarks5 success:", result)
result, irisLandmarks = liveness.getIrisLandmarks()
print("Irislandmarks success:", result)
result, angles = liveness.getAngles()
print("Angles success:", result)
result, scores = liveness.getScores()
print("Scores success:", result)
result, eye_states = liveness.getEyestates()
print("Eye_states success:", result)
print(err.what, success)
err_complex, success_complex = complex_liveness.update(image, image)
print(err_complex.what, success)

liveness.reset()



complex_liveness.reset()
result, detection = complex_liveness.getDetection()
result, warp = complex_liveness.getWarp()
result, landmarks68 = complex_liveness.getLandmarks68()
result, landmarks5 = complex_liveness.getLandmarks5()
result, irisLandmarks = complex_liveness.getIrisLandmarks()
result, angles = complex_liveness.getAngles()
result, scores = complex_liveness.getScores()
result, eye_states = complex_liveness.getEyestates()
complex_liveness.reset()