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
			map[i][j]->GetRootComponent()->SetWorldScale3D(FVector(scaleXY, scaleXY, scaleZ));
		}
	}
}

AHexagon * AHexagonMapManager::getHexagon(FVector pos)
{
	int j = pos.X / 3 / scaleXY, i = pos.Y;

	if (j % 2 != 0)
		i -= 2 * scaleXY;
	i = i / 4 / scaleXY;

	return map[i][j];
}

void AHexagonMapManager::moveHexagons(FVector pos, float space, float time, int32 radious)
{
	AHexagon* aux = getHexagon(pos);
	FVector auxP = aux->GetRootComponent()->GetComponentLocation();
	aux->Raise(space, time);
	float distance;

	for (int i = 1; i <= radious; i++) {
		distance = (space / (radious + 1)) * (radious + 1 - i);
		auxP = auxP + FVector(0.0f, 4 * scaleXY, 0.0f);
		
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(3*scaleXY, -2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				aux->Raise(distance, time);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(0.0f, -4 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY*3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY*4+2*scaleXY) {
				aux = getHexagon(auxP);
				aux->Raise(distance, time);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(-3*scaleXY, -2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				aux->Raise(distance, time);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(-3 * scaleXY, 2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				aux->Raise(distance, time);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(0.0f, 4 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				aux->Raise(distance, time);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(3 * scaleXY, 2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				aux->Raise(distance, time);
			}
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

