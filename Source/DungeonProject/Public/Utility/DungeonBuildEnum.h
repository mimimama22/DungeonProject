// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonBuildEnum.generated.h"

UCLASS()

class DUNGEONPROJECT_API ADungeonBuildEnum : public AActor
{
	GENERATED_BODY()


};

UENUM( Blueprintable)

enum class EBuildModeState : uint8
{
	None			UMETA( DisplayName = "None" ) ,
	BuildMode		UMETA( DisplayName = "BuildMode" ) ,
	PlayMode		UMETA( DisplayName = "PlayMode" )
};

UENUM( Blueprintable )
enum class EBuildType : uint8
{
	None			UMETA( DisplayName = "None" ) ,
	Room			UMETA( DisplayName = "Room" ) ,
	Door			UMETA( DisplayName = "Door" ) ,
	Trap			UMETA( DisplayName = "Trap" ) ,
	Stairs			UMETA( DisplayName = "Stairs" ) ,
	SplinePath		UMETA( DisplayName = "SplinePath" )
};


