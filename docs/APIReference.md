# API Reference

This document provides a reference for all public classes, structs, properties, functions, and events exposed by the **SimpleGameStats** plugin.

**Please Note:** For blueprint compatibility reasons, functions that return values use out reference parameters named `Result`.

## **Modules**

- **SimpleGameStats**: Runtime module containing core stat logic.
- **SimpleGameStatsEditor**: Editor module providing UI for debugging stats.
- **SimpleGameStatsTests**: Editor test module with automated unit tests.

## **Classes**

### `USimpleGameStatsSubsystem`
`UGameInstanceSubsystem` that manages all registered stats at runtime.

**Events**
- `OnGameStatChangeEvent (USimpleGameStat* Stat)`
- `OnGameStatMilestoneReachedEvent (USimpleGameStat* Stat, USimpleGameStatMilestone* Milestone)`

**Functions**
- `void GetStorage(FSimpleGameStatsSubsystemStorage& Result) const`
- `void GetGameStats(TMap<FName, USimpleGameStat*>& Result) const`
- `void GetGameStat(FName StatName, USimpleGameStat*& Result) const`
- `void RegisterGameStats(USimpleGameStatsDefinition* Definitions)`
- `void SetStatValue(FName StatName, float NewValue, bool bBroadcastEvent = true)`
- `void IncrementStat(FName StatName, float Amount = 1, bool bBroadcastEvent = true)`
- `void DecrementStat(FName StatName, float Amount = 1, bool bBroadcastEvent = true)`
- `void RemoveGameStat(const FName StatName, bool& Result)`
- `void RemoveAllGameStats()`
- `void InflateFromStorage(FSimpleGameStatsSubsystemStorage Storage)`

### `USimpleGameStat`
`UObject` subclass that represents a single tracked stat and its milestones.

**Properties**
- `FName StatName`: Name of the stat.
- `float Value`: Current value of the stat.
- `TArray<USimpleGameStatMilestone*> Milestones`: Collection of milestones associated with this stat.

**Events**
- `OnChangeEvent (USimpleGameStat* Stat)`: Fired when the stat’s value changes.
- `OnMilestoneReachedEvent (USimpleGameStat* Stat, USimpleGameStatMilestone* Milestone)`: Fired when a milestone is reached.

**Functions**
- `void GetStorage(FSimpleGameStatStorage& Result)`
- `void GetValue(float& Result) const`
- `void SetValue(float NewValue, bool bBroadcastEvent = true)`
- `void Increment(float Amount = 1, bool bBroadcastEvent = true)`
- `void Decrement(float Amount = 1, bool bBroadcastEvent = true)`
- `void InflateFromStorage(FSimpleGameStatStorage Storage)`

### `USimpleGameStatMilestone`
`UObject` subclass that represents a single milestone for a stat.

**Properties**
- `FName MilestoneName`: Name of the milestone.
- `float TargetValue`: Required value to reach this milestone.
- `bool bReached`: Whether the milestone has been reached.
- `FDateTime ReachedTimestamp`: UTC timestamp when reached.

### `USimpleGameStatsDefinition`
`UDataAsset` that defines all stats and their milestones for registration.

**Properties**
- `TArray<FSimpleGameStatDefinition> StatDefinitions`: List of all stat definitions.

## **Structs**

### `FSimpleGameStatDefinition`
Defines a stat and its initial properties.

- `FName StatName`
- `float DefaultValue`
- `TArray<FSimpleGameStatMilestoneDefinition> Milestones`

### `FSimpleGameStatMilestoneDefinition`
Defines a milestone within a stat definition.

- `FName MilestoneName`
- `float TargetValue`

### `FSimpleGameStatStorage`
Runtime storage for a stat.

- `FName StatName`
- `float Value`
- `TArray<FSimpleGameStatMilestoneStorage> Milestones`

### `FSimpleGameStatMilestoneStorage`
Runtime storage for a milestone.

- `FName MilestoneName`
- `float TargetValue`
- `bool bReached`
- `FDateTime ReachedTimestamp`

### `FSimpleGameStatsSubsystemStorage`
Runtime storage for the subsystem.

- `TArray<FSimpleGameStatStorage> GameStats`
