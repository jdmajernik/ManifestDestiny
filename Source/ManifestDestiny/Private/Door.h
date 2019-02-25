// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Async/AsyncWork.h"
#include "Door.generated.h"

UCLASS()
class UDoor : public UChildActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void MoveDoor(FRotator endRot, float speed);
	UFUNCTION()
		void TimerCall();

	FRotator stopRot;
	FTimerHandle moveDoorHandle;//the timer handle for moving the door

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	
	
};


class FCloseDoor : public FNonAbandonableTask {
	friend class FAutoDeleteAsyncTask<FCloseDoor>;

public:
	FCloseDoor(float CloseDuration, float doorStartAngle, int closeSpeed, UChildActorComponent* doorActor) :
		closeTime(CloseDuration),
		startAngle(doorStartAngle),
		closeDir(closeSpeed),
		door(doorActor),
		time(0)
	{}
protected:
	float closeTime;
	float startAngle;
	int closeDir;
	float time;
	UChildActorComponent* door;

public:
	void DoWork()
	{
		while (time < closeTime)
		{
			FRotator newRotation = FRotator(0.0, 0.0, closeDir);
			FQuat newQuat = FQuat(newRotation);
			door->AddLocalRotation(newQuat, false, 0, ETeleportType::None);
			time++;
		}
	}

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FCloseDoor, STATGROUP_ThreadPoolAsyncTasks);
	}
};
