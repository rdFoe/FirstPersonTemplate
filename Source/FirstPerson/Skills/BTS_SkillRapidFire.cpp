// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SkillRapidFire.h"

#include "EnhancedInputComponent.h"
#include "FirstPerson/FirstPersonPlayerController.h"
#include "FirstPerson/TP_WeaponComponent.h"
#include "FirstPerson/DataAssets/BTS_SkillDataAsset.h"

void UBTS_SkillRapidFire::OnSkillExecuted()
{
	if(bIsOnCooldown)
	{
		UE_LOG(LogTemp, Display, TEXT("bIsOnCooldown + %s"), *this->StaticClass()->GetName());
		return;
	}
	
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
	if (!GetWorld()->GetTimerManager().IsTimerActive(CooldownTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UBTS_SkillBase::OnCooldownFinished, GetSkillDataAsset()->Cooldown, false);
	}
}

void UBTS_SkillRapidFire::OnSkillFinished()
{
	Super::OnSkillFinished();
	
	bIsOnCooldown = true;
	
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
	bIsOnCooldown = false;
	CooldownTimerHandle.Invalidate();
}

void UBTS_SkillRapidFire::BeginDestroy()
{
	CooldownTimerHandle.Invalidate();
	Super::BeginDestroy();
}
