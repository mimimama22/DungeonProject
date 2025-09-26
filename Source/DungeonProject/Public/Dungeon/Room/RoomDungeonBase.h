// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuildTypeBase.h"
#include "GameFramework/Actor.h"
#include "RoomDungeonBase.generated.h"

class UBoxComponent;

UCLASS()
class DUNGEONPROJECT_API ARoomDungeonBase : public ABuildTypeBase
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RoomDungeonBase - Room")
	TObjectPtr<USceneComponent>	 RoomRoot;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "RoomDungeonBase - Room" )
	TObjectPtr<UStaticMeshComponent> RoomFloorMesh;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "RoomDungeonBase - Room" )
	TObjectPtr<UBoxComponent> RoomBoxCollision;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ARoomDungeonBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
