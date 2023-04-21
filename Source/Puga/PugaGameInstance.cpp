// Copyright by Stiner.

#include "PugaGameInstance.h"

DECLARE_LOG_CATEGORY_EXTERN(PugaGameLog, Log, All);


void UPugaGameInstance::Init()
{
    UE_LOG(PugaGameLog, Log, TEXT("[PugaGameInstance] Initialize"))
    Super::Init();
}

void UPugaGameInstance::Shutdown()
{
    UE_LOG(PugaGameLog, Log, TEXT("[PugaGameInstance] Shutdown"))
    Super::Shutdown();
}
