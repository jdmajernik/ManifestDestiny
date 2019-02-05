// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerWeapon.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Engine/CollisionProfile.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APlayerWeapon::APlayerWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerWeapon::FireWeapon()
{
	FireParticles();

	TArray<FHitResult> outHit;
	
	
	APawn* player = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector playerLoc = player->GetActorLocation();
	FVector playerForward = player->GetActorForwardVector();


	//Sweep variables
	FVector startPos = this->GetActorLocation();
	FQuat rotation = this->GetActorRotation().Quaternion();
	FVector endPos = startPos + (this->GetActorForwardVector() * 1000);
	
	DrawDebugLine(GetWorld(), startPos, endPos, FColor::Cyan, false, 1.0);

	//FCollisionQueryParams traceParams(FName(TEXT("GunFire Trace")), true, GetWorld()->GetFirstPlayerController());
	//traceParams.bTraceComplex = true;

	FCollisionObjectQueryParams objectList;
	objectList.AddObjectTypesToQuery(ECC_Pawn);
	//objectList.RemoveObjectTypesToQuery(GetWorld()->GetFirstPlayerController());

	if (GetWorld()->SweepMultiByObjectType(outHit, startPos, endPos, rotation, objectList ,FCollisionShape::MakeSphere(150)))
	{
		float closestDotProd;
		TWeakObjectPtr<AActor> closestActor;
		for (FHitResult hit : outHit)
		{


			//if there is a hit for the enemy type
			if (hit.GetActor() != NULL)
			{
				//checks if the object found is NOT the player
				if (hit.Actor != GetWorld()->GetFirstPlayerController()->GetCharacter())
				{
					FVector enemyLoc = hit.Actor->GetActorLocation();

					DrawDebugLine(GetWorld(), playerLoc, enemyLoc, FColor::Red, false, 10, 0, 4);

					FVector a = enemyLoc - playerLoc;
					a.Normalize();
					float dotProd = FVector::DotProduct(a, playerForward);

					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::SanitizeFloat(dotProd));
					}

					//checks if the actor is in range
					if (dotProd > 0.45 && dotProd < 1.35)
					{
						if (!closestActor.IsValid())
						{
							closestActor = hit.Actor;
							closestDotProd = dotProd;
							DrawDebugLine(GetWorld(), playerLoc, enemyLoc, FColor::Emerald, false, 0.3, -1, 10);
						}
						else
						{
							if (abs(.9 - dotProd) > abs(0.9 - closestDotProd))
							{
								closestActor = hit.Actor;
								closestDotProd = dotProd;
								DrawDebugLine(GetWorld(), playerLoc, enemyLoc, FColor::Emerald, false, 0.2, -1, 10);
							}
						}
					}
					
					
				}

				else
				{
					if (GEngine)
					{
						//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("Found enemy" + hit.Actor->GetName()));
					}
				}

			}
			else
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("No actor found?"));
				}
			}
		}
	}
	
}

// Called when the game starts or when spawned
void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}
void APlayerWeapon::FireParticles_Implementation()
{

}
// Called every frame
void APlayerWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

