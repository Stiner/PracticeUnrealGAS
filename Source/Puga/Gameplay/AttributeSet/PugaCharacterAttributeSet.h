// Copyright by Stiner.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PugaCharacterAttributeSet.generated.h"

/**
 * 캐릭터 능력치
 */
UCLASS()
class PUGA_API UPugaCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attributes")
	float Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attributes")
	float Mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attributes")
	float Stamina;
};
