// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GI_MyGame.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTER_API UGI_MyGame : public UGameInstance
{
	GENERATED_BODY()
	
	public:
		UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Game")
		bool GameStarted = false;
};
