// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpaceShip.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Création du composant mesh et définition comme racine
	AsteroidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsteroidMesh"));
	RootComponent = AsteroidMesh;

	// Active la détection de collision et lie la fonction OnHit
	AsteroidMesh->SetNotifyRigidBodyCollision(true);
	AsteroidMesh->OnComponentHit.AddDynamic(this, &AAsteroid::OnHit);
}

// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	// Tire aléatoirement le nombre de points de vie entre MinHealth et MaxHealth
	Health = FMath::RandRange(MinHealth, MaxHealth);
}

// Call everytime
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (MovementDirection * MovementSpeed * DeltaTime);
	SetActorLocation(NewLocation, true);

	// Détruit l'astéroïde s'il sort trop loin de la zone de jeu
	if (GetActorLocation().Size() > MaxDistanceFromCenter)
	{
		Destroy();
	}
}

void AAsteroid::ApplyDamage()
{
	Health--;

	if (Health <= 0)
	{
		if (ExplosionEffect)
		{
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		}

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
		if (PlayerPawn)
		{
			ASpaceShip* PlayerShip = Cast<ASpaceShip>(PlayerPawn);
			if (PlayerShip)
			{
				PlayerShip->AddScore(100);
			}
		}

		Destroy();
	}
}

void AAsteroid::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		ASpaceShip* HitShip = Cast<ASpaceShip>(OtherActor);
		if (HitShip)
		{
			HitShip->LoseLife();
			Destroy();
		}
	}
}

