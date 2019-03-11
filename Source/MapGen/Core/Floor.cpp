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

FVector AFloor::Init(FVector vector)
{
	FloorMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Plane"));
	UInstancedStaticMeshComponent* pResult = NewObject<UInstancedStaticMeshComponent>(this, TEXT("Floor"));
	pResult->RegisterComponent();
	pResult->SetStaticMesh(FloorMesh);
	pResult->SetFlags(RF_Transactional);
	this->AddInstanceComponent(pResult);
	
	FTransform transform(GetActorLocation());
	pResult->AddInstance(transform);

	FVector MeshExtent = pResult->CalcBounds(transform).BoxExtent;
	BoxComponent->SetBoxExtent(MeshExtent);

	UE_LOG(LogTemp, Log, TEXT("Vector before %f %f"), vector.X, vector.Y);
	vector.X += MeshExtent.X;
	vector.Y += MeshExtent.Y;
	FVector in_vector(MeshExtent.X, MeshExtent.Y, 0);
	BoxComponent->SetWorldLocation(vector);
	pResult->SetRelativeLocation(in_vector);
	UE_LOG(LogTemp, Log, TEXT("Vector after %f %f"), vector.X, vector.Y);

	return pResult->CalcBounds(transform).BoxExtent;
}

// Called every frame
void AFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

