// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PieceOfDialogue.h"
#include "Delegates/Delegate.h"
#include "DialogueSpeaker.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCompletionEvent);

USTRUCT(BlueprintType)
struct FPieceOfDialogue {
	GENERATED_USTRUCT_BODY()

	/*The order in which the dialogue should be written out*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpeechIndex;

	/*The string the dialogue should write out*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Text;

	/*The amount of time it takes to write out the whole piece of dialogue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 1.0f;

	/*The amount of time before the speaker writes out the current dialogue*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Delay = 0.0f;

	/*If the piece has an event to call on completion*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool HasCompletionEvent;

	/*If the current dialogue piece is a question*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsQuestion;

	/*The first answer to the question*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Answer1;

	/*The second answer to the question*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Answer2;

	/*The third answer to the question*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Answer3;

	/*If this dialogue should be locked by progression*/
	UPROPERTY(EditAnywhere)
	bool IsLockedByProgression;

	/*The ID integer that should trigger the progression*/
	UPROPERTY(EditAnywhere)
	int32 ProgressionID;
};

UENUM()
enum LoopType 
{
	ENTIRE UMETA(DisplayName = "Loop entire dialogue"),
	LAST UMETA(DisplayName = "Loop last said phrase"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGUESYSTEMPLUGIN_API UDialogueSpeaker : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueSpeaker();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/// <summary>
	/// Get the max amount of pieces of dialogue
	/// </summary>
	/// <returns></returns>
	int32 GetMaxPieces() { return _maxPieces; }

	/// <summary>
	/// Gets the loop type
	/// </summary>
	/// <returns></returns>
	TEnumAsByte<LoopType> GetLoopType() { return _loop; }

	/// <summary>
	/// Returns the current index
	/// </summary>
	/// <returns></returns>
	UFUNCTION(BlueprintCallable)
	int32 GetCurrentIndex() { return _currentIndex; }

	/// <summary>
	/// Set the current index
	/// </summary>
	/// <param name="value"></param>
	void SetCurrentIndex(int32 value) { _currentIndex = value; }

	/// <summary>
	/// Increases the current index by 1
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void IncrementCurrentIndex() { _currentIndex++; }

	/// <summary>
	/// Gets the piece in the list by the given index
	/// </summary>
	UFUNCTION(BlueprintCallable)
	FPieceOfDialogue GetPieceByID(int32 id);

	/// <summary>
	/// Finds the last dialogue index
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void FindLastIndex();

	/// <summary>
	/// Gets the last index
	/// </summary>
	UFUNCTION(BlueprintCallable)
	int32 GetLastIndex() { return _lastIndex; }

	/// <summary>
	/// Gets the current progression int
	/// </summary>
	int32 GetCurrentProgression() { return _currentProgression; }

	/// <summary>
	/// Sets the current progression
	/// </summary>
	/// <param name="value"></param>
	void SetCurrentProgression(int32 value) { _currentProgression = value; }

	/// <summary>
	/// Increases the current progression by 1
	/// </summary>
	void IncrementProgression() { _currentProgression++; }

	/// <summary>
	/// The completion event
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintAssignable)
	FOnCompletionEvent OnCompletion;

private:
	/// <summary>
	/// Sorts the array of pieces
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void SortPieces();

public:
	//The name of the entity speaking
	UPROPERTY(EditAnywhere)
	FString Name;

	// The pieces of dialogue this speaker will send to the listener
	UPROPERTY(EditAnywhere)
	TArray<FPieceOfDialogue> PiecesOfDialogue;

	//If the dialogue can be skipped
	UPROPERTY(EditAnywhere)
	bool CanSkip;

private:
	// The max amount of pieces of dialogue
	int32 _maxPieces;

	// The way the dialogue loops after completing
	UPROPERTY(EditAnywhere)
	TEnumAsByte<LoopType> _loop;

	//The current index of pieces of dialogue
	int32 _currentIndex;

	//The current progression the speaker is at
	int32 _currentProgression;

	//The last index of the dialogue
	int32 _lastIndex;
};
