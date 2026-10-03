// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class SPACESHOOTER_API ALaser : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALaser();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	UPROPERTY()
	FVector3d Direction;
	
	UPROPERTY(EditAnywhere)
	float Speed = 300.0f;
	
	UPROPERTY(EditAnywhere)
	float Damage = 10.0f;
	
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
