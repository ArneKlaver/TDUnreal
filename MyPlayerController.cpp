// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "Turret.h"
#include "Engine/Engine.h"
#include "GameOverWidget.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"


bool AMyPlayerController::HasEnoughGold()
{
	int neededGold = 0;

	switch (SelectedTurret)
	{
	case 0:
		neededGold = 10; 
		break;
	case 1:
		neededGold = 20;
		break;
	case 2:
		neededGold = 50;
		break;
	}

	if (Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->Gold >= neededGold)
	{
		Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->Gold -= neededGold;
		return true;
	}
	return false;

}

void AMyPlayerController::SetSelectedTower(TSubclassOf<class ATurret> newSelected , int number)
{
	TurretBP = newSelected;
	SelectedTurret = number;
}
void AMyPlayerController::TakePlayerDamage(int damage)
{
	Health -= damage;
	// if health is below 0 spawn game over screen and pause the game
	if (Health <= 0)
	{
		UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), *GameOverScreen);
		widget->AddToViewport();
		this->SetPause(true);
	}
}
void AMyPlayerController::GameFinished()
{
	// spawn the win screen and pause the game
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), *GameWinScreen);
	widget->AddToViewport();
	this->SetPause(true);
}