// Fill out your copyright notice in the Description page of Project Settings.

#include "GenData.h"

// Sets default values
AGenData::AGenData()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetRelativeLocation(FVector(0, 0, 0));
}

// Called when the game starts or when spawned
void AGenData::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGenData::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGenData::GetRootSizeX()
{
	return RoomSizeX;
}

float AGenData::GetRootSizeY()
{
	return RoomSizeY;
}

int AGenData::GetRandomSeed()
{
	return RandomSeed;
}

int AGenData::GetMinSubRoomSize()
{
	return MinSubRoomSize;
}

int AGenData::GetBorderSize()
{
	return BorderSize;
}