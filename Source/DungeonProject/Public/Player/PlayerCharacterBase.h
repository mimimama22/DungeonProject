// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/InteractDungeon.h"
#include "PlayerCharacterBase.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputAction;

UCLASS()
class DUNGEONPROJECT_API APlayerCharacterBase : public ACharacter , public IInteractDungeon
{
	GENERATED_BODY()

public:

	// Camera boom positioning the camera behind the character
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerCharacterBase - Camera" )
	TObjectPtr<USpringArmComponent> CameraBoom;
	// Follow camera
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerCharacterBase - Camera" )
	TObjectPtr<UCameraComponent> FollowCamera;
	
	// Called to bind functionality to input
	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerCharacterBase - IA" )
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerCharacterBase - IA" )
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerCharacterBase - IA" )
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY( EditAnywhere , BlueprintReadWrite , Category = "PlayerCharacterBase - IA" )
	TObjectPtr<UInputAction> InteractionAction;

protected:

	//Bool
	bool bIsInBuildMode = false;

	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement
	UFUNCTION( BlueprintCallable )
	void Move( const FInputActionValue& Value );
	// Look
	UFUNCTION( BlueprintCallable )
	void Look( const FInputActionValue& Value );
	// Jump
	void Jump() override;
	void StopJumping() override;


	

public:

	// Sets default values for this character's properties
	APlayerCharacterBase();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Exit Build Mode
	UFUNCTION( BlueprintCallable , Category = "PlayerCharacterBase - Mode" )
	void ExitBuildMode();


	//Getter
	UFUNCTION( BlueprintCallable , Category = "PlayerCharacterBase - Mode" )
	bool GetIsInBuildMode() const { return bIsInBuildMode; }
	

	// Function Interface
	virtual void SetModeBuildDungeon_Implementation(bool bIsBuildMode) override;

};
