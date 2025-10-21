// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "CMAttributeSet.generated.h"

/**
 * @class UCMAttributeSet
 * @brief UCMAttributeSet 클래스는 Crimson Moon 프로젝트의 캐릭터 속성(Attribute)을 정의하고 관리하는 역할을 수행합니다.
 *
 * 이 클래스는 Unreal Engine의 UAttributeSet를 상속받아 구현되었으며, 게임 플레이 능력 시스템(GAS: Gameplay Ability System)과 연계되어
 * 캐릭터의 여러 속성(health, mana, strength 등)을 효율적으로 관리하거나 업데이트하는 데 사용됩니다.
 *
 * UCMAttributeSet은 ACMCharacterBase 클래스와 같은 캐릭터 클래스에서 주로 사용되며, 캐릭터의 상태와 능력에 따라
 * 속성값이 동적으로 변경될 수 있습니다.
 *
 * [가스 시스템 연계]
 * - GAS를 통해 적용되는 능력(Abilities)을 활성화하거나 종료할 때 속성 값을 자동으로 계산 및 업데이트합니다.
 * - 예: 캐릭터의 체력이 감소하거나 스킬에 의해 스탯이 변화될 경우, 속성을 변경하고 이를 다른 관련 시스템에 알립니다.
 *
 * @note 이 클래스는 GAS 기반 게임 시스템에서만 제대로 동작합니다.
 */
UCLASS()
class CRIMSONMOON_API UCMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
};
