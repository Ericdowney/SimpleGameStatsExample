// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StatConstants.generated.h"

UCLASS(BlueprintType)
class STATPLUGINEXAMPLE_API UStatConstants : public UObject
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintPure, Category="Stat Constants")
    static FName GetStatName_GameTime() { return FName("Game Time"); }
    
    UFUNCTION(BlueprintPure, Category="Stat Constants")
    static FName GetStatName_EnemiesDefeated() { return FName("Enemies Defeated"); }
    
    UFUNCTION(BlueprintPure, Category="Stat Constants")
    static FName GetStatName_GunsCollected() { return FName("Guns Collected"); }
};
