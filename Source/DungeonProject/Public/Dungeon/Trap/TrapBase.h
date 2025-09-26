// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapBase.generated.h"

class UBoxComponent;

UCLASS()
class DUNGEONPROJECT_API ATrapBase : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap")
	TObjectPtr<UBoxComponent> HitBox;

protected:

	//Trap info
	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap_info")
	FName TrapName;
	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap_info")
	FString TrapDescription;
	//trap State
	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap_State")
	float TrapDamage;
	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap_State")
	float TrapCooldown;
	UPROPERTY( EditAnywhere , BlueprintReadOnly, Category="Trap_State")
	bool bIsActive;

	//Timer Handle
	FTimerHandle TrapCooldownTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Begin Overlap HitBox
	UFUNCTION(BlueprintCallable, Category="Trap")
	void BeginOverlapHitBox( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	//Activated Trap
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent , Category="Trap")
	bool ActivateTrap();

	//Reset cooldown
	UFUNCTION( BlueprintCallable , Category="Trap")
	void ResetCooldown();

public:

	// Sets default values for this actor's properties
	ATrapBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Getters
	UFUNCTION( BlueprintCallable , BlueprintPure , Category="Trap")
	bool GetIsActive() const { return bIsActive; }
	UFUNCTION( BlueprintCallable , BlueprintPure , Category="Trap" )
	float GetTrapDamage() const { return TrapDamage; }
	UFUNCTION( BlueprintCallable , BlueprintPure , Category="Trap" )
	FName GetTrapName() const { return TrapName; }
	UFUNCTION( BlueprintCallable , BlueprintPure , Category="Trap" )
	FString GetTrapDescription() const { return TrapDescription; }

	//Setters
	UFUNCTION( BlueprintCallable , Category="Trap")
	void SetIsActive( bool NewState ) { bIsActive = NewState; }
	UFUNCTION( BlueprintCallable , Category="Trap" )
	void SetTrapDamage( float NewDamage ) { TrapDamage = NewDamage; }
	UFUNCTION( BlueprintCallable , Category="Trap" )
	void SetTrapName( FName NewName ) { TrapName = NewName; }
	UFUNCTION( BlueprintCallable , Category="Trap" )
	void SetTrapDescription( FString NewDescription ) { TrapDescription = NewDescription; }
	
};
