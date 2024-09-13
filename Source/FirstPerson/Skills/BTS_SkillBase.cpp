// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_SkillBase.h"

#include "FirstPerson/DataAssets/BTS_SkillDataAsset.h"

void UBTS_SkillBase::OnSkillExecuted()
{
	UE_LOG(LogTemp, Display, TEXT("OnSkillExecuted + %s"), *this->StaticClass()->GetName());
	
	if (!GetWorld()->GetTimerManager().IsTimerActive(SkillTimerHandle))
	{
		GetWorld()->GetTimerManager().SetTimer(SkillTimerHandle, this, &UBTS_SkillBase::OnSkillFinished, GetSkillDataAsset()->SkillDuration, false);
	}
	OnSkillActivated.Broadcast();
}

void UBTS_SkillBase::OnSkillFinished()
{
	UE_LOG(LogTemp, Display, TEXT("OnSkillFinished + %s"), *this->StaticClass()->GetName());
	OnSkillCompleted.Broadcast(EBTS_SkillFinishReason::Completed);
}

void UBTS_SkillBase::OnCooldownFinished()
{
	UE_LOG(LogTemp, Display, TEXT("OnCooldownFinished + %s"), *this->StaticClass()->GetName());
	OnSkillCooldownCompleted.Broadcast();
}

void UBTS_SkillBase::RegisterSkill(TObjectPtr<UBTS_SkillDataAsset> InSkillAsset, TObjectPtr<UBTS_SkillActorComponent> InSkillActorComponent)
{
	SkillDataAsset = InSkillAsset;
	SkillActorComponent = InSkillActorComponent;
	OnSkillRegistered.Broadcast(InSkillAsset);
}

void UBTS_SkillBase::BeginDestroy()
{
	SkillTimerHandle.Invalidate();
	UObject::BeginDestroy();
}

UBTS_SkillDataAsset* UBTS_SkillBase::GetSkillDataAsset()
{
	return SkillDataAsset.Get();
}
