// Copyright by Stiner.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PugaCharacterAbilitySet.generated.h"

/**
 * 입력과 Ability의 Binding
 */
USTRUCT()
struct FPugaCharacterAbilityBindInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = BindInfo)
	TObjectPtr<class UInputAction> InputAction;
	
	UPROPERTY(EditAnywhere, Category = BindInfo)
	TSubclassOf<class UPugaCharacterAbility> GameplayAbilityClass;
};

/**
 * 캐릭터에 부여할 Ability 모음
 */
UCLASS()
class PUGA_API UPugaCharacterAbilitySet : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = AbilitySet)
	TArray<FPugaCharacterAbilityBindInfo> BindInfos;

public:
	void GiveAbilities(class UAbilitySystemComponent* AbilitySystemComponent) const;
};
