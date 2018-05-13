// Fill out your copyright notice in the Description page of Project Settings.

#include "Node.h"

Node::Node(Node* last, AHexagon* hexagon, AHexagon* goal)
{
	this->Last = last;
	this->Hexagon = hexagon;
	this->cost = (goal->GetActorLocation() - hexagon->GetActorLocation()).Size();
}
Node::~Node()
{
}
