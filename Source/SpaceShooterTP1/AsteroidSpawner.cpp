// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidSpawner.h"
#include "Asteroid.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAsteroidSpawner::AAsteroidSpawner()
{
    // Ce spawner n'a pas besoin de Tick, tout passe par un timer
    PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AAsteroidSpawner::BeginPlay()
{
    Super::BeginPlay();

    // Programme le premier spawn
    float FirstDelay = FMath::RandRange(MinSpawnInterval, MaxSpawnInterval);
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, FirstDelay, false);
}

// Called every frame
void AAsteroidSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void AAsteroidSpawner::SpawnAsteroid()
{
    if (AsteroidClass)
    {
        FVector SpawnLocation = GetRandomEdgeLocation();
        FRotator SpawnRotation = FRotator::ZeroRotator;

        AAsteroid* NewAsteroid = GetWorld()->SpawnActor<AAsteroid>(AsteroidClass, SpawnLocation, SpawnRotation);

        if (NewAsteroid)
        {
            // Détermine si l'astéroïde vise le joueur ou part dans une direction aléatoire
            float RandomChance = FMath::FRand();

            if (RandomChance <= ChanceToTargetPlayer)
            {
                APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
                if (PlayerPawn)
                {
                    FVector DirectionToPlayer = (PlayerPawn->GetActorLocation() - SpawnLocation).GetSafeNormal();
                    NewAsteroid->MovementDirection = DirectionToPlayer;
                }
            }
            else
            {
                // Direction aléatoire dans le plan (X/Y)
                float RandomAngle = FMath::RandRange(0.0f, 2.0f * PI);
                FVector RandomDirection = FVector(FMath::Cos(RandomAngle), FMath::Sin(RandomAngle), 0.0f);
                NewAsteroid->MovementDirection = RandomDirection;
            }
        }
    }

    // Programme le prochain spawn avec un nouveau délai aléatoire
    float NextDelay = FMath::RandRange(MinSpawnInterval, MaxSpawnInterval);
    GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AAsteroidSpawner::SpawnAsteroid, NextDelay, false);
}

FVector AAsteroidSpawner::GetRandomEdgeLocation()
{
    // Choisit aléatoirement un bord : 0 = haut, 1 = bas, 2 = gauche, 3 = droite
    int32 EdgeChoice = FMath::RandRange(0, 3);
    FVector SpawnPos = FVector::ZeroVector;

    switch (EdgeChoice)
    {
    case 0: // Haut
        SpawnPos = FVector(SpawnRadius, FMath::RandRange(-SpawnRadius, SpawnRadius), 0.0f);
        break;
    case 1: // Bas
        SpawnPos = FVector(-SpawnRadius, FMath::RandRange(-SpawnRadius, SpawnRadius), 0.0f);
        break;
    case 2: // Gauche
        SpawnPos = FVector(FMath::RandRange(-SpawnRadius, SpawnRadius), -SpawnRadius, 0.0f);
        break;
    case 3: // Droite
        SpawnPos = FVector(FMath::RandRange(-SpawnRadius, SpawnRadius), SpawnRadius, 0.0f);
        break;
    }

    return SpawnPos;
}