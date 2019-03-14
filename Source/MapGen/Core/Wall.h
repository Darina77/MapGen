// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/StaticMesh.h"
#include "Wall.generated.h"

UCLASS()
class MAPGEN_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FVector Init(FVector& vector, FVector& scale);
	void GetCurrentExtension(FVector& vector);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall", meta = (AllowPrivateAccess = "true"))
		UStaticMesh* WallMesh;
	UPROPERTY(EditAnywhere, Category = "Wall")
		UBoxComponent* BoxComponent;
	UPROPERTY(EditAnywhere, Category = "Wall")
	FVector MeshExtension;
};
