//
// Created by mar on 27.04.18.
//
#pragma once

#include <fsdk/FaceEngine.h>
#include <lsdk/LivenessEngine.h>
#include <fstream>
#include <iostream>

struct FSDKErrorResult {

	bool isOk;
	bool isError;
	fsdk::FSDKError fsdkError;
	const char* what;

	FSDKErrorResult(fsdk::Result<fsdk::FSDKError> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	fsdkError(err.getError()),
	what(err.what())
	{};
};

// liveness error
struct LSDKErrorResult {
	
	bool isOk;
	bool isError;
	lsdk::LSDKError lsdkError;
	const char* what;
	
	LSDKErrorResult(fsdk::ResultValue<lsdk::LSDKError, bool> err) :
		isOk(err.isOk()),
		isError(err.isError()),
		lsdkError(err.getError()),
		what(err.what())
	{};
};

struct LSDKErrorValueBool {
	bool isOk;
	bool isError;
	lsdk::LSDKError lsdkError;
	const char* what;
	bool value;
	
	LSDKErrorValueBool(fsdk::ResultValue<lsdk::LSDKError, bool> err) :
		isOk(err.isOk()),
		isError(err.isError()),
		lsdkError(err.getError()),
		what(err.what()),
		value(err.getValue())
	{};
};

//fsdk::Result<fsdk::ISerializableObject::Error>
struct SerializeErrorResult {
	
	bool isOk;
	bool isError;
	fsdk::ISerializableObject::Error serializeError;
	const char* what;
	
	SerializeErrorResult(fsdk::Result<fsdk::ISerializableObject::Error> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	serializeError(err.getError()),
	what(err.what())
	{};
};

struct ImageErrorResult {
	bool isOk;
	bool isError;
	fsdk::Image::Error imageError;
	const char* what;

	ImageErrorResult(fsdk::Result<fsdk::Image::Error> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	imageError(err.getError()),
	what(err.what())
	{};
};

struct DescriptorBatchResult {
	bool isOk;
	bool isError;
	fsdk::IDescriptorBatch::Error descriptorBatchError;
	const char* what;

	DescriptorBatchResult(fsdk::Result<fsdk::IDescriptorBatch::Error> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	descriptorBatchError(err.getError()),
	what(err.what())
	{};
};

struct FSDKErrorValueInt {
	bool isOk;
	bool isError;
	fsdk::FSDKError fsdkError;
	const char* what;
	int value;

	FSDKErrorValueInt(fsdk::ResultValue<fsdk::FSDKError, int> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	fsdkError(err.getError()),
	what(err.what()),
	value(err.getValue())
	{};
	
	FSDKErrorValueInt(fsdk::ResultValue<fsdk::FSDKError, fsdk::DescriptorId> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	fsdkError(err.getError()),
	what(err.what()),
	value(err.getValue())
	{};
};

struct FSDKErrorValueBool {
	bool isOk;
	bool isError;
	fsdk::FSDKError fsdkError;
	const char* what;
	int value;
	
	FSDKErrorValueBool(fsdk::ResultValue<fsdk::FSDKError, bool> err) :
		isOk(err.isOk()),
		isError(err.isError()),
		fsdkError(err.getError()),
		what(err.what()),
		value(err.getValue())
	{};
};

struct FSDKErrorValueFloat {
	bool isOk;
	bool isError;
	fsdk::FSDKError fsdkError;
	const char* what;
	float value;

	FSDKErrorValueFloat(fsdk::ResultValue<fsdk::FSDKError, float> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	fsdkError(err.getError()),
	what(err.what()),
	value(err.getValue())
	{};

};

struct FSDKErrorValueMatching {
	bool isOk;
	bool isError;
	fsdk::FSDKError fsdkError;
	const char* what;
	fsdk::MatchingResult value;

	FSDKErrorValueMatching(fsdk::ResultValue<fsdk::FSDKError, fsdk::MatchingResult> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	fsdkError(err.getError()),
	what(err.what()),
	value(err.getValue())
	{};

};

//struct DetectionResult {
//	fsdk::Detection detection;
//	fsdk::Landmarks5 landmarks5;
//	fsdk::Landmarks68 landmarks68;
//	DetectionResult(const fsdk::Detection &detection,
//					const fsdk::Landmarks5& landmarks5,
//					const fsdk::Landmarks68&) :
//	detection(detection), landmarks5(landmarks5), landmarks68(landmarks68) {}
//};

struct SettingsProviderResult {
	bool isOk;
	bool isError;
	fsdk::ISettingsProvider::Error settingsProviderError;
	const char* what;

	SettingsProviderResult(fsdk::Result<fsdk::ISettingsProvider::Error> err) :
	isOk(err.isOk()),
	isError(err.isError()),
	settingsProviderError(err.getError()),
	what(err.what())
	{};
};