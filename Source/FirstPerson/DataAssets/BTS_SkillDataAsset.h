// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Engine/DataAsset.h"
#include "FirstPerson/Skills/BTS_SkillBase.h"
#include "BTS_SkillDataAsset.generated.h"


/**
 * Describes a Skill Entity which will be used in the Skill classes.
 */
UCLASS()
class FIRSTPERSON_API UBTS_SkillDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString SkillName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString SkillDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SkillIcon;

	// 0 = instant
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SkillDuration = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Cooldown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UClass* ClassToGenerate;
};
