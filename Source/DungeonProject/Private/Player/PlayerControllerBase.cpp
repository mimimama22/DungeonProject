// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerControllerBase.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"
#include "Dungeon/Room/RoomDungeonBase.h"
#include "Dungeon/Room/SplineDungeonPath.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/SplineComponent.h"
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
			if(LeftClickAction)
			{
				EnhancedInputComponent->BindAction(LeftClickAction, ETriggerEvent::Started, this, &APlayerControllerBase::LeftClickFunction);
			}
		}
	}
}

void APlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<APlayerCharacterBase>(GetPawn());

	PlayerCharacter->SetPlayerControllerRef(this);
}

void APlayerControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	switch (BuildModeState) {
	case EBuildModeState::None:
		break;
	case EBuildModeState::BuildMode:
		HandleBuildMode();
		break;
	case EBuildModeState::PlayMode:
		break;
	}

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

void APlayerControllerBase::LeftClickFunction()
{
	if(PlayerCharacter->GetIsInBuildMode())
	{
		switch (CurrentBuildType) {
		case EBuildType::None:
			break;
		case EBuildType::Room:
			if(RoomSpawned->IsValidLowLevel())
			{
				TArray<AActor*> ActorOverlap;
				RoomSpawned->RoomBoxCollision->GetOverlappingActors( ActorOverlap );
				if(ActorOverlap.IsEmpty())
				{
					GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Blue, TEXT("Room Placed") );
					RoomSpawned = nullptr;
					CurrentBuildType = EBuildType::None;
				}
				else
				{
					GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT("Can't Place Room Here") );
				}
			}
			break;
		case EBuildType::Door:
			break;
		case EBuildType::Trap:
			break;
		case EBuildType::Stairs:
			break;
		case EBuildType::SplinePath:
			if(CorridorSpawned)
			{
				if(CorridorSpawned->GetIsPlace())
				{
					CurrentBuildType = EBuildType::None;
					GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Blue, TEXT("Corridor Placed") );
				}
				else
				{
					CorridorSpawned->SetIsPlace(true);
					CorridorSpawned->SplineComponent->SetMobility( EComponentMobility::Static );
				}
			}
			break;
		}

	}
}

//BuildMode
void APlayerControllerBase::HandleBuildMode()
{
	switch (CurrentBuildType)
	{
	case EBuildType::None:
		break;
	case EBuildType::Room:
		if(RoomSpawned)
		{
			FHitResult HitResult;
			GetHitResultUnderCursor( ECC_Camera , false , HitResult );
			if(HitResult.bBlockingHit)
			{
			
				RoomSpawned->SetActorLocation(UKismetMathLibrary::Vector_SnappedToGrid(HitResult.ImpactPoint, 50 ));
			}
			else
			{
				GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT("No Hit") );
			}
		}
		break;
	case EBuildType::Door:
		break;
	case EBuildType::Trap:
		break;
	case EBuildType::Stairs:
		break;
	case EBuildType::SplinePath:
		if(CorridorSpawned)
		{
			FHitResult HitResult;
			GetHitResultUnderCursor( ECC_Camera , false , HitResult );
			if(HitResult.bBlockingHit)
			{
				if(CorridorSpawned->GetIsPlace())
				{
					GEngine->AddOnScreenDebugMessage( -1, 0.f, FColor::Blue, TEXT("Corridor Moving") );


			
					CorridorSpawned->SplineComponent->SetLocationAtSplinePoint(CorridorSpawned->SplineComponent->GetNumberOfSplinePoints()-1,
						UKismetMathLibrary::Vector_SnappedToGrid(HitResult.ImpactPoint, 50 ), ESplineCoordinateSpace::World);
					CorridorSpawned->GeneratedSlinePath();

				}
				else
				{
					CorridorSpawned->SetActorLocation(UKismetMathLibrary::Vector_SnappedToGrid(HitResult.ImpactPoint, 50 ));
				}
			}
			else
			{
				GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT("No Hit") );
			}
			break;
		}
	}
}

void APlayerControllerBase::SpawnRoomFunction(TSubclassOf<ARoomDungeonBase> RoomToSpawn)
{
	if(RoomToSpawn)
	{
		if(RoomSpawned->IsValidLowLevel())
		{
			RoomSpawned->Destroy();
			RoomSpawned = nullptr;
		}
		FVector SpawnRoomLocation;
		FVector LookRoomDirection = FVector::ZeroVector;
		const FRotator SpawnRoomRotation = FRotator::ZeroRotator;
		DeprojectMousePositionToWorld( SpawnRoomLocation , LookRoomDirection );
		SpawnRoomLocation = SpawnRoomLocation * FVector(1.f,1.f,0.f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		RoomSpawned = GetWorld()->SpawnActor<ARoomDungeonBase>(RoomToSpawn, SpawnRoomLocation, SpawnRoomRotation, SpawnParams);
	}
}

void APlayerControllerBase::SpawnCorridorFunction(TSubclassOf<ASplineDungeonPath> CorridorToSpawn)
{
	if(CorridorToSpawn)
	{
		FVector SpawnRoomLocation;
		FVector LookRoomDirection = FVector::ZeroVector;
		const FRotator SpawnRoomRotation = FRotator::ZeroRotator;
		DeprojectMousePositionToWorld( SpawnRoomLocation , LookRoomDirection );
		SpawnRoomLocation = SpawnRoomLocation * FVector(1.f,1.f,0.f);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		CorridorSpawned = GetWorld()->SpawnActor<ASplineDungeonPath>(CorridorToSpawn, SpawnRoomLocation, SpawnRoomRotation, SpawnParams);
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Blue, TEXT("Corridor Spawned") );
	}
}

//UI
void APlayerControllerBase::OpenSelectBuildMenu_Implementation()
{
}
void APlayerControllerBase::CloseSelectBuildMenu_Implementation()
{
}

