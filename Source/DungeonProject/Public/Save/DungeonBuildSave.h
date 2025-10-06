// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Net/DataChannel.h"
#include "Utility/SaveDungeonData.h"
#include "DungeonBuildSave.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSaveRoomsData
{
	GENERATED_BODY()

public:
	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	TSubclassOf<AActor> ActorClass;
	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	FTransform ActorTransform;
	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	int RoomID;
	

	FSaveRoomsData()
	{
		RoomID = -1;
	}
	FSaveRoomsData(const TSubclassOf<AActor>& InActorClass, const FTransform& InActorTransform, int InRoomID)
	{
		ActorClass = InActorClass;
		ActorTransform = InActorTransform;
		RoomID = InRoomID;
	}
};

USTRUCT(BlueprintType)
struct FSaveCoridorData
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	TSubclassOf<AActor> ActorClass;
	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	FTransform ActorTransform;
	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	FVector EndLocation;
	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="MyStruct" )
	int CoridorID;

	FSaveCoridorData()
	{
		CoridorID = -1;
		EndLocation = FVector::ZeroVector;
	}

	FSaveCoridorData(const TSubclassOf<AActor>& InActorClass, const FTransform& InActorTransform, int InCoridorID, const FVector& InEndLocation)
	{
		ActorClass = InActorClass;
		ActorTransform = InActorTransform;
		CoridorID = InCoridorID;
		EndLocation = InEndLocation;
	}
	
};

UCLASS()
class DUNGEONPROJECT_API UDungeonBuildSave : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite , Category="DungeonBuildSave")
	TArray<FSaveRoomsData> SavedRoomDataArray;

	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="DungeonBuildSave")
	TArray<FSaveCoridorData> SavedCoridorDataArray;

	UPROPERTY( VisibleAnywhere , BlueprintReadWrite , Category="DungeonBuildSave")
	FString Test;

	UPROPERTY(VisibleAnywhere , BlueprintReadWrite , Category="DungeonBuildSave")
	FString SaveSlotName;
	UPROPERTY(VisibleAnywhere , BlueprintReadWrite , Category="DungeonBuildSave")
	int UserIndex;

	UDungeonBuildSave();
	
};


