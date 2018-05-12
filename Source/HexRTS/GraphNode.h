// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "CoreMinimal.h"

/**
 * 
 */
class HEXRTS_API GraphNode
{
public:	
	AActor* Unit;
	int cost;

	GraphNode( AActor* unit, int cost);
	~GraphNode();
};
