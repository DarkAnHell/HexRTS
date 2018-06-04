 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include <map>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
		AActor* hexagonClass;
	UInstancedStaticMeshComponent *ISMComp;
	//UInstancedStaticMeshComponent *ISMComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Preconstructor")
		int32 sizePre = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Preconstructor")
		int32 scaleXYPre = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Preconstructor")
		int32 scaleZPre = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Preconstructor")
		UClass* hexagonPre = NULL;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Preconstructor")
		UStaticMesh * hexMeshPre = NULL;
	
		

	// Sets default values for this actor's properties
	AHexagonMapManager();
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void construct(int32 siz, int32 scalXY, int32 scalZ, UClass* hexag, UStaticMesh * hexMeshs);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FhexagInfo getHexagon(FVector pos);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FhexagInfo getHexagonByIndex(int i, int j);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void moveHexagons(FVector pos, float space, float speed, int32 radious);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		TArray<FhexagInfo> seeAround(FVector pos);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FVector getCenter();
	//UFUNCTION(BlueprintCallable, Category = "Construction")
	//	void generateAbomination();
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FVector getPercentualPosition(float percentX, float percentY);
	UFUNCTION(BlueprintCallable, Category = "Operations")
		FVector getMapSize();
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void saveMap();
	UFUNCTION(BlueprintCallable, Category = "Operations")
		void loadMap(UClass* hexag, UStaticMesh * hexMeshs);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FhexagInfo** map;
	float max_high = 1000.0f;
	float min_high = -1000.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
private:
	std::map<float, float[4]> changesMap;
	std::map<float, float[4]> ::iterator iterator;
	void movePolygons(float DeltaTime);
	void addMovementPolygon(float targetZ, float speed, float i, float j);
};
