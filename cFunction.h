#pragma once
#include "cClasses.h"
#include "cGameHook.h"
#include "cTools.h"
#include "cVar.h"
#include "cDraw.h"

BOOL WALLSHOT = FALSE;
Vec3 Out;
FLOAT PriorityLimit = 1000.0f;




void request()
{
	IActor* mIActor = nullptr;

	SSystemGlobalEnvironment* pSystemGlobalEnvironment = SSystemGlobalEnvironment::Singleton(); if (!pSystemGlobalEnvironment) return;
	IGameFramework* pIGameFramework = IGameFramework::Singleton(); if (!pIGameFramework) return;
	ICVar* SCvars = ICVar::Singleton(); if (!SCvars) return;
	IGame* m_pGame = IGame::Singleton(); if (!m_pGame) return;
	auto pI3DEngine = pSystemGlobalEnvironment->p3DEngine; if (!pI3DEngine) return;

	pIGameFramework->GetClientActor(&mIActor);

	if (mIActor)
	{
		IItem* m_pItem = mIActor->GetCurrentItem();
		if (m_pItem)
		{
			IWeapon* m_pWeapon = m_pItem->GetIWeapon();
			if (m_pWeapon)
			{
				auto WeaponAction = m_pWeapon->GetWeaponPTR()->WeaponActionRead();
				auto WeaponName = m_pWeapon->GetWeaponPTR()->GetWeaponName();
				if (!mIActor->IsDead())
				{
					m_pWeapon->SetFiringPos({ ZERO });

					if (Hack.recoil)
					{
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(66, 0);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(67, 0);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(68, 0);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(69, 0);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(70, 0);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(71, 0);
					}

					if (Hack.jiraffe > 1)
					{
						if (GetAsyncKeyState(0x56)) { mIActor->GetPlayer()->Growth = Hack.jiraffe; }
					}


					if (Hack.unlim)
					{

						if (WeaponAction == 3 || WeaponAction == 15 || WeaponAction == 14 || WeaponAction == 16)
						{

							if (GetCurrentAmmo(m_pItem->GetIWeapon()) <= 0)
							{
								m_pItem->GetIWeapon()->GetWeaponPTR()->WeaponState(1);
								SCvars->Set(i_unlimitedammo, 1);

								WALLSHOT = TRUE;

							}
							else
							{
								SCvars->Set(i_unlimitedammo, 0);

								WALLSHOT = FALSE;

							}
						}
					}

					if (Hack.fknife)
					{
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(eWS_KnifeLKM, 0);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(eWS_KnifePKM, 0);
					}

					if (Hack.sway)
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->m_sway = { 0.f, 0.f, 0.f };

					if (Hack.shutter)
					{
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(17, 0.f);
						m_pWeapon->GetWeaponPTR()->Shutter(0);
					}

					if (Hack.spread) SCvars->Set(0x128, 999.0f); // anti-spread

					SCvars->Set(0x798, 60 * 60 * 2); // aafk
					SCvars->Set(0x794, 60 * 60 * 2); // aafk 

					IEntityIt* pIEntityIt = pIGameFramework->GetEntitySystem()->GetEntityIterator();
					while (IEntity* pIEntity = pIEntityIt->Next())
					{
						const char* Name = pIEntity->GetName();

						IEntityRenderProxy* pIEntityRenderProxy = (IEntityRenderProxy*)pIEntity->GetProxy(ENTITY_PROXY_RENDER); if (!pIEntityRenderProxy) continue;

						if (strstr("laymore", Name) && !pIEntity->isHidden())
						{
							AABB aabb;
							pIEntity->GetWorldBounds(aabb);
							is_visible(pSystemGlobalEnvironment->pRenderer->cam, aabb.max);
							m_pWeapon->SetFiringPos(aabb.GetCenter());
						}

						if (strstr("apsule", Name) && !pIEntity->isHidden())
						{
							AABB aabb;
							pIEntity->GetWorldBounds(aabb);
							is_visible(pSystemGlobalEnvironment->pRenderer->cam, aabb.max);
							m_pWeapon->SetFiringPos(aabb.GetCenter());
						}

						if (strstr("smartmines1_spider", Name) && !pIEntity->isHidden())
						{
							AABB aabb;
							pIEntity->GetWorldBounds(aabb);
							is_visible(pSystemGlobalEnvironment->pRenderer->cam, aabb.max);
							m_pWeapon->SetFiringPos(aabb.GetCenter());
						}

						if (IActor* eIActor = pIGameFramework->GetIActorSystem()->GetActor(pIEntity->GetId()))
						{
							if (GetTeam(mIActor, eIActor))
							{
								if (Hack.sillhouete)
								{
									if (eIActor->GetHealth() >= 100)
										pIEntityRenderProxy->SetHUDSilhouettesParams(255, 0, 255, 0);
									else if (eIActor->GetHealth() >= 60)
										pIEntityRenderProxy->SetHUDSilhouettesParams(255, 255, 255, 0);
									else if (eIActor->GetHealth() <= 30)
										pIEntityRenderProxy->SetHUDSilhouettesParams(255, 255, 0, 0);
								}
							}
						}
						if (IActor* eIActor = pIGameFramework->GetIActorSystem()->GetActor(pIEntity->GetId()))
						{
							if (!GetTeam(mIActor, eIActor) || eIActor->IsDead()) continue;
							{
								if ((strstr(eIActor->GetLinkedEntity()->GetName(), "mech2300") || strstr(eIActor->GetLinkedEntity()->GetName(), "_Flagship_MainArtillery") || strstr(eIActor->GetLinkedEntity()->GetName(), "_Flagship_Artillery") || strstr(eIActor->GetLinkedEntity()->GetName(), "Black_Wolf") || strstr(eIActor->GetLinkedEntity()->GetName(), "Mantis") || strstr(eIActor->GetLinkedEntity()->GetName(), "Mech2300") || strstr(eIActor->GetLinkedEntity()->GetName(), "Tank_Turret") || strstr(eIActor->GetLinkedEntity()->GetName(), "_TurretAPC") || strstr(eIActor->GetLinkedEntity()->GetName(), "_Turret_MG_OneShot") || strstr(eIActor->GetLinkedEntity()->GetName(), "Helicopter")))
									continue;

								if (Hack.rotate) rotate(eIActor, mIActor);

								if (Hack.aim)
								{
									if ((!eIActor->IsDead())) return;

									Vec3 AimBone = { ZERO };

									switch (Hack.aimtype)
									{
									case 0:
										AimBone = BonePosition(pIEntity);
										if (is_visible(AimBone, 0.0f))
										{
											if (Hack.aimshot == 0)
											{
												Vector(mIActor, AimBone);
											}
											else if (Hack.aimshot == 1)
											{
												Vector(mIActor, AimBone);
												m_pWeapon->StartFireTest();
											}
										}
									case 1:
										AimBone = BonePosition(pIEntity);
										if (Hack.aimshot == 0)
										{
											m_pWeapon->SetFiringPos(AimBone);
										}
										else if (Hack.aimshot == 1)
										{
											m_pWeapon->StartFire();
											m_pWeapon->SetFiringPos(AimBone);
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

/*

void hello_world(IDirect3DDevice9* m_pDevice)
{

	IActor* mIActor = nullptr;
	IActor* eIActor = nullptr;
	IActor* GetActor = nullptr;

	IEntityIt* pIEntityIt = nullptr;

	SSystemGlobalEnvironment* pSystemGlobalEnvironment = SSystemGlobalEnvironment::Singleton(); if (!pSystemGlobalEnvironment) return;
	IGameFramework* pIGameFramework = IGameFramework::Singleton(); if (!pIGameFramework) return;
	ICVar* SCvars = ICVar::Singleton(); if (!SCvars) return;
	IGame* m_pGame = IGame::Singleton(); if (!m_pGame) return;
	IRenderer* m_pRender = IRenderer::Singleton(); if (!m_pRender) return;
	auto pI3DEngine = pSystemGlobalEnvironment->p3DEngine; if (!pI3DEngine) return;

	pIGameFramework->GetClientActor(&mIActor);

	if (mIActor)
	{
		IItem* m_pItem = mIActor->GetCurrentItem();
		if (m_pItem)
		{
			IWeapon* m_pWeapon = m_pItem->GetIWeapon();
			if (m_pWeapon)
			{
				auto WeaponAction = m_pWeapon->GetWeaponPTR()->WeaponActionRead();
				auto WeaponName = m_pWeapon->GetWeaponPTR()->GetWeaponName();
				if (!mIActor->IsDead())
				{
					if (strstr(WeaponName, "arl")) return;

					m_pWeapon->SetFiringPos();

					if (Hack.recoil)
						mIActor->GetPlayer()->m_ignoreRecoil = true; // anti-recoil

					if (Hack.unlim)
					{
						if (WeaponAction == 3 || WeaponAction == 15 || WeaponAction == 14 || WeaponAction == 16)
						{
							if (GetCurrentAmmo(m_pItem->GetIWeapon()) <= 0)
							{
								m_pItem->GetIWeapon()->GetWeaponPTR()->uAmmo(true);
								SCvars->Set(i_unlimitedammo, 1);
							}
							else
							{
								SCvars->Set(i_unlimitedammo, 0);
							}
						}
					}

					if (Hack.fastknife)
					{
						if (WeaponAction == 31)
						{
							m_pWeapon->GetWeaponPTR()->uAmmo(true);
							m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(56, 0.f);
							m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(83, 0.f);
						}
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(63, 3.3f);
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(87, 3.3f);
					}

					if (Hack.sway)
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->m_sway = { 0.f, 0.f, 0.f };

					if (Hack.shutter)
					{
						m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(17, 0.f);
						m_pWeapon->GetWeaponPTR()->Shutter(false);
					}

					if (Hack.antiflash)
					{
						pI3DEngine->SetPostEffectParam("Flashbang_Time", 0);
						pI3DEngine->SetPostEffectParam("FlashBang_BlindAmount", 0);
						pI3DEngine->SetPostEffectParam("Flashbang_DifractionAmount", 0);
						pI3DEngine->SetPostEffectParam("Flashbang_Active", 0);
						pI3DEngine->SetPostEffectParam("FilterRadialBlurring_Radius", 0);
						pI3DEngine->SetPostEffectParam("FilterRadialBlurring_Amount", 0);
					}

					if (Hack.antismoke)
					{
						pI3DEngine->SetPostEffectParam("Smoke", 0);
						pI3DEngine->SetPostEffectParam("Smoke_Active", 0);
						pI3DEngine->SetPostEffectParam("Smoke_DifractionAmount", 0);
						pI3DEngine->SetPostEffectParam("Smoke_Time", 0);
						pI3DEngine->SetPostEffectParam("Smoke_BlindAmount", 0);
					}

					if (Hack.climb)
					{
						m_pGame->SetClimbExtraHeight(GetAsyncKeyState(VK_SPACE) ? 20.0f : 0.0f);
					}

					if (Hack.spread)
						SCvars->Set(0x128, 999.0f); // anti-spread

					if (Hack.antiafk)
					{
						SCvars->Set(0x790, 60 * 60 * 2); // aafk
						SCvars->Set(0x794, 60 * 60 * 2); // aafk
					}

					switch (Hack.damage)
					{
					case 0: hHit.m_dwDamageMult = 0;
					case 1: hHit.m_dwDamageMult = 2;
					case 2: hHit.m_dwDamageMult = 5;
					case 3: hHit.m_dwDamageMult = 10;
					case 4: hHit.m_dwDamageMult = 15;
					case 5: hHit.m_dwDamageMult = 20;
					}
					switch (Hack.rateoffire)
					{
					case 0: m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(80, 1000.0f); // rate of fire
					case 1: m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(80, 3000.0f); // rate of fire
					case 2: m_pWeapon->GetWeaponPTR()->GetSwayParams()->EncryptFloat(80, 5000.0f); // rate of fire
					}

					pIEntityIt = pIGameFramework->GetEntitySystem()->GetEntityIterator();
					if (pIEntityIt)
					{
						while (IEntity* pIEntity = pIEntityIt->Next())
						{
							const char* Name = pIEntity->GetName();
							IEntityRenderProxy* pIEntityRenderProxy = (IEntityRenderProxy*)pIEntity->GetProxy(ENTITY_PROXY_RENDER); if (!pIEntityRenderProxy) continue;

							eIActor = pIGameFramework->GetIActorSystem()->GetActor(pIEntity->GetId());

							if (GetAsyncKeyState(VK_RETURN))
							{
								for (int i = 1; i < 86; i++)
								{
									Vec3 Out;
									Vec3 Bone = m_pRender->cam;
									if (m_pRender->WorldToScreen(Bone, Out))
									{
										Log("Name: %s | ID: %d", pIEntity->GetName(), i);
									}
								}
							}
							if (eIActor)
							{
								if (mIActor != eIActor)
								{
									if (GetTeam(mIActor, eIActor))
									{
										if (Hack.sillhouete)
										{
											if (eIActor->GetHealth() >= 100)
												pIEntityRenderProxy->SetHUDSilhouettesParams(255, 0, 255, 0);
											else if (eIActor->GetHealth() >= 60)
												pIEntityRenderProxy->SetHUDSilhouettesParams(255, 255, 255, 0);
											else if (eIActor->GetHealth() <= 30)
												pIEntityRenderProxy->SetHUDSilhouettesParams(255, 255, 0, 0);
										}
									}
								}
							}

							if (eIActor)
							{
								if (GetTeam(mIActor, eIActor))
								{
									if ((strstr(eIActor->GetLinkedEntity()->GetName(), "mech2300") || strstr(eIActor->GetLinkedEntity()->GetName(), "_Flagship_MainArtillery") || strstr(eIActor->GetLinkedEntity()->GetName(), "_Flagship_Artillery") || strstr(eIActor->GetLinkedEntity()->GetName(), "Black_Wolf") || strstr(eIActor->GetLinkedEntity()->GetName(), "Mantis") || strstr(eIActor->GetLinkedEntity()->GetName(), "Mech2300") || strstr(eIActor->GetLinkedEntity()->GetName(), "Tank_Turret") || strstr(eIActor->GetLinkedEntity()->GetName(), "_TurretAPC") || strstr(eIActor->GetLinkedEntity()->GetName(), "_Turret_MG_OneShot") || strstr(eIActor->GetLinkedEntity()->GetName(), "Helicopter")))
										continue;

									if (Hack.rotate)
										rotate(eIActor, mIActor);

									if (Hack.aim)
									{
										if (eIActor)
										{
											if ((!eIActor->IsDead()))
											{
												Vec3 AimBone = { ZERO };
												switch (Hack.aimtype)
												{
												case 0:
													AimBone = BonePosition(pIEntity);
													Vector(mIActor, AimBone);
												case 1:
													AimBone = BonePosition(pIEntity);
													m_pWeapon->SetFiringPos(AimBone);
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

*/