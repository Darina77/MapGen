// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Algorithm.h"
#include "AgentBaseAlgorithm.generated.h"

UCLASS()
class MAPGEN_API AAgentBaseAlgorithm : public AAlgorithm
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgentBaseAlgorithm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Go(int RandmSeed, int BorderSize, int MinSubRoomSize, float GetRootSizeX, float GetRootSizeY) override;
	AVisualBox * InitStartRoom(int MinRoomSpace);
	FVector MakeStep(AVisualBox* from, AVisualBox* newRoom);
	bool isBoxHere(AVisualBox* newRoom, FVector place);
	virtual TQueue<AVisualBox*>* GetAllSections() override;
private:
	// All generated sections
	TQueue<AVisualBox*> AllSections;
	static const int MAX_TRY = 25;
	bool run;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AgentBaseAlgorithm", meta = (AllowPrivateAccess = "true"))
		FRandomStream random;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AgentBaseAlgorithm", meta = (AllowPrivateAccess = "true"))
		float BounderX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AgentBaseAlgorithm", meta = (AllowPrivateAccess = "true"))
		float BounderY;
		
};