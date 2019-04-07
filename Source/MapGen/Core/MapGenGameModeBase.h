// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GenData.h"
#include "Algorithm.h"
#include "Generator.h"
#include "EngineUtils.h"
#include "MapGenGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAPGEN_API AMapGenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	//Initialize the game.
	virtual void BeginPlay() override;
private:
	void CheckGenData();
private:
	
	UPROPERTY(VisibleAnywhere, Category = "GameMode")
	FRandomStream MainStream;

	UPROPERTY(VisibleAnywhere, Category="GameMode")
	AGenData* GenData;
	
	UPROPERTY(VisibleAnywhere, Category = "GameMode")
	AGenerator* Generator;

	UPROPERTY(VisibleAnywhere, Category = "GameMode")
	AAlgorithm* Algorithm;

	UPROPERTY(VisibleAnywhere, Category="GameMode")
	bool isGenData;
};
