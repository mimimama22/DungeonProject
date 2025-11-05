// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_FollowingWithOffset.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API UBTService_FollowingWithOffset : public UBTService
{
	GENERATED_BODY()

	UBTService_FollowingWithOffset();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere , Category = "Blackboard")
	FBlackboardKeySelector FollowingTargetKey;
	UPROPERTY( EditAnywhere , Category = "Blackboard")
	FBlackboardKeySelector OffsetKey;
	UPROPERTY( EditAnywhere , Category = "Blackboard")
	FBlackboardKeySelector MoveLocationKey;
	
};
