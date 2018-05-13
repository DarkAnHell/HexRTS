// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GridHexagonMap/HexagonMapManager.h"
#include "CoreMinimal.h"

/**
 * 
 */
class HEXRTS_API Node
{

public:

	Node * Last;
	FhexagInfo Hexagon;
	float cost = 0;

	Node(Node* last, FhexagInfo hexagon, FhexagInfo goal);

	~Node();
};
