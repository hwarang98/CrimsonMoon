// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "CMStructTypes.generated.h"

class UCMPlayerGameplayAbility;

USTRUCT(BlueprintType)
struct FCMInputActionConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction;

	bool IsValid() const;
};

USTRUCT(BlueprintType)
struct FCMPlayerAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UCMPlayerGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};