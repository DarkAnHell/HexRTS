// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexagon.h"
#include "PerlinNoiseMatrix.h"
#include "HexagonMapManager.generated.h"

USTRUCT(BlueprintType)
struct FhexagInfo {
	GENERATED_BODY();
	UPROPERTY()
		int32 i;
	UPROPERTY()
		int32 j;
	UPROPERTY()
		FVector pos;
	UPROPERTY()
		int32 status;
	UPROPERTY()
		int32 index;
};

UCLASS()
class HEXRTS_API AHexagonMapManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		int32 size;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		int32 scaleXY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		int32 scaleZ;

	// Sets default values for this actor's properties
	AHexagonMapManager();
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void construct(int32 siz, int32 scalXY, int32 scalZ, UClass* hexag, UStaticMesh * hexMesh);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FhexagInfo getHexagon(FVector pos);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void moveHexagons(FVector pos, float space, float time, int32 radious);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		TArray<FhexagInfo> seeAround(FVector pos);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FhexagInfo** map;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
