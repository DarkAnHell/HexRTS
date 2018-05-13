// Fill out your copyright notice in the Description page of Project Settings.

#include "AStar.h"

AStar::AStar(AHexagonMapManager* map)
{
	this->Map = map;
}

TArray<AHexagon*> AStar::PathTo(AHexagon* start, AHexagon* goal)
{
	_Discovered = TArray<Node>();
	_Descarted = TArray<Node>();

	TArray<AHexagon*> path = TArray<AHexagon*>();
	
	while (_Discovered.Num()>0) {
		
		Node current = _Discovered[0];
		_Descarted.Add(current);

		_Discovered.RemoveAt(0);

		if (current.Hexagon == goal) {
			do {
				path.Add(current.Hexagon);
				current = *current.Last;

			} while (current.Last != NULL);

			break;
		}

		TArray<Node> neighbours = this->Discover(current);

		_Discovered.Append(neighbours);
		_Discovered.Sort([]( Node A, Node B) {
			return A.cost < B.cost;
		});
	}


	return path;
}

AStar::~AStar()
{
}

TArray<Node> AStar::Discover(Node node)
{
	return TArray<Node>();
}


