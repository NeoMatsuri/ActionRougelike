// Fill out your copyright notice in the Description page of Project Settings.


#include "ARTeleport.h"


AARTeleport::AARTeleport()
{
	PrimaryActorTick.bCanEverTick = true;
	
	

}

void AARTeleport::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(.5f);

	

}

void AARTeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
