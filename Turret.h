// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Turret.generated.h"

UCLASS()
class TD_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<class AEnemy*>* SpawnedEnemies;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FindTarget();
	void AimTurret();
	void ShootTarget();
	UPROPERTY(EditAnywhere)
	int TurretRange;
	UPROPERTY(EditAnywhere)
	int TurretDamage;
	UPROPERTY(EditAnywhere)
	float AttackSpeed;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABullet> BulletToSpawn;
	UPROPERTY(EditAnywhere)
	USceneComponent* BulletSpawnSlot;

	class AEnemy* Target;

private:
	float atackSpeedCounter = 0;
};

