// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class SPACESHOOTERTP1_API AProjectile : public AActor
{
	GENERATED_BODY()
    
public: 
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public: 
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Composant visuel du projectile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectile")
	class UStaticMeshComponent* ProjectileMesh;

	// Vitesse de déplacement du projectile
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float ProjectileSpeed = 1500.0f;

	// Direction de déplacement (définie au moment du tir)
	FVector MovementDirection = FVector(1.0f, 0.0f, 0.0f);

	// Fonction appelée lors d'une collision
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	// Acteur d'effet d'impact 2D (flipbook) à faire apparaître quand le projectile touche
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<AActor> HitClass;

};