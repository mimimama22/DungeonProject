// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIControllerBase.h"

#include "AI/AIBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(BehaviorTree)
	{
		UBlackboardComponent* b;
		UseBlackboard(BehaviorTree->BlackboardAsset, b);
		Blackboard = b;
		RunBehaviorTree(BehaviorTree);
		if(AAIBase* AIBase = Cast<AAIBase>(InPawn))
		{
			Blackboard->SetValueAsBool("IsLeader", AIBase->GetIsLeader());
			FollowingGroup = AIBase->GetFollowingGroup();
			for(AActor * Member : AIBase->GetFollowingGroup())
			{
				if(AAIBase* MemberAI = Cast<AAIBase>(Member))
				{
					if(MemberAI->GetIsLeader())
					{
						FollowingTraget = Member;
						FVector Offset = InPawn->GetActorLocation() - Member->GetActorLocation();
						OffsetFromLeader = Offset;
						break;
					}
				}
			}
			Blackboard->SetValueAsObject("FollowingTarget", FollowingTraget);
			Blackboard->SetValueAsVector("OffsetFromLeader", OffsetFromLeader);
		}
	}
	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Green, TEXT("pawnName : " + GetPawn().GetName()) );
}
