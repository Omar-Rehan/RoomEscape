// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReporter.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UPositionReporter::BeginPlay() {
	Super::BeginPlay();
	
	m_owningActor = GetOwner();
	FString owningActorName = m_owningActor->GetName();
	FString owningActorPosition = m_owningActor->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Log, TEXT("%s is at position %s"), *owningActorName, *owningActorPosition);
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

