// Fill out your copyright notice in the Description page of Project Settings.
#include "SessionSubsystem.h"
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSessionSettings.h"
#include "SessionSubsystem.generated.h"

.cpp のインクルード
#include "SessionSubsystem.h"
#include "OnlineSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

.cpp
// UE側で一般的に使われる固定名（"GameSession"）

static const FName SESSION_NAME = NAME_GameSession;


.cpp
void USessionSubsystem::ClearDelegates()

{

    if (!Session.IsValid()) return;

    if (OnCreateHandle.IsValid())  Session->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateHandle);

    if (OnDestroyHandle.IsValid()) Session->ClearOnDestroySessionCompleteDelegate_Handle(OnDestroyHandle);

    OnCreateHandle.Reset();

    OnDestroyHandle.Reset();

}

void USessionSubsystem::DestroyThenRecreate(int32 PublicConnections)

{

    ClearDelegates();

    OnDestroyHandle = Session->AddOnDestroySessionCompleteDelegate_Handle(

        FOnDestroySessionCompleteDelegate::CreateWeakLambda(this, [this, PublicConnections](FName, bool)

            {

                CreateLanSession(PublicConnections);

            }));

    Session->DestroySession(SESSION_NAME);

}

