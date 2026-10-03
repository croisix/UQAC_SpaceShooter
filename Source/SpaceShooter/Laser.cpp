// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser.h"

#include "Asteroides.h"
#include "MyPlayer.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ALaser::ALaser()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	// Se détruit si ne touche rien
	Super::BeginPlay();
	SetLifeSpan(7.0f);
	this->OnActorBeginOverlap.AddDynamic(this, &ALaser::OnOverlap);
}

void ALaser::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
	if (auto Asteroide = Cast<AAsteroides>(OtherActor)) {
		Destroy();
		Asteroide->Health = Asteroide->Health - Damage;
	}
}


// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	AddActorWorldOffset(Direction * Speed * DeltaTime, true);
}



