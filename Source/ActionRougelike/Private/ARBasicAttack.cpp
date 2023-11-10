// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBasicAttack.h"
#include "Components/SphereComponent.h"
#include "ARAttributeComponent.h"



AARBasicAttack::AARBasicAttack()
{
	SphereComp->SetSphereRadius(20.0f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AARBasicAttack::OnActorOverlap);
	
}

void AARBasicAttack::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UARAttributeComponent* AttributeComp = Cast<UARAttributeComponent>(OtherActor->GetComponentByClass(UARAttributeComponent::StaticClass()));
		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-20.0f);

			Destroy();
		}
	}
}

void AARBasicAttack::BeginPlay()
{
	Super::BeginPlay();
}



void AARBasicAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
