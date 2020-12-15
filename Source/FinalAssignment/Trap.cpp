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


	//BPEnemy = CreateDefaultSubobject<ACharacter>(TEXT("BPEnemy"));
	//BPEnemy->SetupAttachment(RootComponent);


}

void ATrap::SpawnEnemy()
{
	UWorld* world = GetWorld();
	FVector const location = GetActorLocation();
	FRotator const rotation (0.0f, 0.0f, 0.0f);
	//FActorSpawnParameters param;
	//param.Owner = this;
	//GetWorld()->SpawnActor<>()
	//AEnemy* Enemy = 
	GetWorld()->SpawnActor<AEnemy>(BPEnemy, location, rotation);
	if (BPEnemy) {
		//GetWorld()->SpawnActor<ACharacter>(BPEnemy, location, rotation, param);
		//SpawnActor<ACharacter>(BPEnemy, location, rotation, param);
	}
	//world->SpawnActor<BP_Enemy>(BPEnemy, location, rotation, param);
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


