// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerLineToolUtilityLibrary.h"
#if WITH_EDITOR
#include "Editor.h"
#include "LevelEditorViewport.h"
#include "EditorViewportClient.h"


void UPowerLineToolUtilityLibrary::MarkObjectToSave(UObject* MyObject)
{
    MyObject->Modify();
    MyObject->MarkPackageDirty();
}
AActor* UPowerLineToolUtilityLibrary::SpawnPoleActor(TSubclassOf<AActor> ActorClass, float GroundScanDistance)
{
    if (!GEditor || !GCurrentLevelEditingViewportClient || !ActorClass)
        return nullptr;

    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!World)
        return nullptr;

    AActor* SpawnedPole = nullptr;

    FVector CameraLoc = GCurrentLevelEditingViewportClient->GetViewLocation();
    FRotator CameraRot = GCurrentLevelEditingViewportClient->GetViewRotation();
    FVector ForwardVector = CameraRot.Vector();

    FVector TraceStart = CameraLoc;
    FVector TraceEnd = TraceStart + CameraRot.Vector() * GroundScanDistance;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.bTraceComplex = true;

    bool bHitted = World->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_WorldStatic, Params);

    if (bHitted)
    {
        FTransform SpawnTransform(FRotator(0.0f, CameraRot.Yaw, 0.0f), Hit.ImpactPoint);
        SpawnedPole = World->SpawnActor<AActor>(ActorClass, SpawnTransform);
        DrawDebugLine(World, TraceStart, TraceEnd, FColor::Green, false, 5.0f);
        DrawDebugPoint(World, Hit.ImpactPoint, 20.0f, FColor::Red, false, 5.0f);
    }
    else {
        FVector SpawnLocation = CameraLoc + FVector(0.0f, 0.0f, -20.0f) + ForwardVector * 200.0f;
        FTransform SpawnTransform(FRotator(0.0f, CameraRot.Yaw, 0.0f), SpawnLocation);
        SpawnedPole = World->SpawnActor<AActor>(ActorClass, SpawnTransform);
    }

    return SpawnedPole;
}

TArray<AActor*> UPowerLineToolUtilityLibrary::GetSelectedActors()
{
    TArray<AActor*> SelectedActors = UEditorLevelLibrary::GetSelectedLevelActors();

    return SelectedActors;
}

void UPowerLineToolUtilityLibrary::SetSelectedActors(TArray<AActor*> ActorsList)
{
    UEditorLevelLibrary::SetSelectedLevelActors(ActorsList);
}

TArray<AActor*> UPowerLineToolUtilityLibrary::SpawnPolesAlongSpline(USplineComponent* SplineComp, TSubclassOf<AActor> ActorClass, float DistanceBetweenPoles, bool bScanForGround, float ScanRangeUpDown)
{
    UWorld* World = GEditor->GetEditorWorldContext().World();
    if (!SplineComp || !ActorClass || !World)
    {
        return TArray<AActor*>();
    }
    TArray<AActor*> SpawnedActors;
    float SplineLength = SplineComp->GetSplineLength();

    for (float Distance = 0; Distance < SplineLength; Distance += DistanceBetweenPoles)
    {
        FVector Location = SplineComp->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);
        FRotator Rotation = SplineComp->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::World);

        AActor* NewActor = World->SpawnActor<AActor>(ActorClass, Location, Rotation + FRotator(0.0f, 90.0f, 0.0f));
        SpawnedActors.Add(NewActor);
    }
    return SpawnedActors;
}
TArray<AActor*> UPowerLineToolUtilityLibrary::SortActorsByNearestNeighbor(const TArray<AActor*>& Actors)

{
    if (Actors.Num() <= 1) return Actors;

    TArray<AActor*> Sorted;
    TSet<AActor*> Visited;

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