// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraPawn.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Runtime/Engine/Classes/Engine/EngineBaseTypes.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "TowerNode.h"


// Sets default values
ACameraPawn::ACameraPawn()
{
	GetActorLocation() = FVector(0, 0, 0);
	GetActorRotation() = FRotator(0, 0, 0);
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->AddRelativeLocation(FVector(-640, -10, 1040));
	Camera->AddLocalRotation(FRotator(-61, 0, 0));

}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// create action LeftMouseButton
	PlayerInputComponent->BindAction("LeftMouseButton", IE_Pressed, this, &ACameraPawn::OnMouseClick);

}

// use picking to see if we clicked on a tower node to spawn a tower
void ACameraPawn::OnMouseClick()
{
	// picking
	FVector WorldDirection = Camera->GetForwardVector();
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	FVector2D MousePosition;
	bool pos = playerController->GetMousePosition(MousePosition.X , MousePosition.Y);
	FVector TraceStart = Camera->RelativeLocation;
	// convert mouse to 3D space
	playerController->DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, TraceStart, WorldDirection);
	FVector TraceEnd = TraceStart + WorldDirection * 65536.0f;

	// raycast
	FHitResult TraceHitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = "MouseTrace";
	GetWorld()->LineTraceSingleByChannel(TraceHitResult, TraceStart, TraceEnd, ECC_Visibility , CollisionParams);
	//DrawDebugLine(
	//	GetWorld(),
	//	TraceHitResult.TraceStart,
	//	TraceHitResult.TraceEnd,
	//	FColor(255, 0, 0),
	//	false, 10, 0,
	//	0.1f
	//);
	
	if (TraceHitResult.GetActor() != nullptr)
	{
		FName name = TraceHitResult.Actor->GetFName();

		TArray<FName> tags = TraceHitResult.GetActor()->Tags;
		for (FName& tag : tags)
		{
			if (tag == "TowerNode")
			{
				ATowerNode* towerNodeClass;
				towerNodeClass = Cast<ATowerNode>(TraceHitResult.GetActor());
				if (towerNodeClass != nullptr)
				{
					towerNodeClass->OnClicked(towerNodeClass);
				}
			}
		}
	}


}