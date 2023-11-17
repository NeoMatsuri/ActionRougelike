// Fill out your copyright notice in the Description page of Project Settings.


#include "ARProjectileBaseClass.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AARProjectileBaseClass::AARProjectileBaseClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &AARProjectileBaseClass::OnActorHit);
	RootComponent = SphereComp;
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);


	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000;

	ImpactSFX = CreateDefaultSubobject<USoundBase>("ImpactSFX");
}

// Called when the game starts or when spawned
void AARProjectileBaseClass::BeginPlay()
{
	Super::BeginPlay();

}
	


// Called every frame
void AARProjectileBaseClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AARProjectileBaseClass::OnActorHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

void AARProjectileBaseClass::Explode_Implementation()
{
	if (IsValid(SphereComp))
	{
		
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactVFX, GetActorLocation(), GetActorRotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSFX, GetActorLocation());
		EffectComp->DeactivateSystem();

		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);

		MoveComp->StopMovementImmediately();
		SetActorEnableCollision(false);

		Destroy();
	}
}

void AARProjectileBaseClass::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);

}


