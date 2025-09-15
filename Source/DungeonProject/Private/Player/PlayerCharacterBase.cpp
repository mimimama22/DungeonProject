// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterBase.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/PlayerControllerBase.h"

// Sets default values
APlayerCharacterBase::APlayerCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void APlayerCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	

}

// Called to bind functionality to input
void APlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		if( MoveAction )
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Move);
		}
		if( LookAction )
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Look);
		}
		if( JumpAction )
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		}
		if(ZoomAction)
		{
			EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &APlayerCharacterBase::Zoom);
		}
	}
}

void APlayerCharacterBase::Move(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();

	if(!bIsInBuildMode)
	{
		AddMovementInput( GetActorForwardVector() , MovementVector.X );
		AddMovementInput( GetActorRightVector() , MovementVector.Y );
	}
	else
	{
		FVector NewLocation = FollowCamera->GetComponentLocation() + (FollowCamera->GetUpVector() * MovementVector.X * 10.f) +
			(FollowCamera->GetRightVector() * MovementVector.Y * 10.f);
		FollowCamera->SetWorldLocation(NewLocation);
	}
}

void APlayerCharacterBase::Look(const FInputActionValue& Value)
{
	if(bIsInBuildMode) return;
	FVector2d LookAxisVector = Value.Get<FVector2d>();
	
	AddControllerYawInput( LookAxisVector.X * 0.5f );
	AddControllerPitchInput( LookAxisVector.Y );
}

void APlayerCharacterBase::Zoom(const FInputActionValue& Value)
{
	if(!bIsInBuildMode) return;
	float ZoomAxis = Value.Get<float>();
	
	FollowCamera->SetWorldLocation( FollowCamera->GetComponentLocation() + (FollowCamera->GetForwardVector() * ZoomAxis * 20.f) );
}

void APlayerCharacterBase::Jump()
{
	Super::Jump();
}

void APlayerCharacterBase::StopJumping()
{
	Super::StopJumping();
	
}

void APlayerCharacterBase::ExitBuildMode()
{
	bIsInBuildMode = false;
	bIsInBuildMode = false;
	FollowCamera->AttachToComponent( CameraBoom, FAttachmentTransformRules::SnapToTargetIncludingScale);
}

void APlayerCharacterBase::SetModeBuildDungeon_Implementation(bool bIsBuildMode)
{
	IInteractDungeon::SetModeBuildDungeon_Implementation(bIsBuildMode);
	bIsInBuildMode = bIsBuildMode;
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interact with Player Character") );

	const FDetachmentTransformRules DetachRules(EDetachmentRule::KeepWorld, true);
	FollowCamera->DetachFromComponent( DetachRules);

	FollowCamera->SetWorldLocation( GetActorLocation() + FVector(0.f,0.f,700.f));
	FollowCamera->SetWorldRotation( FRotator(-90.f,0.f,0.f));

	PlayerControllerRef->OpenSelectBuildMenu();
	
	
}

