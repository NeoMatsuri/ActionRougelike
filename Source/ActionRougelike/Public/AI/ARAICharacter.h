// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ARAICharacter.generated.h"

class UPawnSensingComponent;
class UARAttributeComponent;
class UUserWidget;
class UARWorldUserWidget;
UCLASS()
class ACTIONROUGELIKE_API AARAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AARAICharacter();

protected:

	UARWorldUserWidget* ActiveHealthBar;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;
	
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(BlueprintReadOnly, Category = "Components")
	UARAttributeComponent* AttributeComp;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void SetTargetActor(AActor* NewTarget);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UARAttributeComponent* OwningComp, float NewHealth, float Delta);

public:

	UFUNCTION()
	void HealSelf(float Amount = 100);
};
