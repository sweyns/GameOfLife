// (c) Stephen Weyns


#include "CellActor.h"
#include "GameOfLifeState.h"
#include "Kismet/GameplayStatics.h"

ACellActor::ACellActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>( TEXT( "CellRootComponent" ) );
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "CellMesh" ) );
	StaticMeshComponent->SetupAttachment( RootComponent );

	FScriptDelegate OnClickedDelegate;
	FScriptDelegate OnBeginCursorOverDelegate;
	FScriptDelegate OnEndCursorOverDelegate;
	OnClickedDelegate.BindUFunction( this, "Clicked" );
	OnBeginCursorOverDelegate.BindUFunction( this, "BeginCursorOver" );
	OnEndCursorOverDelegate.BindUFunction( this, "EndCursorOver" );
	OnClicked.Add( OnClickedDelegate );
	OnBeginCursorOver.Add( OnBeginCursorOverDelegate );
	OnEndCursorOver.Add( OnEndCursorOverDelegate );
}

void ACellActor::BeginPlay()
{
	Super::BeginPlay();
	Alive = false;
	AliveNext = false;
}

void ACellActor::Clicked()
{
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) ); //const pointer to non-const game state
	if( MyGameState->GetEditMode() ) {
		if( Alive ) {
			StaticMeshComponent->SetMaterial( 0, BeginCursorOverMaterial );
			Alive = false;
		}
		else {
			StaticMeshComponent->SetMaterial( 0, ClickedMaterial );
			Alive = true;
		}
	}
}

void ACellActor::BeginCursorOver()
{
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) );
	if( MyGameState->GetEditMode() ) {
		StaticMeshComponent->SetMaterial( 0, BeginCursorOverMaterial );
	}
}

void ACellActor::EndCursorOver()
{
	AGameOfLifeState* const MyGameState = Cast<AGameOfLifeState>( UGameplayStatics::GetGameState( GetWorld() ) );
	if( MyGameState->GetEditMode() ) {
		if( !Alive ) {
			StaticMeshComponent->SetMaterial( 0, EndCursorOverMaterial );
		}
		else {
			StaticMeshComponent->SetMaterial( 0, ClickedMaterial );
		}
	}
}

void ACellActor::Update()
{
	if( AliveNext ) {
		StaticMeshComponent->SetMaterial( 0, ClickedMaterial );
		Alive = true;
		SetActorHiddenInGame( false );
	}
	else {
		SetActorHiddenInGame( true );
		StaticMeshComponent->SetMaterial( 0, EndCursorOverMaterial );
		Alive = false;
	}
}

void ACellActor::Reset()
{
	StaticMeshComponent->SetMaterial( 0, EndCursorOverMaterial );
	Alive = false;
}
