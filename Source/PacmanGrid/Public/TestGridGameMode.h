// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridGenerator.h"
#include "GridPawn.h"
#include "GameFramework/GameMode.h"
#include "TestGridGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PACMANGRID_API ATestGridGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	// TSubclassOf is a template class that provides UClass type safety.
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGridGenerator> GridGeneratorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<AGridPawn> GridPawnClass;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		AGridGenerator* GField;

	UPROPERTY(VisibleAnywhere)
		AGridPawn* MyPawn;

	ATestGridGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
