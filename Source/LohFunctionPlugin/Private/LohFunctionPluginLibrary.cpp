// Copyright (c) 2023 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "LohFunctionPluginLibrary.h"
#include "LohFunctionPlugin.h"
#include "Misc/OutputDeviceNull.h"

bool ULohFunctionPluginLibrary::ContainPoint(const FLFPIntPointList& List, const int32 Index)
{
	return List.ContainIndex(Index);
}

void ULohFunctionPluginLibrary::AddPoint(UPARAM(ref)FLFPIntPointList& List, const FIntPoint Range)
{
	List.Add(Range);
}

void ULohFunctionPluginLibrary::RemovePoint(UPARAM(ref)FLFPIntPointList& List, const FIntPoint Range)
{
	List.Remove(Range);
}

FGameplayTag ULohFunctionPluginLibrary::GetGameplayTagFromName(const FName TagName)
{
	return FGameplayTag::RequestGameplayTag(TagName, false);
}

int32 ULohFunctionPluginLibrary::GetMetaDataAsInt(UPARAM(ref)FLFPCompactMetaData& MetaData)
{
	return MetaData.GetDataAsInt();
}

void ULohFunctionPluginLibrary::SetMetaDataAsInt(UPARAM(ref)FLFPCompactMetaData& MetaData, const int32 Value)
{
	MetaData.SetDataAsInt(Value);
}

float ULohFunctionPluginLibrary::GetMetaDataAsFloat(UPARAM(ref)FLFPCompactMetaData& MetaData)
{
	return MetaData.GetDataAsFloat();
}

void ULohFunctionPluginLibrary::SetMetaDataAsFloat(UPARAM(ref)FLFPCompactMetaData& MetaData, const float Value)
{
	MetaData.SetDataAsFloat(Value);
}

bool ULohFunctionPluginLibrary::GetMetaDataAsBool(UPARAM(ref)FLFPCompactMetaData& MetaData)
{
	return MetaData.GetDataAsBool();
}

void ULohFunctionPluginLibrary::SetMetaDataAsBool(UPARAM(ref)FLFPCompactMetaData& MetaData, const bool Value)
{
	MetaData.SetDataAsBool(Value);
}

FString ULohFunctionPluginLibrary::GetMetaDataAsString(UPARAM(ref)FLFPCompactMetaData& MetaData)
{
	return MetaData.GetDataAsString();
}

void ULohFunctionPluginLibrary::SetMetaDataAsString(UPARAM(ref)FLFPCompactMetaData& MetaData, const FString Value)
{
	MetaData.SetDataAsString(Value);
}
