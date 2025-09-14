// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerBase.h"
#include "EnhancedInputSubsystems.h"

void APlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
