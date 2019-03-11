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
		//GenerateDoor(oneSection);
	}
}

void AGenerator::GenerateWalls(AVisualBox* section)
{
	float top = section->getTopBounder();
	float bottom = section->getBottomBounder();
	float rigth = section->getRigthBounder();
	float left = section->getLeftBounder();
	float border = GenData->GetBorderSize();
	UE_LOG(LogTemp, Log, TEXT("Generate Walls for Top - %f, Bottom - %f, Right - %f, Left - %f"), top, bottom, rigth, left);
	float step = 50;
	
	for (float j = left; j < rigth; j += step)
	{
		FVector vector_top(top, j, 0.f);
		FVector vector_bottom(bottom, j, 0.f);

		FVector scale;
		if (j + step > rigth)
		{
			scale.X = border/10.f;
			scale.Y = (rigth - j)/ step;
			scale.Z = 1.f;
			j = rigth;
		}
		else {
			scale.X = border/10.f;
			scale.Y = 1.f;
			scale.Z = 1.f;
		}

		AWall* wall_top = GetWorld()->SpawnActor<AWall>(vector_top, FRotator::ZeroRotator);
		wall_top->Init(vector_top, scale);

		AWall* wall_bottom = GetWorld()->SpawnActor<AWall>(vector_bottom, FRotator::ZeroRotator);
		step = wall_bottom->Init(vector_bottom, scale).Y*2.f;
	}

	for (float i = bottom; i < top; i += step)
	{
		FVector vector_right(i, rigth, 0.f);
		FVector vector_left(i, left, 0.f);
		FVector scale;
		if (i + step > top)
		{
			scale.X = (top - i) / step;
			scale.Y = border/10.f;
			scale.Z = 1.f;
			i = top;
		}
		else {
			scale.X = 1.f;
			scale.Y = border/10.f;
			scale.Z = 1.f;
		}
	
		AWall* wall_right = GetWorld()->SpawnActor<AWall>(vector_right, FRotator::ZeroRotator);
		wall_right->Init(vector_right, scale);

		AWall* wall_left = GetWorld()->SpawnActor<AWall>(vector_left, FRotator::ZeroRotator);
		step = wall_left->Init(vector_left, scale).X * 2.f;
	}
	
	
}

void AGenerator::GenerateDoor(AVisualBox* section)
{
	
}

void AGenerator::GenerateFloor()
{
	float top = GenData->GetRootSizeX()/2;
	float bottom = -GenData->GetRootSizeX()/2;
	float rigth = GenData->GetRootSizeY()/2;
	float left = -GenData->GetRootSizeY() / 2;
	UE_LOG(LogTemp, Log, TEXT("Generate Floor for Top - %f, Bottom - %f, Right - %f, Left - %f"), top, bottom, rigth, left);
	float step = 0;
	for (float i = bottom; i < top; i+= step)
	{
		for (float j = left; j < rigth; j+= step)
		{
			UE_LOG(LogTemp, Log, TEXT("Place x - %f, y - %f"), i, j);
			FVector vector(i, j, 0);
			AFloor* floor = GetWorld()->SpawnActor<AFloor>(vector, FRotator::ZeroRotator);
			step = floor->Init(vector).X * 2;
		}
	}
}

