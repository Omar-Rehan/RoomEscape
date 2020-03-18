// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectRotator.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UObjectRotator::UObjectRotator() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UObjectRotator::BeginPlay() {
	Super::BeginPlay();

	m_owningActor = GetOwner();
	FRotator newRotation = FRotator(0.0f, 70.0f, 0.0f);
	m_owningActor->SetActorRotation(newRotation);
}


// Called every frame
void UObjectRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

