// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool TakeBulletDamage(int Damage);

	TArray<FVector>* positions;
	UPROPERTY(EditAnywhere)
	float Speed = 1;
	UPROPERTY(EditAnywhere)
	int Health = 20;
	UPROPERTY(EditAnywhere)
	int GoldGain = 20;
	UPROPERTY(EditAnywhere)
	int Damage = 1;
private:
	int CurrentPositionIndex = 1;
};
