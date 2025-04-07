// Fill out your copyright notice in the Description page of Project Settings.

#include "Data/LFPGridSetting.h"

ULFPGridFragmentSettingBase* ULFPGridSetting::GetGridFragment( const TSubclassOf< ULFPGridFragmentSettingBase >& ClassType ) const
{
	for ( const TObjectPtr< ULFPGridFragmentSettingBase >& Fragment : GridFragmentList )
	{
		if ( IsValid(Fragment) && Fragment->IsA(ClassType.Get()) )
		{
			return Fragment;
		}
	}

	return nullptr;
}
