// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueSpeaker.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "DialogueListener.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGUESYSTEMPLUGIN_API UDialogueListener : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueListener();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	/// <summary>
	/// Set the current speaker this script will use
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetSpeaker(UDialogueSpeaker* speaker);

	/// <summary>
	/// Interact with the current speaker
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void InteractSpeaker();

	/// <summary>
	/// Link all the UI elements to the listener
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void LinkUIAll(UTextBlock* main, UTextBlock* name, UTextBlock* option1, UTextBlock* option2, UTextBlock* option3, UButton* button1, UButton* button2, UButton* button3);

	/// <summary>
	/// Link only the main and name to the UI elements to the listener
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void LinkUIMainName(UTextBlock* main, UTextBlock* name);

	/// <summary>
	/// Link only the main to the UI elements to the listener
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void LinkUIMain(UTextBlock* main);

	/// <summary>
	/// End questions that the player is given
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void EndQuestion();

	/// <summary>
	/// Set the current speech index of the current speaker to a specific index value
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SetSpeechIndex(int32 index);

private:
	/// <summary>
	/// Ready the arrays and variables to defaults for writing
	/// </summary>
	void SetupDialogue();

	/// <summary>
	/// Write to UI text using array elements
	/// </summary>
	/// <param name="deltaTime"></param>
	void WriteDialogue(float deltaTime);

	/// <summary>
	/// Check the indexes in the arrays
	/// </summary>
	void CheckIndex();

public:
	// The current speaker the listener is interacting with
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDialogueSpeaker* CurrentSpeaker;
	// The main UI text block
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TBMain;
	// The main UI text block
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TBName;
	// The first option for response dialogue
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TBOption1;
	// The second option for response dialogue
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TBOption2;
	// The third option for response dialogue
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextBlock* TBOption3;
	// The first options button
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* BUOption1;
	// The second options button
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* BUOption2;
	// The third options button
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UButton* BUOption3;
	// The current text to be writting to the UI
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString CurrentSpeech;

private:
	// Bools for writing
	bool _isWriting, _isFinishedWriting, _hasDelayPassed, _finishedDialogue;
	// Floats for writing
	float _durationTimer, _delayTimer, _currentDuration;
	// Ints for writing
	int _currentStringIndex;
	// The current string text to be filled while writing
	FString _currentText;
	// The current piece
	FPieceOfDialogue _currentPiece;
	// If a question is being asked
	bool _isQuestioned;
};
