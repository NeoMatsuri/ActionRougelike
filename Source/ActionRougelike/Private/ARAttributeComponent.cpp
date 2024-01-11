// Fill out your copyright notice in the Description page of Project Settings.


#include "ARAttributeComponent.h"
#include "Math/UnrealMathUtility.h"
#include <ARGameModeBase.h>



// Sets default values for this component's properties
UARAttributeComponent::UARAttributeComponent()
{
	MaxHealth = 100.f;
	Health = MaxHealth;
}

bool UARAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool UARAttributeComponent::IsLowHealth() const
{
	return Health <= MaxHealth / 2;
}

float UARAttributeComponent::GetMaxHealth() const
{
	return MaxHealth;
}

bool UARAttributeComponent::IsMaxHealth() const
{
	return Health >= MaxHealth;
}


bool UARAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetMaxHealth());
}

bool UARAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}


	float OldHealth = Health; 

	Health = FMath::Clamp(Health + Delta, 0.0f, MaxHealth);

	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	//Died
	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		AARGameModeBase* GM = GetWorld()->GetAuthGameMode<AARGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}


	return ActualDelta != 0;
}

UARAttributeComponent* UARAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return FromActor->FindComponentByClass<UARAttributeComponent>();
	}

	return nullptr;
}

bool UARAttributeComponent::IsActorAlive(AActor* Actor)
{
	UARAttributeComponent* AttributeComp = GetAttributes(Actor);
	
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}
