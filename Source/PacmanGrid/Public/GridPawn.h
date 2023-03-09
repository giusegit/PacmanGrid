// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GridBaseNode.h"
#include "GameFramework/Pawn.h"
#include "GridPawn.generated.h"

UCLASS()
class PACMANGRID_API AGridPawn : public APawn
{
	GENERATED_BODY()

public:

public:
	// Sets default values for this pawn's properties
	AGridPawn();
	void SetVerticalInput(float AxisValue);
	void SetHorizontalInput(float AxisValue);

	UFUNCTION(BlueprintCallable)
		void SetNextNodeByDir(FVector InputDir);
	FVector GetLastValidDirection() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		FVector LastInputDirection;
	UPROPERTY(VisibleAnywhere, Category = "Movement")
		FVector LastValidInputDirection;

	void SetLastValidDirection(FVector Dir);

	UPROPERTY(EditAnywhere, Category = "Movement")
		float CurrentMovementSpeed = 100.0f;
	UPROPERTY(EditAnywhere)
		float AcceptedDistance = 4.f;
	UPROPERTY(VisibleAnywhere)
		FVector2D CurrentGridCoords;
	UPROPERTY()
		float TimeAccumulator;

	UPROPERTY(VisibleAnywhere)
		class ATestGridGameMode* GameMode;

	// reference to a GameField object
	UPROPERTY(VisibleAnywhere)
		class AGridGenerator* TheGridGen;

	UPROPERTY(VisibleAnywhere, Category = "Nodes")
		AGridBaseNode* NextNode;
	UPROPERTY(VisibleAnywhere, Category = "Nodes")
		AGridBaseNode* TargetNode;
	UPROPERTY(VisibleAnywhere, Category = "Nodes")
		AGridBaseNode* LastNode;

	void HandleMovement();
	void OnNodeReached();
	void MoveToCurrentTargetNode();
	void SetTargetNode(AGridBaseNode* Node);
	void SetNextNode(AGridBaseNode* Node);
	void SetNodeGeneric(const FVector Dir);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// called on left mouse click (binding)
	UFUNCTION()
		void OnClick();

};
