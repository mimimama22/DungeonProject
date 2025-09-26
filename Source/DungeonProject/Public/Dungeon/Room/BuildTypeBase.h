// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildTypeBase.generated.h"

UCLASS()
class DUNGEONPROJECT_API ABuildTypeBase : public AActor
{
	GENERATED_BODY()
	
public:	


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BuildType")
	TArray<TObjectPtr<AActor>> AllBuildAttachments;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	ABuildTypeBase();

};
