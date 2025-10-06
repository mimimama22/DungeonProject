// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/CustomGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Save/DungeonBuildSave.h"

void UCustomGameInstance::Init()
{
	Super::Init();

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("CustomGameInstance Initialized"));
	GetDungeonSaveInstance();

}

void UCustomGameInstance::GetDungeonSaveInstance()
{
		
	// Create the Save Game Object
	if(UGameplayStatics::DoesSaveGameExist(TEXT("DungeonBuildSaveSlot"),0))
	{
		DungeonSaveInstance = Cast<UDungeonBuildSave>( UGameplayStatics::LoadGameFromSlot( TEXT("DungeonBuildSaveSlot") , 0 ) );
	}
	else
	{
		DungeonSaveInstance = Cast<UDungeonBuildSave>( UGameplayStatics::CreateSaveGameObject( UDungeonBuildSave::StaticClass() ) );
	}
	
	if(DungeonSaveInstance->IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("DungeonSaveInstance is valid"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DungeonSaveInstance is not valid"));
	}

	
}

