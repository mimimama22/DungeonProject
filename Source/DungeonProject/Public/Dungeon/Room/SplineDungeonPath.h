// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SplineDungeonPath.generated.h"

class USplineComponent;

UCLASS()
class DUNGEONPROJECT_API ASplineDungeonPath : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spline")
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="Spline")
	TObjectPtr<UStaticMesh> PathMesh;



protected:
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category="Spline")
	float LenghtMesh = 100.0f;
	UPROPERTY( EditAnywhere , BlueprintReadWrite, Category="Spline")
	float Offset = 0.0f;
	UPROPERTY( EditAnywhere , BlueprintReadWrite, Category="Spline")
	float Spacing = 0.f;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when properties are changed in editor
	virtual void OnConstruction(const FTransform& Transform) override;

public:

	// Sets default values for this actor's properties
	ASplineDungeonPath();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
