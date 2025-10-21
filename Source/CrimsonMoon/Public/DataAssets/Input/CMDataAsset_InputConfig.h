// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "CMDataAsset_InputConfig.generated.h"

struct FCMInputActionConfig;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class CRIMSONMOON_API UCMDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FCMInputActionConfig> NativeInputActions;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FCMInputActionConfig> AbilityInputActions;
	
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag) const;
	
};
