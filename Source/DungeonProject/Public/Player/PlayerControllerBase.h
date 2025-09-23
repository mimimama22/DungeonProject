// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/InteractDungeon.h"
#include "Utility/DungeonBuildEnum.h"
#include "PlayerControllerBase.generated.h"

class ASplineDungeonPath;
class ARoomDungeonBase;
class APlayerCharacterBase;
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API APlayerControllerBase : public APlayerController , public IInteractDungeon
{
	GENERATED_BODY()
public:
	// Sets default values for this controller's properties
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerControllerBase - IMC" )
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerControllerBase - IA" )
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerControllerBase - IA" )
	TObjectPtr<UInputAction> LeftClickAction;
	
protected:
	//Ref
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "PlayerControllerBase - IMC" )
	TObjectPtr<APlayerCharacterBase> PlayerCharacter;

	//Build Mode
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerControllerBase - BuildMode" )
	EBuildModeState BuildModeState = EBuildModeState::None;
	//Current Build Type
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerControllerBase - BuildMode" )
	EBuildType CurrentBuildType = EBuildType::None;
	//Reference to the room to spawn
	TObjectPtr<ARoomDungeonBase> RoomSpawned;
	//Reference to the corridor to spawn
	TObjectPtr<ASplineDungeonPath> CorridorSpawned;
	

	
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Input" )
	void InteractFunction();

	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Input" )
	void LeftClickFunction();
	//Function to handle the build mode
	UFUNCTION(BlueprintCallable, Category = "PlayerControllerBase - BuildMode")
	void HandleBuildMode();



public:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	//Spawn Room Function
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Room" )
	void SpawnRoomFunction( TSubclassOf< ARoomDungeonBase> RoomToSpawn);
	//Spawn Corridor Function
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Corridor" )
	void SpawnCorridorFunction(TSubclassOf<ASplineDungeonPath> CorridorToSpawn);

	//UI
	UFUNCTION( BlueprintNativeEvent , Category = "PlayerControllerBase - UI" )
	void OpenSelectBuildMenu();
	UFUNCTION( BlueprintNativeEvent , Category = "PlayerControllerBase - UI" )
	void CloseSelectBuildMenu();

	//Getter
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Getter" )
	APlayerCharacterBase* GetPlayerCharacter() const { return PlayerCharacter; }
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Getter" )
	EBuildModeState GetBuildModeState() const{ return BuildModeState; };
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Getter" )
	EBuildType GetCurrentBuildType() const{ return CurrentBuildType; };

	//Setter
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Setter" )
	void SetBuildModeState(EBuildModeState NewState){ BuildModeState = NewState;};
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Setter" )
	void SetCurrentBuildType(EBuildType NewBuildType){ CurrentBuildType = NewBuildType; };
};


