#include "Offsets.h"
#include <atlstr.h>
#include "PtrList.h"
class Main;
class Client;
class GameTime;
class ClientPlayerManager;
class BorderInputNode;
class ClientGameContext;

class BoneCollisionComponent;
class ClientAnimatedSoldierWeaponHandler;
class ClientAntAnimatableComponent;
class ClientCharacterEntity;
class ClientControllableEntity;
class ClientPlayer;
class ClientSoldierPrediction;
class ClientRagDollComponent;
class CharacterPhysicsData;
class CharacterPhysicEntity;
class ClientSoldierEntity;
class ClientVehicleEntity;
class ClientWeapon;
class ClientSoldierAimingEnvironment;
class ClientSoldierAimingSimulation;
class AimAssist;
class DxRenderer;
class GameRenderer;
class GameWorld;
class HavokPhysicsManager;
class IPhysicsRayCaster;
class RayCastHit;
class Screen;
class SoldierEntity;
class ShotConfigData;
class UpdatePoseResultData;
class WeaponModifier;
class WeaponSway;
class WorldRenderSettings;
class FOVTransitionData;
class ZoomLevelData;
class AxisAlignedBox;
class PhysicsEntityData;
class MaterialDecl;
class CharacterPhysicsData;
class CharacterPhysicEntity;
class EntryComponent;
class EntryComponentData;
class EmitterSystemSettings;
class MeshSettings;
class PhysicsSettings;
class SystemSettings;
class WeaponData;
class ToolData;
class GameObject;
class CObjectEntry;
class CObjectList;


template< class T > class WeakPtr
{
private:
	T** m_ptr;

public:
	T* GetData()
	{
		if( !m_ptr )
			return NULL;

		if( !*m_ptr )
			return NULL;

		T* ptr = *m_ptr;

		return ( T* )( ( DWORD64 )ptr - 0x8 ); 
	}
};
namespace eastl
{
	class allocator
	{
	public:
		__forceinline allocator()
		{
		}

		__forceinline allocator( eastl::allocator *__formal )
		{
		}

		__forceinline void set_name( const char *__formal )
		{
		}

		__forceinline const char* get_name()
		{
			return "EASTL";
		}

		__forceinline void* allocate( unsigned int n, int flags )
		{
			return malloc( n );
		}

		__forceinline void deallocate( void *p, unsigned int __formal )
		{
			free( p );
		}
	};

	template <class T>
	class vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		void* vftable;
	public:
		size_t size()
		{ 
			return (((intptr_t)m_lastElement - (intptr_t)m_firstElement) / sizeof(void*));
		}

		T at(int nIndex)
		{
			return *(T*)((intptr_t)m_firstElement + (nIndex * sizeof(T)));
		}
		T operator [](int index) 
		{ 
			return At(index);
		}
	};

	template <class T, INT Count, INT PadSize>
	class fixed_vector
	{
	private:
		T* m_firstElement;
		T* m_lastElement;
		T* m_arrayBound;
		//LPVOID m_pad[PadSize];
		T m_data[Count];

	public:
		fixed_vector( ) {
			m_firstElement = (T *)m_data;
			m_lastElement = (T *)m_data;
			m_arrayBound = (T *)&m_data[Count];
		}

		void push_back( T *const value ) {
			if( m_lastElement > m_arrayBound ) {

				return;
			}
			*m_lastElement = *value;
			m_lastElement = m_lastElement + 1;
		};

		void clear( ) {
			m_firstElement = m_data;
			m_lastElement = m_data;
		}

		UINT Size() {
			return m_lastElement - m_firstElement; 
		}

		T At(INT nIndex) { 
			return m_firstElement[nIndex];
		}

		T operator [](INT index) { return At(index); }
	};
}


class GameTime
{
public:
	DWORD m_ticks; //0x0000 
	DWORD m_tickFrequency; //0x0004 
	DWORD m_tickIndexInFrame; //0x0008 
	DWORD m_lastTickIndexInFrame; //0x000C 
	DWORD m_tickCountInFrame; //0x0010 
	float m_deltaTime; //0x0014 
	float m_passedDeltaTimeInFrame; //0x0018 
};

class ClientGameView
{
public:
	virtual __int64 GetType( ); //
	virtual void GetTransform( D3DXMATRIX &, D3DXVECTOR2 & ); //
	virtual void GetLocalTransform( D3DXMATRIX & ); //
	virtual void GetCurrentCameraTransform( D3DXMATRIX & ); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void setActiveCamera(int id); //

	enum FreeCameraMode
	{
		Static = 0,
		Follow = 1,
		LookAt = 2
	};

	class FreeCamera
	{
	public:
		char _0x0000[16];
		D3DXMATRIX m_transform; //0x0010
		D3DXMATRIX m_transform2; //0x0050
		char _0x0090[24];
		float m_fov; //0x00A8
		float m_dofFocusDistance; //0x00AC
		char _0x00B0[104];
	};//Size=0x0118

	__int32 m_ActiveCamera; //0x0008
	char _0x000C[12];
	__int32 m_Camera; //0x0018
	char _0x001C[148];
	D3DXVECTOR4 m_cameraTargetDistance; //0x00B0
	__int64 m_freeCameraScene; //0x00C0
	FreeCamera* m_pFreeCamera; //0x00C8
	FreeCameraMode m_pFreeCameraMode; //0x00D0
	__int32 m_freeCameraPriority; //0x00D4
	BYTE m_cameraPosInitialized1; //0x00D8
	BYTE m_cameraPosInitialized2; //0x00D9
	BYTE m_cameraPosInitialized3; //0x00DA
	BYTE m_freeCameraActivated; //0x00DB
	char _0x00DC[4];
	__int64 m_cameraEntryTarget; //0x00E0 ClientEntryComponent *
	__int64 m_targetEntryUnSpawnCallback; //0x00E8
};//Size=0x00F0

class Client
{
public:
	char pad_0x0000[40];
	ClientGameContext* m_pGameContext; //0x0028
	__int64 m_pSettings; //0x0030 
	char pad_0x0038[8];
	ClientPlayerManager* m_pClientPlayerManager; //0x0040 
	char pad_0x0048[8];
	ClientGameView* m_pGameView; //0x0050
	char pad_0x0058[8];
	GameTime* m_pGameTime; //0x0060     
	BorderInputNode* m_pBorderInputNode; //0x0068 
};

class Main
{
public:
	char pad_0x0000[32];
	BYTE m_isDedicatedServer; //0x0020 
	BYTE m_isDedicatedServerData; //0x0021 
	BYTE m_isPaused; //0x0022 
	char pad_0x0024[45];
	Client* m_pClient; //0x0050 

	static Main* GetInstance( )
	{
		return *( Main** )( OFFSET_MAIN ); // 0x1420784B8
	}
};

class WeaponSway
{
public:
	char pad_0x0000[304];
	float m_deviationPitch; //0x0130 
	float m_deviationYaw; //0x0134 
	float m_deviationRoll; //0x0138 
	float m_deviationTransY; //0x013C 
	float m_timeSinceLastShot; //0x0140 
	DWORD m_cameraRecoilDeviation; //0x0144 
	D3DXMATRIX m_cameraRecoilTransform; //0x0148 
	char pad_0x0188[24];
	float m_dispersionAngle; //0x01A0 
	float m_minDispersionAngle; //0x01A4 
	float m_crossHairDispersionFactor; //0x01A8 
	float m_currentDispersionPitch; //0x01AC 
	float m_currentDispersionYaw; //0x01B0 
	float m_currentDispersionRoll; //0x01B4 
	float m_currentDispersionTransY; //0x01B8 
}; // Size 0x0438

class MaterialDecl
{
public:
		unsigned int m_Packed; //+0x0
};

class SoundAsset
{
	public:

	class SoundScopeData
	{
		public:

		class SoundScopeStrategyData
		{
		public:
			char _0x0000[16];
			char* m_Name; //0x0010 
			char* m_Stages; //0x0018 
			char _0x0020[32];
		};//Size=0x0040

		char _0x0000[16];
		char* m_Name; //0x0010 
		SoundScopeStrategyData* m_DefaultStrategy; //0x0018 
	};//Size=0x0020

	char _0x0000[24];
	SoundScopeData* m_Scope; //0x0018 
	SoundScopeData* m_ReferencedData; //0x0020 
};//Size=0x0028

class ProjectileEntityData: public DataContainer
{
public:
	 class WeaponSuppressionData
	 {
	 public:
		 char _0x0000[16];
		 float m_MinMultiplier; //0x0010 
		 float m_MaxMultiplier; //0x0014 
		 float m_MinDistance; //0x0018 
		 float m_MaxDistance; //0x001C 
	 };//Size=0x0020

	 enum AntHitReactionWeaponType
	 {
		 AntHitReactionWeaponType_Pistol = 0,
		 AntHitReactionWeaponType_SMG = 1,
		 AntHitReactionWeaponType_AssaultRifle = 2,
		 AntHitReactionWeaponType_LMG = 3,
		 AntHitReactionWeaponType_Shotgun = 4,
		 AntHitReactionWeaponType_SniperRifle = 5,
		 AntHitReactionWeaponType_Explosion = 6,
		 AntHitReactionWeaponType_Flashbang = 7,
		 AntHitReactionWeaponType_Melee = 8
	 };

	char pad_0x0000[80];//96 before inherited datacontainer
	char* m_Name; //0x0060 char* Gameplay/Weapons/Common/Bullets/9x19mm_Pistol 
	char pad_0x0068[40];
	float m_InitialSpeed; //0x0090 
	float m_TimeToLive; //0x0094 
	int m_MaxCount; //0x0098 
	float m_InitMeshHideTime; //0x009C 
	float m_VisualConvergeDistance; //0x00A0 
	float m_VisualConvergenceDelay; //0x00A4 
	float m_VisualConvergenceDuration; //0x00A8 
	float m_ProxyVisualConvergenceDelay; //0x00AC 
	float m_ProxyVisualConvergenceDuration; //0x00B0 
	char _0x00B4[12];
	WeaponSuppressionData* m_suppressionData; //0x00C0 
	char* m_AmmunitionType; //0x00C8 char* 9x19mm
	MaterialDecl m_MaterialPair; //0x00D0 
	AntHitReactionWeaponType m_HitReactionWeaponType; //0x00D4 
	BYTE m_DetonateOnTimeout; //0x00D8 
	BYTE m_ServerProjectileDisabled; //0x00D9 
	char pad_0x00DA[6];
};//Size=0x00E0

class MeshProjectileEntityData : public ProjectileEntityData
{
public:
	D3DXVECTOR4 m_InitialAngularVelocity; //0x00E0 NULL 
	char pad_0x00F0[16];
	float m_InstantAttachableTestDistance; //0x0100 
	float m_InstantAttachableVisualConvergenceDelay; //0x0104 
	float m_InstantAttachableVisualConvergenceDuration; //0x0108 
	float m_MaxAttachableInclination; //0x010C 
	float m_UnspawnAfterDetonationDelay; //0x0110 
	BYTE m_IsAttachable; //0x0114 
	BYTE m_InstantAttachableTestUnderReticule; //0x0115 
	BYTE m_ExtraDamping; //0x0116 
	char pad_0x0117[9];

};//Size=0x0120

class BulletEntityData : public MeshProjectileEntityData
{
public:
	SoundAsset* m_FlyBySound; //0x0120 
	__int64 m_DudExplosion; //0x0128 ExplosionEntityData*
	float m_Gravity; //0x0130 
	float m_ImpactImpulse; //0x0134 
	float m_DetonationTimeVariation; //0x0138 
	float m_VehicleDetonationRadius; //0x013C 
	float m_VehicleDetonationActivationDelay; //0x0140 
	float m_FlyBySoundRadius; //0x0144 
	float m_FlyBySoundSpeed; //0x0148 
	float m_Stamina; //0x014C 
	float m_DistributeDamageOverTime; //0x0150 
	float m_StartDamage; //0x0154 
	float m_EndDamage; //0x0158 
	float m_DamageFalloffStartDistance; //0x015C 
	float m_DamageFalloffEndDistance; //0x0160 
	float m_TimeToArmExplosion; //0x0164 
	float m_FirstFrameTravelDistance; //0x0168 
	BYTE m_HasVehicleDetonation; //0x016C 
	BYTE m_InstantHit; //0x016D 
	BYTE m_StopTrailEffectOnUnspawn; //0x016E 
	char pad_0x016F[1];
};//Size=0x0170  

class FiringFunctionData
{
public:
	class ShotConfigData
	{
	public:
		D3DXVECTOR4 m_InitialPosition; //0x0000
		D3DXVECTOR4 m_InitialDirection; //0x0010
		D3DXVECTOR4 m_InitialSpeed; //0x0020
		char pad_0x0030[24];
		__int64 m_MuzzleExplosion; //0x0048 ExplosionEntityData*
		BulletEntityData* m_ProjectileData; //0x0050 ProjectileEntityData*
		BulletEntityData* m_SecondaryProjectileData; //0x0058 ProjectileEntityData*
		char pad_0x0060[16];
		float m_SpawnDelay; //0x0070
		__int32 m_NumberOfBulletsPerShell; //0x0074
		__int32 m_NumberOfBulletsPerShot; //0x0078
		__int32 m_NumberOfBulletsPerBurst; //0x007C
		BYTE m_RelativeTargetAiming; //0x0080
		BYTE m_ForceSpawnToCamera; //0x0081
		BYTE m_SpawnVisualAtWeaponBone; //0x0082
		BYTE m_ActiveForceSpawnToCamera; //0x0083
		char pad_0x0084[12];
	};//Size=0x0090

	class OverHeatData
	{
	public:
		char pad_0x0000[80];
		float m_HeatPerBullet; //0x0050
		float m_HeatDropPerSecond; //0x0054
		float m_OverHeatPenaltyTime; //0x0058
		float m_OverHeatThreshold; //0x005C
	};//Size=0x0060

	class FireLogicData
	{
	public:

		enum ReloadLogic
		{
			rlWeaponSwitchCancelsUnfinishedReload = 0,
			rlReloadUnaffectedByWeaponSwitch = 1
		};

		enum ReloadType
		{
			rtSingleBullet = 0,
			rtMagazine = 1,
			rtMagazineWithPossibleShorterReload = 2
		};

		char pad_0x0000[96];
		float m_RateOfFire; //0x0060
		float m_RateOfFireForBurst; //0x0064
		float m_ClientFireRateMultiplier; //0x0068
		float m_ReloadDelay; //0x006C
		float m_ReloadTime; //0x0070
		char pad_0x0074[12];
		float m_ReloadTimeBulletsLeft; //0x0080
		float m_ReloadThreshold; //0x0084
		float m_PreFireDelay; //0x0088
		float m_AutomaticDelay; //0x008C
		ReloadLogic m_ReloadLogic; //+0x90
		ReloadType m_ReloadType; //+0x94
		__int32 m_FireLogicType; //0x0098
		char pad_0x009C[20];
	};//Size=0x00B0

	class AmmoConfigData
	{
	public:
		__int32 m_MagazineCapacity; //0x0000
		__int32 m_NumberOfMagazines; //0x0004
		__int32 m_TraceFrequency; //0x0008
		__int32 m_AmmoPickupMinAmount; //0x000C
		__int32 m_AmmoPickupMaxAmount; //0x0010
		float m_AutoReplenishDelay; //0x0014
		float m_AmmoBagPickupDelayMultiplier; //0x0018
		__int32 m_AmmoBagPickupAmount; //0x001C
		BYTE m_AutoReplenishMagazine; //0x0020
		char pad_0x0021[3];
	};//Size=0x0024

	char pad_0x0000[96];
	ShotConfigData m_ShotConfigData; //0x0060
	OverHeatData m_OverHeatData; //0x00F0
	__int64 m_FireEffects1p; //0x0150 WeaponDispersion*
	__int64 m_FireEffects3p; //0x0158 WeaponDispersion*
	__int64 m_Sound; //0x0160 SoundAsset*
	FireLogicData m_FireLogicData; //0x0168 Weird Alignment Issues
	AmmoConfigData m_AmmoConfigData; //0x0218
	float m_SelfHealTimeWhenDeployed; //0x023C
	BYTE m_UsePrimaryAmmo; //0x0240
	BYTE m_UnlimitedAmmoForAI; //0x0241
};//Size=0x0242

class PrimaryFire
{
public:
	BYTE pad00[0x10];                    // 0x0000
	FiringFunctionData* m_FiringData;    // 0x0010
};

class WeaponFiring
{
public:
	char pad_0x0000[120];
	WeaponSway* m_pSway; //0x0078 
	char pad_0x0080[168];
	PrimaryFire* m_pPrimaryFire; //0x0128 
	char pad_0x0130[24];
	DWORD m_weaponState; //0x0148 
	DWORD m_lastWeaponState; //0x014C 
	DWORD m_nextWeaponState; //0x0150 
	char pad_0x0154[8];
	float m_timeToWait; //0x015C 
	float m_reloadTimer; //0x0160 
	float m_holdReleaseMinDelay; //0x0164 
	float m_recoilTimer; //0x0168 
	float m_recoilAngleX; //0x016C 
	float m_recoilAngleY; //0x0170 
	float m_recoilAngleZ; //0x0174 
	float m_recoilFovAngle; //0x0178 
	float m_recoilTimeMultiplier; //0x017C 
	float m_overheatDropMultiplier; //0x0180 
	int m_primaryAmmoToFill; //0x0184 
	int m_reloadStage; //0x0188 
	DWORD_PTR m_pCharacterMeleeEntity; //0x018C 
	int m_externalPrimaryMagazineCapacity; //0x0194 
	char pad_0x0198[8];
	int m_projectilesLoaded; //0x01A0 
	int m_projectilesInMagazines; //0x01A4 
	int m_numberOfProjectilesToFire; //0x01A8 
	BYTE m_hasStoppedFiring; //0x01AC 
	BYTE m_primaryFireTriggeredLastFrame; //0x01AD 
	BYTE m_isOverheated; //0x01AE 
	BYTE m_unknown; //0x01AF 
	char pad_0x01B0[8];
	DWORD m_tickCounter; //0x01B8 
	int m_fireMode; //0x01BC 
	char pad_0x01C0[8];
	DWORD_PTR m_pFiringHolderData; //0x01C8 
};

class WeaponModifier
{
public:
	char pad_0x0000[64];
	BYTE m_breathControl; //0x0040 
	BYTE m_supportedShooting; //0x0041 
	BYTE m_unZoomOnBoltAction; //0x0042 Fixes unzoom when sniping
	BYTE m_holdBoltActionUntilZoomRelease; //0x0043 
};

class ClientWeapon
{
public:

	class ControllableFinder
	{
	public:

		class ControllableResult
		{
		public:
			char pad_0x0000[112];
			D3DXVECTOR3 m_Collision; //0x0070 
		};

		__int64 vtable; //0x0950 
		char pad_0x0958[88];
		D3DXVECTOR4 m_lastRayBegin; //0x09B0 
		D3DXVECTOR4 m_lastRayEnd; //0x09C0
		char pad_0x09CC[84];
		ControllableResult* m_pControllableResult; //0x0A28 
	};

	char pad_0x0000[24];
	PrimaryFire* m_pWeaponFiring;
	WeaponModifier* m_pModifier; //0x0020 
	char pad_0x0028[8];
	D3DXVECTOR3 m_moveSpeed; //0x0030 
	float m_moveSpeedPad; //0x003C 
	D3DXMATRIX m_shootSpace; //0x0040 
	D3DXMATRIX m_shootSpaceIdentity; //0x0080 
	char pad_0x00C0[464];
	float m_cameraFov; //0x0290 
	float m_weaponFov; //0x0294 
	float m_fovScaleFactor; //0x0298 
	char pad_0x029C[20];
	DWORD m_zoomLevel; //0x02B0 
	char pad_0x02B4[1692];
	ControllableFinder m_controllableFinder; //0x0950 
};

class ClientSoldierAimingEnvironment
{
public:
	char _0x0000[8];
	ClientSoldierEntity* m_soldier; //0x0008 
};//Size=0x0010

class AimAssist
{
public:
	__int64 m_data; //0x0000 
	char _0x0008[12];
	float m_yaw; //0x0014 
	float m_pitch; //0x0018 

};//Size=0x001C

class FOVTransitionData
{
public:
	enum FOVTransitionType
	{
		FOVTransitionType_Linear=0,
		FOVTransitionType_Smooth=1,
		FOVTransitionType_Count=2,
	};

	char aDataContainer[16]; //+0x00 Inherited
	FOVTransitionType m_TransitionType; //+0x10
	float m_Shape; //+0x14
	float m_StartDelay; //+0x18
	float m_StartJump; //+0x1C	
	float m_EndEarly; //+0x20
	bool m_Invert; //+0x24
};

class ZoomLevelData
{
public:
	enum ZoomLevelActivateEventType
	{
		ZoomLevelActivateEventType_Disable=0,
		ZoomLevelActivateEventType_Enable=1,
		ZoomLevelActivateEventType_ToggleOnLightSwitch=2,
	};
	char aDataContainer[16]; //+0x00 Inherited
	float m_FieldOfView; //+0x10
	float m_FieldOfViewSP; //+0x14
	FOVTransitionData m_FieldOfViewTransition; //+0x18
	float m_LookSpeedMultiplier; //+0x20
	float m_SprintLookSpeedMultiplier; //+0x24
	float m_MoveSpeedMultiplier; //+0x28
	float m_SwayPitchMagnitude; //+0x2C
	float m_SwayYawMagnitude; //+0x30
	float m_SupportedSwayPitchMagnitude; //+0x34
	float m_SupportedSwayYawMagnitude; //+0x38
	float m_SuppressedSwayPitchMagnitude; //+0x3C
	float m_SuppressedSwayYawMagnitude; //+0x40
	float m_SuppressedSwayMinFactor; //+0x44
	float m_TimePitchMultiplier; //+0x48
	float m_TimeYawMultiplier; //+0x4C
	float m_DispersionMultiplier; //+0x50
	float m_DispersionRotation; //+0x54
	float m_RecoilMultiplier; //+0x58
	float m_RecoilFovMultiplier; //+0x5C
	float m_CameraImpulseMultiplier; //+0x60
	float m_StartFadeToBlackAtTime; //+0x64
	float m_FadeToBlackDuration; //+0x68
	float m_StartFadeFromBlackAtTime; //+0x6C
	float m_FadeFromBlackDuration; //+0x70
	float m_ScreenExposureAreaScale; //+0x74
	ZoomLevelActivateEventType m_OnActivateEventType; //+0x78
	float m_AttractYawStrength; //+0x7C
	float m_AttractPitchStrength; //+0x80
	bool m_AllowFieldOfViewScaling; //+0x84
	bool m_FadeToBlackInZoomTransition; //+0x85
	bool m_UseFovSpecialisation; //+0x86
	bool m_UseWeaponMeshZoom1p; //+0x87
};

class AimingPoseData
{
public:
	float m_MinimumPitch; //+0x0
	float m_MaximumPitch; //+0x4
	float m_TargetingFov; //+0x8
	float m_AimSteadiness; //+0xC
	float m_SpeedMultiplier; //+0x10
	float m_RecoilMultiplier; //+0x14
};

class SoldierAimAssistData
{
public:
	char pad_0x00[0x10]; //+0x00
	__int64 m_InputPolynomial; //+0x10
	__int64 m_ZoomedInputPolynomial; //+0x18
	D3DXVECTOR3 m_StickyBoxScale; //+0x20
	D3DXVECTOR3 m_StickyDistanceScale; //+0x30
	D3DXVECTOR3 m_SnapBoxScale; //+0x40
	D3DXVECTOR3 m_SnapDistanceScale; //+0x50
	D3DXVECTOR3 m_EyePosOffset; //+0x60
	float m_AccelerationInputThreshold; //+0x70
	float m_AccelerationMultiplier; //+0x74
	float m_AccelerationDamping; //+0x78
	float m_AccelerationTimeThreshold; //+0x7C
	float m_SquaredAcceleration; //+0x80
	D3DXVECTOR2 m_MaxAcceleration; //+0x84
	float m_YawSpeedStrength; //+0x8C
	float m_PitchSpeedStrength; //+0x90
	D3DXVECTOR2 m_AttractDistanceFallOffs; //+0x94
	float m_AttractSoftZone; //+0x9C
	float m_AttractUserInputMultiplier; //+0xA0
	float m_AttractUserInputMultiplier_NoZoom; //+0xA4
	float m_AttractOwnSpeedInfluence; //+0xA8
	float m_AttractTargetSpeedInfluence; //+0xAC
	float m_AttractOwnRequiredMovementForMaximumAttract; //+0xB0
	float m_AttractStartInputThreshold; //+0xB4
	float m_AttractMoveInputCap; //+0xB8
	float m_AttractYawStrength; //+0xBC
	float m_AttractPitchStrength; //+0xC0
	float m_MaxToTargetAngle; //+0xC4
	float m_MaxToTargetXZAngle; //+0xC8
	float m_ViewObstructedKeepTime; //+0xCC
	float m_SnapZoomLateralSpeedLimit; //+0xD0
	float m_SnapZoomTime; //+0xD4
	float m_SnapZoomPostTimeNoInput; //+0xD8
	float m_SnapZoomPostTime; //+0xDC
	unsigned int m_SnapZoomReticlePointPriority; //+0xE0
	float m_SnapZoomAutoEngageTime; //+0xE4
	float m_SnapZoomBreakTimeAtMaxInput; //+0xE8
	float m_SnapZoomBreakMaxInput; //+0xEC
	float m_SnapZoomBreakMinAngle; //+0xF0
	float m_SnapZoomSpamGuardTime; //+0xF4
	__int64 m_SoldierBackupSkeletonCollisionData; //+0xF8
	float m_CheckBoneCenterOnlyDistance; //+0x100
	float m_DisableForcedTargetRecalcDistance; //+0x104
	float m_OverrideAimingRange; //+0x108
	float m_OverrideAimingRangeCrouch; //+0x10C
	float m_OverrideAimingRangeProne; //+0x110
	bool m_UseYawAcceleration; //+0x114
	bool m_UsePitchAcceleration; //+0x115
	bool m_SnapZoomUserShorterWeaponTime; //+0x116
	bool m_SnapZoomPostTimeDynamicPoint; //+0x117
	bool m_ForceSoldierBackupSkeletonCollisionUse; //+0x118
};

class SoldierAimingSimulationData
{
public:
	char aGameDataContainer[16]; //+0x00 Inherited
	ZoomLevelData** m_ZoomLevels; //+0x10
	bool m_ReturnToZoomAfterReload; //+0x90
	SoldierAimAssistData* m_AimAssist; //+0x18
	AimingPoseData m_StandPose; //+0x20
	AimingPoseData m_CrouchPose; //+0x38
	AimingPoseData m_PronePose; //+0x50
	float m_ZoomTransitionTime; //+0x68
	float m_ZoomTransitionTimeArray; //+0x70
	float m_FovDelayTime; //+0x78
	float m_FovTransitionTime; //+0x7C
	float m_AimingRange; //+0x80
	float m_LockAimToTargetSpeed; //+0x84
	float m_Modifiers; //+0x88
};

class ClientSoldierAimingSimulation
{
public:
	SoldierAimingSimulationData* m_data; //0x0000 
	ClientSoldierAimingEnvironment* m_environment; //0x0008 
	AimAssist* m_fpsAimer; //0x0010 
	float m_yaw; //0x0018 
	float m_pitch; //0x001C 
	float m_aimYawTimer; //0x0020 
	float m_aimPitchTimer; //0x0024 
	D3DXVECTOR2 m_sway; //0x0028 
	char _0x0030[56];
	float m_zoomLevel; //0x0068 
	char _0x006C[180];

};//Size=0x0120

class SpatialEntityData
{
public:
	char aEntityData[24]; //+0x00 Inherited
	D3DXMATRIX m_Transform; //+0x20 LinearTransform
};

class ComponentEntityData
{
public:
	char aSpatialEntityData[96]; //+0x00 Inherited
	SpatialEntityData* m_Components; //+0x60
	unsigned _int8 m_ClientRuntimeComponentCount; //+0x68
	unsigned _int8 m_ServerRuntimeComponentCount; //+0x69
	unsigned _int8 m_ClientRuntimeTransformationCount; //+0x6A
	unsigned _int8 m_ServerRuntimeTransformationCount; //+0x6B
};

class GameComponentEntityData : public ComponentEntityData
{
public:
	bool m_Enabled; //+0x70
};

class FireLogicData
{
public:
	class HoldAndReleaseData
	{
	public:
		float m_MaxHoldTime; //+0x0
		float m_MinPowerModifier; //+0x4
		float m_MaxPowerModifier; //+0x8
		float m_PowerIncreasePerSecond; //+0xC
		float m_Delay; //+0x10
		float m_KilledHoldingPowerModifier; //+0x14
		bool m_ForceFireWhenKilledHolding; //+0x18
	};

	class BoltActionData
	{
	public:
		float m_BoltActionDelay; //+0x0
		float m_BoltActionTime; //+0x4
		bool m_HoldBoltActionUntilFireRelease; //+0x8
		bool m_HoldBoltActionUntilZoomRelease; //+0x9
		bool m_ForceBoltActionOnFireTrigger; //+0xA
		bool m_UnZoomOnBoltAction; //+0xB
		bool m_ReturnToZoomAfterBoltAction;//+0xC
	};

	class RecoilData
	{
	public:
		float m_MaxRecoilAngleX; //+0x0
		float m_MinRecoilAngleX; //+0x4
		float m_MaxRecoilAngleY; //+0x8
		float m_MinRecoilAngleY; //+0xC
		float m_MaxRecoilAngleZ; //+0x10
		float m_MinRecoilAngleZ; //+0x14
		float m_MaxRecoilFov; //+0x18
		float m_MinRecoilFov; //+0x1C
		bool m_RecoilFollowsDispersion; //+0x20
	};

	HoldAndReleaseData m_HoldAndRelease; //+0x0
	BoltActionData m_BoltAction; //+0x1C
	RecoilData m_Recoil; //+0x2C
	int m_FireInputAction; //+0x50
	int m_ReloadInputAction; //+0x54
	int m_CycleFireModeInputAction; //+0x58
	float m_TriggerPullWeight; //+0x5C
	float m_RateOfFire; //+0x60
	float m_RateOfFireForBurst; //+0x64
	float m_ClientFireRateMultiplier; //+0x68
	float m_ReloadDelay; //+0x6C
	float m_ReloadTime; //+0x70
	float m_ReloadTimerArray; //+0x78
	float m_ReloadTimeBulletsLeft; //+0x80
	float m_ReloadThreshold; //+0x84
	float m_PreFireDelay; //+0x88
	float m_AutomaticDelay; //+0x8C
	ReloadLogic m_ReloadLogic; //+0x90
	ReloadType m_ReloadType; //+0x94
	FireLogicType m_FireLogicType; //+0x98
	FireLogicType m_FireLogicTypeArray; //+0xA0
	bool m_HoldOffReloadUntilFireRelease; //+0xA8
	bool m_HoldOffReloadUntilZoomRelease; //+0xA9
	bool m_ForceReloadActionOnFireTrigger; //+0xAA
	bool m_AlwaysAutoReload; //+0xAB
};

class WeaponFiringData: public DataContainer
{
public:
	class RumbleFiringData
	{
	public:
		float m_LowRumble; //+0x0
		float m_HighRumble; //+0x4
		float m_RumbleDuration; //+0x8
	};

	FiringFunctionData m_PrimaryFire; //+0x10
	float m_DeployTime; //+0x18
	float m_ReactivateCooldownTime; //+0x1C
	float m_DisableZoomOnDeployTime; //+0x20
	float m_AltDeployTime; //+0x24
	int m_AltDeployId; //+0x28
	void* m_WeaponSway; //+0x30 WeaponSwayData
	RumbleFiringData m_Rumble; //+0x38
	float m_SupportDelayStand; //+0x44
	float m_SupportDelayProne; //+0x48
	bool m_UseAutoAiming; //+0x4C
	bool m_InflictSelfDamage; //+0x4D
	bool m_ShowEnemyNametagOnAim; //+0x4E
	bool m_ReloadWholeMags; //+0x4F
	bool m_DisableReloadWhileSprinting; //+0x50
	bool m_AbortReloadOnSprint; //+0x51
};

class ToolData: public DataContainer
{
public:
	bool m_IsAlwaysActive; //+0x10
};

class WeaponData : public ToolData
{
public:
	bool m_ShowLaserPaintedVehicles; //+0x18
};

class WeaponEntityData : public GameComponentEntityData
{
public:
	class GameAIWeaponData
	{
	public:
		char aAsset[24]; //+0x00 Inherited
	};

	WeaponClassEnum m_WeaponClass; //+0x80
	WeaponClassEnum m_WeaponStates; //+0x88
	WeaponFiringData* m_WeaponFiring; //+0x90
	WeaponData* m_CustomWeaponType; //+0x98
	GameAIWeaponData* m_AIData; //+0xA0
};

class ClientSoldierWeapon
{
public:
	char _0x0000[48];
	WeaponEntityData* m_data; //0x0030 
	char _0x0038[18768];
	ClientSoldierAimingSimulation* m_authorativeAiming;    //0x4988 
	char _0x4990[24];
	ClientWeapon* m_pWeapon;                            //0x49A8  
	char pad_0x49B0[16];                                //0x49B0 
	WeaponFiring* m_pPrimary;                            //0x49C0 
};

class ClientSoldierWeaponsComponent
{
public:

	class ClientAnimatedSoldierWeaponHandler
	{
	public:
		ClientSoldierWeapon* m_WeaponList[7]; //0x0000 
	}; 

	enum WeaponSlot
	{
		M_PRIMARY = 0, 
		M_SECONDARY = 1,
		M_GADGET = 2,
		M_GRENADE = 6,
		M_KNIFE = 7                 
	};

	char pad_0x0000[208];
	D3DXMATRIX m_weaponTransform; //0x00D0 
	char pad_0x0110[1680];
	ClientAnimatedSoldierWeaponHandler* m_handler; //0x07A0 
	char pad_0x07A8[32];
	ClientAntAnimatableComponent* m_animatableComponent[2]; //0x07C8 
	ClientSoldierEntity* m_soldier; //0x07D8 
	char pad_0x07E0[456];
	WeaponSlot m_activeSlot; //0x09A8
	WeaponSlot m_lastActiveSlot; //0x09AC 
	WeaponSlot m_lastActiveWeaponSlot; //0x09B0 
	char pad_0x09B4[28];
	int m_currentZoomLevel; //0x09D0 
	int m_zoomLevelMax; //0x09D4 
	int m_zeroingDistanceLevel; //0x09D8 
	BYTE m_noMagnifierAccessory; //0x09DC 
	char pad_0x09DD[779];
	float m_timeSinceLastShot; //0x0CE8 

	ClientSoldierWeapon* GetActiveSoldierWeapon( )
	{
		if(!IsValidPtr(m_handler))
			return NULL;

		if ( m_activeSlot == 0 || m_activeSlot == 1 ) 
			return m_handler->m_WeaponList[m_activeSlot]; 
		else 
			return NULL; 
	};
	int GetSlot()
	{
		return m_activeSlot;
		//0 or 1 is primary or secondary
	}
};

class UpdatePoseResultData
{
public:

	enum BONES
	{
		BONE_HEAD = 104,
		BONE_NECK = 142,
		BONE_SPINE2 = 7,
		BONE_SPINE1 = 6,
		BONE_SPINE = 5,
		BONE_LEFTSHOULDER = 9,
		BONE_RIGHTSHOULDER = 109,
		BONE_LEFTELBOWROLL = 11,
		BONE_RIGHTELBOWROLL = 111,
		BONE_LEFTHAND = 15,
		BONE_RIGHTHAND = 115,
		BONE_LEFTKNEEROLL = 188,
		BONE_RIGHTKNEEROLL = 197,
		BONE_LEFTFOOT = 184,
		BONE_RIGHTFOOT = 198
	};

	class QuatTransform
	{
	public:
		D3DXVECTOR4 m_TransAndScale; // 0x0000
		D3DXVECTOR4 m_Rotation;  // 0x0010
	}; // Size 0x0020

	QuatTransform* m_LocalTransform;  // 0x0000
	QuatTransform* m_WorldTransform; // 0x0008
	QuatTransform* DB00147A; // 0x0010
	QuatTransform* DB00147B; // 0x0018
	QuatTransform* DB00147D; // 0x0020
	QuatTransform* m_ActiveWorldTransforms; // 0x0028
	QuatTransform* m_ActiveLocalTransforms; // 0x0030
	int m_Slot; // 0x0038
	int m_ReaderIndex;  // 0x003C
	BYTE m_ValidTransforms; // 0x0040
	BYTE m_PoseUpdateEnabled; // 0x0041
	BYTE m_PoseNeeded; // 0x0042
	BYTE pad44[0x01]; // 0x0044
};

class GameAnimatable 
{ 
public: 
	BYTE pad[0xD4]; 
	bool m_hadVisualUpdate;  // 0xD4 
};

class ClientAntAnimatableComponent
	// :public ClientGameComponent
{
public:
	BYTE pad00[0x68];  
	GameAnimatable* m_handler;    //0x68
};  

class ClientRagDollComponent
{
public:
	char pad_0x0000[136];
	UpdatePoseResultData m_ragdollTransforms; //0x0088 
	char pad_0x0090[1344];
	D3DXMATRIX m_Transform; //0x05D0 
};

class BoneCollisionComponent
{
public:

	class BoneTransformInfo
	{
	public:
		D3DXMATRIX transform;    // 0x00
		D3DXVECTOR4 position;    // 0x40
	};

	char pad_0x0000[80];
	__int64 m_skeleton; //0x0050 
	BoneTransformInfo* m_boneCollisionTransforms; //0x0058 
};

class VehicleEntityData
{
public:
	class VehicleHudData
	{
	public:
		D3DXVECTOR4 m_CustomizationOffset; //0x0000 
		__int64 m_Customization; //0x0010 
		__int64 m_MinimapIcon; //0x0018 
		char* m_IconName; //0x0020 char* vehicles.tank  
		__int64 m_Texture; //0x0028 
		__int64 m_VehicleItemHash; //0x0030 
		BYTE m_RotateInMap; //0x0038 
		BYTE m_ShowHealth; //0x0039 
		char _0x003A[10];
	};//Size=0x0044

	class VehicleHealthZone
	{
	public:
		float m_MaxHealth; //0x0000 
		float m_MaxShieldHealth; //0x0004 
		float m_MinDamageAngle; //0x0008 
		float m_DamageAngleMultiplier; //0x000C 
		__int64 m_DamageAngleMultiplierCurve; //0x0010 
		float m_VerticalFactor; //0x0018 
		int m_UseDampingAngleCalculation; //0x001C 
	};//Size=0x0020

	__int64 VTable; //0x0000 
	char _0x0008[104];
	int m_enabled; //0x0070 
	char _0x0074[92];
	VehicleHudData m_HudData; //0x00D0 
	D3DXVECTOR4 m_FLIRKeyColor; //0x0114 
	D3DXVECTOR4 m_InteractionOffset; //0x0124 
	char* m_ControllableType; //0x0130 char* Gameplay/Vehicles/M1A2/M1Abrams 
	float m_DisabledDamageThreshold; //0x0138 
	float m_PreDestructionDamageThreshold; //0x013C 
	VehicleHealthZone m_FrontHealthZone; //0x0140 
	VehicleHealthZone m_RearHealthZone; //0x0160 
	VehicleHealthZone m_LeftHealthZone; //0x0180 
	VehicleHealthZone m_RightHealthZone; //0x01A0 
	VehicleHealthZone m_TopHealthZone; //0x01C0 
	float m_TopHitHeight; //0x01E0 
	float m_TopHitAngle; //0x01E4 
	float m_RegenerationDelay; //0x01E8 
	float m_RegenerationRate; //0x01EC 
	float m_ArmorMultiplier; //0x01F0 
	float m_RegenerationDelayMultiplier; //0x01F4 
	float m_RegenerationRateMultiplier; //0x01F8 
	float m_EmergencyRepairHealth; //0x01FC 
	float m_DecayDelay; //0x0200 
	float m_DecayRate; //0x0204 
	char _0x0208[8];
	float m_CriticalDamageTime; //0x0210 
	char _0x0214[12];
	float m_PreExplosionTime; //0x0220 
	char _0x0224[28];
	char* m_NameSid; //0x0240 char* ID_P_VNAME_M1ABRAMS   
	int m_MaxPlayersInVehicle; //0x0248 
	float m_MinSpeedForMineActivate; //0x024C 
	float m_UpsideDownDamage; //0x0250 
	float m_UpsideDownDelay; //0x0254 
	float m_UpsideDownAngle; //0x0258 
	float m_WaterDamage; //0x025C 
	float m_BelowWaterDamageDelay; //0x0260 
	float m_WaterDamageOffset; //0x0264 
	float m_VelocityDamageThreshold; //0x0268 
	float m_VelocityDamageMagnifier; //0x026C 
	float m_KillSoldierMinCollisionSpeed; //0x0270 
	float m_ExitSpeedThreshold; //0x0274 
	float m_ExitSpeedDirectionThreshold; //0x0278 
	float m_FLIRValue; //0x027C 
	int m_MPMode; //0x0280 
	float m_ExitCameraSwitchDelay; //0x0284 
	char _0x0288[24];
	float m_LockingTimeMultiplier; //0x02A0 
	char _0x02A4[36];
	float m_NameTagHeightScale; //0x02C8 
	float m_SpottingFOVScale; //0x02CC 
	BYTE m_AllowVehicleOutSideCombatAreas; //0x02D0 
	BYTE m_UseTopZone; //0x02D1 
	BYTE m_HealthZonesShareDmg; //0x02D2 
	BYTE m_UseProtectedShields; //0x02D3 
	BYTE m_ShowPlayerHealth; //0x02D4 
	BYTE m_ForegroundRenderCockpitMesh; //0x02D5 
	BYTE m_MotionBlurMask; //0x02D6 
	BYTE m_SuppressDamageByPassengers; //0x02D7 
	BYTE m_IsAffectedByEMP; //0x02D8 
	BYTE m_CanTakeDynamicFireDmg; //0x02D9 
	BYTE m_ThrowOutSoldierInsideOnWaterDamage; //0x02DA 
	BYTE m_IgnoreSoldierCollision; //0x02DB 
	BYTE m_ChoseExitPointByDirection; //0x02DC 
	BYTE m_ExitAllowed; //0x02DD 
	BYTE m_EnableGroundMapLighting; //0x02DE 
	BYTE m_UseAsTeamSpawner; //0x02DF 
	BYTE m_IsLockable; //0x02E0 
	BYTE m_NeverReportVehicleEmpty; //0x02E1 
	BYTE m_UseLowAltitudeHeatSignature; //0x02E2 
	BYTE m_UseSpottingTargetComponentForRayCast; //0x02E3 
	BYTE m_EquipmentFakeVehicle; //0x02E4 
	BYTE m_ExplosionPacksAttachable; //0x02E5 
};

class Asset :public DataContainer 
{
public:
	char* name;
};

class PhysicsEntityData 
{
public:
	DWORD N0129C30A; //0x0000 
	char _0x0004[8];
	Asset* asset; //0x000C 
	char _0x0010[64];
};//Size=0x0050

class PhysicsEntity
{
public:
	char _0x0000[136];
	PhysicsEntityData* data; //0x0088 
	char _0x008C[20];
};

class ClientControllableEntity
{
public:
	class HealthComponent
	{
	public:
		char _0x0000[32];
		float m_Health; //0x0020 
		float m_MaxHealth; //0x0024 
		char _0x0028[16];
		float m_vehicleHealth; //0x0038 
	};//Size=0x003C

	virtual TypeInfo* GetType( );
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); //
	virtual void GetTransform( D3DXMATRIX* mTransform ); 
	virtual void Function24(); //
	virtual void Function25(); //
	virtual void Function26(); //
	virtual void Function27();
	virtual void Function28(); //
	virtual void Function29(); //
	virtual void Function30(); //
	virtual void Function31(); //
	virtual void Function32(); //
	virtual void Function33(); //
	virtual void Function34(); //
	virtual void Function35(); //
	virtual void Function36(); //
	virtual void Function37(); //
	virtual void Function38(); //
	virtual void Function39(); //
	virtual void Function40(); //
	virtual void Function41(); //
	virtual void Function42(); //
	virtual void Function43(); //
	virtual void Function44(); //
	virtual void Function45(); //
	virtual void Function46(); //
	virtual void Function47(); //
	virtual void Function48(); //
	virtual void Function49(); //
	virtual void Function50(); //
	virtual void Function51(); //
	virtual void Function52(); //
	virtual void Function53(); //
	virtual void Function54(); //
	virtual void Function55(); //
	virtual void Function56(); //
	virtual void Function57(); //
	virtual void Function58(); //
	virtual void Function59(); //
	virtual PhysicsEntity* GetPhysiscsEntity(); //physics
	virtual D3DXVECTOR3* GetVelocity(); //velocity
	virtual void Function62(); //
	virtual void Function63(); //
	virtual void Function64(); //
	virtual void Function65(); //
	virtual void Function66(); //
	virtual void Function67(); //
	virtual void Function68(); //
	virtual void Function69(); //
	virtual void Function70(); //
	virtual void Function71(); //
	virtual void Function72(); //
	virtual void Function73(); //
	virtual void Function74(); //

	char _0x0000[32];
	Components* m_pComponents; //0x0028 
	VehicleEntityData* m_data; //0x0030 
	char _0x0038[264];
	HealthComponent* m_pHealthComponent; //0x0140 
	char _0x0148[64];

};//Size=0x0188

class ClientCharacterEntity : public ClientControllableEntity
{
public:
	char pad_0x0188[80]; //72 with vt? 0x30
	//CharacterPhysicsEntity* m_PhysicsEnt;//0x1b8
	//char pad_0x1C0[0x18];
	ClientPlayer* m_pPlayer; //0x01D8 
	ClientAntAnimatableComponent* m_animatableComponent[2]; //0x01E0 
	__int64 m_pCharacterCameraComponent; //0x01F0 
	char pad_0x01F8[136];
};

class CharacterPhysicsData
{
public:

	class CharacterSprintData
	{
	public:
		char pad_0x00[0x10]; //+0x00
		float m_SprintPowerDecreasePerSecond; //+0x10
		float m_SprintPowerIncreasePerSecond; //+0x14
		float m_SprintMinimumPower; //+0x18
		bool m_AllowContinousSprinting; //+0x1C
	};

	char pad_0x00[0x18]; //+0x00 Inherited
	__int64 m_Poses; //+0x18
	__int64 m_States;//+0x20
	int m_DefaultState; //+0x28
	char pad_0x2C[0x4];
	CharacterSprintData* m_Sprint; //+0x30
	__int64 m_MaterialPair;//+0x38
	int m_PushableObjectWeight;//+0x3C
	float m_Mass; //+0x40
	float m_MaxAscendAngle; //+0x44
	float m_PhysicalRadius; //+0x48
	float m_EnterSwimStateDepth; //+0x4C
	float m_ExitSwimStateDepth; //+0x50
	float m_InputAcceleration; //+0x54
	float m_LadderAcceptAngle; //+0x58
	float m_LadderAcceptAnglePitch; //+0x5C
	float m_JumpPenaltyTime; //+0x60
	float m_JumpPenaltyFactor; //+0x64
	float m_RadiusToPredictCollisionOnCharacters; //+0x68
	bool m_AllowPoseChangeDuringTransition; //+0x6C
	bool m_AutoPushAwayFromWallsInProne; //+0x6D
};

class SoldierEntityData
{
public:
	class SoldierSprintSettingsData
	{
	public:
		char pad_0x00[0x10]; //+0x00
		float m_Fov; //+0x10
		float m_FovInDelay; //+0x14
		float m_FovInTime; //+0x18
		float m_FovOutDelay; //+0x1C
		float m_FovOutTime; //+0x20
		float m_RecoverTime; //+0x24
		float m_SprintToProneRecoverTime; //+0x28
		float m_InterruptingActions; //+0x30
	};

	enum PersonViewMode
	{
		PersonViewMode_FirstPerson = 0,
		PersonViewMode_ThirdPerson = 1
	};

	enum PlayerSpawnType
	{
		PlayerSpawnType_HumanPlayer = 0,
		PlayerSpawnType_AiPlayer = 1,
		PlayerSpawnType_Actor = 2,
		PlayerSpawnType_BrainAI = 3,
		PlayerSpawnType_Ai2Player = 300
	};

	char pad_0x00[0x90];
	int m_DefaultTeam; //+0x90
	float m_LowHealthThreshold; //+0x94 ControllableEntityData
	int m_MaterialPair; //+0x98
	bool m_UsePrediction; //+0x9C
	bool m_ResetTeamOnLastPlayerExits; //+0x9D
	bool m_Immortal; //+0x9E
	bool m_FakeImmortal; //+0x9F
	bool m_ForceForegroundRendering; //+0xA0
	char pad_0x00A1[0xF];
	float m_MaxHealth; //0xB0 CharacterEntityData 
	PersonViewMode m_DefaultViewMode; //0x00B4 
	PlayerSpawnType m_PlayerSpawnType; //0x00B8
	char pad_0xBC[0x14]; //+0xBC
	bool m_CharacterLightingEnable; //+0xD0
	char pad_0x00BC[156];
	CharacterPhysicsData* m_CharacterPhysics; //+0x118
	SoldierSprintSettingsData* m_SprintSettings; //+0x120
	bool m_HidableMeshParts; //+0x128
	char pad_0x129[0x1]; //+0x129
	float m_ImpulseReactionTime; //+0x130
	char pad_0x134[0x4];
	__int64 m_HealthModule; //+0x138
	__int64 m_AbortSpawnInvisibilityInputs; //+0x140
	bool m_BreathControl; //+0x148
	char pad_0x149[0x1]; //+0x149
	__int64 m_CollisionInfo; //+0x150
	float m_FLIRValue; //0x0158 
	float m_ExplosionDamageModifier; //0x015C 
	float m_RegenerationDelayModifier; //0x0160 
	float m_FallDamageThreshold; //0x0164 
	BYTE m_UseSpineXRotation; //0x0168 
	BYTE m_ShowWeaponWhenDead; //0x0169 
	BYTE m_EnableGroundmapLighting; //0x016A 
	BYTE m_LowerGunOnOwnTeam; //0x016B 
	BYTE m_ProximityCheck; //0x016C 
	BYTE m_FreeSpaceCheck; //0x016D 
	BYTE m_CollisionEnabled; //0x016E 
	BYTE m_PhysicsControlled; //0x016F 
	BYTE m_IsPushable; //0x0170 
	BYTE m_HumanPlayerControlled; //0x0171 
	BYTE m_InteractiveManDownAllowed; //0x0172 
	BYTE m_ShowNametag; //0x0173 
};

class SoldierEntity
{
public:
	class CharacterPhysicsEntity_CharacterInput
	{
		D3DXVECTOR4 m_forwardVector;                            //0x0090 //3d Model, not camera
		D3DXVECTOR4 m_upVector;                                 //0x00A0
		D3DXVECTOR4 m_characterGravity;                         //0x00B0
		float m_waterLevel_2;                                   //0x00C0
		float m_waterSpeed_2;                                   //0x00С4
		float m_speedScale;                                     //0x00C8
		float m_yaw;                                            //0x00CC
		float m_pitch;                                          //0x00D0
		float m_forwardInput;                                   //0x00D4 /  1 fwd, -1 bwd
		float m_strafeInput;                                    //0x00D8 / -1 left, 1 right
		float m_sprintMultiplier;                               //0x00DC
		char pad_0x00E0[4];                                     //0x00E0
		bool m_tryJump_1;                                       //0x00E4
		bool bUnkn_1;                                           //0x00E5
		bool m_tryJump_2;                                       //0x00E6
		bool m_sprint;                                          //0x00E7
		char pad_0x00E8[24];                                    //0x00E8
	};

	virtual BoneCollisionComponent* boneCollisionComponent(); // not tested
	virtual D3DXMATRIX& soldierTransform();
	virtual bool SoldierEntity_funct2();
	virtual bool SoldierEntity_funct3();
	virtual bool isFiring();
	virtual bool isReloading();
	virtual bool SoldierEntity_funct6();
	virtual WeaponSway* getWeaponSway();
	virtual WeaponFiring* getCurrentWeaponFiring();
	virtual void* getCurrentWeaponFiringData();     // PrimaryFire* m_pPrimaryFire == WeaponFiringData* ;
	virtual bool SoldierEntity_funct10();
	virtual float moveSpeedMultiplier();


	SoldierEntityData* m_pSoldierData; //0x0008 
	char pad_0x0010[44];                                    //0x0010
	float m_headRotationSpeed;                              //0x003C <?> - 5.0
	bool m_allowedToMoveEyes ;                              //0x0040 <?> - true
	char pad_0x0041[39];                                    //0x0041
	__int64 ptrUnkn_1;                                      //0x0068
	__int64 ptrUnkn_2;                                      //0x0070
	__int64 ptrUnkn_3;                                      //0x0078
	char pad_0x0080[16];									//0x0080
	CharacterPhysicsEntity_CharacterInput m_CharInputClass; //0x0090 
	__int64 m_pBoneCollisionComponent; //0x0100
	float m_moveSpeedMultiplier; //0x0108 
	float m_sprintSpeedMultiplier; //0x010C 
	float m_jumpHeightMultiplier; //0x0110 
	float m_lookSpeedMultiplier; //0x0114 
	float m_waterLevel; //0x0118 
	float m_waterSpeed; //0x011C 
	char pad_0x0120[8];
	__int64 m_pCharacterEntity; //0x0128 
};
class CharacterPhysicsEntity
{
public:
	virtual TypeInfo* getType();
	virtual void deconstructor(); //
	virtual void addToWorld(); //
	virtual void removeFromWorld(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //

	char  pad_0x0008[128];            //00 
	void* m_pad;                //88 
	D3DXMATRIX* m_gameWorldTransform;        //90 
	void* m_pad2;                //98 
	int   m_Unk1;                    //A0 
	int   m_currentPose; //0x00A4 
	int   m_changingToPose; //0x00A8 
	float m_poseTransitionTimer; //0x00AC 
	char _0x00B0[32];
	D3DXVECTOR3 m_currentLocalEyePosition; //0x00D0 
	int   alignmentpad; //0x00DC 
	float m_mass; //0x00E0 
	char _0x00E4[4];
	CharacterPhysicsData* m_data; //0x00E8 

	__forceinline D3DXVECTOR3 worldEyePosition() 
	{ 
		if( !m_gameWorldTransform )  
			return D3DXVECTOR3( 0, 0, 0 ); 

		D3DXVECTOR3 Trans=D3DXVECTOR3
		(m_gameWorldTransform->_41,
		m_gameWorldTransform->_42,
		m_gameWorldTransform->_43);

		return D3DXVECTOR3(  
			( Trans.x + m_currentLocalEyePosition.x ),  
			( Trans.y + m_currentLocalEyePosition.y ),  
			( Trans.z + m_currentLocalEyePosition.z ) ); 
	} 
};//Size=0x00F0

class ClientSoldierPrediction
{
public:
	virtual void            function_0();
	virtual D3DXVECTOR3		getPosition();
	virtual void            setPosition( D3DXVECTOR3 pos );

	CharacterPhysicsEntity* m_characterPhyEntity; //0x0008 
	char _0x0010[16];
	D3DXQUATERNION m_ParachuteRotation; //0x0020 
	D3DXVECTOR3 m_Position; //0x0030 
	int alignmentpad; //0x003C 
	D3DXVECTOR3 surfaceVelocity; //0x0040 
	int alignmentpad2; //0x004C 
	D3DXVECTOR3 m_Velocity; //0x0050 
	int alignmentpad3; //0x005C 
	D3DXVECTOR3 groundNormal; //0x0060 
	int alignmentpad4; //0x006C 
	int groundSupported; //0x0070 
	int groundMaterialIndex; //0x0074 
	int m_state; //0x0078 
	BYTE m_Pose; //0x007C 
	char _0x007D[3];
	BYTE m_ChangingToPose; //0x0080 
	char _0x0081[23];
	int Event; //0x0098 
	BYTE PlayerState; //0x009C 
};//Size=0x009D

class ClientSoldierEntity : public ClientCharacterEntity,    // +0x000
	public SoldierEntity            // +0x280
{    
public:

	class BreathControlHandler 
	{ 
	public: 
		char _0x0000[56]; 
		float m_breathControlTimer; //0x0038  
		float m_breathControlMultiplier; //0x003C  
		float m_breathControlPenaltyTimer; //0x0040  
		float m_breathControlpenaltyMultiplier; //0x0044  
		float m_breathControlActive; //0x0048  
		float m_breathControlInput; //0x004C  
		float m_breathActive; //0x0050  
		char _0x0054[4]; 
		float m_Enabled; //0x0058  
	};  

	class SprintInputHandler
	{
	public:
		int m_currentState; //0x0000 
		float m_doubleTapTimer; //0x0004 
		float m_sprintReleaseTimer; //0x0008 
		int m_waitForSprintRelease; //0x000C 
	};

	char pad_0x03B0[216];
	__int64 m_pVehicleEntry; //0x0488 
	ClientSoldierPrediction* m_pPredictedController; //0x0490 
	char pad_0x0498[64];
	float m_authorativeYaw; //0x04D8 
	float m_authorativePitch; //0x04DC 
	int m_aimingEnabled; //0x04E0 
	float m_cachedPitch; //0x04E4 
	__int64 m_soldierSound; //0x04E8 
	int m_poseType; //0x04F0 
	char pad_0x04F4[92];
	ClientSoldierWeaponsComponent* m_soldierWeaponsComponent; //0x0550 
	__int64 m_bodyComponent; //0x0558 
	ClientRagDollComponent* m_ragdollComponent; //0x0560 
	BreathControlHandler* m_breathControlHandler; //0x0568 
	char pad_0x0570[16];
	SprintInputHandler* m_sprintInputHandler; //0x0580 
	int padThis; //0x0588 
	float m_timeSinceLastSprinted; //0x058C 
	BYTE m_sprinting; //0x0590 
	BYTE m_occluded; //0x0591 
	char pad_0x0592[286];
	ClientCharacterEntity* m_pClientCharacterEntity; //0x06B0 
	char pad_0x06B8[416];

	bool isVisible( )
	{
		return !m_occluded;
	}

	ClientSoldierWeapon* GetActiveWeapon( )
	{
		if ( !m_soldierWeaponsComponent ) 
			return NULL;     

		if ( ( DWORD_PTR )m_soldierWeaponsComponent > 0xFFFFFFFF ) 
			return NULL; 

		if ( IsBadReadPtr( m_soldierWeaponsComponent, 8 ) ) 
			return NULL; 

		if (!IsValidPtr(m_soldierWeaponsComponent))
			return NULL;

		return m_soldierWeaponsComponent->GetActiveSoldierWeapon( );
	}

	SoldierEntityData* GetSoldierEntityData()
	{
		return (SoldierEntityData*)this+0x08;
	}
};

class AxisAlignedBox 
{ 
public: 
	__declspec( align( 16 ) )D3DXVECTOR3 min; 
	__declspec( align( 16 ) )D3DXVECTOR3 max; 
};  

class ClientChassisComponent
{
public:
	char _0x0000[448];
	D3DXVECTOR3 m_Velocity; //0x01C0 
};//Size=0x0200

class ClientVehicleEntity : public ClientControllableEntity
{
public:
	char _0x0188[184];
	float m_waterLevel; //0x0240 
	float m_terrainLevel; //0x0244 
	float m_waterLevelUpdateTimer; //0x0248 
	float m_terrainLevelUpdateTime; //0x024C 
	AxisAlignedBox m_childrenAABB; //0x0250 
	char _0x0268[24];
	D3DXVECTOR3 m_Velocity; //0x0280 
	char _0x028C[4];
	D3DXVECTOR3 m_prevVelocity; //0x0290 
	char _0x029C[312];
	ClientChassisComponent* m_Chassis; //0x03E0 
};//Size=0x0440

class ClientPlayer
{
public:
	class ClientPlayerView 
	{ 
	public: 
		char _0x0000[248]; 
		ClientPlayer* m_Owner; //0x00F8  
		char _0x0100[272]; 
	};//Size=0x0210

	virtual ~ClientPlayer( ); 
	virtual DWORD_PTR GetCharacterEntity( ); // ClientSoldierEntity + 188 
	virtual DWORD_PTR GetCharacterUserData( ); // PlayerCharacterUserData
	virtual EntryComponent* GetEntryComponent( );
	virtual bool InVehicle( );
	virtual unsigned int getId();
	virtual bool hasUnlockAsset(LPVOID, bool);
	virtual void getUnlockAssets( eastl::vector<LPVOID> *);
	virtual bool isUnlocked(LPVOID);
	//0x28 is super secret ptr
	BYTE pad00[0x38];                                // 0x000
	CHAR szName[0x10];                                // 0x040
	BYTE pad38[0x135C];                                // 0x050 C6C
	int m_teamId;                                    // 0xCBC
	BYTE padB34[0xE0];                                // 0xCC0 F0
	WeakPtr<ClientCharacterEntity> m_character;				// 0x3C8
	WeakPtr<ClientPlayer> m_player;	
	ClientSoldierEntity* m_pAttachedControllable;    // 0xDB0
	unsigned int m_attachedEntryId;                    // 0xDB8
	ClientSoldierEntity* m_pControlledControllable;    // 0xDC0
	__int64 m_EntryID;
	char _0x0DD0[24]; 
	__int32 m_Id; //0x0DE8  
	__int32 m_ConnectionId; //0x0DEC  
	__int32 m_lastTeamHit; //0x0DF0  
	__int32 m_inputNetworkId; //0x0DF4  
	char _0x0DF8[8]; 
	void* m_pPlayerManager; //0x0E00  
	ClientPlayerView* m_ownPlayerView; //0x0E08  
	ClientPlayerView* m_PlayerView; //0x0E10  
	__int32 m_customHead; //0x0E18  
	char _0x0E1C[4]; 
	void* m_InputActionMap; //0x0E20  
	void* m_InputTranslator; //0x0E28 

	ClientSoldierEntity* GetClientSoldier( )
	{
		if ( this->InVehicle( ) )
			return ( ClientSoldierEntity* )( this->GetCharacterUserData( ) - 0x290 );

		if ( m_pControlledControllable )
			return m_pControlledControllable;

		return NULL;
	}

	ClientVehicleEntity* GetClientVehicleEntity( )
	{
		if ( this->InVehicle( ) )
			return ( ClientVehicleEntity* )m_pAttachedControllable;

		return NULL;
	}
};

class ClientPlayerManager
{
public:
	virtual void function();
	virtual eastl::vector<ClientPlayer*>* getPlayers();
	virtual eastl::vector<ClientPlayer*>* getSpectators();
	BYTE pad00[0x538];                  // 0x00 //was 0x298 //was 2a0
	ClientPlayer*    m_pLocalPlayer;        // 0x2A0
	ClientPlayer**    m_ppPlayers;        // 0x2A8

	ClientPlayer* GetPlayerById( unsigned int id )
	{
		if ( id < 70 )
			return this->m_ppPlayers[id];

		return NULL;
	}
};

class RayCastHit
{
public:
	D3DXVECTOR4 m_position; //0x0000
	D3DXVECTOR4 m_normal;    //0x0010
	char pad_0x0020[80];
};

class IPhysicsRayCaster
{
public:

	enum RayCastFlags
	{
		NoCheck = 0,
		CheckDetailMesh = 0x0DB,
		IsAsyncRaycast = 0x2,
		DontCheckWater = 0x0FD,
		DontCheckTerrain = 0x07A,
		DontCheckRagdoll = 0x10,
		DontCheckCharacter = 0x20,
		DontCheckGroup = 0x40,
		DontCheckPhantoms = 0x80,
	};

	virtual bool PhysicsRayQuery( const char* identifier, D3DXVECTOR4* from, D3DXVECTOR4* to, RayCastHit* hit, int flag, eastl::fixed_vector<PhysicsEntity const*,8,0>* PhysicsEntityList );
};

class GameWorld
{
public:
	BYTE pad00[0x58];    // 0x00
	IPhysicsRayCaster* m_RayCaster;  // 0x0058
};

class WorldRenderSettings
{
public:
	char pad_0x0000[120];
	float m_motionBlurScale; //0x0078 
	float m_motionBlurMax; //0x007C 
	float m_motionBlurNoiseScale; //0x0080 
	DWORD m_motionBlurQuality; //0x0084 
	DWORD m_dynamicEnvmapResolution; //0x0088 
	DWORD m_maxDecalVolumeCount; //0x008C 
	DWORD m_motionBlurMaxSampleCount; //0x0090 
	DWORD m_motionBlurFrameAverageCount; //0x0094 
	float m_motionBlurMaxFrameTime; //0x0098 
	float m_forceMotionBlurDepthCutoff; //0x009C 
	float m_forceMotionBlurCutoffGradientScale; //0x00A0 
	DWORD m_multisampleCount; //0x00A4 
	float m_multisampleThreshold; //0x00A8 
	DWORD m_maxSpotLightShadowCount; //0x00AC 
	DWORD m_reflectionEnvmapSize; //0x00B0 
	float m_spotLightNearPlane; //0x00B4 
	float m_subSurfaceRolloff; //0x00B8 
	DWORD m_unk0; //0x00BC 
	DWORD m_maxSpotLightCount; //0x00C0 
	DWORD m_spotLightShadowmapResolution; //0x00C4 
	DWORD m_spotLightShadowmapQuality; //0x00C8 
	char pad_0x00CC[105];
	BYTE m_drawSky; //0x0135 
	BYTE m_drawSunRays; //0x0136 
	BYTE m_drawFog; //0x0137 
	BYTE m_drawSunBlur; //0x0138 
	char pad_0x0139[285];
	BYTE m_drawSunRays2; //0x0256 

	static WorldRenderSettings* GetInstance( )
	{
		return *( WorldRenderSettings** )OFFSET_WORLDRENDERSETTINGS;
	}
};

class HavokPhysicsManager
{
public:
	BYTE pad00[0x120];            // 0x00
	GameWorld* m_GameWorld;        // 0x120
};

class ClientGameContext
{
public:
	BYTE pad00[0x20];                        // 0x00
	DWORD_PTR m_GameTime;                    // 0x20
	HavokPhysicsManager* m_pPhysicsManager;    // 0x28
	BYTE pad30[0x30];                        // 0x30
	ClientPlayerManager* m_pPlayerManager;    // 0x60

	static ClientGameContext* GetInstance( )
	{
		return *( ClientGameContext** )( OFFSET_GAMECONTEXT );
	}
};

class RenderView
{
public:
	char _0x0000[64];
	D3DXMATRIX m_Transform; //0x0040 
	char _0x0080[52];
	float m_FovY; //0x00B4 
	float defualtFovY; //0x00B8 
	float nearPlane; //0x00BC 
	float farPlane; //0x00C0 
	float m_Aspect; //0x00C4 
	float orthoWidth; //0x00C8 
	float orthoHeight; //0x00CC 
	char _0x00D0[384];
	float m_FovX; //0x0250 
	float depthHeightRatio; //0x0254 
	float fovScale; //0x0258 
	float fovScaleSqr; //0x025C 
	D3DXMATRIX m_viewMatrix; //0x0260 
	D3DXMATRIX m_viewMatrixTranspose; //0x02A0 
	D3DXMATRIX m_viewMatrixInverse; //0x02E0 
	D3DXMATRIX m_ProjectionMatrix; //0x0320 
	D3DXMATRIX m_viewMatrixAtOrigin; //0x0360 
	D3DXMATRIX m_ProjectionTranspose; //0x03A0 
	D3DXMATRIX m_ProjectionInverse; //0x03E0 
	D3DXMATRIX m_ViewProj; //0x0420 
	D3DXMATRIX m_ViewProjTranspose; //0x0460 
	D3DXMATRIX m_ViewProjInverse; //0x04A0 
	D3DXMATRIX m_UnknMatrix; //0x04E0   
	D3DXMATRIX m_Transform2; //0x0520 
	D3DXMATRIX m_UnknMatrix2; //0x0560 
};

class GameRenderSettings: public DataContainer
{
public:
	unsigned int m_InactiveSkipFrameCount; //+0x10
	float m_ResolutionScale; //+0x14
	unsigned int m_XenonRingBufferSize; //+0x18
	unsigned int m_XenonLinearFrameBufferSize; //+0x1C
	unsigned int m_XenonPresentImmediateThreshold; //+0x20
	unsigned int m_XenonGammaRampType; //+0x24
	float m_Ps3VideoGamma; //+0x28
	unsigned int m_Ps3FrameMainBufferSize; //+0x2C
	unsigned int m_Ps3FrameLocalBufferSize; //+0x30
	unsigned int m_Ps3VSyncMethod; //+0x34
	float m_CameraCutMaxFrameTranslation; //+0x38
	float m_NearPlane; //+0x3C
	float m_ViewDistance; //+0x40
	float m_ForceFov; //+0x44
	float m_FovMultiplier; //+0x48
	float m_ForceOrthoViewSize; //+0x4C
	float m_EdgeModelScreenAreaScale; //+0x50
	float m_EdgeModelViewDistance; //+0x54
	int m_EdgeModelForceLod; //+0x58
	float m_EdgeModelLodScale; //+0x5C
	unsigned int m_EdgeModelMaxVisibleInstanceCount; //+0x60
	float m_StaticModelPartOcclusionMaxScreenArea; //+0x64
	unsigned int m_StaticModelCullJobCount; //+0x68
	unsigned int m_SplitScreenTestViewCount; //+0x6C
	unsigned int m_SplitScreenTestCase; //+0x70
	float m_ForceBlurAmount; //+0x74
	float m_ForceWorldFadeAmount; //+0x78
	float m_StereoCrosshairMaxHitDepth; //+0x7C
	float m_StereoCrosshairRadius; //+0x80
	float m_StereoCrosshairDampingFactor; //+0x84
	bool m_Enable; //+0x88
	bool m_NullRendererEnable; //+0x89
	bool m_JobEnable; //+0x8A
	bool m_BuildJobSyncEnable; //+0x8B
	bool m_EarlyGpuSyncEnable; //+0x8C
	bool m_DrawDebugInfo; //+0x8D
	bool m_DrawScreenInfo; //+0x8E
	bool m_Fullscreen; //+0x8F
	bool m_ForceVSyncEnable; //+0x90
	bool m_MovieVSyncEnable; //+0x91
	bool m_VSyncFlashTestEnable; //+0x92
	bool m_MantleEnable; //+0x93
	bool m_XenonBufferTwoFramesEnable; //+0x94
	bool m_XenonRes1280x704Enable; //+0x95
	bool m_Ps3LinearFrameCmdBufEnable; //+0x96
	bool m_Ps3CellMemoryTexturesEnable; //+0x97
	bool m_GcmHudEnable; //+0x98
	bool m_Ps3Res1280x704Enable; //+0x99
	bool m_Gen4bColorRemap; //+0x9A
	bool m_GpuTextureCompressorEnable; //+0x9B
	bool m_EmittersEnable; //+0x9C
	bool m_EntityRenderEnable; //+0x9D
	bool m_DebugRendererEnable; //+0x9E
	bool m_DebugRenderServiceEnable; //+0x9F
	bool m_InitialClearEnable; //+0xA0
	bool m_GpuProfilerEnable; //+0xA1
	bool m_ForceOrthoViewEnable; //+0xA2
	bool m_ForceSquareOrthoView; //+0xA3
	bool m_DestructionVolumeDrawEnable; //+0xA4
	bool m_EdgeModelsEnable; //+0xA5
	bool m_EdgeModelCastShadowsEnable; //+0xA6
	bool m_EdgeModelDepthBiasEnable; //+0xA7
	bool m_EdgeModelShadowDepthBiasEnable; //+0xA8
	bool m_EdgeModelSpuInstancingEnable; //+0xA9
	bool m_EdgeModelUseMainLodEnable; //+0xAA
	bool m_EdgeModelUseLodBox; //+0xAB
	bool m_EdgeModelCullEnable; //+0xAC
	bool m_EdgeModelFrustumCullEnable; //+0xAD
	bool m_EdgeModelOcclusionCullEnable; //+0xAE
	bool m_EdgeModelDrawBoxes; //+0xAF
	bool m_EdgeModelDrawStats; //+0xB0
	bool m_StaticModelEnable; //+0xB1
	bool m_StaticModelMeshesEnable; //+0xB2
	bool m_StaticModelZPassEnable; //+0xB3
	bool m_StaticModelPartCullEnable; //+0xB4
	bool m_StaticModelPartFrustumCullEnable; //+0xB5
	bool m_StaticModelPartOcclusionCullEnable; //+0xB6
	bool m_StaticModelPartShadowCullEnable; //+0xB7
	bool m_StaticModelDrawBoxes; //+0xB8
	bool m_StaticModelDrawStats; //+0xB9
	bool m_StaticModelCullSpuJobEnable; //+0xBA
	bool m_StaticModelSurfaceShaderTerrainAccessEnable; //+0xBB
	bool m_LockView; //+0xBC
	bool m_ResetLockedView; //+0xBD
	bool m_SecondaryStreamingViewEnable; //+0xBE
	bool m_FadeEnable; //+0xBF
	bool m_FadeWaitingEnable; //+0xC0
	bool m_BlurEnable; //+0xC1
};

class GameRenderer
{
public:
	char _0x0000[72];
	GameRenderSettings* m_GameRenderSettings; //0x0048 
	char _0x0050[16];
	RenderView* m_pRenderView;        // 0x60

	static GameRenderer* GetInstance( )
	{
		return *( GameRenderer** )( OFFSET_GAMERENDERER );
	}
};

class Screen
{
public:
	BYTE pad00[0x28];     //0x00
	unsigned int m_Width;    //0x28
	unsigned int m_Height;    //0x2C
	BYTE pad02[0x88];     //0x30
	IDXGISwapChain* m_pSwapChain;  //0xB8
};

class SystemSettings: public DataContainer
{
public:
	char* m_Name; //+0x10
	GamePlatform m_Platform; //+0x18 make enum
};

class DxDisplaySettings : public SystemSettings
{
public:
	char* m_Name; //+0x10
	GamePlatform m_Platform; //+0x18
	bool m_DebugBreakIgnoredIDs; //+0x20
	unsigned int m_FullscreenHeight; //+0x28
	unsigned int m_FullscreenWidth; //+0x2c
	float m_FullscreenRefreshRate; //+0x30
	int m_FullscreenOutputIndex; //+0x34
	int m_PresentInterval; //+0x38
	unsigned int m_PresentImmediateThreshold; //+0x3c
	int m_RenderAheadLimit; //+0x40
	float m_StereoDepth; //+0x44
	float m_StereoConvergenceScale; //+0x48
	float m_StereoSeparationScale; //+0x4c
	float m_StereoSoldierZoomConvergenceScale; //+0x50
	unsigned int m_NvidiaMinDriverVersion; //+0x54
	char* m_AmdMinDriverVersion; //+0x58
	float m_LowResDisplayPlaneScale; //+0x60
	bool m_NullDriverEnable; //+0x64
	bool m_RefDriverEnable; //+0x65
	bool m_WarpDriverEnable; //+0x66
	bool m_Dx10Dot0Enable; //+0x67
	bool m_Dx10Dot1Enable; //+0x68
	bool m_Dx10PlusEnable; //+0x69
	bool m_Dx11Enable; //+0x6a
	bool m_Dx11Dot1Enable; //+0x6b
	bool m_Dx11Dot1RuntimeEnable; //+0x6c
	bool m_CreateMinimalWindow; //+0x6d
	bool m_DriverInternalThreadingEnable; //+0x6e
	bool m_DxDiagDriverDetectionEnable; //+0x6f
	bool m_DebugInfoEnable; //+0x70
	bool m_DebugInfoOutputEnable; //+0x71
	bool m_DebugBreakOnErrorEnable; //+0x72
	bool m_DebugBreakOnWarningEnable; //+0x73
	bool m_DebugBreakOnInfoEnable; //+0x74
	bool m_FullscreenModeEnable; //+0x75
	bool m_Fullscreen; //+0x76
	bool m_WindowBordersEnable; //+0x77
	bool m_VSyncEnable; //+0x78
	bool m_TripleBufferingEnable; //+0x79
	bool m_NvApiEnable; //+0x7a
	bool m_NvPerfHudEnable; //+0x7b
	bool m_AnnotationInterfaceEnable; //+0x7c
	bool m_StereoEnable; //+0x7d
	bool m_StereoSplitScreenEnable; //+0x7e
	bool m_MinDriverRequired; //+0x7f
	bool m_AmdQuadsEnable; //+0x80
	bool m_DepthBoundsExtensionEnable; //+0x81
	bool m_MultiGpuValidationEnable; //+0x82
	bool m_DiscardFrameTempBuffersEnable; //+0x83
	bool m_PixProfilingEnable; //+0x84
	bool m_AsyncCmdListExecutionEnable; //+0x85
	bool m_VideoOutSrgbFullEnable; //+0x86
	bool m_VideoOutSrgbToRec709Enable; //+0x87
	bool m_EndFrameJobEnable; //+0x88
	bool m_LowResDisplayPlaneEnable; //+0x89
	bool m_ForceRenderTargetInEsramTest; //+0x8a
};

class DxRenderer
{
public:
	BYTE pad00[0x38];                    // 0x00
	Screen* m_pScreen;                    // 0x38
	BYTE pad78[0xC0];                    // 0x40
	ID3D11Device* m_pDevice;            // 0x100
	ID3D11DeviceContext* m_pContext;    // 0x108
	char _0x0110[192];
	DxDisplaySettings* m_settings; //0x01D0 
public:
	static DxRenderer* GetInstance( )
	{
		return *( DxRenderer** )( OFFSET_DXRENDERER );
	}
};

class BorderInputNode
{
public:

	class InputCache
	{
	public:
		char pad_0x0000[0x04];
		float flInputBuffer[123]; 
	};

	virtual void init( );
	virtual void exit( );

	//char pad_0x0000[8];
	InputCache* m_inputCache; //0x0008 
	char pad_0x0010[48];
	__int64 vtable_class_40; //0x0040 

	static BorderInputNode* GetInstance( )
	{
		return *( BorderInputNode** )( OFFSET_BORDERINPUTNODE );
	}
};  

class EnlightenRuntimeSettings : public SystemSettings
{
public:
	//char pad_0x00[0x20]; //+0x00 
	D3DXVECTOR3 m_AlbedoDefaultColor; //+0x20
	float m_TemporalCoherenceThreshold; //+0x30
	float m_SkyBoxScale; //+0x34
	float m_MaxPerFrameSolveTime; //+0x38
	int m_MinSystemUpdateCount; //+0x3C
	int m_JobCount; //+0x40
	int m_CubeMapMaxUpdateCount; //+0x44
	int m_CubeMapConvolutionSampleCount; //+0x48
	float m_CubeMapForceGlobalScale; //+0x4C
	int m_LightProbeMaxSourceSolveCount; //+0x50
	int m_LightProbeMaxInstanceUpdateCount; //+0x54
	int m_LightProbeLookupTableGridRes; //+0x58
	float m_LocalLightForceRadius; //+0x5C
	int m_DrawDebugSystemDependenciesEnable; //+0x60
	int m_DrawDebugSystemBoundingBoxEnable; //+0x64
	float m_DrawDebugLightProbeSize; //+0x68
	bool m_Enable; //+0x6C
	bool m_ForceDynamic;//+0x6D
	bool m_ForceUpdateStaticLightingBuffersEnable; //+0x6E
	bool m_SaveRadiosityTexturesEnable; //+0x6F
	bool m_JobsEnable; //+0x70
	bool m_ShadowsEnable; //+0x71
	bool m_SpotLightShadowsEnable; //+0x72
	bool m_CubeMapsEnable; //+0x73
	bool m_CubeMapMip0OnlyEnable; //+0x74
	bool m_CubeMapCpuMipMapGenerationEnable; //+0x75
	bool m_CubeMapConvolutionEnable; //+0x76
	bool m_CompensateSunShadowHeightScale; //+0x77
	bool m_LightMapsEnable; //+0x78
	bool m_LightProbeEnable; //+0x79
	bool m_LightProbeNewSamplingEnable; //+0x7A
	bool m_LightProbeForceUpdate; //+0x7B
	bool m_LightProbeJobsEnable; //+0x7C
	bool m_LocalLightsEnable; //+0x7D
	bool m_LocalLightCullingEnable; //+0x7E
	bool m_LocalLightCustumFalloff; //+0x7F
	bool m_DrawDebugCubeMaps; //+0x80
	bool m_DrawDebugEntities; //+0x81
	bool m_DrawDebugSystemsEnable; //+0x82
	bool m_DrawDebugLightProbes; //+0x83
	bool m_DrawDebugLightProbeGrid;//+0x84
	bool m_DrawDebugLightProbeOcclusion; //+0x85
	bool m_DrawDebugLightProbeStats; //+0x86
	bool m_DrawDebugLightProbeBoundingBoxes; //+0x87
	bool m_DrawSolveTaskPerformance; //+0x88
	bool m_DrawDebugColoringEnable; //+0x89
	bool m_DrawDebugTextures; //+0x8A
	bool m_DrawDebugBackFaces; //+0x8B
	bool m_DrawDebugTargetMeshes; //+0x8C
	bool m_DrawWarningsEnable; //+0x8D
	bool m_AlbedoForceUpdateEnable; //+0x8E
	bool m_AlbedoForceColorEnable; //+0x8F
	bool m_TerrainMapEnable; //+0x90
	bool m_EmissiveEnable; //+0x91

	static EnlightenRuntimeSettings* Singleton()
	{
		return *(EnlightenRuntimeSettings**)OFFSET_ENLIGHTENRUNTIMESETTINGS;
	}	
};

class DebugRenderSettings : public DataContainer
{
public:
	float m_TextViewDistance; //+0x10
	unsigned int m_TextQueueMaxLineCount; //+0x14
	float m_TextQueueTimeVisible; //+0x18
	int m_ProcessJobCount; //+0x1C
	char pad_0x20[0x4];
	unsigned int m_DxMaxVertexCount; //+0x24
	bool m_Enable; //+0x28
	bool m_DrawStatsEnable; //+0x29
	bool m_TextQueueLocationTop; //+0x2A
	bool m_Ps3SpuEnable; //+0x2B
	bool m_DxLine2dAntialiasingEnable; //+0x2C
	bool m_DxLine3dAntialiasingEnable; //+0x2D

	static DebugRenderSettings* Singleton()
	{
		return *(DebugRenderSettings**)OFFSET_DEBUGRENDERSETTINGS;
	}
};
class EntryComponentData : public DataContainer
{
public:
	enum EntryClass
	{
		ecPrimary = 0,
		ecSecondary = 1
	};
	class EntryInputActionMapsData
	{
	public:
		enum InputActionMapSlot
		{
			InputActionMapSlot_Undefined = 0,
			InputActionMapSlot_Root1 = 1,
			InputActionMapSlot_Root2 = 2,
			InputActionMapSlot_Root3 = 3,
			InputActionMapSlot_Root4 = 4,
			InputActionMapSlot_Root5 = 5,
			InputActionMapSlot_Root6 = 6,
			InputActionMapSlot_Root7 = 7,
			InputActionMapSlot_Root8 = 8,
			InputActionMapSlot_Root9 = 9,
			InputActionMapSlot_Root10 = 10,
			InputActionMapSlot_Root11 = 11,
			InputActionMapSlot_Root12 = 12,
			InputActionMapSlot_Root13 = 13,
			InputActionMapSlot_Root14 = 14,
			InputActionMapSlot_Root15 = 15,
			InputActionMapSlot_Root16 = 16,
			InputActionMapSlot_Sticks1 = 17,
			InputActionMapSlot_Sticks2 = 18,
			InputActionMapSlot_Sticks3 = 19,
			InputActionMapSlot_Sticks4 = 20,
			InputActionMapSlot_Buttons1 = 21,
			InputActionMapSlot_Buttons2 = 22,
			InputActionMapSlot_Buttons3 = 23,
			InputActionMapSlot_Buttons4 = 24,
			InputActionMapSlot_Sticks1Buttons1 = 25,
			InputActionMapSlot_Sticks1Buttons2 = 26,
			InputActionMapSlot_Sticks1Buttons3 = 27,
			InputActionMapSlot_Sticks1Buttons4 = 28,
			InputActionMapSlot_Sticks2Buttons1 = 29,
			InputActionMapSlot_Sticks2Buttons2 = 30,
			InputActionMapSlot_Sticks2Buttons3 = 31,
			InputActionMapSlot_Sticks2Buttons4 = 32,
			InputActionMapSlot_Sticks3Buttons1 = 33,
			InputActionMapSlot_Sticks3Buttons2 = 34,
			InputActionMapSlot_Sticks3Buttons3 = 35,
			InputActionMapSlot_Sticks3Buttons4 = 36,
			InputActionMapSlot_Sticks4Buttons1 = 37,
			InputActionMapSlot_Sticks4Buttons2 = 38,
			InputActionMapSlot_Sticks4Buttons3 = 39,
			InputActionMapSlot_Sticks4Buttons4 = 40,
			InputActionMapSlot_Count = 41
		};
		char aAsset[24]; //+0x00 Inherited
		int m_ActionMapSettingsScheme; //+0x18
		InputActionMapSlot m_DefaultInputActionMap; //+0x1C
		InputActionMapSlot m_InputActionMaps; //+0x20
	};
	class InputActionMappingsData
	{
	public:
		class DataContainer
		{
		public:
			char Pad[16]; //+0x00 Inherited
		};
		char aDataContainer[16]; //+0x00 Inherited
		DataContainer m_Mappings; //+0x10
	};
	class EntryComponentHudData
	{
	public:
		enum EntrySeatType
		{
			EST_Driver = 0,
			EST_Gunner = 1,
			EST_Passenger = 2
		};
		int m_Index; //+0x0
		EntrySeatType m_SeatType; //+0x4
		bool m_Frustum; //+0x8
		bool m_Visible; //+0x9
		bool m_MaximizeMiniMapOnEntry; //+0xA
	};
	enum EntrySpottingSettings
	{
		ESSDefault = 0,
		ESSSendAndReceive = 1,
		ESSReceive = 2,
		ESSCount = 3
	};
	class EntryComponentSoundData
	{
	public:
		class DataContainer
		{
		public:
			char Pad[16]; //+0x00 Inherited
		};
		char aDataContainer[16]; //+0x00 Inherited
		DataContainer* m_StanceSounds; //+0x10
		SoundAsset* m_StanceSwitchSound; //+0x18
	};
	class PoseConstraintsData
	{
	public:
		bool m_StandPose; //+0x0
		bool m_CrouchPose; //+0x1
		bool m_PronePose; //+0x2
	};
	char aGameComponentData[96]; //+0x00 Inherited padding 112
	D3DXVECTOR3 m_SoldierOffset; //+0x70
	EntryClass* m_EntryClass; //+0x80
	char m_AIData[0x08]; //+0x88 GameAIEntryData
	EntryInputActionMapsData* m_InputConceptDefinition; //+0x90
	InputActionMappingsData* m_InputMapping; //+0x98
	InputActionMappingsData* m_InputCurves; //+0xA0
	EntryComponentHudData m_HudData; //+0xA8
	int m_EntryOrderNumber; //+0xB4
	float m_EnterImpulse; //+0xB8
	float m_EntryRadius; //+0xBC
	float m_SoldierTransitionInvisbleTime; //+0xC0
	int m_NumberOfStances; //+0xC4
	EntrySpottingSettings* m_EntrySpottingSettings; //+0xC8
	EntryComponentSoundData* m_EntryComponentSound; //+0xD0
	int m_TriggerEventOnKey; //+0xD8
	bool m_ForbiddenForHuman; //+0xDC
	bool m_IsAllowedToExitInAir; //+0xDD
	bool m_IsShielded; //+0xDE
	bool m_LockSoldierAimingToEntry; //+0xDF
	bool m_ShowSoldierInEntry; //+0xE0
	bool m_Show1pSoldierInEntry; //+0xE1
	bool m_StancesEnabled; //+0xE2
	bool m_ShowSoldierWeaponInEntry; //+0xE3
	bool m_Show1pSoldierInEntryForPlayerOnly; //+0xE4
	bool m_Show3pSoldierWeaponInEntry; //+0xE5
	bool m_ShowSoldierGearInEntry; //+0xE6
	PoseConstraintsData m_PoseConstraints; //+0xE7
	bool m_AllowRagdollFromEntry; //+0xEA
};
class EntryComponent {
public:
	class WeaponInfo {
	public:
		virtual void Function0();
		virtual void Function1();
		virtual void Function2();
		virtual void Function3();
		virtual WeaponFiring* GetWeaponFiring();
		virtual ClientWeapon* GetWeapon();
		virtual bool ActiveInStance(int stance);
		virtual void* GetWeaponComponent(); //WeaponComponent
	};

	class FiringCallbacks {
	public:
		virtual void Function0();
		char __0x0004[0x4];
		WeaponInfo* weapon_info;
	};

	virtual int GetActiveStance();

	eastl::vector<FiringCallbacks*> weapons;
};

class PhysicsSettings: public DataContainer
{
public:
	unsigned int m_ClientEffectWorldThreadCount; //+0x10
	unsigned int m_ClientClothWorldThreadCount; //+0x14
	unsigned int m_ClientWorldThreadCount; //+0x18
	unsigned int m_ServerWorldThreadCount; //+0x1c
	unsigned int m_IntegrateJobCount; //+0x20
	unsigned int m_CollideJobCount; //+0x24
	unsigned int m_ClothJobCount; //+0x28
	float m_WindManagerAwakeningRadius; //+0x2c
	unsigned int m_ClientWorldWorkerThreadCount; //+0x30
	unsigned int m_ServerWorldWorkerThreadCount; //+0x34
	unsigned int m_EffectWorldWorkerThreadCount; //+0x38
	bool m_Enable; //+0x3c
	bool m_EnableClothInterpolationJobs; //+0x3d
	bool m_EnableClothUpdateJob; //+0x3e
	bool m_EnableAIRigidBody; //+0x3f
	bool m_ForestEnable; //+0x40
	bool m_EnableJobs; //+0x41
	bool m_RemoveRagdollWhenWoken; //+0x42
	bool m_RemoveFromWorldOnCollisionOverflow; //+0x43
	bool m_SingleStepCharacter; //+0x44
	bool m_ForceSingleStepCharacterInSP; //+0x45
	bool m_EnableFollowWheelRaycasts; //+0x46
	bool m_EnableClientWheelRaycasts; //+0x47
	bool m_EnableASyncWheelRaycasts; //+0x48
	bool m_UseDelayedWakeUpClient; //+0x49
	bool m_UseDelayedWakeUpServer; //+0x4a
	bool m_SuppressDebrisSpawnUntilReady; //+0x4b
	bool m_EnablePlayerVSAICollisions; //+0x4c

	static PhysicsSettings* Singleton()
	{
		return *(PhysicsSettings**)OFFSET_PHYSICSSETTINGS;
	}
};
class MeshSettings: public DataContainer
{
public:
	char* m_OverrideShadersShaderName; //+0x10
	char* m_OverrideShadersMeshName; //+0x18
	int m_ForceLod; //+0x20
	float m_GlobalLodScale; //+0x24
	float m_ShadowDistanceScale; //+0x28
	float m_TessellationMaxFactor; //+0x2c
	float m_TessellationForceTessellationFactor; //+0x30
	float m_TessellationMaxDistance; //+0x34
	float m_TessellationMaxDistanceFade; //+0x38
	QualityLevel m_CastSunShadowQualityLevel; //+0x3c
	QualityLevel m_CastDynamicEnvmapQualityLevel; //+0x40
	QualityLevel m_CastPlanarReflectionQualityLevel; //+0x44
	bool m_LoadingEnabled; //+0x48
	bool m_TessellationEnable; //+0x49
	bool m_TessellationBackFaceCullingEnable; //+0x4a
	bool m_TessellationScreenSpaceAdativeEnable; //+0x4b

	static MeshSettings* Singleton()
	{
		return *(MeshSettings**)OFFSET_MESHSETTINGS;
	}
};
class EmitterSystemSettings : public DataContainer
{
public:
	
	unsigned int m_SkipUpdateMaxCount; //+0x10
	int m_ForceJobCount; //+0x14
	float m_TimeScale; //+0x18
	float m_GlobalResetStartTimeInterval; //+0x1C
	unsigned int m_CollisionRayCastMaxCount; //+0x20
	unsigned int m_ProximityPhysicsEntitiesMaxCount; //+0x24
	QualityLevel m_EmitterQualityLevel; //+0x28
	float m_TemplateTimeoutTime; //+0x2C
	float m_ScreenAreaCullingStart; //+0x30
	float m_ScreenAreaCullingEnd; //+0x34
	float m_ScreenAreaCullingMinTotalArea; //+0x38
	float m_ScreenAreaCullingMaxTotalArea; //+0x3C
	float m_ScreenAreaCullingMaxMultiplier; //+0x40
	float m_ProcessJobYieldTime; //+0x44
	float m_VisibleJobYieldTime; //+0x48
	unsigned int m_DrawStats; //+0x4C
	unsigned int m_DrawBoundingBoxes; //+0x50
	float m_MinScreenArea; //+0x54
	unsigned int m_DrawDebugAtlasMiplevel; //+0x58
	int m_DrawDebugAtlasTextureIndex; //+0x5C
	int m_QuadTechnique; //+0x60
	float m_QuadNearFadeDistance; //+0x64
	unsigned int m_QuadMaxCount; //+0x68
	float m_MeshCullingDistance; //+0x6C
	unsigned int m_MeshDrawCountLimit; //+0x70
	float m_MeshStreamingPriorityMultiplier; //+0x74
	unsigned int m_MeshMaxCount; //+0x78
	bool m_Enable; //+0x7C
	bool m_UpdateJobEnable; //+0x7D
	bool m_EnableFixedTimeStep; //+0x7E
	bool m_EnableFixedDelta; //+0x7F
	bool m_EnableJobs; //+0x80
	bool m_CollisionRayCastEnable; //+0x81
	bool m_DrawDebugRayCastCollision; //+0x82
	bool m_EnableRendering; //+0x83
	bool m_ZBufferCullEnable; //+0x84
	bool m_DrawProjectedBoxes; //+0x85
	bool m_DrawTransforms; //+0x86
	bool m_DrawDebugBaseAtlas; //+0x87
	bool m_DrawDebugNormalAtlas; //+0x88
	bool m_QuadClipScaleEnable; //+0x89
	bool m_QuadEnableRendering; //+0x8A
	bool m_QuadNiceRenderingEnable; //+0x8B
	bool m_QuadSimpleRenderingEnable; //+0x8C
	bool m_QuadEnableOpaque; //+0x8D
	bool m_QuadEnableCustomShader; //+0x8E
	bool m_QuadColorShaderCostsEnable; //+0x8F
	bool m_QuadEnableSorting; //+0x90
	bool m_QuadEnableWireframe; //+0x91
	bool m_QuadHalfResEnable; //+0x92
	bool m_QuadGroupsJoinAll; //+0x93
	bool m_QuadGroupsJoinNone; //+0x94
	bool m_QuadGroupsJoinNiceAndSimple; //+0x95
	bool m_QuadVertexShadowsEnable; //+0x96
	bool m_QuadCloudVertexShadowsEnable; //+0x97
	bool m_QuadPlanarReflectionEnable; //+0x98
	bool m_QuadPointLightsEnable; //+0x99
	bool m_QuadSpotLightsEnable; //+0x9A
	bool m_QuadResourceSyncJobEnable; //+0x9B
	bool m_MeshRenderingEnable; //+0x9C
	bool m_MeshDrawTransforms; //+0x9D
	bool m_MeshDrawBoundingBoxes; //+0x9E
	bool m_MeshShadowEnable; //+0x9F
	bool m_MeshPlanarReflectionEnable; //+0xA0
	bool m_MeshDrawCullStats; //+0xA1

	static EmitterSystemSettings* Singleton()
	{
		return *(EmitterSystemSettings**)OFFSET_EMITTERSYSTEMSETTINGS;
	}
};

class OcclusionSettings : public DataContainer
{
public:
	bool m_Enable; //+0x10
	bool m_CoverageEnable; //+0x11
	bool m_DrawShadowZbuffer; //+0x12
	bool m_DrawZbuffer; //+0x13
	bool m_DrawSplitView; //+0x14
	bool m_DrawBinaryBuffer; //+0x15
	bool m_DrawCoverageBuffer; //+0x16

	static OcclusionSettings* Singleton()
	{
		return *(OcclusionSettings**)OFFSET_OCCLUSIONSETTINGS;
	}
};

class EntitySettings: public SystemSettings
{
public:
	char* m_Name; //+0x10
	GamePlatform m_Platform; //+0x18
	int m_ExecutionMode; //+0x20
	unsigned int m_OutOfEntityBusNetworkIdThreshold; //+0x24
	bool m_EditorGameViewEnable; //+0x28
	bool m_SpawnSubLevelsFromLogic; //+0x29

	static EntitySettings* Singleton()
	{
		return *(EntitySettings**)OFFSET_ENTITYSETTINGS;
	}
};

enum TerrainRenderMode
{
	TerrainRenderMode_Default = 0,
	TerrainRenderMode_DrawPassCount2d = 1,
	TerrainRenderMode_LayerCount2d = 2,
	TerrainRenderMode_LayerCount3d = 3,
	TerrainRenderMode_MaskedLayerCount2d = 4,
	TerrainRenderMode_MaskedLayerCount3d = 5,
	TerrainRenderMode_DensityMap = 6
};

class DxTexture
{
public:

	class TextureHeader
	{
	public:
		char _0x0000[12];
		__int32 flags; //0x000C 
		__int16 width; //0x0010 
		__int16 height; //0x0012 
		__int16 depth; //0x0014 
		__int16 sliceCount; //0x0016 
		__int16 unused0; //0x0018 
		BYTE mipmapCount; //0x001A 
		BYTE mipmapBaseIndex; //0x001B 
	};//Size=0x001C

	class TextureCreateDesc
	{
	public:
		char _0x0000[24];
		__int32 type; //0x0018 
		__int32 format; //0x001C 
		__int32 width; //0x0020 
		__int32 height; //0x0024 
		__int32 depth; //0x0028 
		__int32 mipmapCount; //0x002C 
		__int32 sampleCount; //0x0030 
		__int32 sRgb; //0x0034 
		char _0x0038[12];
		__int32 bindFlags; //0x0044 
		__int32 subResourceCount; //0x0048 
		char _0x004C[4];
		__int64 m_pDxRenderBuffer; //0x0050 DxRenderBuffer
		char _0x0058[24];
	};//Size=0x0070

	// fb::ITypedObject

	virtual __int64 GetType( );

	// fb::IResourceObject

	virtual int AddRef( );
	virtual int Release( );

	// fb::IRenderResource

	virtual const char* GetDebugName( ); // fb::IRenderResource
	virtual unsigned int GetMemorySize( );
	virtual unsigned int GetMemoryFlags( );
	virtual int GetUsage( ); // enum RenderResourceUsage

	// fb::ITexture

	virtual int GetFormat( ); // enum fb::TextureFormat
	virtual int GetTextureType( );    // enum fb::TextureType
	virtual void Function9( );
	virtual void Function10( ); //
	virtual unsigned int GetWidth( );
	virtual unsigned int GetHeight( );
	virtual unsigned int GetDepth( );
	virtual unsigned int GetMipmapCount( );
	virtual unsigned int GetSampleCount( );
	virtual void Function16( );
	virtual TextureHeader* GetStreamingHeader( );
	virtual void Function18( );
	virtual unsigned short GetHandle( );
	virtual void SetHandle( unsigned short );

	char _0x0000[8];
	TextureCreateDesc m_desc; //0x0010 
	__int32 m_handle; //0x0080 
	__int32 m_bindFlags; //0x0084 
	__int32 m_resourceFormat; //0x0088 
	__int32 m_shaderFormat; //0x008C 
	TextureHeader* m_pStreamingHeader; //0x0090
	ID3D11Resource* m_pResource; //0x0098
	char _0x00A0[8];
	ID3D11Texture2D* m_pTexture2d; //0x00A8
	ID3D11Texture3D* m_pTexture3d; //0x00B0
	__int32 m_ownsResource; //0x00B8 
	char _0x00BC[4];
};  

class VisualTerrainSettings: public DataContainer
{
public:
	QualityLevel m_MeshScatteringQualityLevel; //+0x10
	TerrainRenderMode m_RenderMode; //+0x14		
	float m_TriangleSizeMin; //+0x18
	float m_LodScale; //+0x1C
	float m_LodCenterExtrapolationDistanceMax; //+0x20
	float m_LodCenterExtrapolationTime; //+0x24
	float m_TextureSkipMipSpeed; //+0x28
	float m_DxTessellatedTriWidth; //+0x2C
	float m_DxTessellationPatchShrink; //+0x30
	unsigned int m_DxTessellationPatchFacesPerSide; //+0x34
	unsigned int m_TextureAtlasSampleCountXFactor; //+0x38
	unsigned int m_TextureAtlasSampleCountYFactor; //+0x3C
	float m_TextureSamplesPerMeterMax; //+0x40
	float m_TextureDetailFalloffFactor; //+0x44
	float m_TextureDetailFalloffDistance; //+0x48
	float m_TextureDetailFalloffCurve; //+0x4C
	float m_TextureInvisibleDetailReductionFactor; //+0x50
	float m_TextureOccludedDetailReductionFactor; //+0x54
	unsigned int m_TextureRenderJobCount; //+0x58
	unsigned int m_TextureRenderJobsLaunchedPerFrameCountMax; //+0x5C
	unsigned int m_TextureTileSamplesPerSide; //+0x60
	unsigned int m_TextureTileBorderWidth; //+0x64
	int m_TextureLevelOffset; //+0x68
	unsigned int m_TextureClodFrameCount; //+0x6C
	float m_TextureClodCutoffPriority; //+0x70
	unsigned int m_TextureStreamableTextureInstanceBufferSize; //+0x74
	unsigned int m_TextureCompressJobCount; //+0x78
	int m_TextureCompressionQuality; //+0x7C
	float m_TextureDetailSlopeBoost; //+0x80
	float m_TextureGenerationMipBias; //+0x84
	float m_TextureDirtyRetryRate; //+0x88
	int m_TextureForceDrawPass; //+0x8C
	unsigned int m_TextureQuadsPerTileLevel; //+0x90
	float m_DecalZPassDrawDistance; //+0x94
	float m_DecalOffsetY; //+0x98
	float m_Decal3dFarDrawDistanceScaleFactor; //+0x9C
	int m_DrawQuadtreeZoomIndex; //+0xA0
	float m_PatchErrorFov; //+0xA4
	float m_ZPassDistance; //+0xA8
	float m_DebugOverlayGridSize; //+0xAC
	float m_DebugOverlayIsolineSpacing; //+0xB0
	unsigned int m_SlotReuseWaitCount; //+0xB4
	unsigned int m_BuildJobCount; //+0xB8
	float m_DynamicMaskDecalWidthScale; //+0xBC
	unsigned int m_MaxNonVisibleTextureUpdateCount; //+0xC0
	unsigned int m_PatchFacesPerSide; //+0xC4
	unsigned int m_TessellationFacesPerSideMin; //+0xC8
	unsigned int m_PatchSlotCount; //+0xCC
	unsigned int m_OccluderJobCount; //+0xD0
	unsigned int m_OccluderPatchFacesPerSide; //+0xD4
	float m_OccluderLodScale; //+0xD8
	float m_OccludedMinDistance; //+0xDC
	unsigned int m_MeshScatteringCellPoolCapacity; //+0xE0
	unsigned int m_MeshScatteringTreeNodePoolCapacity; //+0xE4
	float m_MeshScatteringInvisibleCellFovFactor; //+0xE8
	unsigned int m_MeshScatteringCullRecordCount; //+0xEC
	unsigned int m_MeshScatteringBuildChannelCount; //+0xF0
	unsigned int m_MeshScatteringBuildChannelsLaunchedPerFrameCountMax; //+0xF4
	unsigned int m_MeshScatteringClodFrameCount; //+0xF8
	float m_MeshScatteringWindSpeed; //+0xFC
	unsigned int m_MeshScatteringInstancesPerCellMax; //+0x100
	float m_MeshScatteringDensityMarginFactor; //+0x104
	float m_MeshScatteringPregenerationDistanceRatio; //+0x108
	float m_MeshScatteringKeepDistanceRatio; //+0x10C
	int m_MeshScatteringVirtualTextureBlurriness; //+0x110
	float m_MeshScatteringDistanceScaleFactor; //+0x114
	unsigned int m_MeshScatteringInstanceCullJobCount; //+0x118
	unsigned int m_MeshScatteringInstanceCullListCount; //+0x11C
	float m_MeshScatteringSnappingGridMultiplierVertical; //+0x120
	float m_MeshScatteringSnappingGridMultiplierHorizontal; //+0x124
	bool m_WireframeEnable; //+0x128
	bool m_Enable; //+0x129
	bool m_EditServiceEnable; //+0x12A
	bool m_DxDisplacementMappingEnable; //+0x12B
	bool m_DxDensityMapEnable; //+0x12C
	bool m_VertexBufferHeightsEnable; //+0x12D
	bool m_DrawVertexYTextureEnable; //+0x12E
	bool m_TextureVtIndirectionJobEnable; //+0x12F
	bool m_TextureVtIndirectionSpuJobEnable; //+0x130
	bool m_TextureStreamingPrioritizationJobEnable; //+0x131
	bool m_TextureStreamingPrioritizationSpuJobEnable; //+0x132
	bool m_TextureClodEnable; //+0x133
	bool m_TextureForceUpdateEnable; //+0x134
	bool m_TextureCompressFastAlgorithmEnable; //+0x135
	bool m_TextureCompressSpuJobsEnable; //+0x136
	bool m_DrawTextureDebugColors; //+0x137
	bool m_TextureDrawTerrainLayersEnable; //+0x138
	bool m_TextureKeepPoolFullEnable; //+0x139
	bool m_TextureLayerCullingEnable; //+0x13A
	bool m_GpuTextureCompressionEnable; //+0x13B
	bool m_TextureStreamingPrioritizationEnable; //+0x13C
	bool m_DetailTextureStreamingPrioritizationEnable; //+0x13D
	bool m_MeshScatteringMeshStreamingPrioritizationEnable; //+0x13E
	bool m_PrioritizationSpuJobEnable; //+0x13F
	bool m_PrioritizationOcclusionEnable; //+0x140
	bool m_DrawEnable; //+0x141
	bool m_DrawPatchesEnable; //+0x142
	bool m_DetailOverlayEnable; //+0x143
	bool m_DecalEnable; //+0x144
	bool m_ForceDecalReducedQuality; //+0x145
	bool m_DrawDecal2dEnable; //+0x146
	bool m_DrawDecal3dEnable; //+0x147
	bool m_DrawDecalZPassEnable; //+0x148
	bool m_DrawOnlyDecalZPassEnable; //+0x149
	bool m_DrawPatchBoxesEnable; //+0x14A
	bool m_DrawBadPatchesEnable; //+0x14B
	bool m_DrawTextureTileBoxesEnable; //+0x14C
	bool m_DrawDebugTextEnable; //+0x14D
	bool m_DrawDebugTexturesEnable; //+0x14E
	bool m_DrawQuadtreesEnable; //+0x14F
	bool m_DrawQuadtreeStatsEnable; //+0x150
	bool m_DrawQuadtreeAtlasTexturesEnable; //+0x151
	bool m_DrawDestructionMask; //+0x152
	bool m_DrawWaterEnable; //+0x153
	bool m_PatchErrorFovEnable; //+0x154
	bool m_DebugOverlayGridEnable; //+0x155
	bool m_DebugOverlayIsolinesEnable; //+0x156
	bool m_DebugOverlayWireframeEnable; //+0x157
	bool m_DebugOverlaySketchTextureEnable; //+0x158
	bool m_DebugOverlayBrushEnable; //+0x159
	bool m_ForceGraphicsDriverCrash; //+0x15A
	bool m_ForcePatchRebuildEnable; //+0x15B
	bool m_DestroyAll; //+0x15C
	bool m_SlotDebugOutputEnable; //+0x15D
	bool m_UpdateJobsEnable; //+0x15E
	bool m_CullSpuJobEnable; //+0x15F
	bool m_PrepareBuildSpuJobEnable; //+0x160
	bool m_BuildSpuJobEnable; //+0x161
	bool m_RegenerateTexturesEnable; //+0x162
	bool m_DynamicMaskEnable; //+0x163
	bool m_PatchLodTransitionsEnable; //+0x164
	bool m_PatchMaterialSortingEnable; //+0x165
	bool m_CullSampleBoundingBoxHeightEnable; //+0x166
	bool m_CastShadowsEnable; //+0x167
	bool m_CastPlanarReflectionEnable; //+0x168
	bool m_CastEnvmapReflectionEnable; //+0x169
	bool m_CastDecal3dPlanarReflectionEnable; //+0x16A
	bool m_CastDecal3dEnvmapReflectionEnable; //+0x16B
	bool m_GlobalColormapEnable; //+0x16C
	bool m_OccluderEnable; //+0x16D
	bool m_OccluderJobEnable; //+0x16E
	bool m_OccluderSpuJobEnable; //+0x16F
	bool m_OccludedEnable; //+0x170
	bool m_MeshScatteringEnable; //+0x171
	bool m_MeshScatteringJobsEnable; //+0x172
	bool m_MeshScatteringCastShadowsEnable; //+0x173
	bool m_DrawMeshScatteringEnable; //+0x174
	bool m_DrawMeshScatteringCellBoxesEnable; //+0x175
	bool m_DrawMeshScatteringBatchBoxesEnable; //+0x176
	bool m_DrawMeshScatteringNodeBoxesEnable; //+0x177
	bool m_DrawMeshScatteringCulledCellBoxesEnable; //+0x178
	bool m_DrawMeshScatteringDebugMaskScaleTexturesEnable; //+0x179
	bool m_DrawMeshScatteringStatsEnable; //+0x17A
	bool m_DrawMeshScatteringQuadtreeEnable; //+0x17B
	bool m_MeshScatteringForceUpdateEnable; //+0x17C
	bool m_MeshScatteringBuildVisibleFirst; //+0x17D
	bool m_MeshScatteringCullSpuJobEnable; //+0x17E
	bool m_MeshScatteringMergeInstanceLists; //+0x17F
	bool m_MeshScatteringInstanceCullSpuJobEnable; //+0x180
	bool m_MeshScatteringPrioritizationSpuJobEnable; //+0x181
	bool m_MeshScatteringSpuJobEnable; //+0x182
	bool m_MeshScatteringInstanceCullBoxTestEnable; //+0x183
	bool m_MeshScatteringInstanceNewCodeEnable; //+0x184
	bool m_MeshScatteringInstanceFrustumCullEnable; //+0x185
	bool m_MeshScatteringInstanceOcclusionCullEnable; //+0x186
	bool m_MeshScatteringInstanceAdditionalCullEnable; //+0x187
	bool m_DrawMeshScatteringInstanceBoxesEnable; //+0x188
	bool m_MeshScatteringInstanceCullDynamicAllocEnable; //+0x189
	bool m_Ps3MeshScatteringInstanceCellMemoryEnable; //+0x18A
	bool m_MeshScatteringWindEnable; //+0x18B

	static VisualTerrainSettings* Singleton()
	{
		return *(VisualTerrainSettings**)OFFSET_VISUALTERRAINDATA;
	}
};

class InputConfigurationAsset
{
public:

	class EntryInputActionMapsData
	{
	public:
		char aAsset[24]; //+0x00 Inherited
		int m_ActionMapSettingsScheme; //+0x18
		int m_DefaultInputActionMap; //+0x1C
		int m_InputActionMaps; //+0x20
	};

	char aAsset[24]; //+0x00 Inherited
	EntryInputActionMapsData* m_DefaultInputConceptDefinition; //+0x18
	EntryInputActionMapsData* m_DefaultExclusiveInputConcepts; //+0x20
	__int64 m_EntryInputActionBindings; //+0x28
	__int64 m_UserConfigurableActionMaps; //+0x30
	int m_TogglePoseAction; //+0x38
	int m_CrouchAction; //+0x3C
	int m_CrouchAndHoldAction; //+0x40
	int m_PickupInteractionAction; //+0x44
	int m_PickupInteractionActionKeyboard; //+0x48
	float m_SprintReleaseTime; //+0x4C
	float m_ThrottleInputRequiredForSprint; //+0x50
	float m_VehicleBoostIsToggleMinInput; //+0x54
	float m_EnterVehicleHoldTime; //+0x58
	bool m_FiringDisablingTransitions; //+0x60
	bool m_ProneToStandOnJump; //+0x68
	bool m_StandAutomaticallyIfSprinting; //+0x69
	bool m_DisableCrouch; //+0x6A
	bool m_DisableProne; //+0x6B
	bool m_DisableCrawlingWhileFiring; //+0x6C
	bool m_DisableCrawlingWhileReloading; //+0x6D
	bool m_DisableFiringWhileDeployingBipod; //+0x6E
	bool m_DisableFiringWhileJumping; //+0x6F
	bool m_DisableSprintingWhileReloading; //+0x70
	bool m_EnableSprintToCrouchTransition; //+0x71
	bool m_StopSprintingWhenReleasingThrottle; //+0x72
	bool m_StopSprintingWhenReleasingSprint; //+0x73
	bool m_WaitForSprintReleaseBeforeSprintAgain; //+0x74
	bool m_VehicleBoostIsToggle; //+0x75
	bool m_InputCurvesEnabled; //+0x76

	static InputConfigurationAsset* Singleton()
	{
		return *(InputConfigurationAsset**)OFFSET_INPUTCONFIGASSET;
	}	
};

class DecalSettings: public SystemSettings
{
public:
	char* m_Name; //+0x10
	GamePlatform m_Platform; //+0x18
	unsigned int m_DecalImpactLifetimeMs; //+0x20
	unsigned int m_DecalImpactPoolSize; //+0x24
	unsigned int m_StaticBufferMaxVertexCount; //+0x28
	unsigned int m_RingBufferMaxVertexCount; //+0x2c
	bool m_Enable; //+0x30
	bool m_DrawEnable; //+0x31
	bool m_SystemEnable; //+0x32
	bool m_SystemEnable2; //+0x33
	bool m_DrawDecalReflectionOnBreakableModelEnable; //+0x34
	bool m_DebugMemUsageEnable; //+0x35
	bool m_DebugWarningsEnable; //+0x36
	bool m_NvidiaStreamOutputWorkaroundEnable; //+0x37

	static DecalSettings* Singleton()
	{
		return *(DecalSettings**)0x14242F6A8;
	}
};

class TextureSettings: public DataContainer
{
public:
	unsigned int m_SkipMipmapCount; //+0x10
	bool m_LoadingEnabled; //+0x14
	bool m_RenderTexturesEnabled; //+0x15

	static TextureSettings* Singleton()
	{
		return *(TextureSettings**)OFFSET_TEXTURESETTINGS;
	}
};

class WindowSettings
{
public:
	char inheritedSystemSettings[0x10]; //+0x00
	char* m_Name; //+0x10
	GamePlatform m_Platform; //+0x18
	__int32 m_PosX; //+0x20
	__int32 m_PosY; //+0x24
	unsigned __int32 m_Width; //+0x28
	unsigned __int32 m_Height; //+0x2c
	bool m_AutoSize; //+0x30
	bool m_FullscreenAutoSize; //+0x31
	bool m_EnableEscape; //+0x32
	bool m_EnableInputOnActivate; //+0x33
	bool m_HibernateOnClose; //+0x34
	bool m_Hidden; //+0x35
	bool m_Minimized; //+0x36

	static WindowSettings* Singleton()
	{
		return *(WindowSettings**)OFFSET_WINDOWSETTINGS;
	}
};

class UISettings : public SystemSettings
{
public:
	class UIBundlesAsset
	{
	public:
		char aAsset[24]; //+0x00 Inherited
		void* m_UIBundleAssetStateList; //+0x18 Asset
		void* m_FontCollectionLookups; //+0x20
		char* m_RootMovieClipPath; //+0x28
	};

	class ProfileOptionsAsset
	{
	public:
		char aAsset[24]; //+0x00 Inherited
		char* m_FileName; //+0x18
		char* m_ContentName; //+0x20
		unsigned int m_FileSize; //+0x28
		bool m_Options; //+0x30
		bool m_OptionsPs3; //+0x38
		bool m_OptionsXenon; //+0x40
		bool m_OptionsGen4a; //+0x48
		bool m_OptionsGen4b; //+0x50
		bool m_OptionsWin; //+0x58
		bool m_AutoSaveOnQuit; //+0x60
	};

	char* m_Name; //+0x10
	GamePlatform m_Platform; //+0x18
	UISystemType m_System; //+0x20
	UIBundlesAsset m_Bundles; //+0x28
	ProfileOptionsAsset* m_ProfileOptions; //+0x30
	LanguageFormat m_Language; //+0x38
	bool m_OneBundlePerGraph; //+0x3c
	bool m_DrawEnable; //+0x3d
};
class ExplosiveEntity
{
public:
	virtual TypeInfo* GetType(); //
	virtual void Function1(); //
	virtual void Function2(); //
	virtual void Function3(); //
	virtual void Function4(); //
	virtual void Function5(); //
	virtual void Function6(); //
	virtual void Function7(); //
	virtual void Function8(); //
	virtual void Function9(); //
	virtual void Function10(); //
	virtual void Function11(); //
	virtual void Function12(); //
	virtual void Function13(); //
	virtual void Function14(); //
	virtual void Function15(); //
	virtual void Function16(); //
	virtual void Function17(); //
	virtual void Function18(); //
	virtual void Function19(); //
	virtual void Function20(); //
	virtual void Function21(); //
	virtual void Function22(); //
	virtual void GetTransform( D3DXMATRIX* mTransform ); 
};

class CObjectEntry 
{ 
public: 
	__int64 func1; //0x0000  
	__int64 func2; //0x0008  
	__int64 func3; //0x0010  
	__int64 func4; //0x0018  
	BYTE m_EntityType; //0x0020 is sometimes 1 or 3 and 0 if no valid shit 
	char N3F2B6DC1[7]; //0x0021  
	D3DXVECTOR4 m_position; //0x0028  
	D3DXVECTOR4 m_vec; //0x0038   
	GameObject* m_pEntity; //0x0048 
};//Size=0x0050

class GameObject
{
public:
	ClientPlayer* LocalPlayer; //0x0000 valid for vehicle invalid for explosive
	void* Ptr1;                   //0x08 char*: reads explosive or gadgets.explosives for explosive entity || pickups.medbag or pickups.ammobag for other 
	ClientPlayer* PlayerInVehicle; //0x0010 valid for vehicle if occupied not if empty
	void* Ptr2;                        //0x0018 valid for explosive, this is the actual explosive ptr      
	ClientVehicleEntity* pClientVehicle; //0x0020 vehicle ptr
	void* Ptr3; //0x0028 
	char _0x0030[16];
	char* m_name1; //0x0040 
	char _0x0048[40];
	char* m_name2; //0x0070 // name for vehicle, just a valid ptr for explosive no char*
};//Size=0x0078

class CObjectList 
{ 
public: 
	char _0x0000[0x8]; 
	CObjectEntry m_Collection[1000]; //0x0058  
	char N3F1631D5[40]; //0x13888  
	__int32 size; //0x138B0  
	char _0x138B4[196];//

	int Size( ) 
	{ 
		return size; 
	} 
	static CObjectList* GetInstance( )
	{
		return (CObjectList* )( OFFSET_ENTITYSIZE-0x138B0);
	}
};//Size=0x0E60

class ExplosionEntityData:public SpatialEntityData
{
public:
	void* m_DetonationEffect; //+0x60 EffectBlueprint
	void* m_DetonationEffectForFriendlies; //+0x68 EffectBlueprint
	void* m_MaskVolume; //+0x70 MaskVolumeEntityData
	void* m_DestructionMaskVolume; //+0x78 DestructionMaskVolumeEntityData
	MaterialDecl m_MaterialPair; //+0x80
	MaterialDecl m_SecondaryMaterialPair; //+0x84
	DamageIndicationType m_DamageIndicationType; //+0x88
	float m_EmpTime; //+0x8C
	float m_MaxOcclusionRaycastRadius; //+0x90
	float m_InnerBlastRadius; //+0x94
	float m_BlastDamage; //+0x98
	float m_BlastRadius; //+0x9C
	float m_BlastImpulse; //+0xA0
	float m_ShockwaveDamage; //+0xA4
	float m_ShockwaveRadius; //+0xA8
	float m_ShockwaveImpulse; //+0xAC
	float m_ShockwaveTime; //+0xB0
	float m_CameraShockwaveRadius; //+0xB4
	float m_SpawnDelay; //+0xB8
	bool m_NoFriendliesEffectOnEnabledFriendlyFire; //+0xBC
	bool m_UseEntityTransformForDetonationEffect; //+0xBD
	bool m_SecondaryMaterialsActive; //+0xBE
	bool m_HasStunEffect; //+0xBF
	bool m_DisableOcclusion; //+0xC0
	bool m_DisableStaticEntityOcclusion; //+0xC1
	bool m_TriggerImpairedHearing; //+0xC2
	bool m_Enabled; //+0xC3
};

class LockingControllerData: public DataContainer
{
public:
	class LockingAndHomingData
	{
	public:
		WarnTarget m_WarnLock; //+0x0
		bool m_IsHoming; //+0x4
		bool m_IsGuided; //+0x5
		bool m_IsGuidedWhenZoomed; //+0x6
		bool m_IsGuidedHoming; //+0x7
		bool m_FireOnlyWhenLockedOn; //+0x8
	};

	DataContainer* m_ZoomLevelLock; //+0x10
	float m_LockTime; //+0x18
	float m_UnLockTime; //+0x1C
	float m_ReleaseTime; //+0x20
	float m_ReleaseOnNewTargetTime; //+0x24
	float m_SampleRate; //+0x28
	float m_HoldStillThreshold; //+0x2C
	float m_CheckVisibilityLength; //+0x30
	float m_RayLength; //+0x34
	float m_AcceptanceAngle; //+0x38
	float m_AngleConstant; //+0x3C
	float m_DistanceConstant; //+0x40
	float m_Sensitivity; //+0x44
	float m_MinimumLockTime; //+0x48
	LockingAndHomingData m_LockingWeaponData; //+0x4C
	bool m_LockOnVisibleTargetsOnly; //+0x58
	bool m_RequireAmmoToLock; //+0x59
	bool m_PositionOnly; //+0x5A
	bool m_LockOnWorldSpacePos; //+0x5B
	bool m_LockOnEmptyVehicles; //+0x5C
	bool m_LockOnCharacters; //+0x5D
	bool m_IgnoreHeigthLockDistance; //+0x5E
	bool m_LockInCombatAreaOnly; //+0x5F
};

class MissileEntityData
{
public:
	class MissileUnguidedData
	{
	public:
		D3DXVECTOR2 m_StaticPosition; //+0x0
		D3DXVECTOR2 m_TargetPositionOffset; //+0x8
		bool m_UseStaticPosition; //+0x10
		bool m_UseTargetPosition; //+0x11
	};

	class MissileLockableInfoData
	{
	public:
		float m_HeatSignature; //+0x0
		float m_RadarSignature; //+0x4
	};

	class NearTargetDetonationData
	{
	public:
		float m_DetonationRadius; //+0x0
		float m_MaxDetonationDelay; //+0x4
		float m_MinDetonationDelay; //+0x8
		bool m_DetonateNearTarget; //+0xC
	};

	char aGhostedProjectileEntityData[304]; //+0x00 Inherited
	void* m_EngineEffect; //+0x130 EffectBlueprint
	ExplosionEntityData* m_DudExplosion; //+0x138 ExplosionEntityData
	SoundAsset* m_FlyBySound; //+0x140
	float m_EngineStrength; //+0x148
	float m_MaxSpeed; //+0x14C
	float m_EngineTimeToIgnition; //+0x150
	float m_EngineTimeToLive; //+0x154
	float m_TimeToActivateGuidingSystem; //+0x158
	float m_TimeToArm; //+0x15C
	float m_MaxTurnAngle; //+0x160
	float m_MinTurnAngle; //+0x164
	float m_TurnAngleMultiplier; //+0x168
	float m_Drag; //+0x16C
	float m_Gravity; //+0x170
	float m_FlyBySoundRadius; //+0x174
	float m_FlyBySoundSpeed; //+0x178
	float m_ImpactImpulse; //+0x17C
	float m_Damage; //+0x180
	TeamId m_DefaultTeam; //+0x184
	WarnTarget m_WarnTarget; //+0x188
	LockingControllerData* m_LockingController; //+0x190
	MissileLockableInfoData m_LockableInfo; //+0x198 could be ptr
	MissileUnguidedData m_UnguidedData; //+0x1A0
	NearTargetDetonationData m_NearTargetDetonation; //+0x1B4
	float m_MaxBankAngle; //+0x1C4
	float m_BankingSpeed; //+0x1C8
	char* m_Icon; //+0x1D0
	char* m_TargetIcon; //+0x1D8
	char* m_TargetIconEnemy; //+0x1E0
	float m_MinGhostFrequency; //+0x1E8
	bool m_ApplyGravityWhenGuided; //+0x1EC
	bool m_WarnOnPointingMissile; //+0x1ED
	bool m_EnableBanking; //+0x1EE
};

class SyncedBFSettings
{
public:

	class SystemSettings: public DataContainer
	{
	public:

		enum GamePlatform
		{
			GamePlatform_Ps3 = 0,
			GamePlatform_Win32 = 1,
			GamePlatform_Xenon = 2,
			GamePlatform_Gen4a = 3,
			GamePlatform_Gen4b = 4,
			GamePlatform_Any = 5,
			GamePlatform_Invalid = 6,
			GamePlatformCount = 7
		};
		char* m_Name; //0x0010 char*
		GamePlatform m_Platform; //0x0018 
		char pad_0x001C[4];
	}; //Size=0x0020

	enum ServerTypeValues
	{
		ServerType_OFFICIAL = 0,
		ServerType_RANKED = 1,
		ServerType_UNRANKED = 2,
		ServerType_PRIVATE = 3
	};

	SystemSettings m_Settings; //0x0000
	float m_GameModeCounterModifier; //0x0020 
	float m_RoundTimeLimit; //0x0024 
	__int64 m_JesusModeForPlayerTag; //0x0028 char* 0x00 
	__int32 m_Team1Faction; //0x0030 
	__int32 m_Team2Faction; //0x0034 
	__int32 m_Team3Faction; //0x0038 
	__int32 m_Team4Faction; //0x003C 
	__int64 m_CommanderSize; //0x0040 alignment to 8 
	char* m_FieldSpecLevels; //0x0048 char*
	ServerTypeValues m_ServerType; //0x0050 
	BYTE m_AllUnlocksUnlocked; //0x0054 
	BYTE m_NoMinimap; //0x0055 
	BYTE m_NoHud; //0x0056 
	BYTE m_NoMinimapSpotting; //0x0057 
	BYTE m_No3dSpotting; //0x0058 
	BYTE m_NoNameTag; //0x0059 
	BYTE m_OnlySquadLeaderSpawn; //0x005A 
	BYTE m_TeamSwitchingAllowed; //0x005B 
	BYTE m_RevertBackToBF3KillerCamera; //0x005C 
	BYTE m_DisableHitIndicators; //0x005D 
	BYTE m_DisableVehicleCommanderActions; //0x005E 
	BYTE m_CommanderEnabled; //0x005F 
	BYTE m_FieldUpgradeSystemActive; //0x0060 

	static SyncedBFSettings* GetInstance( )
	{
		return *( SyncedBFSettings** )( OFFSET_SYNCEDSETTINGS );
	}
};  
class AntSettings:public DataContainer
{
public:
	float m_ForceLodDistance; //0x0010 
	__int32 m_MaxAnimatablesPerPoseJob; //0x0014 
	float m_ReducedInterpolationDistance; //0x0018 
	float m_TrajectoryInterpolationDistance; //0x001C 
	__int32 m_MaxInterpolationSlots; //0x0020 
	__int32 m_MaxSingleBoneInterpolationSlots; //0x0024 
	float m_CheckGiantSoldiers; //0x0028 
	float m_LeanSignalScale; //0x002C 
	float m_LeanSignalClamp; //0x0030 
	float m_DetailedCollisionSpeedLimit; //0x0034 
	float m_MaxInterpolationDistance; //0x0038 
	__int32 m_MaxInterpolationTicks; //0x003C 
	__int32 m_AutoCullPixelSize; //0x0040 
	__int8 m_UsePA; //0x0044 
	__int8 m_UseHIK; //0x0045 
	__int8 m_BlockOnJobs; //0x0046 
	__int8 m_InterpolatePoses; //0x0047 
	__int8 m_AllowVariableTickLength; //0x0048 
	__int8 m_UseWeaponFov; //0x0049 
	__int8 m_ForcePoseUpdate; //0x004A 
	__int8 m_UseCameraFov; //0x004B 
	__int8 m_EnablePA; //0x004C 
	__int8 m_ClientEmulatesServer; //0x004D 
	__int8 m_UpdateEnable; //0x004E 
	__int8 m_EnablePackageCache; //0x004F 
	__int8 m_EnableDebugLogFile; //0x0050 
	__int8 m_EnablePoseJobs; //0x0051 
	__int8 m_DisableAILodFeature; //0x0052 
	__int8 m_DisableModelAnimationCulling; //0x0053 
	__int8 m_EnableJobs; //0x0054 
	__int8 m_RunAsHighPriority; //0x0055 
	__int8 m_UpdateLoddingEnable; //0x0056 
	static AntSettings* GetInstance( )
	{
		return *( AntSettings** )( OFFSET_AntSettings );
	}
};//Size=0x0057
class ServerMetricsSettings:public DataContainer
{
public:
	CString m_ReportName; //+0x10
	CString m_LogSettingsPrefix; //+0x18
	bool m_Enabled; //+0x20
	bool m_DbxReportEnabled; //+0x21
	bool m_TickTelemetryEnabled; //+0x22
	bool m_DevelopmentTelemetryEnabled; //+0x23
	bool m_PerformanceTelemetryEnabled; //+0x24
	bool m_JuiceTelemetryEnabled; //+0x25
	bool m_PerformanceProfileStateEnabled; //+0x26
	bool m_TransactionTelemetryEnabled; //+0x27
	bool m_CompressTransactions; //+0x28
	static ServerMetricsSettings* GetInstance( )
	{
		return *( ServerMetricsSettings** )( OFFSET_ServerMetricsSettings );
	}
};