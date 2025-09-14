// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
public:
	// Sets default values for this controller's properties
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerControllerBase - IMC" )
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
protected:
	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
};
