// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SaveDungeonLibrary.generated.h"

class UDungeonBuildSave;
class ARoomDungeonBase;
/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API USaveDungeonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
protected:
	
public:
	
	UFUNCTION( BlueprintCallable, Category = "SaveDungeonLibrary" )
	static void SaveRoomDungeon(ARoomDungeonBase* RoomDungeon, UWorld* WorldContext);

	//Get the SaveGame Instance
	static UDungeonBuildSave* GetSaveGameInstance( const UWorld* WorldContext);
	
	
	
};
