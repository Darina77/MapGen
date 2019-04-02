// Fill out your copyright notice in the Description page of Project Settings.

#include "AgentBaseAlgorithm.h"

// Sets default values
AAgentBaseAlgorithm::AAgentBaseAlgorithm()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgentBaseAlgorithm::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAgentBaseAlgorithm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAgentBaseAlgorithm::Go(int RandmSeed, int BorderSize, int MinSubRoomSize, float GetRootSizeX, float GetRootSizeY)
{
	random.Initialize(RandmSeed);
	BounderX = GetRootSizeX / 2;
	BounderY = GetRootSizeY / 2;
	run = true;

	int MinRoomSpace = (BorderSize * 2) + MinSubRoomSize;
	FVector step;
	AVisualBox* lastRoom = InitStartRoom(MinRoomSpace);

	for (int i = 0; i < MAX_TRY; ++i)
	{
		run = true;
		float sizeX = random.FRandRange(MinRoomSpace, BounderX);
		float sizeY = random.FRandRange(MinRoomSpace, BounderY);
		AVisualBox* newRoom = GetWorld()->SpawnActor<AVisualBox>(step, FRotator::ZeroRotator);
		newRoom->Initialize(sizeX, sizeY, 0, 0);
		step = MakeStep(lastRoom, newRoom);
		if (run) {
			newRoom->Initialize(sizeX, sizeY, step.X, step.Y);
			AllSections.Enqueue(newRoom);
			lastRoom = newRoom;
		}
		else {
			newRoom->Destroy();
		}
		
	}
}

AVisualBox* AAgentBaseAlgorithm::InitStartRoom(int MinRoomSpace)
{
	FVector Location = GetActorLocation();

	float sizeX = random.FRandRange(MinRoomSpace, BounderX);
	float sizeY = random.FRandRange(MinRoomSpace, BounderY);
	AVisualBox* StartBox = GetWorld()->SpawnActor<AVisualBox>(FVector(Location.X, Location.Y, 0), FRotator::ZeroRotator);
	StartBox->Initialize(sizeX, sizeY, Location.X, Location.Y);
	AllSections.Enqueue(StartBox);

	return StartBox;
}

FVector AAgentBaseAlgorithm::MakeStep(AVisualBox* from, AVisualBox* newRoom)
{
	
	int trys = 0;
	
	while (trys < MAX_TRY) {
		float direction = random.FRandRange(0, 100);
		UE_LOG(LogTemp, Log, TEXT("Direction %f"), direction);
		FVector to = from->GetActorLocation();
		FVector check = to;
		float stepX = from->getHalfWidth();
		float stepY = from->getHalfHeight();
		float newRoomX = newRoom->getHalfWidth();
		float newRoomY = newRoom->getHalfHeight();
		if (direction <= 25) 
		{
			UE_LOG(LogTemp, Log, TEXT("Step top"));//Top
			to.Y += stepY+ newRoomY;
			check.Y += to.Y + 2;
		}
		else if (direction > 25 && direction <= 50) //Bottom
		{
			UE_LOG(LogTemp, Log, TEXT("Step bottom"));
			to.Y -= stepY+ newRoomY;
			check.Y -= to.Y + 2;
		}
		else if (direction > 50 && direction <= 75) //Right
		{
			UE_LOG(LogTemp, Log, TEXT("Step right"));
			to.X += stepX+ newRoomX;
			check.X += to.X + 2;
		}
		else if (direction > 75 && direction <= 100) //Left
		{
			UE_LOG(LogTemp, Log, TEXT("Step left"));
			to.X -= stepX+ newRoomX;
			check.X -= to.X + 2;
		}

		UE_LOG(LogTemp, Log, TEXT("Step Vector (%f, %f)"), to.X, to.Y);
		if ((to.X + newRoomX )<= BounderX && (to.X - newRoomX) >= -BounderX && (to.Y + newRoomY)<= BounderY && (to.Y - newRoomY )>= -BounderY && !isBoxHere(newRoom, check))
		{
			UE_LOG(LogTemp, Log, TEXT("End Vector"));
			return to;
		}
		else 
		{
			trys++;
		}
	}

	if (trys == MAX_TRY) {
		run = false;
	}
	return from->GetActorLocation();
}

bool AAgentBaseAlgorithm::isBoxHere(AVisualBox* newRoom, FVector place)
{
	TArray<AActor*> collisionActors;
	newRoom->SetActorLocation(place);
	newRoom->GetOverlappingActors(collisionActors, TSubclassOf<class AVisualBox>());
	return collisionActors.FindItemByClass<AVisualBox>();
}

TQueue<AVisualBox*>* AAgentBaseAlgorithm::GetAllSections()
{
	return &AllSections;
}
