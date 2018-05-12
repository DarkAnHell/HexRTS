// Fill out your copyright notice in the Description page of Project Settings.

#include "PolyformGraph.h"


// Sets default values for this component's properties
UPolyformGraph::UPolyformGraph()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	UnitsLinkedList = new TLinkedList<GraphNode>();

	// ...
}


// Called when the game starts
void UPolyformGraph::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPolyformGraph::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

