// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "VisualBox.generated.h"

UCLASS()
//Class to define the section
class MAPGEN_API AVisualBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVisualBox();
	void Initialize(float LengthX, float LengthY, float OutCenterX, float OutCenterY, AVisualBox* Parent = nullptr);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Give the north-west corner of section
	FVector getNWCorner();
	// Give the north-east corner of section
	FVector getNECorner();
	// Give the south-west corner of section
	FVector getSWCorner();
	// Give the south-east corner of section
	FVector getSECorner();
	// Give the extents of top bounder of section
	float getTopBounder();
	// Give the extents of rigth bounder of section
	float getRigthBounder();
	// Give the extents of left bounder of section
	float getLeftBounder();
	// Give the extents of bottom bounder of section
	float getBottomBounder();
	float getHalfWidth();
	float getHalfHeight();
	void addChild(AVisualBox* box);
private:
	//Painted the section bounds
	UPROPERTY(EditAnywhere, Category = "VisualBox")
	UBoxComponent* BoxComponent;
	//X coordinate of section location
	UPROPERTY(EditAnywhere, Category = "VisualBox")
		float CenterX = 0;
	//Y coordinate of section location
	UPROPERTY(EditAnywhere, Category = "VisualBox")
		float CenterY = 0;
	//Length from center to end of section rectangle on x coordinate
	UPROPERTY(EditAnywhere, Category = "VisualBox")
		float HalfLengthX = 0;
	//Length from center to end of section rectangle on y coordinate
	UPROPERTY(EditAnywhere, Category = "VisualBox")
		float HalfLengthY = 0;
	//All subboxes of this section
	UPROPERTY(EditAnywhere, Category = "VisualBox")
	TArray<AVisualBox*> ChildBoxes;
	//The parent of this section
	UPROPERTY(EditAnywhere, Category = "VisualBox")
	AVisualBox* BoxParent;
};
