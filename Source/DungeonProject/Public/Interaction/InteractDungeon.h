// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractDungeon.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractDungeon : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DUNGEONPROJECT_API IInteractDungeon
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* Caller);

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void SetModeBuildDungeon(bool bModeBuild);
};
