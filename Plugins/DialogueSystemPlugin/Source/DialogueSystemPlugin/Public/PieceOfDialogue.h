// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class DIALOGUESYSTEMPLUGIN_API PieceOfDialogue
{
public:
	PieceOfDialogue();
	~PieceOfDialogue();
public:
	/*The ID number this piece has, this is used to find this specific piece in the list*/
	UPROPERTY(VisibleAnywhere)
	int32 PieceID;

	/*The order in which the dialogue should be written out*/
	UPROPERTY(EditAnywhere)
	int32 SpeechIndex;

	/*The string the dialogue should write out*/
	UPROPERTY(EditAnywhere)
	FString Text;

	/*The amount of time it takes to write out the whole piece of dialogue*/
	UPROPERTY(EditAnywhere)
	float Duration = 1.0f;

	/*The amount of time before the speaker writes out the current dialogue*/
	UPROPERTY(EditAnywhere)
	float Delay = 0.0f;

	/*If this piece should trigger an event when it is completed writing*/
	UPROPERTY(EditAnywhere)
	bool HasEventOnCompletion;

	/*If the current dialogue piece is a question*/
	UPROPERTY(EditAnywhere)
	bool IsQuestion;

	/*The first answer to the question*/
	UPROPERTY(EditAnywhere)
	FString Answer1;

	/*The second answer to the question*/
	UPROPERTY(EditAnywhere)
	FString Answer2;

	/*The third answer to the question*/
	UPROPERTY(EditAnywhere)
	FString Answer3;

	/*If this dialogue should be locked by progression*/
	UPROPERTY(EditAnywhere)
	bool IsLockedByProgression;

	/*The ID integer that should trigger the progression*/
	UPROPERTY(EditAnywhere)
	int32 ProgressionID;
};
