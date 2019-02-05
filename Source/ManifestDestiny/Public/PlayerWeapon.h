// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerWeapon.generated.h"

UENUM(BlueprintType)
enum class WeaponType : uint8
{
	RaycastWeapon,
	SpawnWeapon,
	FlamerWeapon
};
UENUM(BlueprintType)
enum class WeaponState : uint8
{
	Idle,
	SpoolUp,
	Firing
};


UCLASS()
class MANIFESTDESTINY_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon();

	UFUNCTION(BlueprintCallable, Category = "CodedWeapon")
		void FireWeapon();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void FireParticles();

	void FireParticles_Implementation();

	UPROPERTY(BlueprintReadWrite)
		WeaponType type;

	UPROPERTY(BlueprintReadWrite)
		float range;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* FirePoint;
	UPROPERTY(BlueprintReadWrite)
		WeaponState state;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
