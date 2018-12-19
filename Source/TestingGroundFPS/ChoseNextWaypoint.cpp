// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoseNextWaypoint.h"
#include"BehaviorTree/BlackboardComponent.h"
#include "PatrollingGuard.h"
#include "AIController.h"

EBTNodeResult::Type UChoseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// TODO - add protection in case of an empty patrpoints array

	AAIController *AIOwner = OwnerComp.GetAIOwner();
	APawn *ControlledPawn = AIOwner->GetPawn();
	auto *PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);

	//Get patrol points
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCPP;

	//Set next waypoint

	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	//Cycle Index
	Index++;
	Index = Index % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);


	//finish execute
	return EBTNodeResult::Succeeded;
}
