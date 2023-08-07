#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UEBuffSystemDemo/UEBuffSystemDemoCharacter.h"
#include "GunsTableRow.generated.h"

USTRUCT(BlueprintType)
struct FGunsTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName GunName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGunType GunType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UDataAsset> GunParams;
};
