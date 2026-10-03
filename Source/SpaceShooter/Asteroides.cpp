// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroides.h"

#include "MyPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Engine/InstancedStaticMesh.h"

// Sets default values
AAsteroides::AAsteroides()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
	
	
}

// Called when the game starts or when spawned
void AAsteroides::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsDivided)
	{
		// Taille Random avec Speed et HP adapté a la taille
		Size = FMath::RandRange(minSize, maxSize); 
		Health = Size * (FMath::RandBool() ? 20 : 30); // Vie égale a la Size * 20 ou 30
		
		// Speed gérée d'un calcul avec la Size
		float MaxSpeed = 1000;
		Speed = MaxSpeed - (Size - 1.0f)  / (maxSize - minSize) * 800.0f; 
		
		
		if (APawn* MyPlayer = UGameplayStatics::GetPlayerPawn(this, 0))
		{
			Direction = Seek(MyPlayer->GetActorLocation());
		}
	}
	SetActorScale3D(FVector(Size, Size, Size));
}

void AAsteroides::Divide()
{
	APawn* MyPlayer = UGameplayStatics::GetPlayerPawn(this, 0);
	AMyPlayer* Player = Cast<AMyPlayer>(MyPlayer);
	// Boucle de 2 itérations pour faire spawn les 2 petits asteroides
	if (!IsDivided)
	{
		for (int i = 0; i < 2; i++)
		{
			FTransform SpawnTransform(GetActorRotation(), GetActorLocation());
			AAsteroides* AsteroideEnfant = GetWorld()->SpawnActorDeferred<AAsteroides>(GetClass(), SpawnTransform,nullptr, nullptr,ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			if (AsteroideEnfant)
			{
				AsteroideEnfant->IsDivided = true;
				AsteroideEnfant->Size = Size / 2;
				AsteroideEnfant->Health = 20;
				
			
				// Décalage pour éviter la collision entre les 2
				float Offset;
				if (i==0)
				{
					Offset = 15.0f;
				}
				else
				{
					Offset = -15.0f;
				}
				AsteroideEnfant->Direction = Direction.RotateAngleAxis(Offset, FVector::UpVector) * 1.1f;
			
				AsteroideEnfant->FinishSpawning(SpawnTransform);
			}	
		}
		Player->Score += 20;
		Explode();
	}
	else
	{
		Player->Score += 10;
		Destroy(); // Si c un enfant, on ne le fait pas detruire pour eviter trop de particule
	}
	
}

// Faire exploser l'asteroide via Fracture et Niagara
void AAsteroides::Explode()
{
	
	if (!FracturedClass)
	{
		Destroy();
		return;
	}
	
	AActor* Fractured = GetWorld()->SpawnActor<AActor>(FracturedClass, GetActorTransform());
	if (Fractured)
	{
		Fractured->SetLifeSpan(5.0f);
		if (UGeometryCollectionComponent* GC =Fractured->FindComponentByClass<UGeometryCollectionComponent>())
		{
			GC->AddRadialImpulse(
			GetActorLocation(),
			500.f * Size,
			ExplosionStrength,
			ERadialImpulseFalloff::RIF_Linear,
			true);
			GC->SetEnableGravity(false);
		}
	}
	Destroy();
}


// Called every frame
void AAsteroides::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (Health <= 0)
	{
		Divide();
		return;
	}
	
	AddActorWorldOffset(Direction * DeltaTime);

}

FVector AAsteroides::Seek(const FVector3d vTarget)
{
	FVector vDesired = (vTarget - GetActorLocation()).GetSafeNormal();
	return vDesired * Speed;
}


// Called to bind functionality to input
void AAsteroides::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

