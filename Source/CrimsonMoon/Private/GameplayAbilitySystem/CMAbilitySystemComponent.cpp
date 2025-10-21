// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/CMAbilitySystemComponent.h"

void UCMAbilitySystemComponent::ServerAddLooseGameplayTag_Implementation(FGameplayTag TagToAdd)
{
	if (!HasMatchingGameplayTag(TagToAdd))
	{
		AddLooseGameplayTag(TagToAdd);
	}
}

void UCMAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			continue;
		}

		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UCMAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid())
	{
		return;
	}

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
}
