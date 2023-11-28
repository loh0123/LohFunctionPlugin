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
