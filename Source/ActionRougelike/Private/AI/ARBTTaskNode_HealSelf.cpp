// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARBTTaskNode_HealSelf.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "ARAttributeComponent.h"


EBTNodeResult::Type UARBTTaskNode_HealSelf::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		UARAttributeComponent* AttributeComp = Cast<UARAttributeComponent>(MyPawn->GetComponentByClass(UARAttributeComponent::StaticClass()));
		if (AttributeComp == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		AttributeComp->ApplyHealthChange(MyPawn, 100.f);
		EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
