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
    float MovementSpeed = 700.0f;
    
    // Classe de projectile à faire apparaître, assignable depuis le Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
    TSubclassOf<class AProjectile> ProjectileClass;

    // Cadence de tir (temps entre deux tirs en secondes)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
    float FireRate = 0.2f;
    
    // Nombre de vies du joueur
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
    int32 Lives = 3;

    // Fonction appelée quand le vaisseau perd une vie
    void LoseLife();
    
    // Classe du Widget HUD à afficher, assignable depuis le Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    // Référence vers l'instance du widget créée
    UPROPERTY(BlueprintReadOnly, Category = "UI")
    UUserWidget* HUDWidgetInstance;
    
    // Widget HUD casté pour appeler ses fonctions Blueprint
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnLivesChanged(int32 NewLives);
    
    UPROPERTY(BlueprintReadOnly, Category = "Ship")
    int32 Score = 0;

    UFUNCTION(BlueprintCallable, Category = "Ship")
    void AddScore(int32 Points);

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnScoreChanged(int32 NewScore);
    
    // Classe du Widget Game Over à afficher, assignable depuis le Blueprint
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<class UUserWidget> GameOverWidgetClass;
    
    // Event déclenché au moment du Game Over, pour transmettre le widget créé et le score final
    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnGameOver(UUserWidget* GameOverWidget, int32 FinalScore);
    
    // Event déclenché à chaque tir, pour afficher l'effet de canon en Blueprint
    UFUNCTION(BlueprintImplementableEvent, Category = "Ship")
    void OnFire();
    
    // Limites de la zone de jeu (le vaisseau ne peut pas en sortir)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
    float MaxX = 800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ship")
    float MaxY = 1400.0f;
private:
    // Fonctions appelées par les axes d'input
    void MoveHorizontal(float Value);
    void MoveVertical(float Value);
    
    // Fonction appelée pour tirer
    void Fire();

    // Timer pour gérer le tir en rafale
    FTimerHandle FireTimerHandle;
    void StartFiring();
    void StopFiring();
    
    FVector LastMoveInput = FVector(1.0f, 0.0f, 0.0f);
    void UpdateShipRotation();

};