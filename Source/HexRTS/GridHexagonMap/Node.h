// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Hexagon.h"
#include "CoreMinimal.h"

/**
 * 
 */
class HEXRTS_API Node
{

public:

	Node * Last;
	AHexagon* Hexagon;
	float cost = 0;

	Node(Node* last, AHexagon* hexagon, AHexagon* goal);

	~Node();
};
