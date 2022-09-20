// Copyright (c) 2022 Loh Zhi Kang ( loh0123@hotmail.com )
//
// Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
// or copy at http://opensource.org/licenses/MIT)

#include "LohFunctionPluginLibrary.h"
#include "LohFunctionPlugin.h"
#include "Misc/OutputDeviceNull.h"

bool ULohFunctionPluginLibrary::CallFunctionByFunctionData(const FLFPFunctionData& FunctionData, const bool bForce)
{
	if (IsValid(FunctionData.Caller) == false)  return false;

	FOutputDeviceNull OutputDeviceNull;

	return FunctionData.Caller->CallFunctionByNameWithArguments(*FunctionData.NameAndParam, OutputDeviceNull, nullptr, bForce);
}
