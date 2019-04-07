// Fill out your copyright notice in the Description page of Project Settings.

#include "AlgorithmBSP.h"

// Sets default values
AAlgorithmBSP::AAlgorithmBSP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAlgorithmBSP::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AAlgorithmBSP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


bool AAlgorithmBSP::Slice(AVisualBox* section, int MinRoomSpace)
{
	int slicesTries = 0;
	float boundRigth = section->getRigthBounder();
	float boundLeft = section->getLeftBounder();
	float boundTop = section->getTopBounder();
	float boundBottom = section->getBottomBounder();

	float isHorizontOrVertical = random.FRandRange(0, 100);
	
	if (isHorizontOrVertical > 50)
	{
		//UE_LOG(LogTemp, Log, TEXT("Horizont"));
		while (slicesTries < MAX_SLICES)
		{
			float horizontRand = random.FRandRange((boundTop - MinRoomSpace )/ TAIL_SIZE, (boundBottom + MinRoomSpace)/ TAIL_SIZE);
			float horizontalSlice = horizontRand * TAIL_SIZE;

			//UE_LOG(LogTemp, Log, TEXT("Slice - %f"), horizontalSlice);

			float firstLengthY = boundTop - horizontalSlice;
			float secondLengthY =  horizontalSlice - boundBottom;

			if (FMath::Abs(firstLengthY) <= MinRoomSpace || FMath::Abs(secondLengthY) <= MinRoomSpace)
			{
				slicesTries++;
			}
			else
			{
	
				float firstLengthX = boundRigth - boundLeft;
				float firstCenterX = boundRigth - firstLengthX / 2.0;
				float firstCenterY = boundTop - firstLengthY / 2.0;

				float secondLengthX = boundRigth - boundLeft;
				float secondCenterX = boundLeft + secondLengthX / 2.0;
				float secondCenterY = boundBottom + secondLengthY / 2.0;

				AVisualBox* FirstBox = GetWorld()->SpawnActor<AVisualBox>(FVector(firstCenterX, firstCenterY, 0), FRotator::ZeroRotator);
				FirstBox->Initialize(firstLengthX, firstLengthY, firstCenterX, firstCenterY, section);
				section->addChild(FirstBox);
				AllSections.Enqueue(FirstBox);

				AVisualBox* SecondBox = GetWorld()->SpawnActor<AVisualBox>(FVector(secondCenterX, secondCenterY, 0), FRotator::ZeroRotator);
				SecondBox->Initialize(secondLengthX, secondLengthY, secondCenterX, secondCenterY, section);
				section->addChild(SecondBox);
				AllSections.Enqueue(SecondBox);
				return true;
			}
		}
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Vertical"));
		while (slicesTries < MAX_SLICES)
		{
			float verticalRand = random.FRandRange((boundRigth - MinRoomSpace )/ TAIL_SIZE, (boundLeft + MinRoomSpace )/ TAIL_SIZE);
			float verticalSlice = verticalRand * TAIL_SIZE;

			//UE_LOG(LogTemp, Log, TEXT("Slice - %f"), verticalSlice);

			float firstLengthX = boundRigth - verticalSlice;
			float secondLengthX = verticalSlice - boundLeft;

			if (FMath::Abs(firstLengthX) <= MinRoomSpace || FMath::Abs(secondLengthX) <= MinRoomSpace)
			{
				slicesTries++;
			}
			else
			{
				float firstLengthY = boundTop - boundBottom;
				float firstCenterX = boundRigth - firstLengthX / 2.0;
				float firstCenterY = boundTop - firstLengthY / 2.0;

				float secondLengthY = boundTop - boundBottom;
				float secondCenterX = boundLeft + secondLengthX / 2.0;
				float secondCenterY = boundBottom + secondLengthY / 2.0;;

				AVisualBox* FirstBox = GetWorld()->SpawnActor<AVisualBox>(FVector(firstCenterX, firstCenterY, 0), FRotator::ZeroRotator);
				FirstBox->Initialize(firstLengthX, firstLengthY, firstCenterX, firstCenterY, section);
				section->addChild(FirstBox);
				AllSections.Enqueue(FirstBox);

				AVisualBox* SecondBox = GetWorld()->SpawnActor<AVisualBox>(FVector(secondCenterX, secondCenterY, 0), FRotator::ZeroRotator);
				SecondBox->Initialize(secondLengthX, secondLengthY, secondCenterX, secondCenterY, section);
				section->addChild(SecondBox);
				AllSections.Enqueue(SecondBox);
				return true;
			}
		}
	}		
	return false;
}

void AAlgorithmBSP::Go(int RandmSeed, int BorderSize, int MinSubRoomSize, float GetRootSizeX, float GetRootSizeY)
{
	InitStartBox(GetRootSizeX, GetRootSizeY);
	random.Initialize(RandmSeed);
	int MinRoomSpace = (BorderSize * 2) + MinSubRoomSize;
	int roomCount = ((GetRootSizeX / MinRoomSpace) * (GetRootSizeY / MinRoomSpace)) * 0.5;

	for (int i = 0; i < roomCount; ++i)
	{
		if (!AllSections.IsEmpty()) {
			AVisualBox* currentSection;
			AllSections.Dequeue(currentSection);
			bool res = Slice(currentSection, MinRoomSpace);
			if (!res)
			{
				AllSections.Enqueue(currentSection);
			}
		}
		else {
			break;
		}
	}
}

TQueue<AVisualBox*>* AAlgorithmBSP::GetAllSections()
{
	return &AllSections;
}

void AAlgorithmBSP::InitStartBox(float GetRootSizeX, float GetRootSizeY)
{
	
	FVector Location = GetActorLocation();
	AVisualBox* MainBox = GetWorld()->SpawnActor<AVisualBox>(FVector(Location.X, Location.Y, 0), FRotator::ZeroRotator);
	MainBox->Initialize(GetRootSizeX, GetRootSizeY, Location.X, Location.Y);
	AllSections.Enqueue(MainBox);
}