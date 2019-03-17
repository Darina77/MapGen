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
		GenerateWalls(oneSection);
	}
}

void AGenerator::GenerateHorizontalWalls(float left, float rigth, const float y)
{
	UE_LOG(LogTemp, Log, TEXT("Generate Horizontal for Left - %f, Right - %f, Y - %f"), left, rigth, y);
	float border = GenData->GetBorderSize();
	float step = 50.f;
	float doorXPlaceRand = 0;
	bool isDoorPlace = false;

	float mainTop = GenData->GetRootSizeY()/2.f;
	float mainBottom = -GenData->GetRootSizeY()/2.f;
	if (y != mainTop && y != mainBottom)
	{
		doorXPlaceRand = random.FRandRange((left + DOOR_SIZE * 2), (rigth - DOOR_SIZE * 2));
		UE_LOG(LogTemp, Log, TEXT("Generate door %f " ), doorXPlaceRand);
		isDoorPlace = true;
	}

	for (float j = left; j < rigth; j += step)
	{
		FVector vector(j, y, 0.f);
		FVector scale;
		if (j + step > rigth)
		{
			scale.X = ((rigth - j) / step);
			scale.Y = border / TAIL_SIZE;
			scale.Z = 1.f;
			step = rigth - j;
			j = rigth;
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

			UE_LOG(LogTemp, Log, TEXT("Skip Wall on horizontal X - %f, Y - %f, Z - %f"), chackPlaceTop.X, chackPlaceTop.Y, chackPlaceTop.Z);
			FVector collisionExtend;
			collisionWall->GetCurrentExtension(collisionExtend);
			step = collisionExtend.X * 2.f;
		}
		else if (isDoor(chackPlaceTop, &collisionDoor)) {
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on horizontal X - %f, Y - %f, Z - %f"), chackPlaceTop.X, chackPlaceTop.Y, chackPlaceTop.Z);
			FVector collisionExtendDoor;
			collisionDoor->GetCurrentExtension(collisionExtendDoor);
			step = collisionExtendDoor.X * 2.f;
		}
		else
		{
			if (j <= doorXPlaceRand && doorXPlaceRand <= (j + step) && isDoorPlace)
			{
				UE_LOG(LogTemp, Log, TEXT("Generate Door X - %f. Between rigth - %f, left - %f"), j, rigth, left);
				FVector doorLocation(j, y, 0);
				UE_LOG(LogTemp, Log, TEXT("Generate Door on X - %f, Y - %f, Z - %f"), doorLocation.X, doorLocation.Y, doorLocation.Z);
				ADoor* door = GetWorld()->SpawnActor<ADoor>(doorLocation, FRotator::ZeroRotator);
				step = door->Init(FVector(DOOR_SIZE, (DOOR_SIZE *(border / TAIL_SIZE)), DOOR_SIZE), doorLocation).X * 2.f;
			}
			else {
				AWall* wall = GetWorld()->SpawnActor<AWall>(vector, FRotator::ZeroRotator);
				step = wall->Init(vector, scale).X * 2.f;
			}
		}
	}
}

void AGenerator::GenerateVerticalWalls(float bottom, float top, const float x)
{
	UE_LOG(LogTemp, Log, TEXT("Generate Vertical for Top - %f, Bottom - %f, X - %f"), top, bottom, x);
	float border = GenData->GetBorderSize();
	float doorYPlaceRand = -1;
	bool isDoorPlace = false;

	float mainRight = GenData->GetRootSizeX() / 2.f;
	float mainLeft = -GenData->GetRootSizeX() / 2.f;
	float endTop = top + TAIL_SIZE;
	if (x != mainRight && x != mainLeft)
	{
		doorYPlaceRand = random.FRandRange((bottom + DOOR_SIZE * 2), (top - DOOR_SIZE * 2));
		UE_LOG(LogTemp, Log, TEXT("Generate door %f"), doorYPlaceRand);
		isDoorPlace = true;
	}

	float step = 50.f;
	for (float i = bottom; i < endTop; i += step)
	{
		FVector vector(x, i, 0.f);
		FVector scale;
		if (i + step > endTop)
		{
			scale.X = border / TAIL_SIZE;
			scale.Y = ((endTop - i) / step);
			scale.Z = 1.f;
			step = endTop - i;
			i = endTop;
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
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on vertical X - %f, Y - %f, Z - %f"), chackPlaceRight.X, chackPlaceRight.Y, chackPlaceRight.Z);
			FVector collisionExtend;
			collisionWall->GetCurrentExtension(collisionExtend);
			step = collisionExtend.Y * 2.f;
		}
		else if (isDoor(chackPlaceRight, &collisionDoor))
		{
			UE_LOG(LogTemp, Log, TEXT("Skip Wall on vertical X - %f, Y - %f, Z - %f"), chackPlaceRight.X, chackPlaceRight.Y, chackPlaceRight.Z);
			FVector collisionExtendDoor;
			collisionDoor->GetCurrentExtension(collisionExtendDoor);
			step = collisionExtendDoor.Y * 2.f;
		}
		else
		{
			if (i <= doorYPlaceRand && doorYPlaceRand <= (i + step) && isDoorPlace)
			{
				UE_LOG(LogTemp, Log, TEXT("Generate Door Y - %f. Between bottom - %f, top - %f"), i, bottom, top);
				FVector doorLocation(x, i, 0);
				UE_LOG(LogTemp, Log, TEXT("Generate Door on X - %f, Y - %f, Z - %f"), doorLocation.X, doorLocation.Y, doorLocation.Z);
				ADoor* door = GetWorld()->SpawnActor<ADoor>(doorLocation, FRotator::ZeroRotator);
				step = door->Init(FVector((DOOR_SIZE *(border / TAIL_SIZE)), DOOR_SIZE, DOOR_SIZE), doorLocation).Y *2.f;

			}
			else {
				AWall* wall = GetWorld()->SpawnActor<AWall>(vector, FRotator::ZeroRotator);
				step = wall->Init(vector, scale).Y *2.f;
			}

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
	GenerateVerticalWalls(bottom, top, right);
	GenerateVerticalWalls(bottom, top, left);
	GenerateHorizontalWalls(left, right, top);
	GenerateHorizontalWalls(left, right, bottom);
}

void AGenerator::GenerateFloor()
{
	float top = GenData->GetRootSizeX() / 2.f;
	float bottom = -GenData->GetRootSizeX() / 2.f;
	float rigth = GenData->GetRootSizeY() / 2.f;
	float left = -GenData->GetRootSizeY() / 2.f;
	UE_LOG(LogTemp, Log, TEXT("Generate Floor for Top - %f, Bottom - %f, Right - %f, Left - %f"), top, bottom, rigth, left);
	float step = 50.f;
	for (float i = bottom; i < top; i += step)
	{
		for (float j = left; j < rigth; j += step)
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


