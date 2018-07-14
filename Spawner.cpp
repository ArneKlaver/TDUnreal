// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Enemy.h"
#include "MyPlayerController.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if the wave is done set the spawn speed to the new wave
	if (IsWaveFinished)
	{
		IsWaveFinished = false;
		// if there are no more waves
		if (currentWave >= WaveInformation.Num())
		{
			// game is finished
			GetWorld()->GetTimerManager().ClearTimer(FuzeTimerHandle);
			Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->GameFinished();
			return;
		}
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &ASpawner::SpawnEnemy, WaveInformation[currentWave].WaveSpawnSpeed, true);
	}
}


void ASpawner::SpawnEnemy()
{
		// spawn the enemy
		AEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(WaveInformation[currentWave].SpawnEnemie);
		if (SpawnedEnemy == nullptr || positions.Num() < 1)
			return;
		// set its location to be sure
		SpawnedEnemy->SetActorLocation(positions[0]);
		// add it to the enemy list
		SpawnedEnemies.Add(SpawnedEnemy);
		// give the enemy the positions it needs to go to
		SpawnedEnemy->positions = &this->positions;
		// increase the spawned enemies counter
		EnemiesSpawned++;
		// if there are to many enemies spawned go to the next wave
		if (EnemiesSpawned >= WaveInformation[currentWave].SpawnAmount)
		{
			EnemiesSpawned = 0;
			currentWave++;
			IsWaveFinished = true;
		}
}

