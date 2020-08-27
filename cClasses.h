#pragma once
#include <iostream>
#include "cSDK.h"
#include <map>

class SSystemGlobalEnvironment;
class SMovementState;


struct IRenderer;
struct IGameFramework;
struct IGame;
struct ICVar;
class ITimer;

struct I3DEngine;
struct HitInfo;

struct CPlayer;
class IActor;
struct IActorSystem;

struct IEntity;
struct IEntityIt;
struct IEntityProxy;
struct IEntitySystem;
struct IEntityRenderProxy;
struct ICharacterInstance;
class IEntityArchetype;

struct IRenderNode;

struct IGameRules;

class IItem;
class IWeapon;
class IWeaponPTR;
struct SFireParams;
struct SSwayParams;
struct SAmmoParams;

struct IConsole;
class ISystem;

struct SRWIParams;
struct ray_hit; 
struct ray_hit_cached;
class IPhysicalEntity;

class IPhysicalWorld;

struct ISkeletonPose;


typedef unsigned int EntityId;
typedef std::map<uint32_t, uint32_t[2]> TWeaponMap;
typedef std::map<const char*, const char*> THitMaterialMap;


template <class T>
T Function(void* base, DWORD64 index)
{
	return (*(T**)base)[index];
}

template <typename t>
t f_virtual(PVOID f_base, DWORD64 f_index)
{
	return (*(t**)f_base)[f_index / 8];
}

class SSystemGlobalEnvironment
{
public:
	char pad_0x0000[0x48]; //0x0000
	IRenderer* pRenderer; //0x0048 
	char pad_0x0050[0x20]; //0x0050
	IPhysicalWorld* pPhysicalWorld; //0x0070 
	char pad_0x0078[0x40]; //0x0078
	ITimer* pTimer; //0x00B8 
	IConsole* pConsole; //0x00C0 
	IGame* pIGame; //0x00C8 
	char pad_0x00D0[0x8]; //0x00D0
	IEntitySystem* pEntitySystem; //0x00D8 
	char pad_0x00E0[0x8]; //0x00E0
	ISystem* pSystem; //0x00E8 
	char pad_0x00F0[0x8]; //0x00F0
	I3DEngine* p3DEngine; //0x00F8 
	static SSystemGlobalEnvironment* Singleton()
	{
		return *(SSystemGlobalEnvironment**)SSGE;
	}
};

class SMovementState
{
public:
	//
};

class CMovementRequest {};

class IMovementController
{
public:
	virtual virtual ~IMovementController() {}; //0x0 
	virtual bool RequestMovement(CMovementRequest& request) = 0;
	virtual void GetMovementState(SMovementState& state) = 0;
	virtual bool GetStanceState( /*const SStanceStateQuery& query, SStanceState& state*/) = 0;
};

struct IRenderer
{
public:
	class wts_info
	{
	public:
		struct Input {
			float x, y, z;
		}
		input;

		struct Output {
			float* x, * y, * z;
		}
		output;
	};

	FLOAT GetHypotenuseFromCenter(Vec3 Point)
	{
		FLOAT ScreenCenterX = (GetWidth() / 2.0f);
		FLOAT ScreenCenterY = (GetHeight() / 2.0f);
		FLOAT PositionX = Point.x > ScreenCenterX ? Point.x - ScreenCenterX : ScreenCenterX - Point.x;
		FLOAT PositionY = Point.y > ScreenCenterY ? Point.y - ScreenCenterY : ScreenCenterY - Point.y;
		return (FLOAT)_sqrt(PositionX * PositionX + PositionY * PositionY);
	}


	bool WorldToScreen(Vec3 vInput, Vec3& vOutput)
	{
		IRenderer::wts_info info;

		info.input.x = vInput.x;
		info.input.y = vInput.y;
		info.input.z = vInput.z;

		info.output.x = &vOutput.x;
		info.output.y = &vOutput.y;
		info.output.z = &vOutput.z;

		SSystemGlobalEnvironment::Singleton()->pRenderer->ProjectToScreen(&info);

		if (vOutput.z < 0.0f || vOutput.z > 1.0f)
			return false;

		vOutput.x *= (GetWidth() / 100.0f);
		vOutput.y *= (GetHeight() / 100.0f);

		return true;
	}

	bool ProjectToScreen(wts_info* info)
	{
		return Function<bool(__thiscall*)(PVOID, wts_info*)>(this, 100)(this, info);
	}

	DWORD64* GetDirectDevice()
	{
		return (DWORD64*) * (DWORD64*)((DWORD64)this + 0xA6D0);
	}

	DWORD64 GetHeight()
	{
		return (DWORD64) * (DWORD64*)((DWORD64)this + 0x24FB);
	}

	DWORD64 GetWidth()
	{
		return (DWORD64) * (DWORD64*)((DWORD64)this + 0x24FA);
	}

	char pad_0x0000[0x1700]; //0x0000
	Vec3 cam; //0x1700 
	char pad_0x1704[0x113C]; //0x1704
};

class ISystem
{
public:
	bool Update(int updateFlags = 0, int nPauseMode = 0)
	{
		return Function<bool(__fastcall*)(PVOID, int, int)>(this, 4)(this, updateFlags, nPauseMode);
	}
	char pad_0x0004[0x7F0];
	Vec3 m_camera;
};

struct IGameFramework
{
public:

	IActorSystem* GetIActorSystem()
	{
		return Function<IActorSystem * (__thiscall*)(PVOID)>(this, 25)(this);
	}

	IEntitySystem* GetEntitySystem()
	{
		return (IEntitySystem*) * (DWORD64*)((DWORD64)this + 0x30);
	}

	IGameRules* GetIGameRules()
	{
		return Function<IGameRules * (__thiscall*)(PVOID)>(this, 137)(this);
	}

	BOOL GetClientActor(IActor** pAct)
	{
		return Function<BOOL(__thiscall*)(PVOID, IActor**)>(this, 142)(this, pAct);
	}

	static IGameFramework* Singleton()
	{
		return *(IGameFramework**)IGF;
	}
};

struct IGame
{
public:
	static IGame* Singleton()
	{
		return *(IGame**)IG;
	}
	void SetClimbExtraHeight(float fValue)
	{
		if (DWORD64 v0 = *(DWORD64*)(*(DWORD64*)(*(DWORD64*)((DWORD64)this + 0x290) + 0x8) + 0x8))
		{
			*(float*)(v0 + 0x1C) = 2.25f + fValue;
		}
	}
};

struct ICVar
{
public:
	template <class T>
	inline VOID Set(DWORD64 offset, T value)
	{
		*(T*)((DWORD64)this + offset) = value;
	}
	template <class T>
	inline T Get(DWORD64 offset)
	{
		return *(T*)((DWORD64)this + offset);
	}

	static ICVar* Singleton()
	{
		return *(ICVar**)ICV;
	}

	INT GetCurrentRoom()
	{
		return *(INT*)((DWORD64)this + CVars::g_victoryCondition);
	}
};

struct I3DEngine
{
public:
	/*IRenderNode* CreateRenderNode(EERType type)
	{
		return Function<IRenderNode * (__thiscall*)(PVOID, EERType)>(this, ??)(this, type);
	}*/

	VOID SetSunColor(Vec3 vColor)
	{
		return Function<void(__thiscall*)(PVOID, Vec3)>(this, 3)(this, vColor);
	}

	VOID SetSkyColor(Vec3 vColor)
	{
		return Function<void(__thiscall*)(PVOID, Vec3)>(this, 5)(this, vColor);
	}

	VOID SetPostEffectParam(const char* pParam, float fValue, bool bForceValue = false)
	{
		return Function<void(__thiscall*)(PVOID, const char*, float, bool)>(this, 143)(this, pParam, fValue, bForceValue);
	}
};

struct CPlayer
{
	Quat& GetViewRotation()
	{
		return m_baseQuat = m_viewQuat = m_viewQuatFinal;
	}
	void SetViewRotation(Quat& rotation)
	{
		m_baseQuat = rotation;
		m_viewQuat = rotation;
		m_viewQuatFinal = rotation;
	}
	void SetZRotation(const Quat& Rotation)
	{
		m_viewQuat.v.z = m_viewQuatFinal.v.z = m_baseQuat.v.z = Rotation.v.z;
		m_viewQuat.w = m_viewQuatFinal.w = m_baseQuat.w = Rotation.w;
	}
	void SetScale(float Value)
	{
		*(float*)((DWORD64)this + 0x8) = Value;
	}

public:
	char pad_0x0000[0x8]; //0x0000
	float Growth; //0x0008 
	char pad_0x000C[0x74]; //0x000C
	Quat m_viewQuat; //0x0080 
	Quat m_viewQuatFinal; //0x0090 
	Quat m_baseQuat; //0x00A0 
	char pad_0x00B0[0x1]; //0x00B0
	bool m_ignoreRecoil; //0x00B1 
	char pad_0x00B2[0xE]; //0x00B2
	Vec3 m_pos; //0x00C0
};

class IEntityArchetype
{
public:
	const char* GetName()
	{
		return Function<const char* (__thiscall*)(void*)>(this, 2)(this);
	}
};


class IActor
{
public:
	bool IsDead()
	{
		return GetHealth() <= 0;
	}

	INT GetHealth()
	{
		return Function<INT(__thiscall*)(PVOID)>(this, 27)(this);
	}

	INT GetTeamID()
	{
		return Function<INT(__thiscall*)(PVOID)>(this, 99)(this);
	}

	IItem* GetCurrentItem(bool includeVehicle = false)
	{
		return Function<IItem * (__thiscall*)(PVOID, bool)>(this, 57)(this, includeVehicle);
	}

	IEntity* GetLinkedEntity()
	{
		return (IEntity*) * (DWORD64*)((DWORD64)this + 0x10);
	}

	CPlayer* GetPlayer()
	{
		return (CPlayer*) * (DWORD64*)((DWORD64)this + 0xD10);//sys_menupreloadpacks // 48 89 83 10 0D 00 00
	}

	EntityId GetTriggeredID()
	{
		DWORD64 offset_0 = *(DWORD64*)(DWORD64(this + 0x18));
		if (!offset_0) return 0;
		DWORD64 offset_1 = *(DWORD64*)(DWORD64(offset_0 + 0x60));
		if (!offset_1) return 0;
		DWORD64 offset_2 = *(DWORD64*)(DWORD64(offset_1 + 0x20));
		if (!offset_2) return 0;

		return *(EntityId*)(DWORD64(offset_2 + 0x170));
	}
	IMovementController* GetMovementController()
	{
		return Function<IMovementController * (__thiscall*)(PVOID)>(this, 61)(this);
	}
};

struct IActorSystem
{
public:
	IActor* GetActor(int entityId)
	{
		return Function<IActor * (__thiscall*)(PVOID, int)>(this, 15)(this, entityId);
	}
};

class IWeaponPTR
{
public:

	auto GetFireParams()
	{
		return (SFireParams*) * (DWORD64*)((DWORD64)this + 0x48);
	}

	auto GetSwayParams()
	{
		return (SSwayParams*) * (DWORD64*)((DWORD64)this + 0x60);
	}

	auto GetAmmoParams()
	{
		return (SAmmoParams*) * (DWORD64*)((DWORD64)this + 0x68);
	}

	void uAmmo(bool status)
	{
		*(DWORD64*)((DWORD64)this + 0xB8) = status;
	}

	void WeaponState(int status)
	{
		*(DWORD64*)((DWORD64)this + 0xB8) = status;
	}

	INT WeaponActionRead()
	{
		return (INT) * (DWORD64*)((DWORD64)this + 0xB8);
	}

	bool IsFiring()
	{
		INT v12 = WeaponActionRead();
		return (v12 == 3 || v12 == 6 || v12 == 12 || v12 == 13 || v12 == 14 || v12 == 15 || v12 == 16 || v12 == 48 || v12 == 49);
	}

	void Shutter(int Status)
	{
		*(int*)((DWORD64)this + 0xD2) = Status;
	}

	const char* GetWeaponName()
	{
		return (const char*) * (DWORD64*)((DWORD64)this + 0x28);
	}
};

struct ICharacterInstance
{
public:
	ISkeletonPose* GetISkeletonPose()
	{
		return Function<ISkeletonPose * (__thiscall*)(PVOID)>(this, 5)(this);
	}
};

struct IEntity
{
public:
	EntityId GetId()
	{
		return Function<EntityId(__thiscall*)(PVOID)>(this, 1)(this);
	}
	VOID GetWorldBounds(AABB& bbox)
	{
		return Function<VOID(__fastcall*)(PVOID, AABB&)>(this, 25)(this, bbox);
	}

	CONST Matrix34& GetWorldTM()
	{
		return Function<const Matrix34 & (__thiscall*)(PVOID)>(this, 23)(this);
	}

	ICharacterInstance* GetCharacter(int nSlot)
	{
		return Function<ICharacterInstance * (__thiscall*)(PVOID, int)>(this, 82)(this, nSlot);
	}

	void SetLocalPos(Vec3& vPos, __int64 RFlag = 0) 
	{ 
		return Function<void(__fastcall*)(PVOID, Vec3&, __int64)>(this, 27)(this, vPos, RFlag); 
	}

	bool isHidden()
	{
		return Function<bool(__thiscall*)(PVOID)>(this, 47)(this);
	}

	VOID SetScale(const Vec3& vScale, int nWhyFlags = 0)
	{
		return Function<void(__thiscall*)(PVOID, Vec3, int)>(this, 31)(this, vScale, nWhyFlags);
	}

	IEntityProxy* GetProxy(EEntityProxy proxy)
	{
		return Function<IEntityProxy * (__thiscall*)(PVOID, EEntityProxy)>(this, 59)(this, proxy);
	}

	IEntityRenderProxy* GetRenderProxy() { return (IEntityRenderProxy*)GetProxy(ENTITY_PROXY_RENDER); }
	// string -> 
	CONST CHAR* GetName()
	{
		return Function<CONST CHAR * (__thiscall*)(PVOID)>(this, 12)(this);
	}

	IEntityArchetype* GetEntityArchetype()
	{
		return pIEntityArchetype;
	}

	char pad_0x0000[0x38]; //0x0000
	IEntityArchetype* pIEntityArchetype; //0x0038 
};

struct IEntityIt
{
public:
	IEntity* Next()
	{
		return Function<IEntity * (__thiscall*)(PVOID)>(this, 6)(this);
	}
};

struct IEntityProxy
{
	virtual VOID function0();
	virtual VOID function1();
	virtual VOID function2();
	virtual VOID function3();
};

class IPhysicalWorld
{
public:

	INT RayWorldIntersection(const Vec3& org, const Vec3& dir, int objtypes, unsigned int flags, ray_hit* hits, int nMaxHits = 1, IPhysicalEntity** pSkipEnts = 0, int nSkipEnts = 0, void* pForeignData = 0, int iForeignData = 0, const char* pNameTag = "RayWorldIntersection(Game)", ray_hit_cached* phitLast = 0, int iCaller = 4)
	{
		return Function<int(__thiscall*)(PVOID, const Vec3&, const Vec3&, int, unsigned int, ray_hit*, int, IPhysicalEntity**, int, void*, int, const char*, ray_hit_cached*, int)>(this, 97)(this, org, dir, objtypes, flags, hits, nMaxHits, pSkipEnts, nSkipEnts, pForeignData, iForeignData, pNameTag, phitLast, iCaller);
	}

	int ray_world_intersection(const Vec3& org, const Vec3& dir, int32 obj_types, uint32 flags, ray_hit* hits, int32 n_max_hits, IPhysicalEntity** p_skip_ents = 0, int32 n_skip_ents = 0, void* p_foreign_data = 0, int32 i_foreign_data = 0, const char* p_name_tag = ("RayWorldIntersection(Game)"), ray_hit_cached* p_hit_Last = 0, int32 i_caller = 4)
	{
		return f_virtual<int32(__thiscall*)(PVOID, const Vec3&, const Vec3&, int32, uint32, ray_hit*, int32, IPhysicalEntity**, int32, void*, int32, const char*, ray_hit_cached*, int32)>(this, 776)(this, org, dir, obj_types, flags, hits, n_max_hits, p_skip_ents, n_skip_ents, p_foreign_data, i_foreign_data, p_name_tag, p_hit_Last, i_caller);
	}

};

struct IEntitySystem
{
public:
	IEntityIt* GetEntityIterator()
	{
		return Function<IEntityIt * (__thiscall*)(PVOID)>(this, 21)(this);
	}
};

struct IEntityRenderProxy
{
public:
	VOID SetHUDSilhouettesParams(float a, float r, float g, float b)
	{
		Function<void(__thiscall*)(PVOID, float, float, float, float)>(this, 44)(this, a, r, g, b);
		m_dwRndFlags |= ESilhouettesParams::eAllMap;
	}

	char pad_0x0000[0x24]; //0x0000
	__int32 m_dwRndFlags; //0x0024
};

struct IGameRules
{
public:
	INT GetTeam(int entityId)
	{
		return Function<INT(__fastcall*)(PVOID, int)>(this, 109)(this, entityId);
	}
};

class IItem
{
public:

	IWeapon* GetIWeapon() { return Function<IWeapon * (__thiscall*)(PVOID)>(this, 79)(this); }

};

class IWeapon
{
public:
	IWeaponPTR* GetWeaponPTR()
	{
		return (IWeaponPTR*) * (DWORD64*)((DWORD64)this + 0x8);
	}

	void StartFire() { return Function<void(__thiscall*)(PVOID)>(this, 11)(this); }
	void StopFire() { return Function<void(__thiscall*)(PVOID)>(this, 12)(this); }

	void StartFireTest()
	{
		*(DWORD64*)((DWORD64)this + 0x160) = *(DWORD64*)((DWORD64)this + 0x168);
	}

	void StopFireTest()
	{
		*(DWORD64*)((DWORD64)this + 0x160) = *(DWORD64*)((DWORD64)this + 0x158);
	}

	void Clamp(__int8 Delay = 0)
	{
		Sleep(Delay);
		StartFire();
		StopFire();
	}
	void ClampTest(__int8 Delay = 0)
	{
		Sleep(Delay);
		StartFireTest();
		StopFireTest();
	}

	void SetFiringPos(Vec3 vPos = { 0.0f, 0.0f, 0.0f })
	{
		if (auto v1 = *(DWORD64*)((DWORD64)this + 0x18))
			*(Vec3*)(v1 + 0x1C) = vPos;
	}
	void ResetFiringPos()
	{
		if (auto v1 = *(DWORD64*)((DWORD64)this + 0x18))
			*(Vec3*)(v1 + 0x1C) = Vec3(ZERO);
	}
};

struct SFireParams
{
public:
	char pad_0x0000[0x10];
	int damage;
};

struct ISkeletonPose
{
public:
	const char* GetJointNameByID(int nJointID)
	{
		return Function<const char* (__thiscall*)(PVOID, int)>(this, 3)(this, nJointID);
	}

	QuatT& GetAbsJointByID(int nJointID)
	{
		return Function<QuatT & (__thiscall*)(PVOID, int)>(this, 7)(this, nJointID);
	}

	UINT GetJointIdByName(const char* strJointName)
	{ 
		return (UINT)Function<INT(__thiscall*)(PVOID, const char*)>(this, 24)(this, strJointName); 
	}
};

struct SSwayParams
{
public:
	Vec3 m_sway; //0x0000
	char pad_0x000C[0x5C]; //0x000C
	TWeaponMap m_mapweapon;

	inline bool DecryptedFloat(uint32_t id, float* value)
	{
		uint32_t* xor_decdata = nullptr;
		if (NULL != (xor_decdata = EncryptedDataEntry(id)))
		{
			*(uint32_t*)value = xor_decdata[0] ^ xor_decdata[1];
			return true;
		}
		return false;
	}

	inline bool EncryptFloat(uint32_t id, float value)
	{
		uint32_t* xor_encdata = nullptr;
		if (NULL != (xor_encdata = EncryptedDataEntry(id)))
		{
			xor_encdata[0] = *(uint32_t*)&value ^ xor_encdata[1];
			return true;
		}
		return false;
	}

private:
	inline uint32_t* EncryptedDataEntry(uint32_t id)
	{
		TWeaponMap::iterator it = m_mapweapon.find(id);
		if (it != m_mapweapon.end())
			return it->second;

		return 0;
	}
};

struct SAmmoParams
{
public:
	char pad_0x0000[0xC];
	int gAmmoCount;
};

struct IConsole
{
public:
	void ExecuteString(const char* command, const bool bSilentMode = false, const bool bDeferExecution = false)
	{
		return Function<void(__thiscall*)(PVOID, const char*, const bool, const bool)>(this, 34)(this, command, bSilentMode, bDeferExecution);
	}
};

class IPhysicalEntity
{
public:
	//
};

struct ray_hit
{
public:
	float dist; //0x0000 
	IPhysicalEntity* pCollider; //0x0008 
	int ipart; //0x0010 
	int partid; //0x0018 
	short surface_idx; //0x0020 
	short idmatOrg; //0x0028 
	int foreignIdx; //0x0030 
	int iNode; //0x0038 
	Vec3 pt; //0x0040 
	Vec3 n; //0x0048 
	int bTerrain; //0x0050 
	int iPrim; //0x0058 
	ray_hit* next; //0x0060 
}; //Size=0x0068


struct ray_hit_cached
{	// used in conjunction with rwi_reuse_last_hitCPlayerRotation
	ray_hit_cached() { pCollider = 0; ipart = 0; }
	ray_hit_cached(const ray_hit& hit) { pCollider = hit.pCollider; ipart = hit.ipart; iNode = hit.iNode; }
	ray_hit_cached& operator=(const ray_hit& hit) { pCollider = hit.pCollider; ipart = hit.ipart; iNode = hit.iNode; return *this; }

	IPhysicalEntity* pCollider;
	int ipart;
	int iNode;
};

struct SRWIParams
{
public:
	char pad_0x0000[0x30];
	int objtypes;
};

struct HitInfo
{
	EntityId shooterId; //0x0000 
	EntityId targetId; //0x0004 
	int material; //0x0008 
	int type; //0x000C 
	int bulletType; //0x0010 Not use 
	int partId; //0x0014 
	Vec3 pos; //0x0018 
	Vec3 dir; //0x0024 Not use
	Vec3 normal; //0x0030 
	bool meleeArmorAbsorb; //0x003C Not use 
	int weaponId; //0x0040 Not use 
	EntityId projectileId; //0x0044 
	char pad_0x0048[0x18]; //0x0048
	float distance; //0x0060 Not use 
	char pad_0x0064[0x5]; //0x0064
	bool bServer; //0x0069 
	char pad_0x006A[0x26]; //0x006A
}; //Size=0x0090