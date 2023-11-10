// Fill out your copyright notice in the Description page of Project Settings.


#include "ARAttributeComponent.h"

// Sets default values for this component's properties
UARAttributeComponent::UARAttributeComponent()
{
	Health = 100;
}


bool UARAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta; 

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}


