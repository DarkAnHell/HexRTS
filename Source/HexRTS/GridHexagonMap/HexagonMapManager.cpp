// Fill out your copyright notice in the Description page of Project Settings.

#include "HexagonMapManager.h"


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
	this->hexagon = hexagon;
	this->hexMesh = hexMesh;

	map = new FhexagInfo*[this->size];
	float n , x, y, xx, yy;

	PerlinNoiseMatrix pm(268);

	this->hexagonClass = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
	ISMComp = NewObject<UInstancedStaticMeshComponent>(this->hexagonClass);
	ISMComp->RegisterComponent();
	ISMComp->SetStaticMesh(hexMesh);
	ISMComp->SetFlags(RF_Transactional);
	this->hexagonClass->AddInstanceComponent(ISMComp);

	FhexagInfo hi;

	for (int i = 0; i < this->size; i++) {
		map[i] = new FhexagInfo[this->size];

		for (int j = 0; j < this->size; j++) {
			xx = i * 10.0f / size;
			yy = j * 10.0f / size;
			x = i * (size / 2.0f);
			y = j * (size / 2.0f);
			n = pm.noise(y, x, 0.85f);
			n = n - floor(n);
			n = pm.octaveNoise(i, j, 0.75f);
			const FVector pos = FVector(j*scaleXY * 3, (j % 2) * 2 * scaleXY + i * scaleXY * 4, /*((sin(xx+yy)+cos(xx*yy)+cos(yy+xx))/5.0f + xx/10.0f + pow(xx*yy/50.0f,3.0f))*100.0f(sin(i / 45.0f) + cos(j / 45.0f)) * 50.0f + (floor(100.0f * n))*/100.0*n);
			FTransform t(FRotator(0.0f, 90.0f, 0.0f), pos, FVector(scaleXY, scaleXY, scaleZ));
			hi.index = ISMComp->AddInstance(t);
			hi.pos = pos;
			hi.status = 0;
			hi.i = i;
			hi.j = j;
			map[i][j] = hi;
		}
	}
}

FhexagInfo AHexagonMapManager::getHexagon(FVector pos)
{
	if (pos.X < map[0][0].pos.X || pos.X > map[size - 1][size - 1].pos.X || pos.Y < map[0][0].pos.Y || pos.Y > map[size - 1][size - 1].pos.Y) {
		FhexagInfo hx;
		hx.i = -1;
		return hx;
	}

	int j = pos.X / 3 / scaleXY, i = pos.Y;

	if (((int)round(j)) % 2 != 0)
		i -= 2 * scaleXY;
	i = i / 4 / scaleXY;

	if (i < 0 || j < 0 || i >= size || j >= size) {
		FhexagInfo hx;
		hx.i = -1;
		return hx;
	}

	return map[i][j];
}

FhexagInfo AHexagonMapManager::getHexagonByIndex(int i, int j)
{
	FhexagInfo hexagon;

	if (i < this->size && j < size)
		hexagon = map[i][j];

	return hexagon;
}

void AHexagonMapManager::saveMap()
{
	std::ofstream file("leMap.txt");

	if (file.is_open()) {
		file << std::to_string(size) << endl;
		file << std::to_string(scaleXY) << endl;
		file << std::to_string(scaleZ) << endl;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				file << std::to_string(map[i][j].i) << endl;
				file << std::to_string(map[i][j].j) << endl;
				file << std::to_string(map[i][j].pos.X) << endl;
				file << std::to_string(map[i][j].pos.Y) << endl;
				file << std::to_string(map[i][j].pos.Z) << endl;
				file << std::to_string(map[i][j].status) << endl;
				file << std::to_string(map[i][j].index) << endl;
			}
		}
		file.close();
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No se ha podido salvar el mapa correctamente debido a causas desconocidas"));
	}
}

void AHexagonMapManager::loadMap(UClass * hexag, UStaticMesh * hexMeshs)
{
	std::string line;
	std::ifstream file("leMap.txt");
	if (file.is_open()) {

		std::getline(file, line);
		this->size = std::stoi(line);
		std::getline(file, line);
		this->scaleXY = std::stoi(line);
		std::getline(file, line);
		this->scaleZ = std::stoi(line);
		this->hexagon = hexag;
		this->hexMesh = hexMeshs;

		map = new FhexagInfo*[this->size];

		this->hexagonClass = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
		ISMComp = NewObject<UInstancedStaticMeshComponent>(this->hexagonClass);
		ISMComp->RegisterComponent();
		ISMComp->SetStaticMesh(hexMesh);
		ISMComp->SetFlags(RF_Transactional);
		this->hexagonClass->AddInstanceComponent(ISMComp);

		FhexagInfo hi;

		for (int i = 0; i < this->size; i++) {
			map[i] = new FhexagInfo[this->size];

			for (int j = 0; j < this->size; j++) {
				hi.pos = FVector();
				std::getline(file, line);
				std::getline(file, line);
				std::getline(file, line);
				hi.pos.X = std::stof(line);
				std::getline(file, line);
				hi.pos.Y = std::stof(line);
				std::getline(file, line);
				hi.pos.Z = std::stof(line);
				std::getline(file, line);
				hi.status = std::stoi(line);
				std::getline(file, line);

				FTransform t(FRotator(0.0f, 90.0f, 0.0f), hi.pos, FVector(scaleXY, scaleXY, scaleZ));
				hi.index = ISMComp->AddInstance(t);
				hi.i = i;
				hi.j = j;
				map[i][j] = hi;
			}
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No se ha podido cargar el mapa correctamente debido a causas desconocidas"));
	}
}

void AHexagonMapManager::moveHexagons(FVector pos, float space, float speed, int32 radious, bool planing)
{
	FhexagInfo aux = getHexagon(pos);
	float normal = aux.pos.Z;

	if (aux.i == -1)
		return;

	FVector auxP = aux.pos;
	float distance;

	for (int i = 1; i <= radious; i++) {
		if (planing)
			distance = (1 / (radious + 1)) * (radious + 1 - i);
		else
			distance = (space / (radious + 1)) * (radious + 1 - i);
		auxP = auxP + FVector(0.0f, 4 * scaleXY, 0.0f);

		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(3*scaleXY, -2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				if (aux.i == -1)
					continue;
				//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, distance), FVector(scaleXY, scaleXY, scaleZ)));
				if (planing)
					addMovementPolygon(distance * (normal - aux.pos.Z), speed, aux.i, aux.j);
				else
					addMovementPolygon(distance, speed, aux.i, aux.j);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(0.0f, -4 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY*3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY*4+2*scaleXY) {
				aux = getHexagon(auxP);
				if (aux.i == -1)
					continue;
				//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, distance), FVector(scaleXY, scaleXY, scaleZ)));
				if (planing)
					addMovementPolygon(distance * (normal - aux.pos.Z), speed, aux.i, aux.j);
				else
					addMovementPolygon(distance, speed, aux.i, aux.j);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(-3*scaleXY, -2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				if (aux.i == -1)
					continue;
				//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, distance), FVector(scaleXY, scaleXY, scaleZ)));
				if (planing)
					addMovementPolygon(distance * (normal - aux.pos.Z), speed, aux.i, aux.j);
				else
					addMovementPolygon(distance, speed, aux.i, aux.j);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(-3 * scaleXY, 2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				if (aux.i == -1)
					continue;
				//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, distance), FVector(scaleXY, scaleXY, scaleZ)));
				if (planing)
					addMovementPolygon(distance * (normal - aux.pos.Z), speed, aux.i, aux.j);
				else
					addMovementPolygon(distance, speed, aux.i, aux.j);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(0.0f, 4 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				if (aux.i == -1)
					continue;
				//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, distance), FVector(scaleXY, scaleXY, scaleZ)));
				if (planing)
					addMovementPolygon(distance * (normal - aux.pos.Z), speed, aux.i, aux.j);
				else
					addMovementPolygon(distance, speed, aux.i, aux.j);
			}
		}
		for (int j = 1; j <= i; j++) {
			auxP = auxP + FVector(3 * scaleXY, 2 * scaleXY, 0.0f);
			if (auxP.X >= 0.0f && auxP.X < size*scaleXY * 3 && auxP.Y >= 0.0f && auxP.Y < size*scaleXY * 4 + 2 * scaleXY) {
				aux = getHexagon(auxP);
				if (aux.i == -1)
					continue;
				//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, distance), FVector(scaleXY, scaleXY, scaleZ)));
				if (planing)
					addMovementPolygon(distance * (normal - aux.pos.Z), speed, aux.i, aux.j);
				else
					addMovementPolygon(distance, speed, aux.i, aux.j);
			}
		}
	}
	aux = getHexagon(pos);
	if (aux.i == -1)
		return;
	//ISMComp->UpdateInstanceTransform(aux.index, FTransform(FRotator(0.0f, 90.0f, 0.0f), aux.pos + FVector(0.0f, 0.0f, space), FVector(scaleXY, scaleXY, scaleZ)), false, true,false);
	if (!planing)
		addMovementPolygon(space, speed, aux.i, aux.j);

}

TArray<FhexagInfo> AHexagonMapManager::seeAround(FVector pos)
{
	TArray<FhexagInfo> aux = TArray<FhexagInfo>();
	int oi, oj, c = 0;

	FhexagInfo centro = getHexagon(pos);

	if (centro.i == -1)
		return aux;

	if (centro.j % 2 == 1)
		oi = -1;
	else
		oi = 1;
	oj = -oi;

	aux.Add(centro);
	if (centro.j + oi >= 0 && centro.j + oi < size)
		aux.Add(map[centro.i][centro.j + oi]);
	if (centro.i - 1 >= 0)
		aux.Add(map[centro.i - 1][centro.j]);
	if (centro.i + 1 < size)
		aux.Add(map[centro.i + 1][centro.j]);
	oi += 2 * oj;
	if (centro.j + oi >= 0 && centro.j + oi < size) {
		aux.Add(map[centro.i][centro.j + oi]);
		if (centro.i - 1 >= 0)
			aux.Add(map[centro.i - 1][centro.j + oi]);
		if (centro.i + 1 < size)
			aux.Add(map[centro.i + 1][centro.j + oi]);
	}

	return aux;
}

FVector AHexagonMapManager::getCenter()
{
	return FVector(abs((map[0][0].pos.X + map[size-1][size-1].pos.X)/2), abs((map[0][0].pos.Y + map[size - 1][size - 1].pos.Y)/2), 0.0f);
}

FVector AHexagonMapManager::getPercentualPosition(float percentX, float percentY)
{
	return FVector((map[size - 1][size - 1].pos.X - map[0][0].pos.X) * percentX + map[0][0].pos.X, (map[size - 1][size - 1].pos.Y - map[0][0].pos.Y) * percentY + map[0][0].pos.Y, 0.0f);
}

FVector AHexagonMapManager::getMapSize()
{
	return FVector((map[size - 1][size -1].pos.X - map[0][0].pos.X), (map[size - 1][size - 1].pos.Y - map[0][0].pos.Y),0);
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
	movePolygons(DeltaTime);

}

void AHexagonMapManager::movePolygons(float DeltaTime)
{
	FhexagInfo* hx;
	std::list<float> dlt;;
	bool anyChanges = false;
	float posZ;
	for (iterator = changesMap.begin(); iterator != changesMap.end(); ++iterator) {
		hx = &map[(int)iterator->second[2]][(int)iterator->second[3]];
		posZ = FMath::FInterpTo(hx->pos.Z, iterator->second[0], DeltaTime, iterator->second[1]); //hx->pos.Z + (iterator->second[0] / iterator->second[1])*DeltaTime;

		map[(int)iterator->second[2]][(int)iterator->second[3]].pos.Z = posZ;
		//iterator->second[1] -= DeltaTime;
		ISMComp->UpdateInstanceTransform(hx->index, FTransform(FRotator(0.0f, 90.0f, 0.0f), FVector(hx->pos.X, hx->pos.Y, posZ), FVector(scaleXY, scaleXY, scaleZ)));
		if (abs(posZ - iterator->second[0]) < 0.1f) {
			ISMComp->UpdateInstanceTransform(hx->index, FTransform(FRotator(0.0f, 90.0f, 0.0f), FVector(hx->pos.X, hx->pos.Y, iterator->second[0]), FVector(scaleXY, scaleXY, scaleZ)));
			map[(int)iterator->second[2]][(int)iterator->second[3]].pos.Z = iterator->second[0];
			dlt.push_back(iterator->first);
		}
		anyChanges = true;
	}
	for (float x : dlt) {
		changesMap.erase(x);
	}
	if (anyChanges)
		ISMComp->UpdateInstanceTransform(0, FTransform(FRotator(0.0f, 90.0f, 0.0f), map[0][0].pos, FVector(scaleXY, scaleXY, scaleZ)), false, true, false);
}

void AHexagonMapManager::addMovementPolygon(float targetZ, float speed, float i, float j)
{
	changesMap[i * size + j][0] = FMath::Clamp(targetZ + map[(int)i][(int)j].pos.Z,min_high,max_high);
	changesMap[i * size + j][1] = speed;
	changesMap[i * size + j][2] = i;
	changesMap[i * size + j][3] = j;
}

