// Fill out your copyright notice in the Description page of Project Settings.


#include "ARTurret.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AARTurret::AARTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArrowComp = CreateDefaultSubobject<UArrowComponent>("ArrowComp");
	ArrowComp->SetVisibility(true);
}

// Called when the game starts or when spawned
void AARTurret::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AARTurret::Attack, 2.0f, true, 5.0f);
	
}

// Called every frame
void AARTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetTargetLocation());;
	ArrowComp->SetWorldRotation(LookAtRot, false, nullptr, ETeleportType::None);
	
}

void AARTurret::Attack()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = Cast<APawn>(this);


	FTransform SpawnTM = FTransform(GetActorRotation(), GetActorLocation());
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);

}