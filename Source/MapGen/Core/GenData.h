// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Algorithm.h"
#include "Components/BoxComponent.h"
#include "GenData.generated.h"

UCLASS()
class MAPGEN_API AGenData : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenData();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetRootSizeX();
	float GetRootSizeY();
	int GetRandomSeed();
	int GetMinSubRoomSize();
	int GetBorderSize();
	AAlgorithm* GetAlgorithm();
private:
	UPROPERTY(Instanced)
		UBoxComponent* BoxComponent;
public:	
	UPROPERTY(EditAnywhere, Category = "GenData")
		AAlgorithm* Algorithm;
	UPROPERTY(EditAnywhere, Category = "GenData")
		float RoomSizeX;
	UPROPERTY(EditAnywhere, Category = "GenData")
		float RoomSizeY;
	UPROPERTY(EditAnywhere, Category = "GenData")
		int RandomSeed;
	UPROPERTY(EditAnywhere, Category = "GenData")
		int MinSubRoomSize;
	UPROPERTY(EditAnywhere, Category = "GenData")
		int BorderSize;
};
