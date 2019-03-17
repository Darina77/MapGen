// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector ADoor::Init(FVector size, FVector location) {
	BoxComponent->SetBoxExtent(size);
	BoxComponent->SetWorldLocation(location+size);
	extension = size;
	return extension;
}

void ADoor::GetCurrentExtension(FVector & vector)
{
	vector = extension;
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

