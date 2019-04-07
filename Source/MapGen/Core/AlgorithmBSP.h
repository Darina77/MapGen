// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Algorithm.h"
#include "GenData.h"
#include "AlgorithmBSP.generated.h"

UCLASS()
class MAPGEN_API AAlgorithmBSP : public AAlgorithm
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
	virtual void Go(int RandmSeed, int BorderSize, int MinSubRoomSize, float GetRootSizeX, float GetRootSizeY) override;
	virtual TQueue<AVisualBox*>* GetAllSections() override;
private:
	void InitStartBox(float GetRootSizeX, float GetRootSizeY);
	bool Slice(AVisualBox* section, int MinRoomSpace);

private:
	//All generated sections
	TQueue<AVisualBox*> AllSections;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AlgorithmBSP", meta = (AllowPrivateAccess = "true"))
	FRandomStream random;

	static const int MAX_SLICES = 25;
	static const int TAIL_SIZE = 100;

};
