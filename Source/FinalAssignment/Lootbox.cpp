// Fill out your copyright notice in the Description page of Project Settings.


#include "Lootbox.h"

// Sets default values
ALootbox::ALootbox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

void ALootbox::SpawnRandomPotion()
{
	FVector const location = GetActorLocation();
	FRotator const rotation(0.0f, 0.0f, 0.0f);
	int r = rand() % 100 + 1;


	if (r <= 60)
	{
		GetWorld()->SpawnActor<AActor>(BPPotion1, location, rotation);
	}
	else if (r > 60 && r < 90)
	{
		GetWorld()->SpawnActor<AActor>(BPPotion2, location, rotation);
	}
	else if (r >= 90)
	{
		GetWorld()->SpawnActor<AActor>(BPPotion3, location, rotation);
	}


}

// Called when the game starts or when spawned
void ALootbox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALootbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

