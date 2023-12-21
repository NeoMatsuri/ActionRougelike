// Fill out your copyright notice in the Description page of Project Settings.



#include "ARGameModeBase.h"
#include "AI/ARAICharacter.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "ARAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"





AARGameModeBase::AARGameModeBase()
{
	SpawnTimerInterval = 2.0f;
}

void AARGameModeBase::StartPlay()
{
	Super::StartPlay();

	//Continuos time to spawn in more bots. 
	//Actial amount of bots and wether its allowed to spaqwn determined by spawn logic later in chain...
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &AARGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void AARGameModeBase::KillAll()
{
	for (AARAICharacter* Bot : TActorRange<AARAICharacter>(GetWorld()))
	{
		UARAttributeComponent* AIAttributeComp = UARAttributeComponent::GetAttributes(Bot);
		if (ensure(AIAttributeComp) && AIAttributeComp->IsAlive())
		{
			AIAttributeComp->Kill(this); //@fixme: pass in player for kill credit 
		}
	}
}

void AARGameModeBase::SpawnBotTimerElapsed()
{
	int32 NumOfAliveBots = 0;
	for (AARAICharacter* Bot : TActorRange<AARAICharacter>(GetWorld()))
	{
		UARAttributeComponent* AIAttributeComp = UARAttributeComponent::GetAttributes(Bot);
		if (ensure(AIAttributeComp) && AIAttributeComp->IsAlive())
		{
			++NumOfAliveBots;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Found %i alive bots"), NumOfAliveBots);

	float MaxBotCount = 10.0f;

	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NumOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Log, TEXT("At Max bot Capacity. SKipping bot Spawn."), NumOfAliveBots);
		return;
	}


	UEnvQueryInstanceBlueprintWrapper* QueryInstance =  UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
	QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &AARGameModeBase::OnQueryCompleted);
	}
}

void AARGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn Bot EQS Query Failed"));
		return;
	}


	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);
		DrawDebugSphere(GetWorld(), Locations[0], 50.0f, 20, FColor::Blue, false, 60.0f);
	}
}
