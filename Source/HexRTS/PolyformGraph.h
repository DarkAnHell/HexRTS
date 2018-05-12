// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GraphNode.h"
#include "PolyformGraph.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXRTS_API UPolyformGraph : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Units)
		TArray<AActor*> SpecialUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Units)
		TArray<AActor*> Units;

	// Sets default values for this component's properties
	UPolyformGraph();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int GetCost(AActor* AActorToPolyform) {

		int cost = 1;
		int index;


		return cost;

	}
	
	
};
