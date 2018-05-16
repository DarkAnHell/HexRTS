// Fill out your copyright notice in the Description page of Project Settings.

#include "PathFinding.h"

#include "Runtime/Engine/Classes/Engine/Engine.h"
TArray<FhexagInfo> UPathFinding::PathTo(FhexagInfo start, FhexagInfo goal)
{
	_Discovered = TArray<Node*>();
	_Descarted = TArray<Node*>(); 


	TArray<FhexagInfo> path = TArray<FhexagInfo>();
	_Discovered.Add(new Node(NULL,start,goal));

	while (_Discovered.Num()>0) {

		Node* current = _Discovered[0];
		_Descarted.Add(current);
		_Discovered.RemoveAt(0);

		if (current->Hexagon.pos ==goal.pos) {

			while (current != NULL) {
				path.Insert(current->Hexagon,0);
				current = current->Last;

			} 
			
			break;
		}

		TArray<Node*> neighbours = this->Discover(current, goal);

		_Discovered.Append(neighbours);
		_Discovered.Sort([](const Node A, const Node B) {
			return A.cost < B.cost;
		});
	}


	return path;
}

// Sets default values for this component's properties
UPathFinding::UPathFinding()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


TArray<Node*> UPathFinding::Discover(Node* node, FhexagInfo goal)
{
	TArray<FhexagInfo> possibles= Map->seeAround(node->Hexagon.pos);
	TArray<Node*> results = TArray<Node*>();
	int i = 0;

	for (i = 1;i<possibles.Num();i++) {
		FVector hexpos = possibles[i].pos;

		//Look if is accesible
		if (!_Discovered.ContainsByPredicate([&](const Node* InItem) { return InItem->Hexagon.pos==hexpos; })
			&& !_Descarted.ContainsByPredicate([&](const Node* InItem) { return InItem->Hexagon.pos==hexpos; })
			&& possibles[i].status != -1) {
			results.Add(new Node(node,possibles[i],goal));
		}
	}

	return results;
}

// Called when the game starts
void UPathFinding::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPathFinding::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

