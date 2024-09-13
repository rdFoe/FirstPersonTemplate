// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"

class UTP_WeaponComponent;
class UBTS_SkillActorComponent;
class UInputMappingContext;

/**
 *
 */
UCLASS()
class FIRSTPERSON_API AFirstPersonPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UTP_WeaponComponent* GetWeaponComponent();
protected:

	AFirstPersonPlayerController();
	
	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	// Begin Actor interface

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Skills)
	TObjectPtr<UBTS_SkillActorComponent> SkillActorComponent;

	virtual void BeginPlay() override;

	// End Actor interface
};
