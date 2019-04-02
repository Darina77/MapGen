// Fill out your copyright notice in the Description page of Project Settings.

#include "Floor.h"

// Sets default values
AFloor::AFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}

// Called when the game starts or when spawned
void AFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AFloor::Init(FVector vector, FVector& scale)
{
	FloorMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane"));
	FVector MeshExtend(FloorMesh->GetBoundingBox().GetExtent());
	MeshExtend *= scale;
	BoxComponent->SetWorldScale3D(scale);
	BoxComponent->SetWorldLocation((vector + FVector(MeshExtend.X, MeshExtend.Y, 0)));
	BoxComponent->SetBoxExtent(MeshExtend);

	UE_LOG(LogTemp, Log, TEXT("New Floor X - %f, Y - %f, Z - %f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	UInstancedStaticMeshComponent* pResult = NewObject<UInstancedStaticMeshComponent>(this, TEXT("Floor"));
	pResult->SetStaticMesh(FloorMesh);
	pResult->bEditableWhenInherited = true;
	pResult->bSelectable = true;
	pResult->SetFlags(RF_Transactional);
	pResult->RegisterComponent();

	pResult->AddInstance(GetActorTransform());

	return MeshExtend;
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

