// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayer.h"

#include "Asteroides.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Laser.h"
#include "InputActionValue.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
    Super::BeginPlay();

    // Add Input Mapping Context
    if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
    {
        
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->AddMappingContext(InputMapping, 0);
        }
    }
	
    this->OnActorBeginOverlap.AddDynamic(this, &AMyPlayer::OnOverlap);
}

void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            Subsystem->ClearAllMappings();
            Subsystem->AddMappingContext(InputMapping, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyPlayer::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPlayer::Look);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AMyPlayer::Shoot);
    }
}


void AMyPlayer::OnOverlap(AActor* MyActor, AActor* OtherActor)
{
    if (auto Asteroide = Cast<AAsteroides>(OtherActor)) {
        Asteroide->SetActorEnableCollision(false);
        Asteroide->Destroy();
        Health = FMath::Clamp(Health - 25.0f, 0.0f, 100.0f);
        UpdateHUDHealth(Health);
    }
}

void AMyPlayer::Move(const FInputActionValue& Value)
{
    const FVector2D MovementValue = Value.Get<FVector2D>();
    if (Controller)
    {
        const FRotator ControlRotation = Controller->GetControlRotation();
        
        const FVector Forward = ControlRotation.Vector();
        const FRotator YawRotation(0, ControlRotation.Yaw, 0);
        const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        
        AddMovementInput(Forward, MovementValue.Y);
        AddMovementInput(Right, MovementValue.X);   
    }
}

void AMyPlayer::Look(const FInputActionValue& Value)
{
    FVector2D SmoothedLookInput = FVector2D::ZeroVector;
	const FVector2D LookVector = Value.Get<FVector2D>();
    SmoothedLookInput = FMath::Vector2DInterpTo(
        SmoothedLookInput,
        LookVector,
        GetWorld()->GetDeltaSeconds(),
        LookLag
    );
	AddControllerYawInput(SmoothedLookInput.X);
	AddControllerPitchInput(-SmoothedLookInput.Y);
}


void AMyPlayer::Shoot()
{

    // Permet de pas tirer trop vite
    const float Now = GetWorld()->GetTimeSeconds();
    if (Now - LastShotTime < ShootDelay) return;
    LastShotTime = Now;
    UGameplayStatics::PlaySound2D( GetWorld(), ShootSound);
    
    // Spawn du laser
    const FVector PlayerLocation = GetActorLocation();
    const FRotator PlayerRotation = GetActorRotation();
    
    FVector CamLoc1 = PlayerLocation + PlayerRotation.RotateVector(FVector(600.f, -213.f, -89.f));
    FVector CamLoc2 = PlayerLocation + PlayerRotation.RotateVector(FVector(600.f,  216.f, -89.f));
    
    ALaser* Laser1 = GetWorld()->SpawnActor<ALaser>(LaserClass, CamLoc1, PlayerRotation);
    ALaser* Laser2 = GetWorld()->SpawnActor<ALaser>(LaserClass, CamLoc2, PlayerRotation);
    if (Laser1 && Laser2)
    {
        Laser1->Direction = PlayerRotation.Vector();
        Laser2->Direction = PlayerRotation.Vector();
    }
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
    if (Health<=0 && !isDead)
    {
        isDead = true;
        ShowGameOverScreen();
    }
	Super::Tick(DeltaTime);
}



