// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "Enemy.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->IsPendingKill())
	{
		return;
	}
	if (Target == nullptr)
	{
		this->Destroy();
		return;
	}
	FVector movement = Target->GetActorLocation() - GetActorLocation();
	float distance = movement.Size();
	movement.Normalize();
	movement *= DeltaTime * speed;
	SetActorLocation(GetActorLocation() + movement);

	traveledDistance += movement.Size();
	if (traveledDistance > DistanceToTarget)
	{
		bool IsDead = Target->TakeBulletDamage(BulletDamage);
		this->Destroy();
	}

}

