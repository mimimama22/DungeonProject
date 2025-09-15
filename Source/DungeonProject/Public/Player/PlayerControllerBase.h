// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/InteractDungeon.h"
#include "PlayerControllerBase.generated.h"

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
	
protected:

	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "PlayerControllerBase - IMC" )
	TObjectPtr<APlayerCharacterBase> PlayerCharacter;

	
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

	UFUNCTION( BlueprintCallable , Category = "PlayerControllerBase - Input" )
	void InteractFunction();

public:
	// Called when the game starts
	virtual void BeginPlay() override;
};
