// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Save/DungeonBuildSave.h"
#include "CustomGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API ACustomGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

protected:
	//Spawned Dungeon Room
	UFUNCTION( Blueprintable , Category = "CustomGameStateBase - SaveDungeon" )
	void SpawnDungeonRoom(const FSaveRoomsData& RoomData) const;

	UFUNCTION( Blueprintable , Category = "CustomGameStateBase - SaveDungeon" )
	void SpawnDungeonCoridor(const FSaveCoridorData& CoridorData) const;
	
public:


	// Begin Play
	virtual void BeginPlay() override;

	UFUNCTION( BlueprintCallable , Category = "CustomGameStateBase - SaveDungeon" )
	void SaveData();

	UFUNCTION( BlueprintCallable , Category = "CustomGameStateBase - SaveDungeon" )
	void LoadData();

	UFUNCTION( BlueprintCallable , Category = "CustomGameStateBase - SaveDungeon" )
	void LoadDungeon();
};
