// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/DungeonBuildEnum.h"
#include "SplineDungeonPath.generated.h"

class USplineMeshComponent;
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

	//bool
	UPROPERTY( EditAnywhere , BlueprintReadWrite, Category="Spline")
	bool bIsPlace = false;

	// Ref to the all spline meshes
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere , Category="Spline")
	TArray<TObjectPtr<USplineMeshComponent>> SplineMeshArray;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called when properties are changed in editor
	virtual void OnConstruction(const FTransform& Transform) override;



	UFUNCTION( BlueprintCallable , Category="Spline")
	void UpdateSpline();

public:

	// Sets default values for this actor's properties
	ASplineDungeonPath();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Generate the spline path
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category="Spline")
	bool GeneratedSlinePath();

	//Getter
	UFUNCTION(Blueprintable, BlueprintPure, Category="Spline")
	bool GetIsPlace() const { return bIsPlace; }

	//Setter
	UFUNCTION(Blueprintable, BlueprintCallable, Category="Spline")
	void SetIsPlace(bool NewIsPlace) { bIsPlace = NewIsPlace; }

};
