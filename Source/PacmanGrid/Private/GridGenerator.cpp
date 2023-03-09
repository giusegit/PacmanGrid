// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerator.h"

constexpr int MapSizeX = 30;
// la y contiene 28 elementi (il for conta un elemento in meno)
constexpr int MapSizeY = 29;

// # - Wall
// B - Big Point
// N - Empty
// P - Player
//     Phantom:
//     - 1 - Blinky
//     - 2 - Pinky
//     - 3 - Inky
//     - 4 - Clyde
//    
// C - Cherry
// R - Ghost Respawn
// N - Ghost Area
// I - Invisible Not Walkable
// E - Ghost Exit

//static char Map[MapSizeX][MapSizeY] = {
//	"############################",
//	"#            ##            #",
//	"# #### ##### ## ##### #### #",
//	"#B#### ##### ## ##### ####B#",
//	"# #### ##### ## ##### #### #",
//	"#              P           #",
//	"# #### ## ######## ## #### #",
//	"# #### ## ######## ## #### #",
//	"#      ##    ##    ##      #",
//	"###### ##### ## ##### ######",
//	"###### ##### ## ##### ######",
//	"###### ##          ## ######",
//	"###### ## ######## ## ######",
//	"###### ## #IIIIII# ## ######",
//	"T         #IIIIII#         T",
//	"###### ## #IIIIII# ## ######",
//	"###### ## ###II### ## ######",
//	"###### ## 12 RE 34 ## ######",
//	"###### ## ######## ## ######",
//	"###### ## ######## ## ######",
//	"#            ##            #",
//	"# #### ##### ## ##### #### #",
//	"# #### ##### ## ##### #### #",
//	"#B  ##                ##  B#",
//	"### ## ## ######## ## ## ###",
//	"#      ## ######## ##      #",
//	"# #######    ##    ####### #",
//	"# ########## ## ########## #",
//	"#                          #",
//	"############################",
//};

static char Map[MapSizeX][MapSizeY] = {
	"############################",
	"#            ##            #",
	"# #### ##### ## ##### #### #",
	"#B#### ##### ## ##### ####B#",
	"# #### ##### ## ##### #### #",
	"#              P           #",
	"# #### ## ######## ## #### #",
	"# #### ## ######## ## #### #",
	"#      ##    ##    ##      #",
	"###### ##### ## ##### ######",
	"###### ##### ## ##### ######",
	"###### ##          ## ######",
	"###### ## ######## ## ######",
	"###### ## #IIIIII# ## ######",
	"T         #IIIIII#         T",
	"###### ## #IIIIII# ## ######",
	"###### ## ###II### ## ######",
	"###### ##    RE    ## ######",
	"###### ## ######## ## ######",
	"###### ## ######## ## ######",
	"#            ##            #",
	"# #### ##### ## ##### #### #",
	"# #### ##### ## ##### #### #",
	"#B  ##                ##  B#",
	"### ## ## ######## ## ## ###",
	"#      ## ######## ##      #",
	"# #######    ##    ####### #",
	"# ########## ## ########## #",
	"#                          #",
	"############################",
};

// Sets default values
AGridGenerator::AGridGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TileSize = 100;


}

// Called when the game starts or when spawned
void AGridGenerator::BeginPlay()
{
	Super::BeginPlay();
	GenerateGrid();

}

// Called every frame
void AGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TMap<FVector2D, AGridBaseNode*> AGridGenerator::GetTileMAp()
{
	return TileMap;
}

void AGridGenerator::GenerateGrid()
{
	for (int x = 0; x < MapSizeX; x++)
	{
		for (int y = 0; y < MapSizeY - 1; y++)
		{
			const char MapTile = Map[x][y];

			FVector OffsetVector(x * SpawnOffset.X, y * SpawnOffset.Y, 0);
			const FVector CurrentSpawnPosition = GetActorLocation() + OffsetVector;

			const auto SpawnedNode = SpawnNodeActorById(MapTile, CurrentSpawnPosition);

			SpawnedNode->TileGridPosition = (FVector2D(x, y));
			SpawnedNode->TileCoordinatesPosition = CurrentSpawnPosition;

			Grid.Add(SpawnedNode);
			TileMap.Add(FVector2D(x, y), SpawnedNode);
		}
	}
}


AGridBaseNode* AGridGenerator::SpawnNodeActorById(char CharId, FVector Position) const
{
	AGridBaseNode* Node;
	TSubclassOf<AGridBaseNode> ClassToSpawn = AGridBaseNode::StaticClass();

	if (CharId == '#')
	{
		ClassToSpawn = WallNode;
	}
	else if (CharId == 'B')
	{
		ClassToSpawn = PowerNode;
	}
	else if (CharId == 'N')
	{
		ClassToSpawn = NullNode;
	}
	else if (CharId == 'P')
	{
		ClassToSpawn = CharacterNode;
	}
	else if (CharId == '1')
	{
		ClassToSpawn = BlinkyNode;
	}
	else if (CharId == '2')
	{
		ClassToSpawn = PinkyNode;
	}
	else if (CharId == '3')
	{
		ClassToSpawn = InkyNode;
	}
	else if (CharId == '4')
	{
		ClassToSpawn = ClydeNode;
	}
	else if (CharId == 'R')
	{
		ClassToSpawn = GhostRespawnNode;
	}
	else if (CharId == 'T')
	{
		ClassToSpawn = TeleportNode;
	}
	else if (CharId == 'N')
	{
		ClassToSpawn = GhostAreaNode;
	}
	else if (CharId == 'I')
	{
		ClassToSpawn = InvisibleWallNode;
	}
	else if (CharId == 'E')
	{
		ClassToSpawn = GhostExitNode;
	}
	else
	{
		ClassToSpawn = PointNode;
	}
	Node = GetWorld()->SpawnActor<AGridBaseNode>(ClassToSpawn, Position, FRotator::ZeroRotator);
	return Node;
}


bool AGridGenerator::IsNodeValidForWalk(AGridBaseNode* Node)
{
	if (Node == nullptr) return false;
	if (Node->EWalkableId == NotWalkable) return false;

	return true;
}

AGridBaseNode* AGridGenerator::GetNextNode(const FVector2D StartCoords, FVector InputDir)
{

	const float RequestedX = StartCoords.X + InputDir.X;
	const float RequestedY = StartCoords.Y + InputDir.Y;
	// ritorna un numero compreso tra min e max se nel range
	//se più piccolo del min ritorna il min
	//se più grande del max ritorna il max
	const float ClampedX = FMath::Clamp(RequestedX, 0.f, MapSizeX - 1);
	const float ClampedY = FMath::Clamp(RequestedY, 0.f, MapSizeY - 2);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), ClampedX, ClampedY));
	AGridBaseNode* PossibleNode = GetTileMAp()[FVector2D(ClampedX, ClampedY)];

	if (RequestedX > ClampedX || RequestedX < 0)
	{
		//X overflow
		PossibleNode = nullptr;
	}
	if (RequestedY > ClampedY || RequestedY < 0)
	{
		//Y overflow
		PossibleNode = nullptr;
	}
	return PossibleNode;
}

FVector2D AGridGenerator::GetPosition(const FHitResult& Hit)
{
	return Cast<AGridBaseNode>(Hit.GetActor())->GetGridPosition();
}

TArray<AGridBaseNode*>& AGridGenerator::GetTileArray()
{
	return Grid;
}

FVector AGridGenerator::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY)
{
	return  TileSize * FVector(InX, InY, 0);
}

FVector2D AGridGenerator::GetXYPositionByRelativeLocation(const FVector& Location)
{
	double x = floor(Location[0] / (TileSize));
	double y = floor(Location[1] / (TileSize));
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), x, y));
	return FVector2D(x, y);
}

FVector2D AGridGenerator::GetTwoDOfVector(FVector DDDVector)
{
	return FVector2D(DDDVector.X, DDDVector.Y);
}

