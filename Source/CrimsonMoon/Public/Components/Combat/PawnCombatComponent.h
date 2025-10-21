// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class ACMCharacterBase;

/**
 * @brief 공격 판정에 사용하는 손/무기의 종류를 정의하는 열거형 클래스입니다.
 *
 * 이 열거형은 공격 시 판별되는 손/무기의 타입을 나타냅니다.
 * 각각의 요소는 다음과 같습니다:
 * - LeftHand: 왼손 또는 왼쪽 무기
 * - RightHand: 오른손 또는 오른쪽 무기
 *
 * 이 열거형은 Blueprint에서 사용 가능하도록 설정되어 있습니다.
 */
UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	LeftHand,
	RightHand
};

/**
 * @brief 캐릭터의 전투 기능을 관리하는 컴포넌트 클래스입니다.
 *
 * 이 컴포넌트는 공격 시 충돌 판정, 피격 처리, 액터 간 상호작용 등을 처리합니다.
 * 주로 Pawn 캐릭터와 연동되어 전투 관련 로직을 실행합니다.
 */
UCLASS()
class CRIMSONMOON_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	virtual void HandleHit(AActor* HitActor);
	
	UFUNCTION(BlueprintCallable, Category = "Crimson Moon | Combat")
	void ToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);

	UFUNCTION(BlueprintCallable, Category = "Crimson Moon | Combat")
	ACMCharacterBase* GetOwnerCharacter() const;
	
	UFUNCTION(Server, Reliable)
	void ServerToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);


protected:
	// 한 번의 공격 동안 이미 맞은 액터들을 기록하는 배열
	UPROPERTY()
	TArray<TObjectPtr<AActor>> OverlappedActors;

private:
	void HandleToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
};
