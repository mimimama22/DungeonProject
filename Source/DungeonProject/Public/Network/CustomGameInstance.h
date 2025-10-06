// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomGameInstance.generated.h"

class UDungeonBuildSave;
/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API UCustomGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "CustomGameInstance - SaveDungeon")
	UDungeonBuildSave* DungeonSaveInstance;

	FTimerHandle TimerHandle_GetDungeonSaveInstance;

	// Initialize the Game Instance
	virtual void Init() override;

	void GetDungeonSaveInstance();
	
};
