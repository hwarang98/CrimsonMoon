// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interfaces/PawnUIInterface.h"
#include "CMPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CRIMSONMOON_API ACMPlayerController : public APlayerController, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
};
