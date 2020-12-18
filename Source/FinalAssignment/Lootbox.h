// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lootbox.generated.h"

UCLASS()
class FINALASSIGNMENT_API ALootbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootbox();

	UPROPERTY(visibleAnywhere)
		UStaticMeshComponent* Mesh;

	UFUNCTION(BlueprintCallable)//BlueprintImplementableEvent)
		void SpawnRandomPotion();

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BPPotion1;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BPPotion2;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> BPPotion3;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
