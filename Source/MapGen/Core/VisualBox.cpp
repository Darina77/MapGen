// Fill out your copyright notice in the Description page of Project Settings.

#include "VisualBox.h"

// Sets default values
AVisualBox::AVisualBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));	
}

void AVisualBox::Initialize(float LengthX, float LengthY, float OutCenterX, float OutCenterY, AVisualBox* Parent)
{
	HalfLengthX = LengthX / 2;
	HalfLengthY = LengthY / 2;
	CenterX = OutCenterX;
	CenterY = OutCenterY;
	BoxParent = Parent;

	BoxComponent->SetBoxExtent(FVector(HalfLengthX, HalfLengthY, 0));
	BoxComponent->SetWorldLocation(FVector(CenterX, CenterY, 0));
}

// Called when the game starts or when spawned
void AVisualBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVisualBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AVisualBox::getNWCorner()
{
	float x = CenterX + HalfLengthX;
	float y = CenterY + HalfLengthY;
	return FVector(x, y, 0);
}

FVector AVisualBox::getNECorner()
{
	float x = CenterX - HalfLengthX;
	float y = CenterY + HalfLengthY;
	return FVector(x, y, 0);
}

FVector AVisualBox::getSWCorner()
{
	float x = CenterX + HalfLengthX;
	float y = CenterY - HalfLengthY;
	return FVector(x, y, 0);
}

FVector AVisualBox::getSECorner()
{
	float x = CenterX - HalfLengthX;
	float y = CenterY - HalfLengthY;
	return FVector(x, y, 0);
}

float AVisualBox::getTopBounder()
{
	return CenterY + HalfLengthY;
}

float AVisualBox::getRigthBounder()
{
	return CenterX + HalfLengthX;
}

float AVisualBox::getLeftBounder()
{
	return CenterX - HalfLengthX;
}

float AVisualBox::getBottomBounder()
{
	return CenterY - HalfLengthY;
}

void AVisualBox::addChild(AVisualBox * box)
{
	ChildBoxes.Add(box);
}


