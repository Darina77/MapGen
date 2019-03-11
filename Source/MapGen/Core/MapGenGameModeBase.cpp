// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenGameModeBase.h"

void AMapGenGameModeBase::BeginPlay()
{
	CheckGenData();
	if (isGenData)
	{
		MainStream.Initialize(GenData->GetRandomSeed());
		
	
		Algorithm = GetWorld()->SpawnActor<AAlgorithmBSP>(FVector(0, 0, 0), FRotator::ZeroRotator);
		Algorithm->Initialize(GenData);
		Algorithm->Go();
		
		Generator = GetWorld()->SpawnActor<AGenerator>(FVector(50, 50, 0), FRotator::ZeroRotator);
		Generator->Initialize(GenData, Algorithm);
		Generator->Generate();
	}
}

void AMapGenGameModeBase::CheckGenData()
{
	for (TActorIterator<AGenData> ActorItr(this->GetWorld()); ActorItr; ++ActorItr)
	{
		GenData = *ActorItr;
		isGenData = true;
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("WorldData Actor not found, cannot generate level without this actor, place one at 0,0,0 and re-launch the game."));
	isGenData = false;
	return;
}
