// Fill out your copyright notice in the Description page of Project Settings.


#include "Dungeon/Room/SplineDungeonPath.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
ASplineDungeonPath::ASplineDungeonPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SplineComponent;

}

// Called when the game starts or when spawned
void ASplineDungeonPath::BeginPlay()
{
	Super::BeginPlay();

	float SplineLenght = SplineComponent->GetSplineLength();
	float ActualDistance = 0.f;
	bool EndSpline = false;

	if(ActualDistance < SplineLenght && !EndSpline)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("SplineLenght: %f"), SplineLenght));
	    FVector StartLocation = SplineComponent->GetLocationAtDistanceAlongSpline(ActualDistance, ESplineCoordinateSpace::Local);
		FVector StartTangent = SplineComponent->GetTangentAtDistanceAlongSpline(ActualDistance, ESplineCoordinateSpace::Local);
		ActualDistance += LenghtMesh * 100.0f;
		EndSpline = ActualDistance > SplineLenght;

		ActualDistance = EndSpline ? SplineLenght : ActualDistance;

		FVector EndLocation = SplineComponent->GetLocationAtDistanceAlongSpline(ActualDistance, ESplineCoordinateSpace::Local);
		FVector EndTangent = SplineComponent->GetTangentAtDistanceAlongSpline(ActualDistance, ESplineCoordinateSpace::Local);

		USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
		SplineMesh->SetMobility(EComponentMobility::Movable);
		SplineMesh->SetCollisionEnabled( ECollisionEnabled::Type::QueryAndPhysics );

		if(PathMesh)
		{
			SplineMesh->SetStaticMesh(PathMesh);
			SplineMesh->SetMaterial(0, PathMesh->GetMaterial(0));
		}
		//Attach to SplineComponent
		SplineMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
		// Set the start and end positions and tangents
		SplineMesh->SetStartAndEnd(StartLocation, StartTangent, EndLocation, EndTangent, true);
		// Register the component
		SplineMesh->RegisterComponent();
		
	}
	
}

void ASplineDungeonPath::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	
	
}

// Called every frame
void ASplineDungeonPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

