// Fill out your copyright notice in the Description page of Project Settings.

#include "Wall.h"

// Sets default values
AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AWall::Init(FVector& vector, FVector& scale)
{
	WallMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube"));
	FVector MeshExtend(WallMesh->GetBoundingBox().GetExtent());
	MeshExtend *= scale;
	BoxComponent->SetWorldScale3D(scale);
	BoxComponent->SetWorldLocation((vector+MeshExtend));
	BoxComponent->SetBoxExtent(MeshExtend);
	
	UInstancedStaticMeshComponent* pResult = NewObject<UInstancedStaticMeshComponent>(this, TEXT("Wall"));
	pResult->SetStaticMesh(WallMesh);
	pResult->bEditableWhenInherited = true;
	pResult->bSelectable = true;
	pResult->SetFlags(RF_Transactional);
	pResult->RegisterComponent();

	pResult->AddInstance(GetActorTransform());
	
	return MeshExtend;
}