// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CMCharacterBase.h"
#include "CMPlayerCharacterBase.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
struct FGameplayTag;
class UCMDataAsset_InputConfig;
/**
 * 
 */
UCLASS()
class CRIMSONMOON_API ACMPlayerCharacterBase : public ACMCharacterBase
{
	GENERATED_BODY()

public:
	ACMPlayerCharacterBase();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData | DataAsset", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCMDataAsset_InputConfig> InputConfigDataAsset;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera | SpringArm", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> ViewCamera;
	
	void Input_AbilityInputPressed(const FGameplayTag InInputTag);
	void Input_AbilityInputReleased(const FGameplayTag InInputTag);
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);
};
