// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_Patrol.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_Patrol::UBTService_Patrol()
{
	bNotifyBecomeRelevant = true;
	NodeName = "Patrol Service";
}

void UBTService_Patrol::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	FNavLocation RandomPoint;

	NavSys->GetRandomReachablePointInRadius( OwnerComp.GetOwner()->GetActorLocation(), PatrolRadius , RandomPoint);

	OwnerComp.GetBlackboardComponent()->SetValueAsVector(CurrentActionKey.SelectedKeyName, RandomPoint.Location);
}
