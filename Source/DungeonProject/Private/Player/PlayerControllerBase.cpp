// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/PlayerCharacterBase.h"

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent) )
		{

			if( InteractAction )
			{
				EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerControllerBase::InteractFunction);
			}
		}
	}
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacterBase>(GetPawn());
}


void APlayerControllerBase::InteractFunction()
{
	GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT("Interact Function Called") );

	if(!PlayerCharacter->GetIsInBuildMode())
	{
		// Implement interaction logic here
		FHitResult HitResult;
		FCollisionQueryParams Params;

		FVector Start = GetPawn()->GetActorLocation() + FVector(0.f,0.f,80.f);
		FVector End = Start + (PlayerCameraManager->GetActorForwardVector() * 500.0f);
		UKismetSystemLibrary::SphereTraceSingleForObjects(
			GetWorld(),
			Start,
			End,
			20.f,
			{ UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic)  },
			false,
			{ GetPawn() },
			EDrawDebugTrace::ForDuration,
			HitResult,
			true
			);

		if(HitResult.IsValidBlockingHit())
		{
			if(HitResult.GetActor()->IsValidLowLevel())
			{
				GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Green, FString::Printf(TEXT("Hit Actor: %s"), *HitResult.GetActor()->GetName()) );
				if(HitResult.GetActor()->GetClass()->ImplementsInterface(UInteractDungeon::StaticClass()))
				{
					IInteractDungeon::Execute_Interact(HitResult.GetActor(), GetPawn());
				}
			}
		}
	}
	else
	{
		PlayerCharacter->ExitBuildMode();
	}
}


