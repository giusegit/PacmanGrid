// Fill out your copyright notice in the Description page of Project Settings.


#include "TestGridGameMode.h"

ATestGridGameMode::ATestGridGameMode()
{

}


void ATestGridGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	// con questa posizione la tile di coordinate griglia (0,0) ha come
	// coordinate nello spazio dello spigolo inferiore sinistro (0,0) 
	FVector GridPos(50.0f, 50.0f, 0.0f);
	// N.B. tutte le funzioni andrebbero normalizzate se la posizione
	//della griglia non fosse pi� questa ma una qualsiasi nello spazio
	if (GridGeneratorClass != nullptr)
	{
		GField = GetWorld()->SpawnActor<AGridGenerator>(GridGeneratorClass, GridPos, FRotationMatrix::MakeFromX(FVector(0, 0, 0)).Rotator());
	};

}