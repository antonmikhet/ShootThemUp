// Shoot Them Up Game. All Rights Recieved.

#include "Weapon/STULauncherWeapon.h"

#include "STUBaseCharacter.h"
#include "Weapon/Projectile/STUProjectile.h"

void ASTULauncherWeapon::StartFire()
{
        MakeShot();
}

void ASTULauncherWeapon::MakeShot()
{

        if (!GetWorld()) { return; }
        if (!WeaponOwner) { return; }

        FVector TraceStart, TraceEnd;
        if (!GetTraceData(TraceStart, TraceEnd)) { return; }

        FHitResult HitResult;
        MakeHit(HitResult, TraceStart, TraceEnd);

        const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
        const FVector Direction = (EndPoint - GetSocketLocation()).GetSafeNormal();
        const FTransform SpawnTransform(FRotator::ZeroRotator, GetSocketLocation());

        ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);

        if (Projectile)
        {
                Projectile->SetShootDirection(Direction);
                Projectile->SetOwner(WeaponOwner);
                Projectile->FinishSpawning(SpawnTransform);
        }
}