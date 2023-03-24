// Shoot Them Up Game. All Rights Recieved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUCoreTypes.h"
#include "STUAnimNotify.generated.h"


/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUAnimNotify : public UAnimNotify
{
        GENERATED_BODY()

public:
        virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

        FOnNotifiedSignature OnNotified;
};