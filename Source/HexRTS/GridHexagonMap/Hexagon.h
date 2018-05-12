// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hexagon.generated.h"

UCLASS()
class HEXRTS_API AHexagon : public AActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "Data")
		UStaticMeshComponent* hexagon;
	// Sets default values for this actor's properties
	AHexagon();
	UFUNCTION(BlueprintImplementableEvent, Category = "Control")
		void Raise(float high, float time);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
