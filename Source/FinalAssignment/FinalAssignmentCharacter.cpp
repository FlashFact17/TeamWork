// Copyright Epic Games, Inc. All Rights Reserved.

#include "FinalAssignmentCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

AFinalAssignmentCharacter::AFinalAssignmentCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	ProjectileOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileOrigin"));
	ProjectileOrigin->SetupAttachment(RootComponent);

}

void AFinalAssignmentCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void AFinalAssignmentCharacter::ShootProjectile()
{
	GetWorld()->SpawnActor<AActor>(ProjectileActor, ProjectileOrigin->GetComponentTransform());
}

void AFinalAssignmentCharacter::OnDodge()
{
	bIsInvincible = true;
}

void AFinalAssignmentCharacter::HasDodged()
{
	bIsInvincible = false;
}

void AFinalAssignmentCharacter::OnDamage(int damage)
{
	if (!bIsInvincible)
	{
		HP -= damage;
	}
	if (HP <= 0)
	{
		HP = 0;
	}
}

void AFinalAssignmentCharacter::OnManaCost(int cost)
{
	Mana -= cost;
	if (Mana <= 0)
	{
		Mana = 0;
	}
}

void AFinalAssignmentCharacter::UseHpPot()
{
	if (CurHPpot > 0)
	{
		CurHPpot -= 1;
		HP += 25;
		if (HP >= 100)
		{
			HP = 100;
		}
	}
}

void AFinalAssignmentCharacter::UseManaPot()
{
	if (CurManaPot > 0)
	{
		CurManaPot -= 1;
		Mana += 25;
		if (Mana >= 100)
		{
			Mana = 100;
		}
	}
}

void AFinalAssignmentCharacter::UseSpeedPot()
{
	if (CurSpeedPot > 0)
	{
		CurSpeedPot -= 1;
	}
}

void AFinalAssignmentCharacter::PickHpPot()
{
	if (CurHPpot < 3)
	{
		CurHPpot += 1;
	}
}

void AFinalAssignmentCharacter::PickManaPot()
{
	if (CurManaPot < 3)
	{
		CurManaPot += 1;
	}
}

void AFinalAssignmentCharacter::PickSpeedPot()
{
	if (CurSpeedPot < 3)
	{
		CurSpeedPot += 1;
	}
}


void AFinalAssignmentCharacter::Boom()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypes;
	objectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	FVector charLocation = GetActorLocation();
	float radius = 300.0f;
	TArray<ACharacter*> enemyIgnore;
	TArray<ACharacter*> enemyInSphere;
	//UClass* enemies = A::AEnemy();
	//UKismetSystemLibrary::SphereOverlapActors(GetWorld(), charLocation, radius);
	
}


