// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FinalAssignmentCharacter.generated.h"

UCLASS(Blueprintable)
class AFinalAssignmentCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AFinalAssignmentCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	UPROPERTY(BlueprintReadWrite)
		int HP = 100;

	UPROPERTY(BlueprintReadWrite)
		int Mana = 100;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* ProjectileOrigin;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileActor;

	void ShootProjectile();

	UFUNCTION(BlueprintCallable)
	void OnDamage(int damage);

	UFUNCTION(BlueprintCallable)
	void OnManaCost(int cost);

	UFUNCTION(BlueprintCallable)
	void Boom();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;
};

