// Fill out your copyright notice in the Description page of Project Settings.


#include "ARTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "ARAttributeComponent.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ARTargetDummy)

// Sets default values
AARTargetDummy::AARTargetDummy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;
	
	AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");
}
void AARTargetDummy::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//Trigger when health is changed (damage/healing)
	AttributeComp->OnHealthChanged.AddDynamic(this, &AARTargetDummy::OnHealthChanged);
}

void AARTargetDummy::OnHealthChanged(AActor* InstigatorActor, UARAttributeComponent* OwningComp, float NewHealth, float Delta)
{

	if (Delta < 0.0f)
	{
		MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
	}
}



