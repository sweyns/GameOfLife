// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOfLifePawn.h"
#include "GameOfLifeState.h"
#include "Kismet/GameplayStatics.h"

void AGameOfLifePawn::SetupPlayerInputComponent( UInputComponent* PlayerInputComponent )
{
	Super::SetupPlayerInputComponent( PlayerInputComponent );

	PlayerInputComponent->BindAction( "Switch Mode", IE_Pressed, this, &AGameOfLifePawn::SwitchMode );
	PlayerInputComponent->BindAction( "Speed Up", IE_Pressed, this, &AGameOfLifePawn::SpeedUp );
	PlayerInputComponent->BindAction( "Slow Down", IE_Pressed, this, &AGameOfLifePawn::SlowDown );
	PlayerInputComponent->BindAction( "Reset", IE_Pressed, this, &AGameOfLifePawn::Reset );

}

void AGameOfLifePawn::SwitchMode()
{
	UE_LOG( LogTemp, Warning, TEXT( "switching mode" ) );
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) );
	if( MyGameState->GetEditMode() ) {
		MyGameState->SetEditMode( false );
		MyGameState->StartTimers();
	}
	else {
		MyGameState->SetEditMode( true );
		MyGameState->ClearTimers();
	}
}

void AGameOfLifePawn::SpeedUp()
{
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) );
	MyGameState->SpeedUp();
	if( !MyGameState->GetEditMode() ) {
		MyGameState->ClearTimers();
		MyGameState->StartTimers();
	}
	UE_LOG( LogTemp, Warning, TEXT( "speed up, time: %f" ), MyGameState->GetAdvanceTime() );
}

void AGameOfLifePawn::SlowDown()
{
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) );
	MyGameState->SlowDown();
	if( !MyGameState->GetEditMode() ) {
		MyGameState->ClearTimers();
		MyGameState->StartTimers();
	}
	UE_LOG( LogTemp, Warning, TEXT( "slow down, time: %f" ), MyGameState->GetAdvanceTime() );
}

void AGameOfLifePawn::Reset()
{
	UE_LOG( LogTemp, Warning, TEXT( "resetting" ) );
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) );
	MyGameState->Reset();
}

