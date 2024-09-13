// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTS_SkillActorComponent.h"
#include "UObject/NoExportTypes.h"
#include "BTS_SkillBase.generated.h"

UENUM(BlueprintType)
enum class EBTS_SkillFinishReason : uint8
{
	Completed,
	ActivationCanceled
};
/**
 * 
 */



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillRegistered, UBTS_SkillDataAsset*, RegisteredSkill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillActivated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillCompleted, EBTS_SkillFinishReason, SkillFinishReason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSkillCooldownCompleted);

UCLASS(BlueprintType)
class FIRSTPERSON_API UBTS_SkillBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnSkillExecuted();
	UFUNCTION()
	virtual void OnSkillFinished();
	UFUNCTION()
	virtual void OnCooldownFinished();
		
	UFUNCTION(BlueprintCallable, Category="Skills")
	UBTS_SkillDataAsset* GetSkillDataAsset();
	
	virtual void RegisterSkill(TObjectPtr<UBTS_SkillDataAsset> InSkillAsset, TObjectPtr<UBTS_SkillActorComponent> InSkillActorComponent);
protected:
	virtual void BeginDestroy() override;
	
public:
	UPROPERTY(BlueprintAssignable, Category="Skill")
	FOnSkillRegistered OnSkillRegistered;
	UPROPERTY(BlueprintAssignable, Category="Skill")
	FOnSkillActivated OnSkillActivated;
	UPROPERTY(BlueprintAssignable, Category="Skill")
	FOnSkillCompleted OnSkillCompleted;
	UPROPERTY(BlueprintAssignable, Category="Skill")
	FOnSkillCooldownCompleted OnSkillCooldownCompleted;

protected:
	UPROPERTY()
	TObjectPtr<UBTS_SkillDataAsset> SkillDataAsset;
	UPROPERTY()
	TObjectPtr<UBTS_SkillActorComponent> SkillActorComponent;
	
	bool bIsOnCooldown = false;

private:
	FTimerHandle SkillTimerHandle;
};