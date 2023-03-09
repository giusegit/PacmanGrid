// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGridGameMode.h"

ATestGridGameMode::ATestGridGameMode()
{
	//PlayerControllerClass = AGridPlayerController::StaticClass();
	//DefaultPawnClass = AGridPawn::StaticClass();

}


void ATestGridGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	FVector GridPos(50.0f, 50.0f, 0.0f);
	if (GridGeneratorClass != nullptr)
	{
		GField = GetWorld()->SpawnActor<AGridGenerator>(GridGeneratorClass, GridPos, FRotationMatrix::MakeFromX(FVector(0, 0, 0)).Rotator());
	};

}