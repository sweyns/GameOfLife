// (c) Stephen Weyns

#pragma once

#include "CoreMinimal.h"
#include "CellActor.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

UCLASS()
class GAMEOFLIFE_API AGridActor : public AActor
{
	GENERATED_BODY()

public:
	/**
	 * Updates the visibility of the cells for edit mode.
	 * All cells are set to be visible.
	 */
	void ToEditMode();

	/**
	 * Updates the visibility of the cells for play mode.
	 * Dead cells are set to be invisible and alive cells are set to be visible.
	 */
	void ToPlayMode();

	void StartTimer();
	void ClearTimer();
	void Reset();

protected:
	virtual void BeginPlay() override;

private:
	/**
	 * Advances the grid to the next generation.
	 */
	UFUNCTION() //set because called by timers
	void Advance();

	/**
	* Counts the number of alive neighbors for the cell at index j + i * width.
	*/
	int CountAliveNeighbors( const int i, const int j );

	/**
	* Updates the cells' AliveNext field based on the rules of the game.
	*/
	void UpdateAliveNext( const int Index, const int NumAliveNeighbors );

	/**
	* Populates the AliveNext field of all the cells in the grid to be able to advance to the next generation.
	*/
	void GenerateNext();

	/**
	* Updates the visibility and Alive field of the cells in the grid.
	*/
	void UpdateNext();


	TArray<ACellActor*> CellActors; //row-major

	/** Width of grid in number of cells. */
	UPROPERTY( EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true", Category = "Grid Setup") )
	int Width = 10;
	/** Height of grid in number of cells. */
	UPROPERTY( EditAnywhere, meta = (ClampMin = "1", AllowPrivateAccess = "true", Category = "Grid Setup") )
	int Height = 10;
	/** Offset between cells. */
	UPROPERTY( EditAnywhere, meta = (ClampMin = "0.0", AllowPrivateAccess = "true", Category = "Grid Setup") )
	float Offset = 15.0;
	/** Class for cell. */
	UPROPERTY( EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup") )
	TSubclassOf<ACellActor> CellActor;

};
