// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CMAbilitySystemComponent.generated.h"

/**
 * @class UCMAbilitySystemComponent
 * @brief Crimson Moon 게임의 확장된 Ability System Component 클래스.
 *
 * `UCMAbilitySystemComponent`는 게임플레이에서 능력 시스템을 관리하기 위한 클래스입니다.
 * 기본 UAbilitySystemComponent를 상속받아 사용자 정의 기능을 확장합니다.
 */
UCLASS()
class CRIMSONMOON_API UCMAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable)
	void ServerAddLooseGameplayTag(FGameplayTag TagToAdd);
	
	void OnAbilityInputPressed(const FGameplayTag& InputTag);
	void OnAbilityInputReleased(const FGameplayTag& InputTag);
};
