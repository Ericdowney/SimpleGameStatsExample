# Storage

**SimpleGameStats** provides a structure meant to be used in conjunction with Unreal's `USaveGame` class, as well as a simple API to save and load stat data. This allows you to save game stat data however you like.

*All functionality is supported by both Blueprints and C++.*

## FSimpleGameStatsSubsystemStorage

The `FSimpleGameStatsSubsystemStorage` struct can store the list of registered stats with their values and milestones.

To use this in your project, simply add this to your `USaveGame` subclass:

```c++
UPROPERTY(/* Property Config */)
FSimpleGameStatsSubsystemStorage Stats;
```

### Saving Data

The `USimpleGameStatsSubystem` provides two APIs for storage. The first is to retrieve the current state as storage:

```c++
GetStorage(FSimpleGameStatsSubsystemStorage& Result)
```

This function collects all registered stats, converts them to storage, and assigns them to the `Result` reference. You can use the `Result` to set the property on your `USaveGame` subclass.

### Loading Data

The second storage API loads stat data from the storage struct:

```c++
InflateFromStorage(FSimpleGameStatsSubsystemStorage Storage)
```

Once called, this function will load all game stats defined in `Storage`.

**Please note:**, this function clears the current list of stats. If you already have stats registered, they will be removed. Only stats defined in `Storage` will be tracked.