// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DetourCrowdAIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API AAIControllerBase : public ADetourCrowdAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	//Following Property
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI-Following")
	TObjectPtr<AActor> FollowingTraget;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI-Following")
	TArray<TObjectPtr<AActor>> FollowingGroup;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI-Following")
	bool bIsLeader = false;
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "AI-Following")
	FVector OffsetFromLeader;

	
	//Called when the AI possesses a pawn
	virtual void OnPossess(APawn* InPawn) override;
	
	
};
