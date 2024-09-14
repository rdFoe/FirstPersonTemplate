// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SkillRapidFire.h"

#include "EnhancedInputComponent.h"
#include "FirstPerson/FirstPersonPlayerController.h"
#include "FirstPerson/TP_WeaponComponent.h"
#include "FirstPerson/DataAssets/BTS_SkillDataAsset.h"

void UBTS_SkillRapidFire::OnSkillExecuted()
{
	AFirstPersonPlayerController* pc = SkillActorComponent->GetOwner<AFirstPersonPlayerController>();
	if(!pc)
	{
		return;
	}
	if(!pc->GetWeaponComponent())
	{
		OnSkillCompleted.Broadcast(EBTS_SkillFinishReason::ActivationCanceled);
		return;
	}

	Super::OnSkillExecuted();

	pc->GetWeaponComponent()->SetFireRate(0.1f);
}

void UBTS_SkillRapidFire::OnSkillFinished()
{
	Super::OnSkillFinished();
	
	AFirstPersonPlayerController* pc = SkillActorComponent->GetOwner<AFirstPersonPlayerController>();
	if(!pc)
	{
		return;
	}
	
	if(!pc->GetWeaponComponent())
	{
		OnSkillCompleted.Broadcast(EBTS_SkillFinishReason::ActivationCanceled);
		return;
	}
	pc->GetWeaponComponent()->SetFireRate(0.5f);
}

void UBTS_SkillRapidFire::OnCooldownFinished()
{
	Super::OnCooldownFinished();
}