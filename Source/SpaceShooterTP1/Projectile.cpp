// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Asteroid.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Création du composant mesh et définition comme racine
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	RootComponent = ProjectileMesh;

	// Active la détection de collision et lie la fonction OnHit
	ProjectileMesh->SetNotifyRigidBodyCollision(true);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	// Durée de vie automatique : détruit le projectile après 3 secondes s'il ne touche rien
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Le projectile ignore tout (vaisseau, autres projectiles...) sauf les astéroïdes
	ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Block);
    
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * ProjectileSpeed * DeltaTime);
	SetActorLocation(NewLocation, true);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this)
	{
		if (HitClass)
		{
			GetWorld()->SpawnActor<AActor>(HitClass, GetActorLocation(), FRotator::ZeroRotator);
		}

		AAsteroid* HitAsteroid = Cast<AAsteroid>(OtherActor);
		if (HitAsteroid)
		{
			HitAsteroid->ApplyDamage();
		}

		Destroy();
	}
}