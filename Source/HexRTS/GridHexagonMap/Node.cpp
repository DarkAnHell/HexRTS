// Fill out your copyright notice in the Description page of Project Settings.

#include "Node.h"

Node::Node(Node* last, FhexagInfo hexagon, FhexagInfo goal)
{
	this->Last = last;
	this->Hexagon = hexagon;
	this->cost = (goal.pos - hexagon.pos).Size();
}
Node::~Node()
{
}
