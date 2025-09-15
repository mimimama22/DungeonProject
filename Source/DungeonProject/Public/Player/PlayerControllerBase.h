// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/InteractDungeon.h"
#include "PlayerControllerBase.generated.h"

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
	//Reference to the room to spawn
	TObjectPtr<ARoomDungeonBase> RoomSpawned;

	
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Input" )
	void InteractFunction();

	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Input" )
	void LeftClickFunction();



public:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick( float DeltaTime ) override;

	//Spawn Room Function
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Room" )
	void SpawnRoomFunction( TSubclassOf< ARoomDungeonBase> RoomToSpawn);

	//UI
	UFUNCTION( BlueprintNativeEvent , Category = "PlayerControllerBase - UI" )
	void OpenSelectBuildMenu();

	//Getter
	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Getter" )
	APlayerCharacterBase* GetPlayerCharacter() const { return PlayerCharacter; }

	//Setter

	
};
