// Copyright by Stiner.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PugaCharacterAbilitySet.generated.h"



/**
 * �Է°� Ability�� Binding
 */
USTRUCT()
struct FPugaCharacterAbilityBindInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = BindInfo)
	TSubclassOf<class UGameplayAbility> GameplayAbilityClass;
};

/**
 * ĳ���Ϳ� �ο��� Ability ����
 */
UCLASS()
class PUGA_API UPugaCharacterAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = AbilitySet)
	TArray<FPugaCharacterAbilityBindInfo>	Abilities;

public:
	void GiveAbilities(class UAbilitySystemComponent* AbilitySystemComponent) const;
};
