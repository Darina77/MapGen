// Fill out your copyright notice in the Description page of Project Settings.

#include "Generator.h"

// Sets default values
AGenerator::AGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	}
}

void AGenerator::SetAlgorithm(AAlgorithmBSP* Algorithm)
{
	GenAlgorithm = Algorithm;
}

void AGenerator::Initialize(AGenData* OutGenData, AAlgorithmBSP* Algorithm)
{
	GenData = OutGenData;
	GenAlgorithm = Algorithm;
}

// Called when the game starts or when spawned
void AGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGenerator::Generate()
{
	GenerateFloor();
	TQueue<AVisualBox*>* AllSections = GenAlgorithm->GetAllSections();
	while (!AllSections->IsEmpty())
	{
		AVisualBox* oneSection;
		AllSections->Dequeue(oneSection);
		GenerateDoor(oneSection);
		GenerateWalls(oneSection);
	}
}

void AGenerator::GenerateVerticalWalls(float left, float rigth, const float y)
{
	float border = GenData->GetBorderSize();
	float step = 50.f;
	float endRight = rigth + 5.f;
	for (float j = left; j < endRight; j += step)
	{
		FVector vector(j, y, 0.f);
		FVector scale;
		if (j + step > endRight)
		{
			scale.X = ((endRight - j) / step);
			scale.Y = border / TAIL_SIZE;
			scale.Z = 1.f;
			step = endRight - j;
			j = endRight;
		}
		else 
		{
			scale.X = 1.f;
			scale.Y = border / TAIL_SIZE;
			scale.Z = 1.f;
		}

		FVector chackPlaceTop((vector.X + step / 2.f), (vector.Y + TAIL_SIZE), vector.Z);
		AWall* collisionWall = NewObject<AWall>(this, TEXT("CollisionWall"));
		ADoor* collisionDoor = NewObject<ADoor>(this, TEXT("CollisionDoor"));
		if (isWall(chackPlaceTop, &collisionWall)) {
			
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on verical X - %f, Y - %f, Z - %f"), chackPlaceTop.X, chackPlaceTop.Y, chackPlaceTop.Z);
			FVector collisionExtend;
			collisionWall->GetCurrentExtension(collisionExtend);
			step = collisionExtend.X * 2.f;
		}
		else if (isDoor(chackPlaceTop, &collisionDoor)) {
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on verical X - %f, Y - %f, Z - %f"), chackPlaceTop.X, chackPlaceTop.Y, chackPlaceTop.Z);
			FVector collisionExtendDoor;
			collisionDoor->GetCurrentExtension(collisionExtendDoor);
			step = collisionExtendDoor.X * 2.f;
		}
		else 
		{
			AWall* wall = GetWorld()->SpawnActor<AWall>(vector, FRotator::ZeroRotator);
			step = wall->Init(vector, scale).X * 2.f;
		}
	}
}

void AGenerator::GenerateHorizontalWalls(float bottom, float top, const float x)
{
	float border = GenData->GetBorderSize();
	float step = 50.f;
	for (float i = bottom; i < top; i += step)
	{
		FVector vector(x, i, 0.f);
		FVector scale;
		if (i + step > top)
		{
			scale.X = border / TAIL_SIZE;
			scale.Y = ((top - i) / step);
			scale.Z = 1.f;
			step = top - i;
			i = top;
		}
		else 
		{
			scale.X = border / TAIL_SIZE;
			scale.Y = 1.f;
			scale.Z = 1.f;
		}
		FVector chackPlaceRight((vector.X + TAIL_SIZE), (vector.Y + step / 2.f), vector.Z);
		AWall* collisionWall = NewObject<AWall>(this, TEXT("CollisionWall"));
		ADoor* collisionDoor = NewObject<ADoor>(this, TEXT("CollisionDoor"));
		if (isWall(chackPlaceRight, &collisionWall)) {
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on horiz X - %f, Y - %f, Z - %f"), chackPlaceRight.X, chackPlaceRight.Y, chackPlaceRight.Z);
			FVector collisionExtend;
			collisionWall->GetCurrentExtension(collisionExtend);
			step = collisionExtend.Y * 2.f;
		}
		else if (isDoor(chackPlaceRight, &collisionDoor))
		{
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on horiz X - %f, Y - %f, Z - %f"), chackPlaceRight.X, chackPlaceRight.Y, chackPlaceRight.Z);
			FVector collisionExtendDoor;
			collisionDoor->GetCurrentExtension(collisionExtendDoor);
			step = collisionExtendDoor.Y * 2.f;
		}
		else 
		{
			AWall* wall = GetWorld()->SpawnActor<AWall>(vector, FRotator::ZeroRotator);
			step = wall->Init(vector, scale).Y *2.f;
			
		}
	}
}

void AGenerator::GenerateWalls(AVisualBox* section)
{
	float top = section->getTopBounder();
	float bottom = section->getBottomBounder();
	float right = section->getRigthBounder();
	float left = section->getLeftBounder();
	

	UE_LOG(LogTemp, Log, TEXT("Generate Walls for Top - %f, Bottom - %f, Right - %f, Left - %f"), top, bottom, right, left);
	GenerateVerticalWalls(left, right, top);
	GenerateVerticalWalls(left, right, bottom);
	GenerateHorizontalWalls(bottom, top, right);
	GenerateHorizontalWalls(bottom, top, left);
}

void AGenerator::GenerateHorizontalDoor(float bottom, float top, const float x)
{
	float mainRigth = GenData->GetRootSizeY() / 2.f;
	float mainLeft = -GenData->GetRootSizeY() / 2.f;
	float border = GenData->GetBorderSize();

	if (x == mainLeft || x == mainRigth)
	{
		return;
	}
	else
	{
		float doorYPlaceRand = random.FRandRange((bottom + DOOR_SIZE*2) /TAIL_SIZE, (top - DOOR_SIZE*2)/TAIL_SIZE);
		float doorYPlace = doorYPlaceRand*TAIL_SIZE;
		FVector doorLocation(x, doorYPlace, 0);
		UE_LOG(LogTemp, Log, TEXT("Generate Door Y - %f. Between bottom - %f, top - %f"), doorYPlace, bottom, top);
		UE_LOG(LogTemp, Log, TEXT("Generate Door on X - %f, Y - %f, Z - %f"), doorLocation.X, doorLocation.Y, doorLocation.Z);
		ADoor* door = GetWorld()->SpawnActor<ADoor>(doorLocation, FRotator::ZeroRotator);
		door->Init(FVector((DOOR_SIZE *( border / TAIL_SIZE)), DOOR_SIZE, DOOR_SIZE), doorLocation);
	}
}

void AGenerator::GenerateVerticalDoor(float left, float rigth, const float y)
{
	float mainTop = GenData->GetRootSizeX() / 2.f;
	float mainBottom = -GenData->GetRootSizeX() / 2.f;
	float border = GenData->GetBorderSize();

	if (y == mainTop || y == mainBottom)
	{
		return;
	}
	else
	{
		float doorXPlaceRand = random.FRandRange((rigth + DOOR_SIZE*2)/ TAIL_SIZE, (left - DOOR_SIZE*2) / TAIL_SIZE);
		float doorXPlace = doorXPlaceRand * TAIL_SIZE;
		UE_LOG(LogTemp, Log, TEXT("Generate Door X - %f. Between rigth - %f, left - %f"), doorXPlace, rigth, left);
		FVector doorLocation(doorXPlace, y, 0);
		UE_LOG(LogTemp, Log, TEXT("Generate Door on X - %f, Y - %f, Z - %f"), doorLocation.X, doorLocation.Y, doorLocation.Z);
		ADoor* door = GetWorld()->SpawnActor<ADoor>(doorLocation, FRotator::ZeroRotator);
		door->Init(FVector(DOOR_SIZE, (DOOR_SIZE *(border / TAIL_SIZE)), DOOR_SIZE), doorLocation);
	}
}

void AGenerator::GenerateDoor(AVisualBox* section)
{
	float top = section->getTopBounder();
	float bottom = section->getBottomBounder();
	float right = section->getRigthBounder();
	float left = section->getLeftBounder();

	GenerateVerticalDoor(right, left, top);
	GenerateVerticalDoor(right, left, bottom);
	GenerateHorizontalDoor(bottom, top, right);
	GenerateHorizontalDoor(bottom, top, left);
}


void AGenerator::GenerateFloor()
{
	float top = GenData->GetRootSizeX() / 2.f;
	float bottom = -GenData->GetRootSizeX() / 2.f;
	float rigth = GenData->GetRootSizeY() / 2.f;
	float left = -GenData->GetRootSizeY() / 2.f;
	UE_LOG(LogTemp, Log, TEXT("Generate Floor for Top - %f, Bottom - %f, Right - %f, Left - %f"), top, bottom, rigth, left);
	float step = 50.f;
	for (float i = bottom; i < top; i+= step)
	{
		for (float j = left; j < rigth; j+= step)
		{
			UE_LOG(LogTemp, Log, TEXT("Place x - %f, y - %f"), i, j);
			FVector vector(i, j, 0.f);
			AFloor* floor = GetWorld()->SpawnActor<AFloor>(vector, FRotator::ZeroRotator);
			step = floor->Init(vector).X * 2.f;
		}
	}
}

bool AGenerator::isDoor(FVector location, ADoor** wall)
{
	AVisualBox* chackActor = GetWorld()->SpawnActor<AVisualBox>(location, FRotator::ZeroRotator);
	TArray<AActor*> collisionActors;
	chackActor->GetOverlappingActors(collisionActors, TSubclassOf<class ADoor>());
	return collisionActors.FindItemByClass<ADoor>(wall);
}

bool AGenerator::isWall(FVector location, AWall** wall)
{
	AVisualBox* chackActor = GetWorld()->SpawnActor<AVisualBox>(location, FRotator::ZeroRotator);
	TArray<AActor*> collisionActors;
	chackActor->GetOverlappingActors(collisionActors, TSubclassOf<class AWall>());
	return collisionActors.FindItemByClass<AWall>(wall);
}


