// (c) Stephen Weyns


#include "GameOfLifeState.h"

void AGameOfLifeState::BeginPlay()
{
	Super::BeginPlay();

	for( FTransform T : Transforms ) {
		GridActors.Add( GetWorld()->SpawnActor<AGridActor>( GridActor, T ) );
	}

	EditMode = true;
}

void AGameOfLifeState::SetEditMode( const bool Editing ) {
	if( Editing ) {
		for( AGridActor* Grid : GridActors ) {
			Grid->ToEditMode();
		}
	}
	else {
		for( AGridActor* Grid : GridActors ) {
			Grid->ToPlayMode();
		}
	}
	EditMode = Editing;
}

void AGameOfLifeState::StartTimers() {
	for( AGridActor* Grid : GridActors ) {
		Grid->StartTimer();
	}
}

void AGameOfLifeState::ClearTimers() {
	for( AGridActor* Grid : GridActors ) {
		Grid->ClearTimer();
	}
}

void AGameOfLifeState::Reset() {
	for( AGridActor* Grid : GridActors ) {
		Grid->Reset();
	}
	SetEditMode( true );
}

void AGameOfLifeState::SpeedUp() {
	if( AdvanceTime >= 0.2f ) {
		AdvanceTime -= 0.1f;
	}
}

void AGameOfLifeState::SlowDown() {
	if( AdvanceTime <= 9.9f ) {
		AdvanceTime += 0.1f;
	}
}
