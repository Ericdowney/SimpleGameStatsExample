// Copyright Epic Games, Inc. All Rights Reserved.


#include "Variant_Shooter/ShooterGameMode.h"
#include "ShooterUI.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "StatPluginExample.h"

#include "SimpleGameStat.h"
#include "SimpleGameStatMilestone.h"
#include "SimpleGameStatsSubsystem.h"
#include "SimpleGameStatsDefinition.h"

void AShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// create the UI
	ShooterUI = CreateWidget<UShooterUI>(UGameplayStatics::GetPlayerController(GetWorld(), 0), ShooterUIClass);
	ShooterUI->AddToViewport(0);
    
    // =======================
    // Load Game Stat Definitions
    // Get Subsystem From GameInstance
    // Register GameStat Definitions
    // Set `HandleGameStatMilestones` function as Milestone Delegate
    USimpleGameStatsDefinition* Definitions = LoadObject<USimpleGameStatsDefinition>(this, TEXT("/Game/Variant_Shooter/Data/DA_StatDefinitions.DA_StatDefinitions"));
    USimpleGameStatsSubsystem* StatsSubsystem = GetGameInstance()->GetSubsystem<USimpleGameStatsSubsystem>();
    if (IsValid(StatsSubsystem)) {
        StatsSubsystem->RegisterGameStats(Definitions);
        StatsSubsystem->OnGameStatMilestoneReachedEvent.AddDynamic(this, &AShooterGameMode::HandleGameStatMilestones);
    }
    // =======================
}

void AShooterGameMode::IncrementTeamScore(uint8 TeamByte)
{
	// retrieve the team score if any
	int32 Score = 0;
	if (int32* FoundScore = TeamScores.Find(TeamByte))
	{
		Score = *FoundScore;
	}

	// increment the score for the given team
	++Score;
	TeamScores.Add(TeamByte, Score);

	// update the UI
	ShooterUI->BP_UpdateScore(TeamByte, Score);
}

// Handle Milestone Reached
void AShooterGameMode::HandleGameStatMilestones(USimpleGameStat* Stat, USimpleGameStatMilestone* Milestone) {
    UE_LOG(LogStatPluginExample, Log, TEXT("Game Stat: %s || Milestone Reached: %s"), *Stat->StatName.ToString(), *Milestone->MilestoneName.ToString());
    
    // Connect to Steam / Epic Achievements
    // Connect to Analytics
}
