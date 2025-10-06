// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Dungeon/Room/RoomDungeonBase.h"
#include "GameFramework/Actor.h"
#include "SaveDungeonData.generated.h"

UCLASS()
class DUNGEONPROJECT_API ASaveDungeonData : public AActor
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct DUNGEONPROJECT_API FSaveRoomData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="RoomData")
	TObjectPtr<ARoomDungeonBase> RoomRef;


	
};
