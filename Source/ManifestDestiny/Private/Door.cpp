// Fill out your copyright notice in the Description page of Project Settings.

#include "Door.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"


// Sets default values
UDoor::UDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void UDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
/*void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
void UDoor::MoveDoor(FRotator endRot, float speed)
{
	stopRot = endRot;

	FTimerDynamicDelegate closeDoorEvent;
	closeDoorEvent.BindUFunction(this, "TimerCall"); //binds the "TimerCall" function to the move door timer

	GetWorld()->GetTimerManager().SetTimer(moveDoorHandle, closeDoorEvent, speed, true);


	//else if(startY)
	
	//(new FAutoDeleteAsyncTask<FCloseDoor>(60.0f, startYaw, -1, this))->StartBackgroundTask();
}
void UDoor::TimerCall()
{
	//getrotation
	FRotator outputRot = ((GetComponentRotation() * 0.95) + (stopRot * 0.05));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Start -> " + GetComponentRotation().ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("End -> " + stopRot.ToString()));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Output -> " + outputRot.ToString()));
	}
	SetWorldRotation(outputRot);
	//SetRelativeRotation(outputRot);
	if (outputRot == stopRot)
	{
		GetWorld()->GetTimerManager().ClearTimer(moveDoorHandle);
	}
}

