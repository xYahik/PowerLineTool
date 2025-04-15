// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#if WITH_EDITOR
#include "EditorUtilityLibrary.h"
#include "Editor/EditorEngine.h"
#include "EditorLevelLibrary.h"
#include "Engine/Selection.h"
#endif
#include "PowerLineToolUtilityLibrary.generated.h"

/**
 * 
 */
UCLASS()
class POWERLINETOOL_API UPowerLineToolUtilityLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:

#if WITH_EDITOR
    UFUNCTION(BlueprintCallable)
    static void MarkObjectToSave(UObject* MyObject);

    UFUNCTION(CallInEditor, BlueprintCallable)
    static AActor* SpawnPoleActor(TSubclassOf<AActor> ActorClass, float GroundScanDistance);

    UFUNCTION(CallInEditor, BlueprintCallable)
    static TArray<AActor*> GetSelectedActors();

    UFUNCTION(CallInEditor, BlueprintCallable)
    static void SetSelectedActors(TArray<AActor*> ActorsList);

    UFUNCTION(CallInEditor, BlueprintCallable)
    static TArray<AActor*> SpawnPolesAlongSpline(USplineComponent* SplineComp, TSubclassOf<AActor> ActorClass, float DistanceBetweenPoles = 100.0f, bool bScanForGround = false, float ScanRangeUpDown = 500.0f);

    UFUNCTION(BlueprintCallable)
    static TArray<AActor*> SortActorsByNearestNeighbor(const TArray<AActor*>& Actors);
#endif
};

