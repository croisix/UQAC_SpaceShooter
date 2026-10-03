// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyPlayer.generated.h"

class UInputMappingContext;
class UInputAction;
class UEnhancedInputComponent;
class ALaser;

UCLASS()
class SPACESHOOTER_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();
	
	UPROPERTY(EditAnywhere, Category="PlayerStats")
	float Health = 100;
	
	UPROPERTY(EditAnywhere, Category="PlayerStats")
	float Speed = 100.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int Score = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool isDead = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isPause = false;
	
	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	float ShootDelay = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* ShootSound;
	
	float LastShotTime = -100.f;
	
	// INPUT
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "EnhancedInput")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> MoveAction;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> LookAction;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditDefaultsOnly, Category="Shoot")
	TSubclassOf<ALaser> LaserClass;
	
	UPROPERTY(EditAnywhere, Category = "Look")
	float LookLag = 5.0f;
	
	UFUNCTION(BlueprintCallable)
	void Shoot();
	
	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);
	
	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnOverlap(AActor* MyActor, AActor* OtherActor);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void UpdateHUDHealth(float NewHealth);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void ShowGameOverScreen();
	 
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
