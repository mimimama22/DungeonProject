// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/Room/RoomDungeonBase.h"

#include "Components/BoxComponent.h"

// Sets default values
ARoomDungeonBase::ARoomDungeonBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RoomRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RoomRoot"));
	RootComponent = RoomRoot;
	RoomFloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomFloorMesh"));
	RoomFloorMesh->SetupAttachment(RoomRoot);
	RoomBoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RoomBoxCollision"));
	RoomBoxCollision->SetupAttachment(RoomRoot);

	RoomBoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}

// Called when the game starts or when spawned
void ARoomDungeonBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoomDungeonBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

