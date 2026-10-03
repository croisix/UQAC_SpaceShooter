// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroideSpawner.generated.h"

class AAsteroides;
UCLASS()
class SPACESHOOTER_API AAsteroideSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAsteroideSpawner();
	
	UPROPERTY(EditAnywhere, Category="Data")
	float nbmAsteroideParMin = 7.0f;
	
	UPROPERTY(EditAnywhere, Category="Data")
	float Angle;
	
	UPROPERTY(EditAnywhere, Category="Data")
	TSubclassOf<AAsteroides> AsteroideClass;

	UFUNCTION()
	void SpawnAsteroide();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	FTimerHandle TimerHandle_SpawnAsteroid;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
