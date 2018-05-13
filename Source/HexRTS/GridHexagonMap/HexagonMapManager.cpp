// Fill out your copyright notice in the Description page of Project Settings.

#include "HexagonMapManager.h"
#include "Runtime/Engine/Classes/Components/InstancedStaticMeshComponent.h"


// Sets default values
AHexagonMapManager::AHexagonMapManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AHexagonMapManager::construct(int32 size, int32 scaleXY, int32 scaleZ, UClass * hexagon, UStaticMesh * hexMesh)
{
	this->size = size;
	this->scaleXY = scaleXY;
	this->scaleZ = scaleZ;

	map = new FhexagInfo*[this->size];
	float n, x, y;

	PerlinNoiseMatrix pm(268);

	AActor*hex = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
	UInstancedStaticMeshComponent *ISMComp = NewObject<UInstancedStaticMeshComponent>(hex);
	ISMComp->RegisterComponent();
	ISMComp->SetStaticMesh(hexMesh);
	ISMComp->SetFlags(RF_Transactional);
	hex->AddInstanceComponent(ISMComp);

	FhexagInfo hi;

	for (int i = 0; i < this->size; i++) {
		map[i] = new FhexagInfo[this->size];

		for (int j = 0; j < this->size; j++) {
			x = 80 * i / (size);
			y = 80 * j / (size);
			n = pm.noise(y, x, 0.85f);
			n = n - floor(n);
			const FVector pos = FVector(j*scaleXY * 3, (j % 2) * 2 * scaleXY + i * scaleXY * 4, (sin(i / 10.0f) + cos(j / 10.0f)) * 50 + (floor(30 * n) - 15));
			FTransform t(FRotator(0.0f, 90.0f, 0.0f), pos, FVector(scaleXY, scaleXY, scaleZ));
			hi.index = ISMComp->AddInstance(t);
			hi.pos = pos;
			hi.status = 0;
			map[i][j] = hi;
		}
	}
}

FhexagInfo AHexagonMapManager::getHexagon(FVector pos)
{
	float j = pos.X / 3 / scaleXY, i = pos.Y;

	if (((int)round(j)) % 2 != 0)
		i -= 2 * scaleXY;
	i = i / 4 / scaleXY;

	return map[(int)round(i)][(int)round(j)];
}

void AHexagonMapManager::moveHexagons(FVector pos, float space, float time, int32 radious)
{/*
 hexagInfo aux = getHexagon(pos);
 FVector auxP = aux.pos;
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
 }*/
}

TArray<FhexagInfo> AHexagonMapManager::seeAround(FVector pos)
{
	TArray<FhexagInfo> aux = TArray<FhexagInfo>();
	int oi, oj, c = 0;

	FhexagInfo centro = getHexagon(pos);

	if (centro.j % 2 == 1)
		oi = -1;
	else
		oi = 1;
	oj = -oi;

	if (centro.j + oi > 0 && centro.j + oi < size)
		aux.Add(map[centro.i][centro.j + oi]);
	if (centro.i - 1 > 0)
		aux.Add(map[centro.i - 1][centro.j]);
	if (centro.i + 1 < size)
		aux.Add(map[centro.i + 1][centro.j]);
	oi += 2 * oj;
	if (centro.j + oi > 0 && centro.j + oi < size) {
		aux.Add(map[centro.i][centro.j + oi]);
		if (centro.i - 1 > 0)
			aux.Add(map[centro.i - 1][centro.j + oi]);
		if (centro.i + 1 < size)
			aux.Add(map[centro.i + 1][centro.j + oi]);
	}

	return aux;
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

