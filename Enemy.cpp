// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// extra check for pendingKill
	if (this->IsPendingKill())
		return;
	
	// move to the next point
	if (CurrentPositionIndex >= positions->Num())
	{
		// if there are no more points (end of the path) do damage on the player and destroy this object
		APlayerController* tempPlayerController = GetWorld()->GetFirstPlayerController();
		if (tempPlayerController != nullptr)
		{
			Cast<AMyPlayerController>(tempPlayerController)->TakePlayerDamage(Damage);
		}
		this->Destroy();
		return;
	}
	// calculate where to move to
	FVector moveToLocation = (*positions)[CurrentPositionIndex];
	FVector currentLocation = GetActorLocation();
	FVector movement = moveToLocation - currentLocation;
	float distance = movement.Size();
	movement.Normalize();
	movement *= DeltaTime * 100 * Speed;
	SetActorLocation(currentLocation + movement);
	// if the movement distance is bigger then the distance to move. go to the next point.
	float movementDistance = movement.Size();
	if (distance < movementDistance)
	{
		CurrentPositionIndex++;
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	


}

bool AEnemy::TakeBulletDamage(int Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		// Enemy is death
			APlayerController* tempPlayerController = GetWorld()->GetFirstPlayerController();
			if (tempPlayerController != nullptr)
			{
				Cast<AMyPlayerController>(tempPlayerController)->Gold += GoldGain;
			}
			this->Destroy();
			return true;
	}
	return false;
}
