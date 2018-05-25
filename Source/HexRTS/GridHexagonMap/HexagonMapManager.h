// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include <map>
#include <string>
#include <list>
#include "Hexagon.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "PerlinNoiseMatrix.h"
#include "Runtime/Engine/Classes/Components/InstancedStaticMeshComponent.h"
#include "HexagonMapManager.generated.h"

USTRUCT(BlueprintType)
struct FhexagInfo {
	GENERATED_BODY();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 i;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 j;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FVector pos;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 status;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		UClass* hexagon;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		UStaticMesh * hexMesh;
	AActor* hexagonClass;
	UInstancedStaticMeshComponent *ISMComp;
	//UInstancedStaticMeshComponent *ISMComp;

	// Sets default values for this actor's properties
	AHexagonMapManager();
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void construct(int32 siz, int32 scalXY, int32 scalZ, UClass* hexag, UStaticMesh * hexMeshs);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FhexagInfo getHexagon(FVector pos);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void moveHexagons(FVector pos, float space, float speed, int32 radious);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		TArray<FhexagInfo> seeAround(FVector pos);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FVector getCenter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FhexagInfo** map;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	std::map<float, float[4]> changesMap;
	std::map<float, float[4]> ::iterator iterator;
	void movePolygons(float DeltaTime);
	void addMovementPolygon(float targetZ, float speed, float i, float j);
};
