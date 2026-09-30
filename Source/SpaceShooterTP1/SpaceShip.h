// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShip.generated.h"

UCLASS()
class SPACESHOOTERTP1_API ASpaceShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Composant visuel du vaisseau
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ship")
	class UStaticMeshComponent* ShipMesh;
	
	// Vitesse de déplacement, modifiable depuis le Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	float MovementSpeed = 500.0f;
	
	// Classe de projectile à faire apparaître, assignable depuis le Blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
	TSubclassOf<class AProjectile> ProjectileClass;
private:
	// Fonctions appelées par les axes d'input
	void MoveHorizontal(float Value);
	void MoveVertical(float Value);
	
	// Fonction appelée pour tirer
	void Fire();
	
	FVector LastMoveInput = FVector(1.0f, 0.0f, 0.0f);
	void UpdateShipRotation();

};
