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

FVector AWall::Init(FVector vector, FVector scale)
{
	WallMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Cube"));
	UInstancedStaticMeshComponent* pResult = NewObject<UInstancedStaticMeshComponent>(this, TEXT("Wall"));
	pResult->RegisterComponent();
	pResult->SetStaticMesh(WallMesh);
	pResult->SetFlags(RF_Transactional);
	this->AddInstanceComponent(pResult);
	
	BoxComponent->SetWorldScale3D(scale);
	BoxComponent->SetWorldLocation(vector);
	
	
	FTransform transform(GetActorTransform());
	pResult->AddInstance(transform);
	
	FVector MeshExtent = pResult->CalcBounds(transform).BoxExtent;
	BoxComponent->SetBoxExtent(MeshExtent);

	UE_LOG(LogTemp, Log, TEXT("Mesh extent %f %f %f"), MeshExtent.X, MeshExtent.Y, MeshExtent.Z);
	vector.X += MeshExtent.X;
	vector.Y += MeshExtent.Y;
	vector.Z += MeshExtent.Z;
	FVector in_vector(MeshExtent.X, MeshExtent.Y, MeshExtent.Z);
	BoxComponent->SetWorldLocation(vector);
	//pResult->SetRelativeLocation(in_vector);
	//UE_LOG(LogTemp, Log, TEXT("Vector after %f %f"), vector.X, vector.Y);

	return pResult->CalcBounds(transform).BoxExtent;
}