// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSpeaker.h"

// Sets default values for this component's properties
UDialogueSpeaker::UDialogueSpeaker()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueSpeaker::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	_currentIndex = 0;

	//SortPieces();

	//OnCompletionEvent();
}


// Called every frame
void UDialogueSpeaker::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FPieceOfDialogue UDialogueSpeaker::GetPieceByID(int32 id)
{
	return PiecesOfDialogue[id];
}

void UDialogueSpeaker::FindLastIndex()
{
	int i = 0;
	for (int a = 0; a < PiecesOfDialogue.Num(); a++) 
	{
		for (int b = 0; b < PiecesOfDialogue.Num(); b++)
		{
			if (PiecesOfDialogue[a].SpeechIndex > PiecesOfDialogue[b].SpeechIndex) 
			{
				i = PiecesOfDialogue[a].SpeechIndex;
			}
		}
	}
	_lastIndex = i;
}

void UDialogueSpeaker::SortPieces()
{
	//Sort undesirable variables
	for (int i = 0; i < PiecesOfDialogue.Num(); i++)
	{
		//Default negative values to 0
		if (PiecesOfDialogue[i].Delay < 0)
		{
			PiecesOfDialogue[i].Delay = 0;
		}
		if (PiecesOfDialogue[i].Duration < 0)
		{
			PiecesOfDialogue[i].Duration = 0;
		}
	}

	//Sort speech indexes to 0 and up
	TArray<FPieceOfDialogue> tempDialogue = PiecesOfDialogue;
	int32 base = 0;
	int32 max = tempDialogue.Max() - 1;

	//Nested for loop to get both sides of the array
	for (int a = 0; a < tempDialogue.Num(); a++)
	{
		for (int b = 0; b < tempDialogue.Num(); b++)
		{
			//Make sure both indexes arn't the same speech index
			if (tempDialogue[b].SpeechIndex != tempDialogue[a].SpeechIndex) 
			{
				//If the second index is more than the first index, swap their places
				if (tempDialogue[b].SpeechIndex > tempDialogue[a].SpeechIndex)
				{
					FPieceOfDialogue temp = tempDialogue[b];
					tempDialogue[b] = tempDialogue[a];
					tempDialogue[a] = temp;
				}
			}
		}
	}

	PiecesOfDialogue = tempDialogue;
}

