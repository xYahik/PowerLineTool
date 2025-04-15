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
    UFUNCTION(BlueprintCallable)
    static void PrintStringNew(FString text) {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, text);
        }
    }
    UFUNCTION(BlueprintCallable)
    static void MarkObjectToSave(UObject* MyObject) {
        MyObject->Modify();
        MyObject->MarkPackageDirty();
    }
#if WITH_EDITOR
    //virtual bool Initialize() override;

    UFUNCTION(CallInEditor, BlueprintCallable)
    static AActor* SpawnPoleActor(TSubclassOf<AActor> ActorClass, float GroundScanDistance);

    UFUNCTION(CallInEditor, BlueprintCallable)
    static TArray<AActor*> GetSelectedActors();

    UFUNCTION(CallInEditor, BlueprintCallable)
    static void SetSelectedActors(TArray<AActor*> ActorsList);

    UFUNCTION(CallInEditor, BlueprintCallable)
    static TArray<AActor*> SpawnPolesAlongSpline(USplineComponent* SplineComp, TSubclassOf<AActor> ActorClass, float DistanceBetweenPoles = 100.0f, bool bScanForGround = false, float ScanRangeUpDown = 500.0f);

    void OnSelectionChanged(UObject* NewSelection);

    UFUNCTION(BlueprintImplementableEvent)
   void SelectionChanged();

    UFUNCTION(BlueprintCallable)
    static TArray<AActor*> SortActorsByNearestNeighbor(const TArray<AActor*>& Actors)
    {
        if (Actors.Num() <= 1) return Actors;

        TArray<AActor*> Sorted;
        TSet<AActor*> Visited;

        // Find the actor that is the farthest from all others to use as a starting point
        AActor* StartActor = nullptr;
        float MaxAvgDistance = -1.f;

        for (AActor* Candidate : Actors)
        {
            float TotalDistance = 0.f;
            for (AActor* Other : Actors)
            {
                if (Candidate != Other)
                {
                    TotalDistance += FVector::Dist(Candidate->GetActorLocation(), Other->GetActorLocation());
                }
            }

            float AvgDist = TotalDistance / (Actors.Num() - 1);
            if (AvgDist > MaxAvgDistance)
            {
                MaxAvgDistance = AvgDist;
                StartActor = Candidate;
            }
        }

        AActor* Current = StartActor;
        Sorted.Add(Current);
        Visited.Add(Current);

        while (Visited.Num() < Actors.Num())
        {
            float ClosestDist = FLT_MAX;
            AActor* ClosestActor = nullptr;

            for (AActor* Actor : Actors)
            {
                if (!Visited.Contains(Actor))
                {
                    float Dist = FVector::Dist(Current->GetActorLocation(), Actor->GetActorLocation());
                    if (Dist < ClosestDist)
                    {
                        ClosestDist = Dist;
                        ClosestActor = Actor;
                    }
                }
            }

            if (ClosestActor)
            {
                Sorted.Add(ClosestActor);
                Visited.Add(ClosestActor);
                Current = ClosestActor;
            }
        }

        return Sorted;
    }
#endif
};

