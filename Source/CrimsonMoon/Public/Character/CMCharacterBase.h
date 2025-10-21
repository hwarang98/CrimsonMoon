// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CMCharacterBase.generated.h"

class UCMDataAsset_StartupDataBase;
class UCMAttributeSet;
class UCMAbilitySystemComponent;

UCLASS()
class CRIMSONMOON_API ACMCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACMCharacterBase();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

#pragma region FORCEINLINE
	
	FORCEINLINE UCMAbilitySystemComponent* GetPOAbilitySystemComponent() const { return CMAbilitySystemComponent; }
	FORCEINLINE UCMAttributeSet* GetCMAttributeSet() const { return CMAttributeSet; }

#pragma endregion 

protected:
#pragma region Interface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
#pragma endregion 

#pragma region GAS
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCMAbilitySystemComponent> CMAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	TObjectPtr<UCMAttributeSet> CMAttributeSet;
	
#pragma endregion 

#pragma region DataAssets
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData | DataAsset")
	TSoftObjectPtr<UCMDataAsset_StartupDataBase> CharacterStartUpData;
	
#pragma endregion 
	
};
