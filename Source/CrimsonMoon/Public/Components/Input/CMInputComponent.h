// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/CMDataAsset_InputConfig.h"
#include "Structs/CMStructTypes.h"
#include "CMInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class CRIMSONMOON_API UCMInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserObject, typename CallbackFunction>
	void BindNativeInputAction(
		const UCMDataAsset_InputConfig* InputConfig, // 입력 액션들이 들어있는 DataAsset
		const FGameplayTag& InputTag, // 바인딩하고 싶은 InputTag (예: Input.Move)
		ETriggerEvent TriggerEvent, // 어떤 입력 트리거에 반응할지 (Pressed, Released 등)
		UserObject* ContextObject, // 바인딩 대상 객체 (예: this)
		CallbackFunction Callback // 바인딩할 함수 포인터 (예: &AMyCharacter::Move)
	);

	template <class UserObject, typename CallbackFunction>
	void BindAbilityInputAction(
		const UCMDataAsset_InputConfig* InputConfig, // 입력 액션들이 들어있는 DataAsset
		UserObject* ContextObject, // 바인딩 대상 객체 (예: this)
		CallbackFunction InputPressedFunc,
		CallbackFunction InputReleasedFunc
	);
};

template <class UserObject, typename CallbackFunction>
void UCMInputComponent::BindNativeInputAction(
	const UCMDataAsset_InputConfig* InputConfig,
	const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent,
	UserObject* ContextObject,
	CallbackFunction Callback
)
{
	checkf(InputConfig, TEXT("InputConfig 데이터 에셋이 비어 있습니다! [BindNativeInputAction]"));

	if (UInputAction* FoundAction = InputConfig->FindNativeInputActionByTag(InputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Callback);
	}
}

template <class UserObject, typename CallbackFunction>
void UCMInputComponent::BindAbilityInputAction(
	const UCMDataAsset_InputConfig* InputConfig,
	UserObject* ContextObject,
	CallbackFunction InputPressedFunc,
	CallbackFunction InputReleasedFunc
)
{
	checkf(InputConfig, TEXT("InputConfig 데이터 에셋이 비어 있습니다! [BindAbilityInputAction]"));

	for (const FCMInputActionConfig& AbilityInputActionConfig : InputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid())
		{
			continue;
		}

		BindAction(
			AbilityInputActionConfig.InputAction,
			ETriggerEvent::Started,
			ContextObject,
			InputPressedFunc,
			AbilityInputActionConfig.InputTag
		);
		
		BindAction(
			AbilityInputActionConfig.InputAction,
			ETriggerEvent::Completed,
			ContextObject,
			InputReleasedFunc,
			AbilityInputActionConfig.InputTag
		);
	}
}
