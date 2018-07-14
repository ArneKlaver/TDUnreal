// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerNode.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "MyPlayerController.h"
#include "Turret.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Components/SceneComponent.h"
// Sets default values
ATowerNode::ATowerNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("MyMesh");
	this->Tags.Add("TowerNode");
	if (GetWorld() != nullptr)
	{
		APlayerController* tempPlayerController = GetWorld()->GetFirstPlayerController();
		if (tempPlayerController != nullptr)
		{
			playerControler = Cast<AMyPlayerController>(tempPlayerController);
		}
	}
}

// Called when the game starts or when spawned
void ATowerNode::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATowerNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATowerNode::OnClicked(ATowerNode* towerNode)
{
	if (playerControler == nullptr)
	{
		APlayerController* tempPlayerController = GetWorld()->GetFirstPlayerController();
		if (tempPlayerController != nullptr)
		{
			playerControler = Cast<AMyPlayerController>(tempPlayerController);
		}
	}
	// If there is no turret on the node
	if (towerNode->IsEmpty)
	{
		// check if there is enough gold
		if (playerControler->HasEnoughGold())
		{
			ATurret* spawnedTurret = GetWorld()->SpawnActor<ATurret>(playerControler->TurretBP, towerNode->GetTransform());
			FName name = spawnedTurret->GetFName();
		}
	}
}
