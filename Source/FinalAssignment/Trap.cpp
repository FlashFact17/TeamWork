// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalAssignmentCharacter.h"
#include "Trap.h"
#include "Enemy.h"

// Sets default values
ATrap::ATrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);


}

void ATrap::SpawnEnemy()
{
	FVector const location = GetActorLocation();
	FRotator const rotation (0.0f, 0.0f, 0.0f);
	GetWorld()->SpawnActor<AEnemy>(BPEnemy, location, rotation);

}

// Called when the game starts or when spawned
void ATrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


