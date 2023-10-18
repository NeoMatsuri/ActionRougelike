// Fill out your copyright notice in the Description page of Project Settings.


#include "ARExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
AARExplosiveBarrel::AARExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetSimulatePhysics(true);
	RootComponent = MeshComp;

	ForceComp = CreateDefaultSubobject<URadialForceComponent>("ForceComp");
	ForceComp->SetupAttachment(MeshComp);

	ForceComp->SetAutoActivate(false);

	ForceComp->Radius = 750.0f;
	ForceComp->ImpulseStrength = 2500.0f;
	ForceComp->bImpulseVelChange = true; 

	ForceComp->AddCollisionChannelToAffect(ECC_WorldDynamic);

}

void AARExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComp->OnComponentHit.AddDynamic(this, &AARExplosiveBarrel::OnActorHit);
}

void AARExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}

// Called when the game starts or when spawned
//void AARExplosiveBarrel::BeginPlay()
//{
//	Super::BeginPlay();
	
//}


// Called every frame
//void AARExplosiveBarrel::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);

//}

