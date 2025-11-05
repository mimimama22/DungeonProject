// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Service/BTService_FollowingWithOffset.h"
#include "AI/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_FollowingWithOffset::UBTService_FollowingWithOffset()
{
	NodeName = "Following With Offset";
	bNotifyBecomeRelevant = true;
	bNotifyTick = true;
	//Interval = 0.2f;
}

void UBTService_FollowingWithOffset::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AActor* FollowingTarget = Cast<AActor>( OwnerComp.GetBlackboardComponent()->GetValueAsObject(FollowingTargetKey.SelectedKeyName));

	FVector Offset = OwnerComp.GetBlackboardComponent()->GetValueAsVector(OffsetKey.SelectedKeyName);
	FVector RotationOffset = FollowingTarget->GetActorRotation().RotateVector(Offset);
	
	if(FollowingTarget)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(MoveLocationKey.SelectedKeyName, FollowingTarget->GetActorLocation() + RotationOffset);
	}
	else
	{
		UE_LOG( LogTemp , Warning , TEXT("Following Target is null in BTService_FollowingWithOffset"));
	}
}

void UBTService_FollowingWithOffset::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AActor* FollowingTarget = Cast<AActor>( OwnerComp.GetBlackboardComponent()->GetValueAsObject(FollowingTargetKey.SelectedKeyName));

	FVector Offset = OwnerComp.GetBlackboardComponent()->GetValueAsVector(OffsetKey.SelectedKeyName);

	if(FVector::Dist( FollowingTarget->GetActorLocation(),Cast<AAIControllerBase>( OwnerComp.GetOwner())->GetPawn()->GetActorLocation()) < Offset.Size() )
	{
		UE_LOG( LogTemp , Warning , TEXT("Following Target is too far in BTService_FollowingWithOffset"));
		return;
	}

	FVector RotationOffset = FollowingTarget->GetActorRotation().RotateVector(Offset);
	
	if(FollowingTarget)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(MoveLocationKey.SelectedKeyName, FollowingTarget->GetActorLocation() + RotationOffset);
	}
}
