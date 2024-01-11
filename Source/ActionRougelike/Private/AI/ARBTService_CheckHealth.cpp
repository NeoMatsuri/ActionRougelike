// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARBTService_CheckHealth.h"
#include "ARAttributeComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UARBTService_CheckHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	if (ensure(BlackboardComp))
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController))
		{
			APawn* AIPawn = MyController->GetPawn();
			if (ensure(AIPawn))
			{
				UARAttributeComponent* AttributeComp = Cast<UARAttributeComponent>(AIPawn->GetComponentByClass(UARAttributeComponent::StaticClass()));

				if (AttributeComp)
				{
					BlackboardComp->SetValueAsBool(LowHealthKey.SelectedKeyName, AttributeComp->IsLowHealth());
				}
			}

		}
	}
}

	
