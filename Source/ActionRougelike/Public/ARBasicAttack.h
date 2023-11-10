// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARProjectileBaseClass.h"
#include "ARBasicAttack.generated.h"


/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AARBasicAttack : public AARProjectileBaseClass
{
	GENERATED_BODY()


protected:	

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
public:	

	AARBasicAttack();
};
