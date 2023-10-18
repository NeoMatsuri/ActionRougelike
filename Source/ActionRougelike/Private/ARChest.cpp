// Fill out your copyright notice in the Description page of Project Settings.


#include "ARChest.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AARChest::AARChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>("Lid");
	LidMesh->SetupAttachment(RootComponent);

	TargetPitch = 110;

}

void AARChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0, 0));
}
// Called when the game starts or when spawned
void AARChest::BeginPlay()
{
	Super::BeginPlay();
	
}



// Called every frame
void AARChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

