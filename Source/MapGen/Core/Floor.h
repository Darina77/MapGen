// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Floor.generated.h"

UCLASS()
class MAPGEN_API AFloor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector Init(FVector vector);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Floor", meta = (AllowPrivateAccess = "true"))
	UStaticMesh* FloorMesh;
	UPROPERTY(EditAnywhere, Category = "Floor")
	UBoxComponent* BoxComponent;
};