// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

UCLASS()
class SPACESHOOTERTP1_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()
    
public: 
	// Sets default values for this actor's properties
	AAsteroidSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Classe d'astéroïde à faire apparaître, assignable depuis le Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<class AAsteroid> AsteroidClass;

	// Intervalle de spawn aléatoire (min/max en secondes)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MinSpawnInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MaxSpawnInterval = 3.0f;

	// Distance depuis le centre pour définir les bords de spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnRadius = 1500.0f;

	// Probabilité (0 à 1) que l'astéroïde vise le joueur plutôt qu'une direction aléatoire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float ChanceToTargetPlayer = 0.5f;

private:
	// Timer handle pour gérer les spawns successifs
	FTimerHandle SpawnTimerHandle;

	// Fonction appelée à chaque spawn, qui programme aussi le prochain spawn
	void SpawnAsteroid();

	// Calcule une position aléatoire sur les bords (haut, gauche, droite)
	FVector GetRandomEdgeLocation();

};