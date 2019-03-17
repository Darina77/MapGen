// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class MAPGEN_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector Init(FVector size, FVector location);
	void GetCurrentExtension(FVector& vector);
private:
	UPROPERTY(EditAnywhere, Category = "Door")
		UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "Door")
		FVector extension;
};
