// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generator.generated.h"

UCLASS()
class MAPGEN_API AGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerator();

	void Initialize(float RoomSizeX, float RoomSizeY, int RandomSeed, int MaxSubRooms);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
		float GenRoomSizeX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
		float GenRoomSizeY;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
		int GenRandomSeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Generator", meta = (AllowPrivateAccess = "true"))
		int GenMaxSubRooms;
};


