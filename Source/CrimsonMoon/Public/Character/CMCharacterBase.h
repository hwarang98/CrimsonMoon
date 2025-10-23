// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "CMCharacterBase.generated.h"

class UBoxComponent;
class UCMDataAsset_StartupDataBase;
class UCMAttributeSet;
class UCMAbilitySystemComponent;

UCLASS()
class CRIMSONMOON_API ACMCharacterBase : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	ACMCharacterBase();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	// 테스트 푸시

	/**
	 * @brief 이 캐릭터의 공격 판정에 사용될 콜리전 박스를 반환합니다.
	 * @param DamageType 어느 쪽 손/무기인지 구분 (왼손/오른손)
	 * @return 해당하는 UBoxComponent. 없으면 nullptr.
	 *
	 * 이 함수는 자식 클래스(Player, Enemy)에서 반드시 재정의(override)되어야 합니다.
	 */
	virtual UBoxComponent* GetAttackHitCollisionBox_Implementation(EToggleDamageType DamageType) const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	UBoxComponent* GetAttackHitCollisionBox(EToggleDamageType DamageType) const;

#pragma region Interfaces
	
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
#pragma endregion

protected:
	virtual void PossessedBy(AController* NewController) override;

#pragma region GAS
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCMAbilitySystemComponent> CMAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCMAttributeSet> CMAttributeSet;
	
#pragma endregion

#pragma region Interface Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPawnCombatComponent> PawnCombatComponent;
#pragma endregion 

#pragma region DataAssets
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData | DataAsset")
	TSoftObjectPtr<UCMDataAsset_StartupDataBase> CharacterStartUpData;
	
#pragma endregion 


public:
#pragma region FORCEINLINE
	
	FORCEINLINE UCMAbilitySystemComponent* GetPOAbilitySystemComponent() const { return CMAbilitySystemComponent; }
	FORCEINLINE UCMAttributeSet* GetCMAttributeSet() const { return CMAttributeSet; }

#pragma endregion 
};
