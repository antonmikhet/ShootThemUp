// Shoot Them Up Game. All Rights Recieved.

#include "Weapon/STURifleWeapon.h"
#include "DrawDebugHelpers.h"

void ASTURifleWeapon::MakeDamage(AActor* DamagedActor, float Damage, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
        if (!DamagedActor && Damage == 0) { return; }
        DamagedActor->TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
}

void ASTURifleWeapon::MakeShot()
{
        if (!GetWorld()) { return; }
        if (!WeaponOwner) { return; }

        FVector TraceStart, TraceEnd;
        if (!GetTraceData(TraceStart, TraceEnd)) { return; }

        FHitResult HitResult;
        MakeHit(HitResult, TraceStart, TraceEnd);

        if (HitResult.bBlockingHit)
        {

                DrawDebugLine(GetWorld(), GetSocketLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 1.0f);
                DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 10, FColor::Red, false, 4.0f);
                MakeDamage(HitResult.GetActor(), DamageAmount, FDamageEvent(), CharacterController, WeaponOwner);
        }
        else
        {
                DrawDebugLine(GetWorld(), GetSocketLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 1.0f);
        }
}

bool ASTURifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd)
{
        if (!GetWorld()) { return false; }

        FVector ViewLocation;
        FRotator ViewRotation;

        CharacterController->GetPlayerViewPoint(ViewLocation, ViewRotation);

        const float HalfRad = FMath::DegreesToRadians(BulletSpread);
        const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);

        TraceStart = ViewLocation;
        TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
        return true;
}

void ASTURifleWeapon::StartFire()
{
        MakeShot();
        GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, this, &ASTURifleWeapon::MakeShot, FireRate, true);

}

void ASTURifleWeapon::StopFire()
{
        GetWorld()->GetTimerManager().ClearTimer(ShotTimerHandle);
}