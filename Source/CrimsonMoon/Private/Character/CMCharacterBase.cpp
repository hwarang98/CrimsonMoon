// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"

#include "Components/Combat/PawnCombatComponent.h"
#include "CrimsonMoon/DebugHelper.h"
#include "DataAssets/Startup/CMDataAsset_StartupDataBase.h"
#include "GameplayAbilitySystem/CMAbilitySystemComponent.h"
#include "GameplayAbilitySystem/CMAttributeSet.h"

ACMCharacterBase::ACMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	PawnCombatComponent = CreateDefaultSubobject<UPawnCombatComponent>(TEXT("Pawn Combat Component"));
	
	CMAbilitySystemComponent = CreateDefaultSubobject<UCMAbilitySystemComponent>(TEXT("Ability System Component"));
	CMAbilitySystemComponent->SetIsReplicated(true); // 이 컴포넌트를 네트워크로 동기화합니다.
	CMAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); // 동기화할 때, 당사자가 아닌 구경꾼들에게는 꼭 필요한 최소 정보(태그, 스탯 변화)만 보내서 랙을 줄입니다.

	CMAttributeSet = CreateDefaultSubobject<UCMAttributeSet>(TEXT("Attribute Set"));
}

UPawnCombatComponent* ACMCharacterBase::GetPawnCombatComponent() const
{
	ensure(PawnCombatComponent != nullptr);
	
	return PawnCombatComponent;
}

UAbilitySystemComponent* ACMCharacterBase::GetAbilitySystemComponent() const
{
	return GetPOAbilitySystemComponent();
}

void ACMCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UCMDataAsset_StartupDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			constexpr int32 AbilityApplyLevel = 1;
			LoadedData->GiveToAbilitySystemComponent(CMAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}

// Called to bind functionality to input
void ACMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBoxComponent* ACMCharacterBase::GetAttackHitCollisionBox_Implementation(EToggleDamageType DamageType) const
{
	const FString DamageTypeString = UEnum::GetValueAsString(DamageType);
	
	const FString WarningMessage = FString::Printf(
		TEXT("'%s'가 '%s' 타입의 콜리전 박스를 찾으려 했으나, GetAttackHitCollisionBox()가 재정의되지 않았습니다. (기본 nullptr 반환)"),
		*GetName(),
		*DamageTypeString
	);
	
	Debug::Print(TEXT("[CombatWarning] "), WarningMessage, FColor::Yellow, 1); // 100번 키로 갱
	return nullptr;
}

