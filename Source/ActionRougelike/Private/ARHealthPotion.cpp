// Fill out your copyright notice in the Description page of Project Settings.


#include "ARHealthPotion.h"
#include "ARAttributeComponent.h"

AARHealthPotion::AARHealthPotion()
{

}

void AARHealthPotion::SetInnactive()
{
	BaseMesh->SetVisibility(false, true);
	IsActive = false;
}

void AARHealthPotion::SetActive()
{
	BaseMesh->SetVisibility(true, true);
	IsActive = true;
}

void AARHealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	UARAttributeComponent* AttributeComp = Cast<UARAttributeComponent>(InstigatorPawn->GetComponentByClass(UARAttributeComponent::StaticClass()));
	
	if (AttributeComp && IsActive && AttributeComp->IsMaxHealth() != true)
	{
		AttributeComp->ApplyHealthChange(this, HealingAmount);
		SetInnactive();
		GetWorldTimerManager().SetTimer(TimerHandle_CoolDown, this, &AARHealthPotion::SetActive, CoolDown);
	}

	else
	{
		return;
	}
}
