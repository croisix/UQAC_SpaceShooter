// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroideSpawner.h"
#include "EngineUtils.h"
#include "Asteroides.h"
#include "MyPlayer.h"
#include "GI_MyGame.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AAsteroideSpawner::AAsteroideSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAsteroideSpawner::BeginPlay()
{
	Super::BeginPlay();
	float SpawnRate = 60/nbmAsteroideParMin;
	
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_SpawnAsteroid, 
		this, 
		&AAsteroideSpawner::SpawnAsteroide, 
		SpawnRate, 
		true);
}

void AAsteroideSpawner::SpawnAsteroide()
{
	UGI_MyGame* game = Cast<UGI_MyGame>(UGameplayStatics::GetGameInstance(this));
	if (game->GameStarted)
	{
		// Spawn De l'asteroide
		AMyPlayer* Joueur = Cast<AMyPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		FVector PositionJoueur = Joueur->GetActorLocation();
	
		// Calcul de l'emplacement et de l'angle aleatoire
		Angle = FMath::RandRange(0.0f, 360.0f); // Angle aléatoire
		FRotator RotationAngle(0.0f, Angle, 0.0f);
		FVector DistanceJoueur = RotationAngle.Vector() * 7500.0f;
		FVector SpawnLocation = PositionJoueur + DistanceJoueur;
	
		// Spawn de l'asteroide
		GetWorld()->SpawnActor<AAsteroides>(AsteroideClass, SpawnLocation, RotationAngle);
		// Si distance pour chaque asteroide > 15000 on supprime
		for (TActorIterator<AAsteroides> i(GetWorld()); i; ++i)
		{
			AAsteroides* Asteroide = *i; 
    
			if (Asteroide)
			{
				FVector PositionAsteroide = Asteroide->GetActorLocation();
				float Distance = FVector::Dist(PositionAsteroide, PositionJoueur);
				if (Distance >= 10000)
				{
					Asteroide->Destroy();
				}
			}
		}
	}
	
}

// Called every frame
void AAsteroideSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

