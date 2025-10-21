// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "CMGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Character/Player/CMPlayerCharacterBase.h"
#include "Components/BoxComponent.h"

void UPawnCombatComponent::HandleHit(AActor* HitActor)
{
	// 공격마다 1회만 피격 판정 처리
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	
	OverlappedActors.AddUnique(HitActor);

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn(); // 공격자
	EventData.Target = HitActor; // 피격자

	// TODO: 추후 태그 생성후 주석 해제 예정
	
	// POGameplayAbility_Attack.cpp의 UAbilityTask_WaitGameplayEvent::WaitGameplayEvent로 태그와 payload 전송
	// UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
	// 	GetOwningPawn(),
	// 	CMGameplayTags::Shared_Event_MeleeHit,
	// 	EventData
	// );
}

void UPawnCombatComponent::ToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (APawn* OwningPawn = Cast<APawn>(GetOwner()))
	{
		if (!OwningPawn->HasAuthority())
		{
			if (OwningPawn->IsLocallyControlled())
			{
				ServerToggleCollision(bShouldEnable, ToggleDamageType);
			}
			return;
		}
	}

	// 서버에서만 실제 콜리전 변경
	HandleToggleCollision(bShouldEnable, ToggleDamageType);
}

ACMCharacterBase* UPawnCombatComponent::GetOwnerCharacter() const
{
	if (ACMCharacterBase* OwningCharacter = Cast<ACMCharacterBase>(GetOwner()))
	{
		return OwningCharacter;
	}

	return nullptr;
}

void UPawnCombatComponent::HandleToggleCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if (ToggleDamageType == EToggleDamageType::LeftHand || ToggleDamageType == EToggleDamageType::RightHand)
	{
		ACMCharacterBase* OwningCharacter = GetOwnerCharacter();
		if (!OwningCharacter)
		{
			return;
		}
		
		UBoxComponent* CollisionBox = OwningCharacter->GetAttackHitCollisionBox(ToggleDamageType);
		if (!CollisionBox)
		{
			// 이 캐릭터는 해당 DamageType의 콜리전 박스를 가지고 있지 않음.
			return; 
		}
	
		CollisionBox->SetCollisionEnabled(bShouldEnable ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		CollisionBox->SetGenerateOverlapEvents(bShouldEnable);
	
		if (!bShouldEnable)
		{
			OverlappedActors.Empty();
		}
	}
}

void UPawnCombatComponent::ServerToggleCollision_Implementation(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	HandleToggleCollision(bShouldEnable, ToggleDamageType);
}
