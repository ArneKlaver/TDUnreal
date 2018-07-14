// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TD_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float speed = 1000;
	float traveledDistance = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float DistanceToTarget = 0;
	class AEnemy* Target;
	float BulletDamage;
};
