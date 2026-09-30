// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Création du composant mesh et définition comme racine
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	RootComponent = ShipMesh;

}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpaceShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveHorizontal", this, &ASpaceShip::MoveHorizontal);
	PlayerInputComponent->BindAxis("MoveVertical", this, &ASpaceShip::MoveVertical);

}

void ASpaceShip::MoveHorizontal(float Value)
{
	if (Value != 0.0f)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Y += Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
		SetActorLocation(NewLocation);
	}
}

void ASpaceShip::MoveVertical(float Value)
{
	if (Value != 0.0f)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.X += Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
		SetActorLocation(NewLocation);
	}
}

