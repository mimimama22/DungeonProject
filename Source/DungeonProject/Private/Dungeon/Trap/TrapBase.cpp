// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/Trap/TrapBase.h"

#include "Components/BoxComponent.h"

// Sets default values
ATrapBase::ATrapBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject< USceneComponent>( TEXT("Root") );
	RootComponent = Root;

	HitBox = CreateDefaultSubobject<UBoxComponent>( TEXT("Entity detection"));
	HitBox->SetupAttachment(Root);

	HitBox->OnComponentBeginOverlap.AddDynamic( this , &ATrapBase::BeginOverlapHitBox);

	bIsActive = true;

}

// Called when the game starts or when spawned
void ATrapBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrapBase::BeginOverlapHitBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Overlap with: %s"), *OtherActor->GetName()));
	if(bIsActive) return;
	if(ActivateTrap())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("Trap Activated Successfully")));
		GetWorldTimerManager().SetTimer( TrapCooldownTimerHandle , this , &ATrapBase::ResetCooldown , TrapCooldown , false );
	}
}

void ATrapBase::ResetCooldown()
{
	bIsActive = false;
}

bool ATrapBase::ActivateTrap_Implementation()
{
	bIsActive = true;
	return true;
}

// Called every frame
void ATrapBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

