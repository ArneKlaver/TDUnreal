// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.h"

#include "TowerNode.generated.h"

UCLASS()
class TD_API ATowerNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerNode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnClicked(ATowerNode* towerNode);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
		bool IsEmpty = true;

	TSubclassOf<class ATurret> MyItemBlueprint;
private:
	class AMyPlayerController* playerControler;
};
