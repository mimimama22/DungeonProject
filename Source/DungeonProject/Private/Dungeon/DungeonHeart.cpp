// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/DungeonHeart.h"

// Sets default values
ADungeonHeart::ADungeonHeart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	// info default
	MaxHealth = 100;
	CurrentHealth = MaxHealth;

}

// Called when the game starts or when spawned
void ADungeonHeart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADungeonHeart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonHeart::Interact_Implementation(AActor* Caller)
{
	IInteractDungeon::Interact_Implementation(Caller);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Interact with Dungeon Heart") );

	if(Caller->IsValidLowLevel())
	{
		if(Caller->GetClass()->ImplementsInterface(UInteractDungeon::StaticClass()))
		{
			IInteractDungeon::Execute_SetModeBuildDungeon(Caller, true);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Set Mode Build Dungeon True") );
		}
	}
}

