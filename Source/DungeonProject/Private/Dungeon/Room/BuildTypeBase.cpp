// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/Room/BuildTypeBase.h"

// Sets default values
ABuildTypeBase::ABuildTypeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuildTypeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuildTypeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

