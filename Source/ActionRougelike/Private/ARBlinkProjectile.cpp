// Fill out your copyright notice in the Description page of Project Settings.


#include "ARBlinkProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


AARBlinkProjectile::AARBlinkProjectile()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.f;
	
}



void AARBlinkProjectile::BeginPlay()
{

	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_DelayDetonate, this, &AARBlinkProjectile::Explode, DetonateDelay);
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

}



void AARBlinkProjectile::Explode_Implementation()
{
	// Clear timer if the Explode was already called through another source like OnActorHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());

	EffectComp->DeactivateSystem();
	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &AARBlinkProjectile::TeleportInstigator, TeleportDelay);

}

void AARBlinkProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();

	if (ensure(ActorToTeleport))
	{

		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);

	}

}


