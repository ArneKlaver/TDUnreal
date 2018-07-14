// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class TD_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(EditAnywhere)
	int SelectedTurret = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	int Gold = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player stats")
	int Health = 1;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATurret> TurretBP;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameOverScreen;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> GameWinScreen;
public:
	bool HasEnoughGold();
	UFUNCTION(BlueprintCallable, Category = "selected Tower")
	void SetSelectedTower(TSubclassOf<class ATurret> newSelected, int number);
	void TakePlayerDamage(int damage);
	void GameFinished();

};
