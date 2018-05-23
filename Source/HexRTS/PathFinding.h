// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridHexagonMap/Node.h"
#include "GridHexagonMap/HexagonMapManager.h"
#include "Components/ActorComponent.h"
#include "PathFinding.generated.h"
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEXRTS_API UPathFinding : public UActorComponent
{
	GENERATED_BODY()

	TArray<Node*> _Descarted;
	TArray<Node*> _Discovered;
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mira aqui")
	AHexagonMapManager * Map;

	UFUNCTION(BlueprintCallable, Category = "Utilities")
		TArray<FhexagInfo> PathTo(FhexagInfo start, FhexagInfo goal, int aceptableDistance);

	// Sets default values for this component's properties
	UPathFinding();

protected:

	TArray<Node*> Discover(Node* node, FhexagInfo goal);
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
