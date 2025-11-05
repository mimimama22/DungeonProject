// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_Patrol.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEONPROJECT_API UBTService_Patrol : public UBTService
{
	GENERATED_BODY()

	UBTService_Patrol();

	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere , Category = "BlackBoard")
	FBlackboardKeySelector CurrentActionKey;

	UPROPERTY(EditAnywhere , Category = "Patrol")
	float PatrolRadius = 500.0f;
};
