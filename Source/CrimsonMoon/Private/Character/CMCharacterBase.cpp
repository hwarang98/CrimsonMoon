// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CMCharacterBase.h"

#include "GameplayAbilitySystem/CMAbilitySystemComponent.h"

ACMCharacterBase::ACMCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ACMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ACMCharacterBase::GetAbilitySystemComponent() const
{
	return GetPOAbilitySystemComponent();
}

// Called to bind functionality to input
void ACMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

