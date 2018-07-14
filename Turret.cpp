// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h "
#include "Spawner.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"
#include "Bullet.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->AttachTo(RootComponent);
	BulletSpawnSlot = CreateDefaultSubobject<USceneComponent>("BulletSlot");
	BulletSpawnSlot->AttachTo(TurretMesh);
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawner::StaticClass(), FoundActors);
	if (FoundActors.Num() == 1)
	{
		SpawnedEnemies = &Cast<ASpawner>(FoundActors[0])->SpawnedEnemies;
	}

}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FindTarget();
	AimTurret();
	atackSpeedCounter += DeltaTime;
	if (atackSpeedCounter > AttackSpeed  && Target != nullptr)
	{
		atackSpeedCounter = 0;
		ShootTarget();
	}
}
void ATurret::FindTarget()
{
	Target = nullptr;
	float closestDistance = TurretRange + 1;
	//Find closest enemy
	for (int i = 0; i < SpawnedEnemies->Num(); i++)
	{
		if ((*SpawnedEnemies)[i] == nullptr || (*SpawnedEnemies)[i]->IsPendingKill())
		{
			SpawnedEnemies->RemoveAt(i);
			continue;
		}
		FVector actorLocation = ((*SpawnedEnemies)[i])->GetActorLocation() - GetActorLocation();
		float dist = actorLocation.Size();
		if (dist < closestDistance)
		{
			closestDistance = dist;
			Target = (*SpawnedEnemies)[i];
		}
	}
}
void ATurret::AimTurret()
{
	if (Target != nullptr)
	{
		FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), Target->GetTargetLocation());

		BaseMesh->SetWorldRotation(FMath::Lerp(GetActorRotation() , PlayerRot , 0.1f));
	}
}
void ATurret::ShootTarget()
{
	// spawn bullet
	ABullet* SpawnedBullet = GetWorld()->SpawnActor<ABullet>(BulletToSpawn , BulletSpawnSlot->GetComponentTransform());
	if (SpawnedBullet != nullptr)
	{
		SpawnedBullet->BulletDamage = TurretDamage;
		SpawnedBullet->Target = Target;
		SpawnedBullet->DistanceToTarget = (GetActorLocation() - Target->GetTargetLocation()).Size();
	}



}
