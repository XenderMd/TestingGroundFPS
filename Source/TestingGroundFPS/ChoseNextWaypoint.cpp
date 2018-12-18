// Fill out your copyright notice in the Description page of Project Settings.

#include "ChoseNextWaypoint.h"
#include"BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChoseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	
	UE_LOG(LogTemp, Warning, TEXT("Waypoint index is %i"), Index)

	return EBTNodeResult::Succeeded;
}
