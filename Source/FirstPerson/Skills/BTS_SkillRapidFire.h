// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTS_SkillBase.h"
#include "BTS_SkillRapidFire.generated.h"

/**
 * Skill for using rapid fire when having the gun equipped
 */
UCLASS()
class FIRSTPERSON_API UBTS_SkillRapidFire : public UBTS_SkillBase
{
	GENERATED_BODY()

protected:
	virtual void OnSkillExecuted() override;
	virtual void OnSkillFinished() override;
	virtual void OnCooldownFinished() override;
};
