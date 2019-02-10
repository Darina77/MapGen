// Fill out your copyright notice in the Description page of Project Settings.

#include "Generator.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGenerator::Initialize(float RoomSizeX, float RoomSizeY, int RandomSeed, int MaxSubRooms)
{
	GenRoomSizeX = RoomSizeX;
	GenRoomSizeY = RoomSizeY;
	GenRandomSeed = RandomSeed;
	GenMaxSubRooms = MaxSubRooms;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

