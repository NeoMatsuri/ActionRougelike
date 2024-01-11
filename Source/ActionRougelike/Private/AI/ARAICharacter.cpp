// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ARAICharacter.h"
#include "AIController.h"
#include "ARAttributeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "BrainComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "ARWorldUserWidget.h"
#include "Components/CapsuleComponent.h"
AARAICharacter::AARAICharacter()
{
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

	AttributeComp = CreateDefaultSubobject<UARAttributeComponent>("AttributeComp");
	this->AddInstanceComponent(AttributeComp);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	TimeToHitParamName = "TimeToHit";
}

void AARAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PawnSensingComp->OnSeePawn.AddDynamic(this, &AARAICharacter::OnPawnSeen);

	AttributeComp->OnHealthChanged.AddDynamic(this, &AARAICharacter::OnHealthChanged);
}

void AARAICharacter::OnPawnSeen(APawn* Pawn)
{
	
	SetTargetActor(Pawn);
	DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);
	
}

void AARAICharacter::SetTargetActor(AActor* NewTarget)
{
	AAIController* AIC = Cast<AAIController>(GetController());
	if (AIC)
	{
		AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
	}


}

void AARAICharacter::OnHealthChanged(AActor* InstigatorActor, UARAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.0f)
	{
		if (InstigatorActor != this)
		{
			SetTargetActor(InstigatorActor);
		}
		
		if (ActiveHealthBar == nullptr)
		{
			ActiveHealthBar = CreateWidget<UARWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
			if (ActiveHealthBar)
			{
				ActiveHealthBar->AttachedActor = this;
				ActiveHealthBar->AddToViewport();
			}
		}
		
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		if (NewHealth <= 0.0f)
		{
			// Stop BT
			AAIController* AIC = Cast<AAIController>(GetController());
			if (AIC)
			{
				AIC->GetBrainComponent()->StopLogic("Killed");
			}

			//Ragdoll
			GetMesh()->SetAllBodiesSimulatePhysics(true);
			GetMesh()->SetCollisionProfileName("Ragdoll");

			GetCapsuleComponent()->DestroyComponent();
			
			// Set Lifespan
			SetLifeSpan(10.0f);
		}
	}
}

void AARAICharacter::HealSelf(float Amount /*Amount = 100*/)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}


