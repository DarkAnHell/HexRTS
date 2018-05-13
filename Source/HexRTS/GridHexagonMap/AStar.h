// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Node.h"
#include "HexagonMapManager.h"
#include "CoreMinimal.h"

/**
 * 
 */
class HEXRTS_API AStar
{
	TArray<Node> _Descarted;
	TArray<Node> _Discovered;

public:

	AHexagonMapManager * Map;

	AStar(AHexagonMapManager* map);

	UFUNCTION(BlueprintCallable, Category = "Utilities")
	TArray<AHexagon*> PathTo(AHexagon* start,AHexagon* goal);

	~AStar();

protected:

	TArray<Node> Discover(Node node);

	

};
