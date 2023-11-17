// Fill out your copyright notice in the Description page of Project Settings.


#include "ARPowerUpBaseClass.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AARPowerUpBaseClass::AARPowerUpBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AARPowerUpBaseClass::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AARPowerUpBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*
void Interact_Implementation(APawn* InstigatorPawn)
{
	return;

}
*/