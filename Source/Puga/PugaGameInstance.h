// Copyright by Stiner.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PugaGameInstance.generated.h"


/**
 * Puga 게임 인스턴스
 */
UCLASS()
class PUGA_API UPugaGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void Init() override;
	virtual void Shutdown() override;
};
