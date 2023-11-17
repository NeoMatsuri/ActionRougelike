// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARGameplayInterface.h"
#include "ARPowerUpBaseClass.generated.h"

class UStaticMeshComponent;
class USphereComponent;


UCLASS()
class ACTIONROUGELIKE_API AARPowerUpBaseClass : public AActor, public IARGameplayInterface

{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AARPowerUpBaseClass();

	//void Interact_Implementation(APawn* InstigatorPawn);

public: 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
