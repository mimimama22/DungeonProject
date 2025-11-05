// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIBase.generated.h"

UCLASS()
class DUNGEONPROJECT_API AAIBase : public ACharacter
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI-Following")
	TArray<TObjectPtr<AActor>> FollowingGroup;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI-Following")
	bool bIsLeader = false;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this character's properties
	AAIBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Getters
	TArray<TObjectPtr<AActor>> GetFollowingGroup() const { return FollowingGroup; }
	bool GetIsLeader() const { return bIsLeader; }

};
