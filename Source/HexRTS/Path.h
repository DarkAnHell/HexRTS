// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GridHexagonMap/HexagonMapManager.h"
#include "Path.generated.h"
/**
 * 
 */
UCLASS()
class HEXRTS_API UPath : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FhexagInfo> hexagons;
	
	
};
