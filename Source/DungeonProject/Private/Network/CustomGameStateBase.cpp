// Fill out your copyright notice in the Description page of Project Settings.


#include "Network/CustomGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "Save/DungeonBuildSave.h"
#include "Utility/SaveDungeonLibrary.h"

void ACustomGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	LoadDungeon();
}

void ACustomGameStateBase::SaveData()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("TestSaveSlot"),0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Game Exists!"));
		UDungeonBuildSave* LoadSave = Cast<UDungeonBuildSave>( UGameplayStatics::LoadGameFromSlot( TEXT("TestSaveSlot") , 0 ) );
		if ( LoadSave )
		{
			LoadSave->Test = TEXT("This is a new test string! and The old one was: ") + LoadSave->Test;
			UGameplayStatics::SaveGameToSlot( LoadSave , LoadSave->SaveSlotName , LoadSave->UserIndex );
			UE_LOG(LogTemp, Warning, TEXT("Updated String: %s"), *LoadSave->Test);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Game Does Not Exist!"));
	
	
		UDungeonBuildSave* SaveGameInstance = Cast<UDungeonBuildSave>( UGameplayStatics::CreateSaveGameObject( UDungeonBuildSave::StaticClass() ) );
		if ( SaveGameInstance )
		{
			SaveGameInstance->Test = TEXT("This is a test string!");

			UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->UserIndex );
		}
	}
}

void ACustomGameStateBase::LoadData()
{
	if(UGameplayStatics::DoesSaveGameExist(TEXT("TestSaveSlot"),0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Game Exists!"));
		UDungeonBuildSave* LoadSave = Cast<UDungeonBuildSave>( UGameplayStatics::LoadGameFromSlot( TEXT("TestSaveSlot") , 0 ) );
		if ( LoadSave )
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded String: %s"), *LoadSave->Test);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Save Game Does Not Exist!"));
	}
}

void ACustomGameStateBase::LoadDungeon()
{
	const UDungeonBuildSave* LoadDungeonSave = USaveDungeonLibrary::GetSaveGameInstance( GetWorld() );

	if(LoadDungeonSave->IsValidLowLevel())
	{
		for(FSaveRoomsData RoomData : LoadDungeonSave->SavedRoomDataArray)
		{
			SpawnDungeonRoom(RoomData);
		}
	}
	else
	UE_LOG( LogTemp, Warning, TEXT("Save Game Does Not Exist!") );
}

void ACustomGameStateBase::SpawnDungeonRoom(const FSaveRoomsData& RoomData) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Spawning Room"));
	FActorSpawnParameters SpawnParams;
	ARoomDungeonBase* RoomSpawned =  GetWorld()->SpawnActor<ARoomDungeonBase>(RoomData.ActorClass, RoomData.ActorTransform, SpawnParams);
	if(RoomSpawned->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Room Spawned"));
		RoomSpawned->SetRoomID(RoomData.RoomID);
	}
}
