// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexagon.h"
#include "HexagonMapManager.generated.h"

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
		void construct(int32 siz, int32 scalXY, int32 scalZ, UClass* hexag);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		AHexagon* getHexagon(FVector pos);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void moveHexagons(FVector pos, float space, float time, int32 radious);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AHexagon*** map;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
