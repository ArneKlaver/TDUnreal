// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

USTRUCT(BlueprintType)
struct FWaveInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere)
	float WaveSpawnSpeed;
	UPROPERTY(EditAnywhere)
	int SpawnAmount;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AEnemy> SpawnEnemie;

};
UCLASS()
class TD_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere , Meta = (MakeEditWidget = true))
	TArray<FVector> positions;
	UPROPERTY(EditAnywhere)
	TArray<FWaveInfo> WaveInformation;
	UFUNCTION()
	void SpawnEnemy();

	TArray<class AEnemy*> SpawnedEnemies;
private:
	FTimerHandle FuzeTimerHandle;
	int currentWave = 0;
	bool IsWaveFinished = true;
	int EnemiesSpawned = 0;
};
