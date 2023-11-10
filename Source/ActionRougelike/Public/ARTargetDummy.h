// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARTargetDummy.generated.h"

class UARAttributeComponent;


UCLASS()
class ACTIONROUGELIKE_API AARTargetDummy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AARTargetDummy();

	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(VisibleAnywhere, Transient)
	TObjectPtr<UARAttributeComponent> AttributeComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> MeshComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UARAttributeComponent* OwningComp, float NewHealth, float Delta);



	

};