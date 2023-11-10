// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARTurret.generated.h"

class UArrowComponent;

UCLASS()
class ACTIONROUGELIKE_API AARTurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UArrowComponent* ArrowComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	FTimerHandle TimerHandle_PrimaryAttack;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack();

};
