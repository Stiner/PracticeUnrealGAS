// Copyright by Stiner.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PugaGameInstance.generated.h"


/**
 * Puga ���� �ν��Ͻ�
 */
UCLASS()
class PUGA_API UPugaGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:
	virtual void Init() override;
	virtual void Shutdown() override;
};
