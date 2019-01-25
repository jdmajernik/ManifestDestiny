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

UCLASS()
class MANIFESTDESTINY_API APlayerWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerWeapon();

	UFUNCTION(BlueprintCallable, Category = "CodedWeapon")
		void FireWeapon();

	UPROPERTY(BlueprintReadWrite)
		WeaponType type;

	UPROPERTY(BlueprintReadWrite)
		float range;
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* FirePoint;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
