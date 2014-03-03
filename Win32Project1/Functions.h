VOID CreateConsole( )
{
	int hConHandle = 0; 
	HANDLE lStdHandle = 0;
	FILE *fp = 0;
	AllocConsole( );
	lStdHandle = GetStdHandle( STD_OUTPUT_HANDLE );
	hConHandle = _open_osfhandle( PtrToUlong( lStdHandle ), _O_TEXT );
	fp = _fdopen( hConHandle, "w" );
	*stdout = *fp;
	setvbuf( stdout, NULL, _IONBF, 0 );
}  
template <class T>
int pvfIndex(T func)
{
	union {
		T pfn;
		unsigned char* pb;
	};
	pfn = func;
	if( !pb ) return -1;
	int pboff = -1;
	if( pb[0] == 0x8b && pb[1] == 0x01 ) {	//mov eax, [ecx]
		pboff = 2;
	} else if( pb[0] == 0x8b && pb[1] == 0x44 && pb[2] == 0x24 && pb[3] == 0x04 &&		//mov eax, [esp+arg0]
		pb[4] == 0x8b && pb[5] == 0x00 ) {										//mov eax, [eax]
			pboff = 6;
	}

	if( pboff > 0 ) {
		if( pb[pboff] == 0xff ) {
			switch( pb[pboff+1] ) {
			case 0x20:	//jmp dword ptr [eax]
				return 0;
			case 0x60:	//jmp dword ptr [eax+0xNN]
				return (((int)pb[pboff+2])&0xff)/4;
			case 0xa0:	//jmp dword ptr [eax+0xNNN]
				return (*(unsigned int*)(pb+(pboff+2)))/4;
			default:
				break;
			}
		}
	}
	return -1;
}

bool GetBone(ClientSoldierEntity* pEnt,D3DXVECTOR3 *vOut,UpdatePoseResultData::BONES BoneId)
{
	if(!IsValidPtr(pEnt))
		return false;

	ClientRagDollComponent* pRag= pEnt->m_ragdollComponent;
	if(!IsValidPtr(pRag))
		return false;

	UpdatePoseResultData PoseResult=pRag->m_ragdollTransforms;
	if(PoseResult.m_ValidTransforms)
	{
		UpdatePoseResultData::QuatTransform* pQuat=PoseResult.m_ActiveWorldTransforms;
		if(!IsValidPtr(pQuat))
			return false;

		D3DXVECTOR3 Temp=pQuat[BoneId].m_TransAndScale;

		vOut->x=Temp.x;
		vOut->y=Temp.y;
		vOut->z=Temp.z;
		return true;
	}else{
		return false;
	}
}
bool WorldToScreen(D3DXVECTOR3 vLocVec4, D3DXVECTOR3 &vOut)
{

	GameRenderer *gamerenderer = GameRenderer::GetInstance();
	D3DXMATRIX vProjMatrix = gamerenderer->m_pRenderView->m_ViewProj;

	float width =DxRenderer::GetInstance()->m_pScreen->m_Width;
	float height =DxRenderer::GetInstance()->m_pScreen->m_Height;

	float w = vProjMatrix(0,3) * vLocVec4.x + 
		vProjMatrix(1,3) * vLocVec4.y + 
		vProjMatrix(2,3) * vLocVec4.z +  
		vProjMatrix(3,3); 
	if (w < 0.19)
	{
		//printf("broken\n");
		vOut.z = w;
		return false;
	}
	float x =  
		vProjMatrix(0,0) * vLocVec4.x + 
		vProjMatrix(1,0) * vLocVec4.y + 
		vProjMatrix(2,0) * vLocVec4.z +  
		vProjMatrix(3,0); 

	float y =  
		vProjMatrix(0,1) * vLocVec4.x + 
		vProjMatrix(1,1) * vLocVec4.y + 
		vProjMatrix(2,1) * vLocVec4.z +  
		vProjMatrix(3,1); 

	/*printf("PROJECTIONL\n %f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f \n \n",
			vProjMatrix._11,vProjMatrix._12,vProjMatrix._13,vProjMatrix._14,
			vProjMatrix._21,vProjMatrix._22,vProjMatrix._23,vProjMatrix._24,
			vProjMatrix._31,vProjMatrix._32,vProjMatrix._33,vProjMatrix._34,
			vProjMatrix._41,vProjMatrix._42,vProjMatrix._43,vProjMatrix._44);*/

	//printf("x:%f y:%f w:%f \n \n",x, y,w);

	vOut.x = (width*0.5) + (width*0.5) * x / w;
	vOut.y = (height*0.5) - (height*0.5) * y / w;
	vOut.z = w;

	//printf("vx: %f vy: %f vz: %f\nx: %f y:%f w:%f\nvOut.x:%f vOut.y:%f\nwidth:%f height:%f\n \n",vLocVec4.x,vLocVec4.y,vLocVec4.z,x,y,w,vOut.x,vOut.y,width,height);
	return true;
}
bool WorldToScreen(D3DXVECTOR3 &vLocVec4)
{

	GameRenderer *gamerenderer = GameRenderer::GetInstance();
	D3DXMATRIX vProjMatrix = gamerenderer->m_pRenderView->m_ViewProj;

	float width =DxRenderer::GetInstance()->m_pScreen->m_Width;
	float height =DxRenderer::GetInstance()->m_pScreen->m_Height;

	float w = vProjMatrix(0,3) * vLocVec4.x + 
		vProjMatrix(1,3) * vLocVec4.y + 
		vProjMatrix(2,3) * vLocVec4.z +  
		vProjMatrix(3,3); 
	if (w < 0.19)
	{
		//printf("broken\n");
		vLocVec4.z=w;
		return false;
	}
	float x =  
		vProjMatrix(0,0) * vLocVec4.x + 
		vProjMatrix(1,0) * vLocVec4.y + 
		vProjMatrix(2,0) * vLocVec4.z +  
		vProjMatrix(3,0); 

	float y =  
		vProjMatrix(0,1) * vLocVec4.x + 
		vProjMatrix(1,1) * vLocVec4.y + 
		vProjMatrix(2,1) * vLocVec4.z +  
		vProjMatrix(3,1); 

	/*printf("PROJECTIONL\n %f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f \n \n",
			vProjMatrix._11,vProjMatrix._12,vProjMatrix._13,vProjMatrix._14,
			vProjMatrix._21,vProjMatrix._22,vProjMatrix._23,vProjMatrix._24,
			vProjMatrix._31,vProjMatrix._32,vProjMatrix._33,vProjMatrix._34,
			vProjMatrix._41,vProjMatrix._42,vProjMatrix._43,vProjMatrix._44);*/

	//printf("x:%f y:%f w:%f \n \n",x, y,w);

	vLocVec4.x = (width*0.5) + (width*0.5) * x / w;
	vLocVec4.y = (height*0.5) - (height*0.5) * y / w;
	vLocVec4.z= w;
	return true;
}
void *DetourVTable(void **VTable, int Function, void *Detour)
{
	if (!VTable)
		return NULL;

	if (!Detour)
		return NULL;

	void *ret = VTable[Function];

	DWORD old;
	VirtualProtect(&(VTable[Function]), sizeof(void*), PAGE_EXECUTE_READWRITE, &old);
	VTable[Function] = Detour;
	VirtualProtect(&(VTable[Function]), sizeof(void*), old, &old);

	return ret;
}
/*InVec is ByRef, Accelerations are optional and default to 0,0,0*/

ClientSoldierAimingSimulation* GetAimAssist(ClientSoldierEntity* pEnemySoldier)
{
	ClientSoldierWeaponsComponent* pSoldierWepComp=pEnemySoldier->m_soldierWeaponsComponent;
	if(!IsValidPtr(pSoldierWepComp))
		return NULL;

	ClientSoldierWeapon* pSoldierWep=pSoldierWepComp->GetActiveSoldierWeapon();
	if(!IsValidPtr(pSoldierWep))
		return NULL;

	ClientSoldierAimingSimulation* pAimSimulation=pSoldierWep->m_authorativeAiming;
	if(!IsValidPtr(pAimSimulation))
		return NULL;


	return pAimSimulation;
}
float DistanceToVector( D3DXVECTOR3* first,D3DXVECTOR3 const &other )
{
	D3DXVECTOR3 Distance;
	Distance.x = other.x - first->x;
	Distance.y = other.y - first->y;
	Distance.z = other.z - first->z;
	return sqrt( ( Distance.x * Distance.x ) + ( Distance.y * Distance.y ) + ( Distance.z * Distance.z ) );
}
FiringFunctionData* GetFiringFunctionData(ClientSoldierEntity* pSoldier)
{
	ClientSoldierWeapon* pWep=pSoldier->GetActiveWeapon();
	if(!IsValidPtr(pWep))
		return NULL;
	
	WeaponFiring* WepFiring=pWep->m_pPrimary;
	if(!IsValidPtr(WepFiring))
		return NULL;
	
	PrimaryFire* pPrimary=WepFiring->m_pPrimaryFire;
	if(!IsValidPtr(pPrimary))
		return NULL;
	
	FiringFunctionData* pFiringFunctionData=pPrimary->m_FiringData;
	if(!IsValidPtr(pFiringFunctionData))
		return NULL;

	return pFiringFunctionData;
}
bool GetVehicleAABB(ClientVehicleEntity* pVehicle,AxisAlignedBox2 &AABB)
{
	if(!IsValidPtr(pVehicle))
		return false;

	D3DXMATRIX trans;
	pVehicle->GetTransform(&trans);
	D3DXVECTOR3 origin=D3DXVECTOR3(trans._41,trans._42,trans._43);//41,42,43
	
	D3DXVECTOR3 min = pVehicle->m_childrenAABB.min+origin;
	D3DXVECTOR3 max = pVehicle->m_childrenAABB.max+origin;
	D3DXVECTOR3 crnr2 = D3DXVECTOR3(max.x, min.y, min.z);
	D3DXVECTOR3 crnr3 = D3DXVECTOR3(max.x, min.y, max.z);
	D3DXVECTOR3 crnr4 = D3DXVECTOR3(min.x, min.y, max.z);
	D3DXVECTOR3 crnr5 = D3DXVECTOR3(min.x, max.y, max.z);
	D3DXVECTOR3 crnr6 = D3DXVECTOR3(min.x, max.y, min.z);
	D3DXVECTOR3 crnr7 = D3DXVECTOR3(max.x, max.y, min.z);

	if(!WorldToScreen(min))
		return false;
	if(!WorldToScreen(max))
		return false;
	if(!WorldToScreen(crnr2))
		return false;
	if(!WorldToScreen(crnr3))
		return false;
	if(!WorldToScreen(crnr4))
		return false;
	if(!WorldToScreen(crnr5))
		return false;
	if(!WorldToScreen(crnr6))
		return false;
	if(!WorldToScreen(crnr7))
		return false;

	AABB.min=min;
	AABB.max=max;
	AABB.crnr2=crnr2;
	AABB.crnr3=crnr3;
	AABB.crnr4=crnr4;
	AABB.crnr5=crnr5;
	AABB.crnr6=crnr6;
	AABB.crnr7=crnr7;

	return true;
}
float VectorLength2D(D3DXVECTOR3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}
float VectorLength3D(D3DXVECTOR3* pV)
{
	return sqrtf(pV->x * pV->x +pV->y*pV->y+ pV->z * pV->z);
}
D3DXVECTOR3 NormalizeVec(D3DXVECTOR3 in)
{
	D3DXVECTOR3 temp=in;
	float length=D3DXVec3Length(&temp);
	temp.x/=length;
	temp.y/=length;
	temp.z/=length;
	return temp;
}
double GetClosestTime(double TimeArray[4],float Val)
{
	double clossest=-99;
	double difference=99999;
	for(int i=0;i<4;i++)
	{
		if(TimeArray[i]>0.0)
		{
			double tempdiff=abs(TimeArray[i]-Val);
			if(tempdiff<difference)
			{
				difference=tempdiff;
				clossest=TimeArray[i];
			}
		}
	}
	return clossest;
}
void AimCorrection(D3DXVECTOR3 LocalPos,D3DXVECTOR3 EnemyPos,D3DXVECTOR3 MyVelocity,D3DXVECTOR3 EnemyVelocity,D3DXVECTOR3* InVec,float Distance,float Bulletspeed,float Gravity=9.81f,D3DXVECTOR3 MyAccel=D3DXVECTOR3(0,0,0),D3DXVECTOR3 EnemyAccel=D3DXVECTOR3(0,0,0))
{
	//double roots[4];
	//double coefficients[5];
	//D3DXVECTOR3 g=D3DXVECTOR3(0,Gravity,0);
	////x^4*a+x^3*b+x^2*c+x*d+e=0  x=time
	//coefficients[4]= .25f*D3DXVec3LengthSq(&g); //a
	//coefficients[3]= D3DXVec3Dot(&g,&EnemyVelocity); //b
	//coefficients[2]= D3DXVec3Dot(&g,&LocalPos)-D3DXVec3Dot(&g,&EnemyPos)-Bulletspeed*Bulletspeed; //c
	//coefficients[1]= 2*(D3DXVec3Dot(&EnemyVelocity,&LocalPos)-D3DXVec3Dot(&EnemyVelocity,&EnemyPos)); //d
	//coefficients[0]= D3DXVec3LengthSq(&LocalPos)+D3DXVec3LengthSq(&EnemyPos)-2*D3DXVec3Dot(&LocalPos,&EnemyPos); //e
	//solveQuartic(coefficients,roots);

	FLOAT m_time=Distance / fabs(Bulletspeed); //distance=rate*time
	//double m_timeQrt=GetClosestTime(roots,m_time);//select the root closest to approximate time	
	//if(m_timeQrt==0)
	//{
	//	printf("Roots: %f, %f, %f, %f  \n",roots[0],roots[1],roots[2],roots[3]);
	//}else{
	//	m_time=m_timeQrt;
	//}

	FLOAT m_grav = fabs(Gravity);
	*InVec  = *InVec +   (EnemyVelocity * m_time) +(.5f*EnemyAccel*(m_time*m_time)) ;
	//*InVec    = *InVec - (MyVelocity * m_time) + (.5f*MyAccel*(m_time*m_time)) ;
	
	InVec->y += 0.5 * m_grav * m_time * m_time;
}
void DoAimCorrection(ClientPlayer* p_LocalPlayer,ClientPlayer* pEnemyPlayer,D3DXVECTOR3& EnemyVec,ClientVehicleEntity* pEnemyVeh=NULL)
{
	if(!IsValidPtr(p_LocalPlayer))
		return;

	if(!IsValidPtr(pEnemyPlayer))
		return;

	ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
	if(!IsValidPtr(p_LocalSoldier))
		return;

	ClientSoldierEntity* pEnemySoldier=pEnemyPlayer->GetClientSoldier();
	if(!IsValidPtr(pEnemySoldier))
		return;

	ClientSoldierPrediction* p_LocalPrediction=p_LocalSoldier->m_pPredictedController;
	if(!IsValidPtr(p_LocalPrediction))
		return;

	FiringFunctionData* pFiringFunctionData=0;

	if(p_LocalPlayer->InVehicle())
	{
		WeaponFiring* pWeaponFiring = *( WeaponFiring** )OFFSET_PPCURENTWEAPONFIRING;
		if(!IsValidPtr(pWeaponFiring))
			return;

		PrimaryFire* pPrimaryFire=pWeaponFiring->m_pPrimaryFire;
		if(!IsValidPtr(pPrimaryFire))
			return;
		pFiringFunctionData=pPrimaryFire->m_FiringData;
	}else{
		pFiringFunctionData=GetFiringFunctionData(p_LocalSoldier);
	}
	if(!IsValidPtr(pFiringFunctionData))
		return;

	FiringFunctionData::ShotConfigData ShotConfig=pFiringFunctionData->m_ShotConfigData;
	
	BulletEntityData* pProjData=ShotConfig.m_ProjectileData;
	if(!IsValidPtr(pProjData))
		return;

	//TypeInfo* pType=pProjData->getType();
	//if(!IsValidPtr(pType))
	//	return;

	//MemberInfo::MemberInfoData* pMemberInfo=pType->m_infoData;
	//if(!IsValidPtr(pMemberInfo))
	//	return;

	float Gravity=0;
	//if(strcmp(pMemberInfo->m_name,"BulletEntityData")==0) //are we a gun
	//{
		Gravity=pProjData->m_Gravity;

	//}else if(strcmp(pMemberInfo->m_name,"MissileEntityData")==0){ //or are we a missile
	//	MissileEntityData* pMisProjData=(MissileEntityData*)pProjData; //recast to missile
	//	if(!IsValidPtr(pMisProjData))
	//		return;

	//	Gravity=pMisProjData->m_Gravity;
	//}

	D3DXVECTOR3 myvelocity,enemyvelocity;
	if(p_LocalPlayer->InVehicle())
	{
		/*myvelocity=p_LocalPlayer->GetClientVehicleEntity()->m_Velocity;*/
		myvelocity=D3DXVECTOR3(0,0,0);
	}else{
		myvelocity=p_LocalPrediction->m_Velocity;
	}
	if(pEnemyPlayer->InVehicle())
	{
		if(IsValidPtr(pEnemyVeh))
		{
			ClientChassisComponent* pChassis=pEnemyVeh->m_Chassis;
			if(!IsValidPtr(pChassis))
				return;

			enemyvelocity=pChassis->m_Velocity;
		}else{
			ClientVehicleEntity* pVeh=pEnemyPlayer->GetClientVehicleEntity();
			if(!IsValidPtr(pVeh))
				return;

			ClientChassisComponent* pChassis=pVeh->m_Chassis;
			if(!IsValidPtr(pChassis))
				return;

			enemyvelocity=pChassis->m_Velocity;
		}
	}else{
		ClientSoldierPrediction* pEnemyPrediction=pEnemySoldier->m_pPredictedController;
		if(!IsValidPtr(pEnemyPrediction))
			return;

		enemyvelocity=pEnemyPrediction->m_Velocity;
	}
	
	D3DXMATRIX InvMatrix=GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse;
	D3DXVECTOR3 LocalPos=D3DXVECTOR3(InvMatrix._41,InvMatrix._42,InvMatrix._43);
	float distance=VectorLength3D(&(EnemyVec-LocalPos));
	AimCorrection(LocalPos,EnemyVec,myvelocity,enemyvelocity,&EnemyVec,distance,ShotConfig.m_InitialSpeed.z,Gravity);	
}
bool GetPlayerVelocityByIndex(int index,D3DXVECTOR3 &Out)
{
	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return false;

	ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
	if(!IsValidPtr(p_PlayerManager))
		return false;

	ClientPlayer* pEnemyPlayer=p_PlayerManager->GetPlayerById(index);
	if(!IsValidPtr(pEnemyPlayer))
		return false;

	ClientSoldierEntity* pEnemySoldier=pEnemyPlayer->GetClientSoldier();
	if(!IsValidPtr(pEnemySoldier))
		return false;

	if(pEnemySoldier->m_pHealthComponent->m_Health <=0.1f)
		return false;

	ClientSoldierPrediction* pEnemyPrediction=pEnemySoldier->m_pPredictedController;
	if(!IsValidPtr(pEnemyPrediction))
		return false;

	if(pEnemyPlayer->InVehicle())
	{
		ClientVehicleEntity* pVeh=pEnemyPlayer->GetClientVehicleEntity();
		if(!IsValidPtr(pVeh))
			return false;

		Out=pVeh->m_Velocity;
	}else{
		Out=pEnemyPrediction->m_Velocity;
	}
	return true;
}

static bool IsVisible(D3DXVECTOR3* vFrom, D3DXVECTOR3* vTo,bool& visible,eastl::fixed_vector<PhysicsEntity const*,8,0> *excludes=NULL)
{
	if(!IsValidPtr(vFrom) || !IsValidPtr(vTo))
		return false;

	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return false;

	HavokPhysicsManager* pHavok=p_GameContext->m_pPhysicsManager;
	if(!IsValidPtr(pHavok))
		return false;

	GameWorld* pGameWorld=pHavok->m_GameWorld;
	if(!IsValidPtr(pGameWorld))
		return false;

	IPhysicsRayCaster* pRayCaster=pGameWorld->m_RayCaster;
	if(!IsValidPtr(pRayCaster))
		return false;

	RayCastHit ray;

    __declspec(align(16)) D3DXVECTOR4 vFinalFrom = D3DXVECTOR4(vFrom->x,vFrom->y,vFrom->z,0);
    __declspec(align(16)) D3DXVECTOR4 vFinalTo = D3DXVECTOR4(vTo->x,vTo->y,vTo->z,0);

	visible = !pRayCaster->PhysicsRayQuery("OnGroundState::update", &vFinalFrom, &vFinalTo, &ray,IPhysicsRayCaster::DontCheckCharacter | IPhysicsRayCaster::DontCheckRagdoll | IPhysicsRayCaster::DontCheckPhantoms | 0x04 , excludes);

	return true;
} 
bool IsInFOV(D3DXVECTOR3 forward,D3DXVECTOR3 EnemyPos, D3DXVECTOR3 LocalPos,float fov )
{
	D3DXVECTOR3 vec1,vec2;
	D3DXVec3Normalize(&vec1,&forward);
	D3DXVec3Normalize(&vec2,&(EnemyPos-LocalPos));
	float angle=acos(D3DXVec3Dot(&vec1,&vec2));
	angle= D3DXToDegree(angle);
	
	if(angle>(fov/2))
		return false;

	return true;
}
