// Copyright by Stiner.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/EngineSubsystem.h"
#include "PugaEngineSubsystem.generated.h"


UCLASS()
class PUGA_API UPugaEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
};
