// Copyright by Stiner.


#include "PugaGameplayAbility_Attack.h"

bool UPugaGameplayAbility_Attack::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UE_LOG(LogTemp, Log, TEXT("Ability_Attack CanActivateAbility"));
	return true;
}

bool UPugaGameplayAbility_Attack::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
{
	UE_LOG(LogTemp, Log, TEXT("Ability_Attack CheckCost"));
	return true;
}

void UPugaGameplayAbility_Attack::InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	UE_LOG(LogTemp, Log, TEXT("Ability_Attack Input pressed!"));
}

void UPugaGameplayAbility_Attack::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
}

void UPugaGameplayAbility_Attack::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UE_LOG(LogTemp, Log, TEXT("Activating UPugaGameplayAbilityAttack. Action ATTACK!!"))
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}
