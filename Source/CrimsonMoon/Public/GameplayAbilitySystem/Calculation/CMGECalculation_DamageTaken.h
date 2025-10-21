// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "CMGECalculation_DamageTaken.generated.h"

/**
 * @class UCMGECalculation_DamageTaken
 * @brief 피해량 계산을 처리하는 클래스입니다.
 *
 * 이 클래스는 UGameplayEffectExecutionCalculation을 상속받아, 피해량 관련 로직 및 계산식을
 * 게임플레이 시스템에 구현하기 위한 목적으로 사용됩니다.
 *
 * UCMGECalculation_DamageTaken은 게임 내에서 특정 효과나 능력치 변경으로 인해
 * 발생하는 피해량 데이터를 계산하고 처리하는 데 사용됩니다.
 *
 * 
 * - 이 클래스는 피해량 계산의 규칙이나 공식을 구현할 수 있는 확장 가능성이 있습니다.
 * - 일반적으로 게임플레이 효과(UGameplayEffect)와 결합하여 사용됩니다.
 * - 필요한 경우 오버라이딩을 통해 사용자 정의 계산 논리를 추가할 수 있습니다.
 */
UCLASS()
class CRIMSONMOON_API UCMGECalculation_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
};
