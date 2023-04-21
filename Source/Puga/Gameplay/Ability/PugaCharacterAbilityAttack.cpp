// Copyright by Stiner.


#include "PugaCharacterAbilityAttack.h"

bool UPugaCharacterAbilityAttack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UE_LOG(LogTemp, Log, TEXT("Ability_Attack CanActivateAbility"));
	return true;
}

bool UPugaCharacterAbilityAttack::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	UE_LOG(LogTemp, Log, TEXT("Ability_Attack CheckCost"));
	return true;
}

void UPugaCharacterAbilityAttack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	UE_LOG(LogTemp, Log, TEXT("Ability_Attack Input pressed!"));
}

void UPugaCharacterAbilityAttack::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
}

void UPugaCharacterAbilityAttack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Log, TEXT("Activating UPugaGameplayAbilityAttack. Action ATTACK!!"))
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
