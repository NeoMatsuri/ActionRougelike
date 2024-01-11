// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ARAttributeComponent.generated.h"

// We are declaring a custom event (Like for example OnComponentBeginOverlap). We can have any number of needed params. We begin by first naming the event using the letter F as the naming convetion and we seperate the type of parameter and the name with a comma. 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*, InstigatorActor, UARAttributeComponent*, OwningComp, float, NewHealth, float, Delta);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGELIKE_API UARAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	static UARAttributeComponent* GetAttributes(AActor* FromActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (DisplayName ="IsAlive"))
	static bool IsActorAlive(AActor* Actor);

	

	UARAttributeComponent();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
	float MaxHealth;

public:	

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor * InstigatorActor);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;


	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(AActor* InstigatorActor, float Delta);

	UFUNCTION(BlueprintCallable)
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable)
	bool IsLowHealth() const;

	UFUNCTION(BlueprintCallable)
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
	bool IsMaxHealth() const;

};
