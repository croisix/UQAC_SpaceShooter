// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Asteroides.generated.h"

UCLASS()
class SPACESHOOTER_API AAsteroides : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAsteroides();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float Health;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float Size;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float Speed;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	FVector3d Direction;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float minSize = 1.0f;
	
	UPROPERTY(EditAnywhere, Category="Stats")
	float maxSize = 2.5f;
	
	// Permet de savoir si il a été divisé ou pas
	UPROPERTY()
	bool IsDivided = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Destruction")
	TSubclassOf<AActor> FracturedClass;

	UPROPERTY(EditDefaultsOnly, Category = "Destruction")
	float ExplosionStrength = 800.f;
	
	UFUNCTION(BlueprintCallable, Category = "Stats")
	FVector Seek(const FVector vTarget);
	
	UFUNCTION(BlueprintCallable)
	void Divide();
	
	UFUNCTION(BlueprintCallable)
	void Explode();
	
	
	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
