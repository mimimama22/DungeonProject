// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SaveDungeonLibrary.h"
#include "Dungeon/Room/SplineDungeonPath.h"
#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Network/CustomGameInstance.h"
#include "Save/DungeonBuildSave.h"




void USaveDungeonLibrary::SaveRoomDungeon(ARoomDungeonBase* RoomDungeon, UWorld* WorldContext)
{

	UDungeonBuildSave* SaveGameInstance = GetSaveGameInstance(WorldContext);
	if(SaveGameInstance->IsValidLowLevel())
	{
		const FSaveRoomsData NewRoomData(RoomDungeon->GetClass() ,RoomDungeon->GetActorTransform(), RoomDungeon->GetRoomID());
		SaveGameInstance->SavedRoomDataArray.Add(NewRoomData);
		UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->UserIndex );
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameInstance is not valid"));
	}
}

void USaveDungeonLibrary::SaveCoridorDungeon(ASplineDungeonPath* CorridorDungeon, UWorld* WorldContext)
{
	UDungeonBuildSave* SaveGameInstance = GetSaveGameInstance(WorldContext);
	if(SaveGameInstance->IsValidLowLevel())
	{
		const FSaveCoridorData NewCorridorData(CorridorDungeon->GetClass() ,CorridorDungeon->GetActorTransform(), CorridorDungeon->GetCoridorID(),
			CorridorDungeon->SplineComponent->GetLocationAtSplinePoint(CorridorDungeon->SplineComponent->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::Local));
		SaveGameInstance->SavedCoridorDataArray.Add(NewCorridorData);
		UGameplayStatics::SaveGameToSlot( SaveGameInstance , SaveGameInstance->SaveSlotName , SaveGameInstance->UserIndex );
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SaveGameInstance is not valid"));
	}
}

UDungeonBuildSave* USaveDungeonLibrary::GetSaveGameInstance(const UWorld* WorldContext)
{
	if (const UCustomGameInstance* GI = Cast<UCustomGameInstance>(WorldContext->GetGameInstance()))
	{
		return GI->DungeonSaveInstance;
	}
	return nullptr;
}


