// Fill out your copyright notice in the Description page of Project Settings.

#include "DialogueListener.h"

// Sets default values for this component's properties
UDialogueListener::UDialogueListener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueListener::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_finishedDialogue = false;
}


// Called every frame
void UDialogueListener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//If the listener is supposed to be writing, call function
	if (_isWriting)
	{
		WriteDialogue(DeltaTime);
	}
	//If there is a main text linked and a current speaker
	if (TBMain && CurrentSpeaker)
	{
		//Set the main text and the title
		TBMain->SetText(FText::FromString(CurrentSpeech));
		if (TBName) 
		{
			TBName->SetText(FText::FromString(CurrentSpeaker->Name));
		}
	}
}

void UDialogueListener::SetSpeaker(UDialogueSpeaker* speaker)
{
	CurrentSpeaker = speaker;
}

void UDialogueListener::InteractSpeaker()
{
	//If the listener has a speaker
	if (CurrentSpeaker)
	{
		//If the current index has reached the max amount of pieces
		if (_finishedDialogue)
		{
			//Loop in specified ways
			if (CurrentSpeaker->GetLoopType() == LoopType::ENTIRE)
			{
				CurrentSpeaker->SetCurrentIndex(0);
				_finishedDialogue = false;
			}
			if (CurrentSpeaker->GetLoopType() == LoopType::LAST)
			{
				CurrentSpeaker->FindLastIndex();
				CurrentSpeaker->SetCurrentIndex(CurrentSpeaker->GetLastIndex());
				_finishedDialogue = false;
			}
		}
		//Set dialogue to begin writing
		if (!_isWriting)
		{
			SetupDialogue();
		}
		//If can skip, skip
		else if (_isWriting && _hasDelayPassed && CurrentSpeaker->CanSkip && !_currentPiece.IsQuestion)
		{
			_currentDuration = 0.0f;
		}
	}
}

void UDialogueListener::LinkUIAll(UTextBlock* main, UTextBlock* name, UTextBlock* option1, UTextBlock* option2, UTextBlock* option3, UButton* button1, UButton* button2, UButton* button3)
{
	//Link all UI elements
	TBMain = main;
	TBName = name;
	TBOption1 = option1;
	TBOption2 = option2;
	TBOption3 = option3;
	BUOption1 = button1;
	BUOption1->SetVisibility(ESlateVisibility::Hidden);
	BUOption2 = button2;
	BUOption2->SetVisibility(ESlateVisibility::Hidden);
	BUOption3 = button3;
	BUOption3->SetVisibility(ESlateVisibility::Hidden);
}

void UDialogueListener::LinkUIMainName(UTextBlock* main, UTextBlock* name)
{
	TBMain = main;
	TBName = name;
}

void UDialogueListener::LinkUIMain(UTextBlock* main)
{
	TBMain = main;
}

void UDialogueListener::EndQuestion()
{
	//End all the questioning and invisible the texts
	_isQuestioned = false;
	BUOption1->SetVisibility(ESlateVisibility::Hidden);
	TBOption1->SetText(FText::FromString(""));
	BUOption2->SetVisibility(ESlateVisibility::Hidden);
	TBOption2->SetText(FText::FromString(""));
	BUOption3->SetVisibility(ESlateVisibility::Hidden);
	TBOption3->SetText(FText::FromString(""));
}

void UDialogueListener::SetSpeechIndex(int32 index)
{
	//If a current speaker exists, set its index
	if (CurrentSpeaker) 
	{
		CurrentSpeaker->SetCurrentIndex(index);
	}
}

void UDialogueListener::SetupDialogue()
{
	//Default all variables used for writing
	_isFinishedWriting = false;
	_hasDelayPassed = false;
	_isWriting = true;

	_durationTimer = 0;
	_delayTimer = 0;
	_currentStringIndex = 0;

	CurrentSpeech = "";
	_currentText = "";
}

void UDialogueListener::WriteDialogue(float deltaTime)
{
	//If the writer has finished writing, end writing
	if (_isFinishedWriting)
	{
		_isWriting = false;
		return;
	}

	// Add the delta time to the timers
	_delayTimer += deltaTime;
	_durationTimer += deltaTime;

	//If the delay has passed for the current index and delay has not passed yet
	if (_delayTimer > CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Delay && !_hasDelayPassed)
	{
		//Set delay to finished
		_hasDelayPassed = true;

		//Set the current piece
		_currentPiece = CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()];

		//Get the text of the current piece
		_currentText = _currentPiece.Text;

		//Get the time between writing for the current piece
		_currentDuration = (_currentPiece.Duration / _currentText.Len());
	}

	//If the delay has passed
	if (_hasDelayPassed)
	{
		//If the duration time has passed
		if (_durationTimer > _currentDuration)
		{
			//Write the current char to the speech and increase index
			CurrentSpeech = CurrentSpeech + _currentText[_currentStringIndex];

			//Increase indexes
			CheckIndex();
		}
	}
}

void UDialogueListener::CheckIndex()
{
	_durationTimer = 0;
	//If the string has not been written out
	if (_currentStringIndex < _currentText.Len() - 1)
	{
		_currentStringIndex++;
	}
	//If the string finished writing
	else
	{
		//If the piece is locked by progression and the speaker is at that progression
		if (CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].HasCompletionEvent)
		{
			CurrentSpeaker->OnCompletion.Broadcast();
		}
		// If the current dialogue piece is a question
		if (CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].IsQuestion)
		{
			_isQuestioned = true;
			_isFinishedWriting = true;
			//Load all buttons visuals and set the text for all options
			if (BUOption1 && TBOption1 && CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Answer1 != "")
			{
				BUOption1->SetVisibility(ESlateVisibility::Visible);
				TBOption1->SetText(FText::FromString(CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Answer1));
			}
			if (BUOption2 && TBOption2 && CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Answer2 != "")
			{
				BUOption2->SetVisibility(ESlateVisibility::Visible);
				TBOption2->SetText(FText::FromString(CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Answer2));
			}
			if (BUOption3 && TBOption3 && CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Answer3 != "")
			{
				BUOption3->SetVisibility(ESlateVisibility::Visible);
				TBOption3->SetText(FText::FromString(CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex()].Answer3));
			}
		}
		else
		{
			//If there is a next piece of dialogue
			if (CurrentSpeaker->GetCurrentIndex() < CurrentSpeaker->PiecesOfDialogue.Num() - 1)
			{
				//If the next piece is locked by progression
				if (CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex() + 1].IsLockedByProgression)
				{
					//If the progression has been met
					if (CurrentSpeaker->GetCurrentProgression() == CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex() + 1].ProgressionID)
					{
						//If the next piece has the same speech index
						if (CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex() + 1].SpeechIndex == _currentPiece.SpeechIndex)
						{

							CurrentSpeaker->IncrementCurrentIndex();
							_currentStringIndex = 0;
							_delayTimer = 0;
							_hasDelayPassed = false;
						}
					}
				}
				else if (CurrentSpeaker->PiecesOfDialogue[CurrentSpeaker->GetCurrentIndex() + 1].SpeechIndex == _currentPiece.SpeechIndex)
				{
					CurrentSpeaker->IncrementCurrentIndex();
					_currentStringIndex = 0;
					_delayTimer = 0;
					_hasDelayPassed = false;
				}
				//Then go to the next current index
				else
				{
					_isFinishedWriting = true;
					CurrentSpeaker->IncrementCurrentIndex();
				}
			}
			//If there is no next piece of dialogue
			else
			{
				_isFinishedWriting = true;
				_finishedDialogue = true;
			}
		}
	}
}