// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ARBTTaskNode_HealSelf.generated.h"

/**
 * 
 */
class UARAttributeComponent;

UCLASS()
class ACTIONROUGELIKE_API UARBTTaskNode_HealSelf : public UBTTaskNode
{
	GENERATED_BODY()

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
