// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/InteractDungeon.h"
#include "DungeonHeart.generated.h"

UCLASS()
class DUNGEONPROJECT_API ADungeonHeart : public AActor , public IInteractDungeon
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "DungeonHeart - Mesh")
	TObjectPtr<UStaticMeshComponent> Mesh;

	// info
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "DungeonHeart - Info")
	int MaxHealth;
	UPROPERTY(EditAnywhere , BlueprintReadWrite, Category = "DungeonHeart - Info")
	int CurrentHealth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this actor's properties
	ADungeonHeart();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual  void Interact_Implementation(AActor* Caller) override;

	

};
