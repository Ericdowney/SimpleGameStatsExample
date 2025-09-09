# Example Project - StatPluginExample

The provided example project is the Unreal Engine 5.6 First Person template provided by Epic Games. I've added `SimpleGameStats` to the Shooter template, without removing any existing functionality.

In the example project, I've registered three stats with various milestones:

* GameTime
* EnemiesDefeated
    * EnemiesDefeated.1 - AI Menace I, Target Value: 1
    * EnemiesDefeated.2 - AI Menace II, Target Value: 2
* GunsCollected
    * GunsCollected.1 - Armed and Dangerous I, Target Value: 1
    * GunsCollected.2 - Armed and Dangerous II, Target Value: 2
    * GunsCollected.3 - Armed and Dangerous III, Target Value: 3

In addition, I've added a Blueprint Compatible C++ Constants file. This avoids using "magic strings" throughout the project. Please create an equivalent in your project to avoid problems when renaming or removing stats.

**Note:** The provided example project and below examples use C++. The plugin fully supports both Blueprints and C++. The example is implemented with a mix of both.

## UStatConstants

```c++
UCLASS(BlueprintType)
class STATPLUGINEXAMPLE_API UStatConstants : public UObject
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintPure, Category="Stat Constants")
    static FName GetStatName_GameTime() { return FName("GameTime"); }
    
    UFUNCTION(BlueprintPure, Category="Stat Constants")
    static FName GetStatName_EnemiesDefeated() { return FName("EnemiesDefeated"); }
    
    UFUNCTION(BlueprintPure, Category="Stat Constants")
    static FName GetStatName_GunsCollected() { return FName("GunsCollected"); }
};
```

## AShooterGameMode

In the `BeginPlay` function on the `AShooterGameMode` class, I loaded the stat definitions asset and registered that on the `SimpleGameStatsSubsystem`:

```c++
void AShooterGameMode::BeginPlay()
{
    Super::BeginPlay();

    // ...
    
    USimpleGameStatsDefinition* Definitions = LoadObject<USimpleGameStatsDefinition>(this, TEXT("/Game/Variant_Shooter/Data/DA_StatDefinitions.DA_StatDefinitions"));
    USimpleGameStatsSubsystem* StatsSubsystem = GetGameInstance()->GetSubsystem<USimpleGameStatsSubsystem>();
    if (IsValid(StatsSubsystem)) {
        StatsSubsystem->RegisterGameStats(Definitions);
        StatsSubsystem->OnGameStatMilestoneReachedEvent.AddDynamic(this, &AShooterGameMode::HandleGameStatMilestones);
    }
}
```

## AShooterCharacter

For tracking the "GunsCollected" stat, I'm modifying the `AShooterCharacter` class, the `AddWeaponClass` function. This is the class in the example that is inherited by `BP_ShooterCharacter`, the player character.

```c++
void AShooterCharacter::AddWeaponClass(const TSubclassOf<AShooterWeapon>& WeaponClass)
{
    // do we already own this weapon?
    AShooterWeapon* OwnedWeapon = FindWeaponOfType(WeaponClass);

    if (!OwnedWeapon)
    {
        USimpleGameStatsSubsystem* StatsSubsystem = GetGameInstance()->GetSubsystem<USimpleGameStatsSubsystem>();
        if (IsValid(StatsSubsystem)) {
            StatsSubsystem->IncrementStat(UStatConstants::GetStatName_GunsCollected());
        }
        
        // ...
    }
}
```

Using the `SimpleGameStatsSubsystem`, I call `IncrementStat` for the "GunsCollected" stat every time the player picks up a new kind of weapon.

## AShooterNPC

For tracking the "EnemiesDefeated" stat, I'm modifying the `AShooterNPC` class, the `Die` function. This is the class in the example that is inherited by `BP_ShooterNPC`, the AI enemies.

```c++
void AShooterNPC::Die()
{
    // ignore if already dead
    if (bIsDead)
    {
        return;
    }

    // raise the dead flag
    bIsDead = true;

    USimpleGameStatsSubsystem* StatsSubsystem = GetGameInstance()->GetSubsystem<USimpleGameStatsSubsystem>();
    if (IsValid(StatsSubsystem)) {
        StatsSubsystem->IncrementStat(UStatConstants::GetStatName_EnemiesDefeated());
    }

    // ...
}
```

Using the `SimpleGameStatsSubsystem`, I call `IncrementStat` for the "EnemiesDefeated" stat every time the AI NPC dies.

## BP_ShooterGameMode

For tracking the "GameTime" stat, I'm modifying the `BP_ShooterGameMode` blueprint, the `Event Tick` event. I've also added a new function to retrieve the current "GameTime" stat value.

*GetGameTimeStatValue:*

![Blueprint Function: Gets the current Game Time stat value](./Images/GetGameTimeBlueprint.png)

*Event Tick:*

![Blueprint Event Tick: Adds delta time to the current Game Time stat value](./Images/SetGameTimeBlueprint.png)

In the previous screenshots, `Event Tick` uses the `GetGameTimeStatValue` function and then adds delta time, setting the stat to the new value. The same functionality can be achieved by using the `IncrementStat` function.