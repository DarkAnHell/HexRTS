// Fill out your copyright notice in the Description page of Project Settings.

#include "HexagonMapManager.h"


// Sets default values
AHexagonMapManager::AHexagonMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHexagonMapManager::construct(int32 size, int32 scaleXY, int32 scaleZ, UClass * hexagon)
{
	this->size = size;
	this->scaleXY = scaleXY;
	this->scaleZ = scaleZ;

	map = new AHexagon**[this->size];

	for (int i = 0; i < this->size; i++) {
		map[i] = new AHexagon*[this->size];

		for (int j = 0; j < this->size; j++) {
			const FVector pos = FVector(j*scaleXY * 3, (j % 2) * 2 * scaleXY + i * scaleXY * 4, 0.0f);
			map[i][j] = (AHexagon*)((GetWorld())->SpawnActor(hexagon, &pos, &FRotator::ZeroRotator));
		}
	}
}

// Called when the game starts or when spawned
void AHexagonMapManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHexagonMapManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

