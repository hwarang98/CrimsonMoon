// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player/CMPlayerCharacterBase.h"

#include "CMGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/Input/CMInputComponent.h"
#include "DataAssets/Input/CMDataAsset_InputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameplayAbilitySystem/CMAbilitySystemComponent.h"

ACMPlayerCharacterBase::ACMPlayerCharacterBase()
{
	// 기본 회전 세팅
	bUseControllerRotationPitch = false; // 캐릭터의 Pitch는 고정(또는 코드/모션으로만 변경).
	bUseControllerRotationYaw = false; // 이동 방향으로 캐릭터가 돌고, 시야는 자유롭게 별도 회전
	bUseControllerRotationRoll = false; // 보행 캐릭터는 거의 항상 false. 몸이 좌우로 기울어지는 건 보통 애니메이션이 처리

#pragma region Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 120.f);
	CameraBoom->bUsePawnControlRotation = true;
#pragma endregion

#pragma region View Camera
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("View Camera"));
	ViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
#pragma endregion

#pragma region Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);
#pragma endregion 
}

void ACMPlayerCharacterBase::PawnClientRestart()
{
	Super::PawnClientRestart();
	
	if (const APlayerController* OwningPlayerController = GetController<APlayerController>())
	{
		UEnhancedInputLocalPlayerSubsystem* PlayerSubsystem = OwningPlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		
		check(PlayerSubsystem);
		
		PlayerSubsystem->RemoveMappingContext(InputConfigDataAsset->DefaultMappingContext);
		PlayerSubsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}
}

void ACMPlayerCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UCMInputComponent* POInputComponent = CastChecked<UCMInputComponent>(PlayerInputComponent);

	// 입력키 바인딩 방법
	POInputComponent->BindNativeInputAction(InputConfigDataAsset, CMGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	POInputComponent->BindNativeInputAction(InputConfigDataAsset, CMGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	POInputComponent->BindNativeInputAction(InputConfigDataAsset, CMGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, this, &ThisClass::Jump);

	// GA 자동 바인딩
	POInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void ACMPlayerCharacterBase::Input_AbilityInputPressed(const FGameplayTag InInputTag)
{
	if (CMAbilitySystemComponent)
	{
		CMAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
	}
}

void ACMPlayerCharacterBase::Input_AbilityInputReleased(const FGameplayTag InInputTag)
{
	if (CMAbilitySystemComponent)
	{
		CMAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
	}
}

void ACMPlayerCharacterBase::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
	
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ACMPlayerCharacterBase::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
