// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Asteroid.generated.h"

UCLASS()
class SPACESHOOTERTP1_API AAsteroid : public AActor
{
	GENERATED_BODY()
    
public: 
	// Sets default values for this actor's properties
	AAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Composant visuel de l'astéroïde
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Asteroid")
	class UStaticMeshComponent* AsteroidMesh;

	// Vitesse de déplacement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float MovementSpeed = 300.0f;

	// Nombre de tirs nécessaires pour détruire l'astéroïde (défini aléatoirement au spawn)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Asteroid")
	int32 Health;

	// Valeurs min/max pour le nombre aléatoire de points de vie, réglables en Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 MinHealth = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	int32 MaxHealth = 3;

	// Direction de déplacement, définie au spawn
	FVector MovementDirection;

	// Fonction pour infliger des dégâts (appelée par le projectile)
	void ApplyDamage();

	// Fonction appelée lors d'une collision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Distance maximale avant que l'astéroïde soit détruit automatiquement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	float MaxDistanceFromCenter = 3000.0f;
	
	// Acteur d'explosion 2D (flipbook) à faire apparaître à la destruction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Asteroid")
	TSubclassOf<AActor> ExplosionClass;
};