// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VisualBox.h"
#include "AlgorithmBSP.generated.h"

UCLASS()
class MAPGEN_API AAlgorithmBSP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAlgorithmBSP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	void InitStartBox();
private:
	//All generated sections
	TArray<AVisualBox*> AllSections;
};
