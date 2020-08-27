#pragma once
#include "cClasses.h"
#include "includes.h"
#include "cVar.h"
#include "cDraw.h"

#include <vector>

BOOL BONE = FALSE;
Vec3 AimBone = { ZERO };

THitMaterialMap pTHitMaterialMap =
{
	{ "IronMan", "mat_hitpoint1" },
	{ "TurretRail", "mat_hitpoint3" },
	{ "HeavyTurret", "mat_hitpoint3" },
	{ "TurretWall", "mat_hitpoint1" },
	{ "TurretCeil", "mat_hitpoint3" },
	{ "TurretCeil", "mat_hitpoint3" },
	{ "TurretFloor_MG", "mat_hitpoint3" },
	{ "TurretFloor", "mat_hitpoint3" },
	{ "TurretHunt", "mat_hitpoint3" },
	{ "Turret_MG", "mat_hitpoint3" },
	{ "TurretAPC", "mat_metal" },
	{ "TurretFloor_A", "mat_hitpoint3" },
	{ ".Drone.", "mat_metal" },
	{ "Drone_MG", "mat_hitpoint1" },
	{ "HeavyDroid", "mat_head_droid" },
	{ "SED_", "mat_head" },
	{ "SEDSoldier", "mat_metal" },
	{ "SEDAssault", "mat_metal" },
	{ "Helicopter", "mat_head" },
	{ "Destroyer", "mat_head" }
};

INT GetRoomType()
{
	return ICVar::Singleton()->Get<int>(0x600); // g_victoryCondition
}

INT GetCurrentAmmo(IWeapon* pIWeapon)
{
	return pIWeapon->GetWeaponPTR()->GetAmmoParams()->gAmmoCount;
}

Vec3 GetBonePositionByID(IEntity* pIEntity, INT iBoneID)
{
	ICharacterInstance* pICharacterInstance = pIEntity->GetCharacter(0);
	if (!pICharacterInstance) return { ZERO };
	ISkeletonPose* pISkeletonPose = pICharacterInstance->GetISkeletonPose();
	if (!pISkeletonPose) return { ZERO };
	Matrix34 mOut = pIEntity->GetWorldTM() * Matrix34(pISkeletonPose->GetAbsJointByID(iBoneID));
	return mOut.GetTranslation();
}

const char* GetHitMaterial(IEntity* pIEntity)
{
	if (pIEntity && pIEntity->GetEntityArchetype())
	{
		const char* szArchName = pIEntity->GetEntityArchetype()->GetName();
		THitMaterialMap::iterator it = pTHitMaterialMap.begin();
		for (; it != pTHitMaterialMap.end(); ++it)
		{
			if (strstr(szArchName, it->first))
			{
				return it->second;
			}
		}
	}

	return "mat_head";
}

Vec3 GetBonePositionByName(IEntity* pIEntity, CONST CHAR* bonename)
{
	ICharacterInstance* pICharacterInstance = pIEntity->GetCharacter(0);
	if (!pICharacterInstance) return { ZERO };
	ISkeletonPose* pISkeletonPose = pICharacterInstance->GetISkeletonPose();
	if (!pISkeletonPose) return { ZERO };
	__int16 iBoneID = pISkeletonPose->GetJointIdByName(bonename);
	Matrix34 mOut = pIEntity->GetWorldTM() * Matrix34(pISkeletonPose->GetAbsJointByID(iBoneID));
	return mOut.GetTranslation();
}

Vec3 GetCurrentPosition(IEntity* pIEntity)
{
	Matrix34 pMatrix34 = pIEntity->GetWorldTM();
	Vec3 vPos = pMatrix34.GetTranslation();
	return vPos;
}

FLOAT Distance(Vec3 vPosA, Vec3 vPosB)
{
	return sqrt(((vPosA.x - vPosB.x) * (vPosA.x - vPosB.x)) + ((vPosA.y - vPosB.y)
		* (vPosA.y - vPosB.y)) + ((vPosA.z - vPosB.z) * (vPosA.z - vPosB.z)));
}

int get_bone_object(ISkeletonPose* m_pSkeleton, const char* Name)
{
	if (strstr(Name, "SED")) return 58;
	if (strstr(Name, "HeavyTurret")) return 52;
	if (strstr(Name, "IronMan")) return 9;
	if (!strcmp(Name, "Turret")) return m_pSkeleton->GetJointIdByName("bone_head");
	if (strstr(Name, "Cyborg") || strstr(Name, "Destroyer")) return 3;
	return m_pSkeleton->GetJointIdByName("Bip01 Head");
}

bool IsAim(const char* Name, IEntity* pExp, Vec3& vBonePos)
{
	if (!strcmp(Name, "Mantis") || !strcmp(Name, "Helicopter")) return FALSE;
	if (strstr(Name, "mech2300") || strstr(Name, "Helicopter") || strstr(Name, "Artil")) return FALSE;
	if (strstr(Name, "TurretAPC")) return FALSE;
	ICharacterInstance* pCharacter = pExp->GetCharacter(0);
	if (pCharacter)
	{
		ISkeletonPose* m_pSkeleton = pCharacter->GetISkeletonPose();
		__int32 szJointId = get_bone_object(m_pSkeleton, Name);
		if (szJointId)
		{
			vBonePos = pExp->GetWorldTM() * m_pSkeleton->GetAbsJointByID(szJointId).t;
			return true;
		}
	}
	return false;
}

VOID Vector(IActor* mIActor, Vec3 vPos)
{
	// vPos - enemy position
	Vec3 CamPos = SSystemGlobalEnvironment::Singleton()->pRenderer->cam; // vector
	Vec3 vOut = vPos - CamPos;
	vOut /= sqrt(vOut.x * vOut.x + vOut.y * vOut.y + vOut.z * vOut.z);
	Quat Rotation = Quat::CreateRotationVDir(vOut.GetNormalized());

	mIActor->GetPlayer()->SetViewRotation(Rotation);
}

bool GetTeam(IActor* mIActor, IActor* eIActor)
{
	INT m_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(mIActor->GetLinkedEntity()->GetId());
	INT e_team = IGameFramework::Singleton()->GetIGameRules()->GetTeam(eIActor->GetLinkedEntity()->GetId());

	if (m_team != e_team || e_team == 0)
		return true;
	else
		return false;
}

IActor* Priority(Vec3 Pos, IActor* eIActor)
{
	IActor* pIActor = nullptr;
	//
	FLOAT MyDist = 1000.0f;
	FLOAT Dist = SSystemGlobalEnvironment::Singleton()->pRenderer->GetHypotenuseFromCenter(Pos);
	//
	if (Dist <= MyDist)
	{
		pIActor = eIActor;
		MyDist = Dist;
	}

	return pIActor;
}

Vec3 BonePosition(IEntity* pExp)
{
	if (GetRoomType() == 3)
	{
		AimBone = GetBonePositionByID(pExp, 11);
		BONE = FALSE;

		if (strstr(pExp->GetName(), "TurretWall"))
		{
			AimBone = GetBonePositionByID(pExp, 47);
			BONE = TRUE;
		}

		if (strstr(pExp->GetName(), "CQBHeavy") || (strstr(pExp->GetName(), "SMGHeavy")))
		{
			AimBone = GetBonePositionByID(pExp, 13);
			BONE = TRUE;
		}

		if (strstr(pExp->GetName(), "TurretCeil"))
		{
			AimBone = GetBonePositionByID(pExp, 54);
			BONE = TRUE;
		}

		if (strstr(pExp->GetName(), "Crusher"))
		{
			AimBone = GetBonePositionByID(pExp, 13);
			BONE = TRUE;
		}

		if (strstr(pExp->GetName(), "TurretFloor_ASR")
			|| strstr(pExp->GetName(), "Turret_ASR_Target"))
		{
			AimBone = GetBonePositionByID(pExp, 62);
			BONE = TRUE;
		}

		if (strstr(pExp->GetName(), "TurretFloor_cqb")
			|| strstr(pExp->GetName(), "TurretFloor_CQB")
			|| strstr(pExp->GetName(), "TurretHunt_CQB"))
		{
			AimBone = GetBonePositionByID(pExp, 58);
			BONE = TRUE;
		}

		if (strstr(pExp->GetName(), "TurretFloor_mg")
			|| strstr(pExp->GetName(), "TurretFloor_MG")
			|| strstr(pExp->GetName(), "TurretHunt_MG")
			|| strstr(pExp->GetName(), "TurretRail_mg")
			|| strstr(pExp->GetName(), "Turret_MG"))
		{
			AimBone = GetBonePositionByID(pExp, 68);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "Drone"))
		{
			AimBone = GetBonePositionByID(pExp, 12);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "HeavyTurretRail"))
		{
			AimBone = GetBonePositionByID(pExp, 52);
		}
		if (strstr(pExp->GetName(), "SED_RG"))
		{
			AimBone = GetBonePositionByID(pExp, 13);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "SEDAssault"))
		{
			AimBone = GetBonePositionByID(pExp, 60);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "SEDSoldier"))
		{
			AimBone = GetBonePositionByID(pExp, 58);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "Cyborg") || strstr(pExp->GetName(), "Destroyer"))
		{
			AimBone = GetBonePositionByID(pExp, 3);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "IronMan"))
		{
			AimBone = GetBonePositionByID(pExp, 7);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "JP_Flamethrower"))
		{
			AimBone = GetBonePositionByID(pExp, 13);
			BONE = TRUE;
		}
		if (strstr(pExp->GetName(), "HeavyDroid"))
		{
			AimBone = GetBonePositionByID(pExp, 61);
			BONE = TRUE;
		}
	}
	else
	{
		AimBone = GetBonePositionByID(pExp, 13);
		BONE = FALSE;
	}
	return AimBone;
}

VOID rotate(IActor* eIActor, IActor* mIActor)
{
	if (strstr(eIActor->GetLinkedEntity()->GetName(), "Shield"))
		eIActor->GetPlayer()->SetViewRotation(mIActor->GetPlayer()->GetViewRotation());
	if (strstr(eIActor->GetLinkedEntity()->GetName(), "Drone"))
		eIActor->GetPlayer()->SetZRotation(mIActor->GetPlayer()->GetViewRotation());
	if (strstr(eIActor->GetLinkedEntity()->GetName(), "Iron"))
		eIActor->GetPlayer()->SetViewRotation(mIActor->GetPlayer()->GetViewRotation());
	if (strstr(eIActor->GetLinkedEntity()->GetName(), "HeavyTurretRail8mg02_"))
		eIActor->GetPlayer()->SetViewRotation(mIActor->GetPlayer()->GetViewRotation());
	if (strstr(eIActor->GetLinkedEntity()->GetName(), "HeavyTurret"))
		eIActor->GetPlayer()->SetViewRotation(mIActor->GetPlayer()->GetViewRotation());
}

VOID TracingEntity(IEntityRenderProxy* pIEntityRenderProxy, IEntity* pIEntity)
{
	if ((strstr(pIEntity->GetName(), "apsule"))
		|| (strstr(pIEntity->GetName(), "smartmines1_spider"))
		|| (strstr(pIEntity->GetName(), "heavydroid_rocket"))
		|| (strstr(pIEntity->GetName(), "S00_ShootingTarget"))
		|| (strstr(pIEntity->GetName(), "laymore")))
	{
		pIEntityRenderProxy->SetHUDSilhouettesParams(255.0f, 255.0f, 0.0f, 0.0f);
	}
}

bool IsVisibleObject(IEntity* pIEntity, Vec3 vPos, float offset)
{
	ray_hit RayHit;
	Vec3 Camera = SSystemGlobalEnvironment::Singleton()->pRenderer->cam;
	Vec3 vOut = vPos - Camera;
	FLOAT sqr = (FLOAT)sqrt(vOut.x * vOut.x + vOut.y * vOut.y + vOut.z * vOut.z);
	vOut /= sqr;
	vOut *= sqr - offset;
	return !SSystemGlobalEnvironment::Singleton()->pPhysicalWorld->RayWorldIntersection(Camera, vOut, 0x100 | 1, 0xA | 0x400, &RayHit, 1);
}

Vec3 GetMPos(Vec3 vBonePos, Vec3 CamPos, FLOAT popravka)
{
	Vec3 vOut = vBonePos - CamPos;
	FLOAT sqr = (FLOAT)_sqrt(vOut.x * vOut.x + vOut.y * vOut.y + vOut.z * vOut.z);
	vOut /= sqr;
	vOut *= sqr - popravka;
	return vOut;
}
bool is_Visible(Vec3 vBonePos, FLOAT popravka, IRenderer* m_pRender)
{
	ray_hit tmpHit;
	Vec3 CamPos = m_pRender->cam;
	Vec3 vOut(GetMPos(vBonePos, CamPos, popravka));
	return !SSystemGlobalEnvironment::Singleton()->pPhysicalWorld->RayWorldIntersection(CamPos, vOut, 0x100 | 1, 0xA | 0x400, &tmpHit, 1);
}

ILINE int is_visible(Vec3 camera_pos, Vec3 local_pos)
{
	Vec3 v_diff;
	ray_hit ray_hit;
	int32 ray_flags(visible_flags::e_glass);
	v_diff.x = local_pos.x - camera_pos.x;
	v_diff.y = local_pos.y - camera_pos.y;
	v_diff.z = local_pos.z - camera_pos.z;
	return SSystemGlobalEnvironment::Singleton()->pPhysicalWorld->ray_world_intersection(camera_pos, v_diff, 0x100 | 1, ray_flags, &ray_hit, 1);
}

int32 is_visible(Vec3 v_pos, FLOAT popravka)
{
	ray_hit tmp_hit;
	Vec3 v_camera = SSystemGlobalEnvironment::Singleton()->pRenderer->cam;
	Vec3 vOut(GetMPos(v_pos, v_camera, popravka));
	return SSystemGlobalEnvironment::Singleton()->pPhysicalWorld->ray_world_intersection(v_camera, vOut, 0x100 | 1, visible_flags::e_glass | 0x400, &tmp_hit, 1);
}

void WriteLogFile(const char* LogText, ...)
{
	FILE* MyLog;
	fopen_s(&MyLog, "C://Warface//LOGFILE.log", "a");


	char Buffer[1024];
	va_list ArgList;
	va_start(ArgList, LogText);
	vsnprintf_s(Buffer, 1023, LogText, ArgList);
	va_end(ArgList);

	if (MyLog)
	{
		fprintf(MyLog, "%s", Buffer);
		fclose(MyLog);
	}
}

void Log(const char* LogText, ...)
{
	char Buffer[1024];
	va_list ArgList;
	va_start(ArgList, LogText);
	vsnprintf_s(Buffer, 1023, LogText, ArgList);
	va_end(ArgList);

	WriteLogFile("%s\n", Buffer);
}


// 