// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "AlgorithmBSP.h"
#include "GenData.h"
#include "Floor.h"
#include "Wall.h"
#include "Door.h"
#include "Generator.generated.h"


UCLASS()
class MAPGEN_API AGenerator : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AGenerator();

	void Initialize(AGenData* OutGenData, AAlgorithm* Algorithm);
	void SetAlgorithm(AAlgorithm* Algorithm);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Generate();
	
private:
	void GenerateWalls(AVisualBox * section);
	void GenerateFloor(AVisualBox* section);
	bool isDoor(FVector location, ADoor ** wall);
	bool isWall(FVector location, AWall** wall);
	bool isNeedDoorVertical(FVector location);
	bool isNeedDoorHorizontal(FVector location);
	void GenerateVerticalWalls(float bottom, float top, const float x);
	void GenerateHorizontalWalls(float left, float rigth, const float y);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
		AGenData* GenData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
		AAlgorithm* GenAlgorithm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AlgorithmBSP", meta = (AllowPrivateAccess = "true"))
		FRandomStream random;

	 const float TAIL_SIZE = 10.f;
	 const float DOOR_SIZE = 50.f;
};


