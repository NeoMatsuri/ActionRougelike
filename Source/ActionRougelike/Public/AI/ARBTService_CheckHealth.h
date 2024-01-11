// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ARBTService_CheckHealth.generated.h"

/**
 * 
 */

class UARAttributeComponent;
UCLASS()
class ACTIONROUGELIKE_API UARBTService_CheckHealth : public UBTService
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "Ai")
	FBlackboardKeySelector LowHealthKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
