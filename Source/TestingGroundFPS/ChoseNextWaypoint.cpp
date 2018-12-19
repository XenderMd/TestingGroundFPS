// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoseNextWaypoint.h"
#include"BehaviorTree/BlackboardComponent.h"
#include"TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrolRoute.h"
#include "AIController.h"

EBTNodeResult::Type UChoseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// TODO - protect against no Patrol Route component
	// TODO - add protection in case of an empty patrpoints array

	AAIController *AIOwner = OwnerComp.GetAIOwner();
	APawn *ControlledPawn = AIOwner->GetPawn();
	auto *PatrollingGuard = Cast<ATP_ThirdPersonCharacter>(ControlledPawn);

	//Get patrol route
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto PatrolRoute = Cast<UPatrolRoute>(PatrollingGuard->GetComponentByClass(UPatrolRoute::StaticClass()));

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	//Get patrol points
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrol points !"))
		return EBTNodeResult::Failed;
	}

	//Set next waypoint
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle Index
	Index++;
	Index = Index % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);


	//finish execute
	return EBTNodeResult::Succeeded;
}
