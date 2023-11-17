// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPowerUpBaseClass.h"
#include "ARHealthPotion.generated.h"


/**
 * 
 */
UCLASS()
class ACTIONROUGELIKE_API AARHealthPotion : public AARPowerUpBaseClass
{
	GENERATED_BODY()

public:

	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(EditAnywhere = "Stats")
	float HealingAmount = 50.f;
	UPROPERTY(EditDefaultsOnly, Category = "Time")
	float CoolDown = 10.0f;


	FTimerHandle TimerHandle_CoolDown;
	AARHealthPotion();
	
	
	bool IsActive = true;
	void SetInnactive();
	void SetActive();

protected:




private:


	
};
