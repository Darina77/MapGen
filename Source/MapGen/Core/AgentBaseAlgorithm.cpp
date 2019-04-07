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
	BounderX = GetRootSizeX / 4.0f;
	BounderY = GetRootSizeY / 4.0f;

	int MinRoomSpace = (BorderSize * 2.f) + MinSubRoomSize;
	FVector step;
	AVisualBox* lastRoom = InitStartRoom(MinRoomSpace);
	int roomCount = ((GetRootSizeX / MinRoomSpace) * (GetRootSizeY / MinRoomSpace)) * 0.5f;

	for (int i = 0; i < roomCount; ++i)
	{
		float sizeX = random.FRandRange(MinRoomSpace, BounderX);
		float sizeY = random.FRandRange(MinRoomSpace, BounderY);
		AVisualBox* newRoom = MakeStep(lastRoom, sizeX, sizeY);
		if (newRoom)
		{
			AllSections.Enqueue(newRoom);
			lastRoom = newRoom;
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

AVisualBox* AAgentBaseAlgorithm::MakeStep(AVisualBox* from, float sizeX, float sizeY)
{	
	for (int trys = 0; trys < MAX_TRY; trys++) {
		float direction = random.FRandRange(0, 100);
		UE_LOG(LogTemp, Log, TEXT("Direction %f"), direction);
		FVector to = from->GetActorLocation();
		FVector checkNeibors = to;
		FVector checkBoxes = to;
		float stepX = from->getHalfWidth();
		float stepY = from->getHalfHeight();
		float newRoomX = sizeX/2.f;
		float newRoomY = sizeY/2.f;
	
		if (direction <= 25) 
		{
			UE_LOG(LogTemp, Log, TEXT("Step top"));//Top
			to.Y += stepY + newRoomY;
			checkNeibors.Y += stepY + 2.f;
			checkBoxes.Y = to.Y + 2.f;
		}
		else if (direction > 25 && direction <= 50) //Bottom
		{
			UE_LOG(LogTemp, Log, TEXT("Step bottom"));
			to.Y -= stepY + newRoomY;
			checkNeibors.Y -= stepY + 2.f;
			checkBoxes.Y = to.Y - 2.f;
		}
		else if (direction > 50 && direction <= 75) //Right
		{
			UE_LOG(LogTemp, Log, TEXT("Step right"));
			to.X += stepX + newRoomX;
			checkNeibors.X += stepX + 2.f;
			checkBoxes.X = to.X + 2.f;
		}
		else if (direction > 75 && direction <= 100) //Left
		{
			UE_LOG(LogTemp, Log, TEXT("Step left"));
			to.X -= stepX + newRoomX;
			checkNeibors.X -= stepX + 2.f;
			checkBoxes.X = to.X - 2.f;
		}

		if (!isNeibors(checkNeibors))
		{
			AVisualBox* newRoom = GetWorld()->SpawnActor<AVisualBox>(to, FRotator::ZeroRotator);
			newRoom->Initialize(sizeX, sizeY, 0, 0);
			if (!isBoxHere(checkBoxes, newRoom))
			{
				newRoom->Initialize(sizeX, sizeY, to.X, to.Y);
				return newRoom;
			}
			else 
			{
				newRoom->Destroy();
			}
		}

	}

	return nullptr;
}

TQueue<AVisualBox*>* AAgentBaseAlgorithm::GetAllSections()
{
	return &AllSections;
}

bool AAgentBaseAlgorithm::isNeibors(FVector location)
{
	AVisualBox* chackActor = GetWorld()->SpawnActor<AVisualBox>(location, FRotator::ZeroRotator);
	TArray<AActor*> collisionActors;
	chackActor->GetOverlappingActors(collisionActors, TSubclassOf<class AVisualBox>());
	chackActor->Destroy();
	return collisionActors.FindItemByClass<AVisualBox>();
}

bool AAgentBaseAlgorithm::isBoxHere(FVector location, AVisualBox* newRoom)
{
	TArray<AActor*> collisionActors;
	newRoom->SetActorLocation(location);
	newRoom->GetOverlappingActors(collisionActors, TSubclassOf<class AVisualBox>());
	return collisionActors.FindItemByClass<AVisualBox>();
}