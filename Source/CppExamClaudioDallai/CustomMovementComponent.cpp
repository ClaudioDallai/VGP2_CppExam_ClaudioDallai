// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMovementComponent.h"

void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction) {
	Super::TickComponent(DeltaTime, TickType, TickFunction);

	const FVector Gravity = { 0,0,-9.81f };

	if (!this->bIsGrounded)
	{
		Velocity += Gravity;
	}

	FHitResult Hit;

	bIsGrounded = false;

	if (this->bCannotMoveForward && Velocity.X < 0)
	{
		this->bCannotMoveForward = false;
	}
	if (this->bCannotMoveBackward && Velocity.X > 0)
	{
		this->bCannotMoveBackward = false;
	}

	if (!SafeMoveUpdatedComponent(Velocity * DeltaTime, FRotator::ZeroRotator, true, Hit))
	{
		FVector CompenetrationCorrection = GetPenetrationAdjustment(Hit);
		ResolvePenetration(CompenetrationCorrection, Hit, UpdatedComponent->GetComponentQuat());
		
		if (Hit.Normal.Z > 0)
		{
			Velocity.Z = 0;
			this->bIsGrounded = true;
		}
		if (Hit.Normal.X < 0)
		{
			Velocity.X = 0;
			bCannotMoveForward = true;
		}
		if (Hit.Normal.X > 0)
		{
			Velocity.X = 0;
			bCannotMoveBackward = true;
		}
		if (Hit.Normal.Y < 0)
		{
			Velocity.Y = 0;
		}
	}

	this->Velocity.X = 0;
	this->Velocity.Y = 0;
}


void UCustomMovementComponent::MoveForward(float Input)
{
	FVector MoveDirection = UpdatedComponent->GetForwardVector() * Input * 500;

	MoveDirection.Z = Velocity.Z;
	if (this->bCannotMoveForward && MoveDirection.X > 0)
	{
		MoveDirection.X = 0;
	}
	if (this->bCannotMoveBackward && MoveDirection.X < 0)
	{
		MoveDirection.X = 0;
	}
	this->Velocity += MoveDirection;
}

void UCustomMovementComponent::MoveRight(float Input)
{
	FVector MoveDirection = GetOwner()->GetActorRightVector() * Input * 500;

	MoveDirection.Z = Velocity.Z;
	if (this->bCannotMoveForward && MoveDirection.X > 0)
	{
		MoveDirection.X = 0;
	}
	if (this->bCannotMoveBackward && MoveDirection.X < 0)
	{
		MoveDirection.X = 0;
	}
	this->Velocity += MoveDirection;
}

void UCustomMovementComponent::CustomJump()
{
	
}
