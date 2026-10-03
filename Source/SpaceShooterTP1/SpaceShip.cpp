// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShip.h"
#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Blueprint/UserWidget.h"

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

    if (HUDWidgetClass)
    {
       HUDWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
       if (HUDWidgetInstance)
       {
          HUDWidgetInstance->AddToViewport();
          OnLivesChanged(Lives);
          OnScoreChanged(Score);
       }
    }
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
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASpaceShip::StartFiring);
    PlayerInputComponent->BindAction("Fire", IE_Released, this, &ASpaceShip::StopFiring);

}

void ASpaceShip::MoveHorizontal(float Value)
{
    FVector NewLocation = GetActorLocation();
    NewLocation.Y += Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
    NewLocation.Y = FMath::Clamp(NewLocation.Y, -MaxY, MaxY);
    SetActorLocation(NewLocation);

    LastMoveInput.Y = Value;
    UpdateShipRotation();
}

void ASpaceShip::MoveVertical(float Value)
{
    FVector NewLocation = GetActorLocation();
    NewLocation.X += Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
    NewLocation.X = FMath::Clamp(NewLocation.X, -MaxX, MaxX);
    SetActorLocation(NewLocation);

    LastMoveInput.X = Value;
    UpdateShipRotation();
}

void ASpaceShip::UpdateShipRotation()
{
    if (!LastMoveInput.IsNearlyZero())
    {
       FRotator NewRotation = LastMoveInput.Rotation();
       SetActorRotation(NewRotation);
    }
}

void ASpaceShip::Fire()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
        FRotator SpawnRotation = GetActorRotation();

        GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);

        // Déclenche l'effet de tir côté Blueprint
        OnFire();
    }
}

void ASpaceShip::StartFiring()
{
    Fire();
    GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASpaceShip::Fire, FireRate, true);
}

void ASpaceShip::StopFiring()
{
    GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ASpaceShip::LoseLife()
{
    Lives--;
    OnLivesChanged(Lives);

    if (Lives <= 0)
    {
        if (GameOverWidgetClass)
        {
            UUserWidget* GameOverWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
            if (GameOverWidget)
            {
                GameOverWidget->AddToViewport();
                OnGameOver(GameOverWidget, Score);
            }
        }

        DisableInput(Cast<APlayerController>(GetController()));

        if (HUDWidgetInstance)
        {
            HUDWidgetInstance->RemoveFromParent();
        }
    }
}
void ASpaceShip::AddScore(int32 Points)
{
    Score += Points;
    OnScoreChanged(Score);
}