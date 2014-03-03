#include "Includes.h"


HANDLE Handle;
bool norecoil=true;
bool noSway=false;
bool esp=true;
bool snaplines=true;
bool names=false;
bool aimbot=false;
bool noheat=true;
bool drawmenu=false;
int menuindex=0;
int menuelements=7;
bool windowcreated=false;
int fov=5;
bool headshot=true;
int Framecount=0;
float ScreenShotThreshold=5000;//delay so we can see screenshot for 5 seconds
HINSTANCE inst;
typedef int (__cdecl* tScreenshot)();
tScreenshot oScreenshot;

CVMTHookManager64* UpdateHook=0;
typedef DWORD_PTR ( __stdcall* tUpdate )( DWORD_PTR a1, DWORD_PTR a2, DWORD_PTR a3 );
tUpdate oUpdate;//bone update
PVOID* pAntVtable = ( PVOID* )AntVtable;

CVMTHookManager64* PreFrameHook=0;
typedef int (__stdcall* tPreFrameUpdate)(float dt);
tPreFrameUpdate oPreFrame;//borderinputnode
float g_pInputBuffers[123];//input buffer
BorderInputNode* g_pBorderInputNode=BorderInputNode::GetInstance();

CVMTHookManager64* PresentHook=0;
typedef signed int ( __stdcall* tPresent )(IDXGISwapChain* pSwapchain, UINT SyncInterval, UINT Flags);
tPresent oPresent; //our dx hook

void __stdcall ESP();//forward declare
void __stdcall GetSpectators();
dhFPSTimer* OverlayTimer;
dhFPSTimer* GameTimer;

float delta=375; //5 seconds at 70 fps
float cur=0;
bool count=false;;

void DrawMenu()
{
	if(drawmenu)
	{
		norecoil ? DrawShadowString("No Recoil: ON",0,60,255,0,0,pFontSmall):DrawShadowString("No Recoil: OFF",0,60,0,255,0,pFontSmall);
		esp ? DrawShadowString("ESP: ON",0,80,255,0,0,pFontSmall):DrawShadowString("ESP: OFF",0,80,0,255,0,pFontSmall);
		snaplines ? DrawShadowString("SnapLines: ON",0,100,255,0,0,pFontSmall):DrawShadowString("SnapLines: OFF",0,100,0,255,0,pFontSmall);
		names? DrawShadowString("Names: ON",0,120,255,0,0,pFontSmall):DrawShadowString("Names: OFF",0,120,0,255,0,pFontSmall);
		noSway? DrawShadowString("No Sway: ON",0,140,255,0,0,pFontSmall):DrawShadowString("No Sway: OFF",0,140,0,255,0,pFontSmall);
		aimbot? DrawShadowString("Aimbot: ON",0,160,255,0,0,pFontSmall):DrawShadowString("Aimbot: OFF",0,160,0,255,0,pFontSmall);
		headshot? DrawShadowString("HeadShot: ON",0,180,255,0,0,pFontSmall):DrawShadowString("Headshot: OFF",0,180,0,255,0,pFontSmall);
		char fovstring[512];
		sprintf_s(fovstring,"Fov: %d",fov);
		DrawShadowString(fovstring,0,200,255,0,0,pFontSmall);

		switch (menuindex)
		{
		case 0:
			DrawShadowString("<-",110,60,0,0,0,pFontSmall);
			break;
		case 1:
			DrawShadowString("<-",110,80,0,0,0,pFontSmall);
			break;
		case 2:
			DrawShadowString("<-",110,100,0,0,0,pFontSmall);
			break;
		case 3:
			DrawShadowString("<-",110,120,0,0,0,pFontSmall);
			break;
		case 4:
			DrawShadowString("<-",110,140,0,0,0,pFontSmall);
			break;
		case 5:
			DrawShadowString("<-",110,160,0,0,0,pFontSmall);
			break;
		case 6:
			DrawShadowString("<-",110,180,0,0,0,pFontSmall);
			break;
		case 7:
			DrawShadowString("<-",110,200,0,0,0,pFontSmall);
			break;
		default:
			break;
		}
	}
}
int Render()
{
	p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
	p_Device->BeginScene();

	if(tWnd == GetForegroundWindow())
	{

		//text with shadow
		DrawShadowString("Overlay Running", 0, 0, 240, 240, 250, pFontSmall);
		
		//crosshair
		
		FillRGBNOAA(Width / 2 - 22, Height / 2, 44, 1, 240, 240, 250, 255); 
		FillRGBNOAA(Width / 2, Height / 2 - 22, 1, 44, 240, 240, 250, 255);
		ESP();


		float fps;
		DWORD min_fps;
		DWORD max_fps;
		DrawShadowString(OverlayTimer->GetFPSString(),0,20,240,240,250,pFontSmall);
		DrawShadowString(GameTimer->GetFPSString(),0,40,240,240,250,pFontSmall);
		DrawMenu();
		GetSpectators();
		if(*(DWORD64*)PBRecieveSS != 0.0f)
		{
			count=true;
		}
		if(count && cur<delta)
		{
			cur++;
			DrawShadowString("Admin Took ScreenShot",Width/2,Height/2,240,240,250,pFontSmall);
		}else{
			count=false;
			cur=0;
		}
	}
	p_Device->EndScene();
	p_Device->PresentEx(0, 0, 0, 0, 0);
	OverlayTimer->Present();

	return 0;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{

	switch (Message)
	{	
	case WM_PAINT:
		Render();
		break;

	case WM_CREATE:
		DwmExtendFrameIntoClientArea(hWnd, &Margin);
		break;

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;	
		break;
	case  WM_SIZE:
		if(windowcreated)
		{
			Width = DxRenderer::GetInstance()->m_pScreen->m_Width;
			Height = DxRenderer::GetInstance()->m_pScreen->m_Height;
			ZeroMemory(&p_Params, sizeof(p_Params));    
			p_Params.Windowed = TRUE;   
			p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;    
			p_Params.hDeviceWindow = hWnd;    
			p_Params.MultiSampleQuality   = D3DMULTISAMPLE_NONE;
			p_Params.EnableAutoDepthStencil = TRUE;
			p_Params.AutoDepthStencilFormat = D3DFMT_D16;
			p_Params.BackBufferFormat = D3DFMT_A8R8G8B8 ;     
			p_Params.BackBufferWidth = Width;    
			p_Params.BackBufferHeight = Height;    

			p_LineNoAA->OnLostDevice();
			p_Line->OnLostDevice();
			pFontSmall->OnLostDevice();

			p_Device->Reset(&p_Params);

			p_Line->OnResetDevice();
			pFontSmall->OnResetDevice();
			p_LineNoAA->OnResetDevice();
			if(!p_Line)
			{
				D3DXCreateLine(p_Device, &p_Line);
				p_Line->SetAntialias(1); 
			}
			if(!p_LineNoAA)
			D3DXCreateLine(p_Device, &p_LineNoAA);

			if(!pFontSmall)
			D3DXCreateFontA(p_Device, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Calibri", &pFontSmall);
		}
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}
DWORD WINAPI SetWindowToTarget(LPVOID lparams)
{
	while(true)
	{
		tWnd = FindWindow(0, tWindowName);
		if (tWnd)
		{
			GetClientRect(tWnd,&tClient);
			GetWindowRect(tWnd, &tSize);
		
			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);
			int windowheight;
			int windowwidth;
			int clientheight;
			int clientwidth;
			int borderheight;
			int borderwidth;
			if(dwStyle & WS_BORDER)
			{	windowwidth=tSize.right-tSize.left;
				windowheight=tSize.bottom-tSize.top;
			
				clientwidth=tClient.right-tClient.left;
				clientheight=tClient.bottom-tClient.top;
				
				borderheight=(windowheight-tClient.bottom);
				borderwidth=(windowwidth-tClient.right)/2; //only want one side
				borderheight-=borderwidth; //remove bottom
		
				tSize.left+=borderwidth;
				tSize.top+=borderheight;
			}
			MoveWindow(hWnd, tSize.left, tSize.top,clientwidth , clientheight, true);
		}
		/*else
		{
			char ErrorMsg[125];
			sprintf(ErrorMsg, "%s might not be running", tWindowName);
			MessageBox(0, ErrorMsg, "Error can't find game window", MB_OK | MB_ICONERROR);
			exit(1);
		}*/
		Sleep(100);
	}
}
DWORD WINAPI Create(LPVOID lpargs)
{
	
	CreateThread(NULL, NULL, SetWindowToTarget, NULL, NULL, NULL);
	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = inst;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = lWindowName;
	wClass.lpszMenuName = lWindowName;
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	!RegisterClassEx(&wClass);
	
	
	tWnd = FindWindow(0, tWindowName);
	if (tWnd)
	{
		printf("m_pScreen: %X \n",DxRenderer::GetInstance()->m_pScreen);
		Width = DxRenderer::GetInstance()->m_pScreen->m_Width;
		Height = DxRenderer::GetInstance()->m_pScreen->m_Height;
		
		hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, lWindowName, lWindowName,  WS_POPUP, 1, 1, Width, Height, 0, 0, 0, 0);
		SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA);
		SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
		ShowWindow( hWnd, SW_SHOW);
	}
	
	DirectXInit(hWnd);

	printf("Made Window \n");
	windowcreated=true;
	while(true)
	{
		if(PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		Sleep(1);
	}
	return 1;
}

DWORD WINAPI InputThread(LPVOID lpargs)
{
	while(1)
	{
		if(GetAsyncKeyState(VK_DELETE))
		{
			drawmenu=!drawmenu;
			Sleep(500);
		}
		if(drawmenu)
		{
			if(GetAsyncKeyState(VK_UP) && menuindex>0 )//arrow up
			{
				menuindex--;
				Sleep(300);
			}
			if(GetAsyncKeyState(VK_DOWN) && menuindex<menuelements ) //arrow down
			{
				menuindex++;
				Sleep(300);
			}

			if(GetAsyncKeyState(VK_RETURN)) //enter
			{
				switch(menuindex)
				{
				case 0:
					norecoil=!norecoil;
					Sleep(500);
					break;
				case 1:
					esp=!esp;
					Sleep(500);
					break;
				case 2:
					snaplines=!snaplines;
					Sleep(500);
					break;
				case 3:
					names=!names;
					Sleep(500);
					break;
				case 4:
					noSway=!noSway;
					Sleep(500);
					break;
				case 5:
					aimbot=!aimbot;
					Sleep(500);
					break;
				case 6:
					headshot=!headshot;
					Sleep(500);
					break;
				}
			}
			if(menuindex==7)
			{
				if(GetAsyncKeyState(VK_LEFT)&&(fov-5)>0)
				{
					fov-=5;
					Sleep(500);
				}
				if(GetAsyncKeyState(VK_RIGHT)&& (fov+5)<180)
				{
					fov+=5;
					Sleep(500);
				}
			}
		}
		Sleep(20);
	}
}
void __stdcall PrintVehicle()
{
	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return;

	ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
	if(!IsValidPtr(p_PlayerManager))
		return;

	ClientPlayer* p_LocalPlayer=p_PlayerManager->m_pLocalPlayer;
	if(!IsValidPtr(p_LocalPlayer))
		return;

	ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
	if(!IsValidPtr(p_LocalSoldier))
		return;
	ClientVehicleEntity* pVeh=p_LocalPlayer->GetClientVehicleEntity();
	if(!IsValidPtr(pVeh))
		return;

	VehicleEntityData* pVehData=pVeh->m_data;
	if(!IsValidPtr(pVehData))
		return;

	printf("Vehicle: %X \n",pVeh);
	printf("Vehicle Data: %X \n",pVehData);
	printf("Velocity X%f Y%f Z%f \n",pVeh->m_Velocity.x,pVeh->m_Velocity.y,pVeh->m_Velocity.z);
	ClientWeapon* pVehwep=((ClientWeapon*)OFFSET_PPCURENTWEAPONFIRING)-0x28;
	printf("VehClientWep:%X \n",pVehwep);
	WeaponFiring* pWeaponFiring = *( WeaponFiring** )OFFSET_PPCURENTWEAPONFIRING;
	if(!IsValidPtr(pWeaponFiring))
		return;
	printf("Vehicle Wep:%X \n",pWeaponFiring);
	PrimaryFire* pPrimary=pWeaponFiring->m_pPrimaryFire;
	if(!IsValidPtr(pPrimary))
		return;

	FiringFunctionData* pFiringFunctionData=pPrimary->m_FiringData;
	if(!IsValidPtr(pFiringFunctionData))
		return;

	FiringFunctionData::ShotConfigData pShotConfig=pFiringFunctionData->m_ShotConfigData;

	BulletEntityData* pBulletData=pShotConfig.m_ProjectileData;

	printf("Gravity:%f BulletSpeed:%f \n",pBulletData->m_Gravity,pShotConfig.m_InitialSpeed.z);
}
void __stdcall PrintVals()
{
	Main* pMain=Main::GetInstance();
	if(!IsValidPtr(pMain))
		return;
	printf("Main: %X\n",pMain);

	Client* pClient=pMain->m_pClient;
	if(!IsValidPtr(pClient))
		return;
	printf("Client: %X \n",pClient);
	printf("Settings: %X \n",pClient->m_pSettings);

	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return;
	printf("GameContext: %X \n",p_GameContext);

	ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
	if(!IsValidPtr(p_PlayerManager))
		return;
	printf("PlayerManager: %X\n",p_PlayerManager);

	ClientPlayer* p_LocalPlayer=p_PlayerManager->m_pLocalPlayer;
	if(!IsValidPtr(p_LocalPlayer))
		return;
	printf("ClientPlayer: %X\n",p_LocalPlayer);
	//printf("ClientPlayerWeak:%X \n",p_LocalPlayer->m_player.GetData());

	ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
	if(!IsValidPtr(p_LocalSoldier))
		return;
	printf("ClientSoldier: %X\n",p_LocalSoldier);

	ClientCharacterEntity* p_LocalCharacter=(ClientCharacterEntity*)p_LocalPlayer->GetCharacterEntity();
	if(!IsValidPtr(p_LocalCharacter))
		return;
	
	if(p_LocalSoldier->m_pHealthComponent->m_Health<=0.1f)
		return;

	ClientSoldierWeaponsComponent* SoldierWepComp=p_LocalSoldier->m_soldierWeaponsComponent;
	if(!IsValidPtr(SoldierWepComp))
		return;

	ClientSoldierWeapon* SoldierWeapon=SoldierWepComp->GetActiveSoldierWeapon();
	if(!IsValidPtr(SoldierWeapon))
		return;

	ClientAntAnimatableComponent* pAnt=SoldierWepComp->m_animatableComponent[1];
	if(!IsValidPtr(pAnt))
		return;

	ClientSoldierAimingSimulation* pAimSim=SoldierWeapon->m_authorativeAiming;
	if(!IsValidPtr(pAimSim))
		return;
	
	WeaponFiring* WepFiring=SoldierWeapon->m_pPrimary;
	if(!IsValidPtr(WepFiring))
		return;

	WeaponSway* WepSway=WepFiring->m_pSway;
	if(!IsValidPtr(WepSway))
		return;

	ZoomLevelData* zoomData=pAimSim->m_data->m_ZoomLevels[1];

	FiringFunctionData* pFFData=GetFiringFunctionData(p_LocalSoldier);
	if(!IsValidPtr(pFFData))
		return;
	
	FiringFunctionData::ShotConfigData ShotConfig=pFFData->m_ShotConfigData;
	

	

	
	
	printf("SoldierEntityData: %X \n",p_LocalSoldier->m_pSoldierData);
	printf("SoldierWeaponComp:%X \n",SoldierWepComp);
	printf("Ant:%X \n",pAnt);
	printf("SoldierWeapon:%X \n",SoldierWeapon);
	printf("ClientCharacterFunc: %X\n",p_LocalCharacter);
	printf("ClientCharacterAdd: %X\n",p_LocalSoldier->m_pCharacterEntity);
	printf("ClientCharacter Weak:%X \n",p_LocalPlayer->m_character.GetData());
	printf("Predicted Controller: %X \n",p_LocalSoldier->m_pPredictedController);
	
	printf("Aiming Simulation:%X \n",pAimSim);
	printf("ZoomData: %X \n",zoomData);	
	printf("ShotConfig %X \n",ShotConfig);
	printf("BulletEntity Data: %X \n",ShotConfig.m_ProjectileData);
	printf("Gravity: %f \n",ShotConfig.m_ProjectileData->m_Gravity);
	printf("Entry: %X \n",p_LocalPlayer->GetEntryComponent());
	printf("GameRenderer: %X \n",GameRenderer::GetInstance());
	printf("DxRender: %X \n",DxRenderer::GetInstance());
	printf("DxRenderSettings: %X \n",DxRenderer::GetInstance()->m_settings);
	printf("GameRendererSettings: %X \n",GameRenderer::GetInstance()->m_GameRenderSettings);
	printf("Player Velocity:X%f Y%f Z%f\n",p_LocalSoldier->m_pPredictedController->m_Velocity.x,p_LocalSoldier->m_pPredictedController->m_Velocity.y,p_LocalSoldier->m_pPredictedController->m_Velocity.z);
	//printInfo(p_LocalPlayer->GetEntryComponent()->entryData()->getType());
	//p_LocalSoldier->m_pComponents->Dump();
}
void __stdcall PrintWeaponType()
{
	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return;

	ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
	if(!IsValidPtr(p_PlayerManager))
		return;

	ClientPlayer* p_LocalPlayer=p_PlayerManager->m_pLocalPlayer;
	if(!IsValidPtr(p_LocalPlayer))
		return;

	ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
	if(!IsValidPtr(p_LocalSoldier))
		return;

	FiringFunctionData* pFiringFunctionData=GetFiringFunctionData(p_LocalSoldier);
	if(!IsValidPtr(pFiringFunctionData))
		return;

	FiringFunctionData::ShotConfigData ShotConfig=pFiringFunctionData->m_ShotConfigData;

	BulletEntityData* pBulletData=ShotConfig.m_ProjectileData;
	if(!IsValidPtr(pBulletData))
		return;

	printf("Bullet Data Name:%s \n",ShotConfig.m_ProjectileData->getType()->m_infoData->m_name);
	printf("Hit Type: %X \n",ShotConfig.m_ProjectileData->m_HitReactionWeaponType);
	printf("Gravity:%f BulletSpeed:%f \n",pBulletData->m_Gravity,ShotConfig.m_InitialSpeed.z);
}

void __stdcall noRecoil()
{
		ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
		if(!IsValidPtr(p_GameContext))
			return;
		
		ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
		if(!IsValidPtr(p_PlayerManager))
			return;

		ClientPlayer* p_LocalPlayer=p_PlayerManager->m_pLocalPlayer;
		if(!IsValidPtr(p_LocalPlayer))
			return;
		
		ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
		if(!IsValidPtr(p_LocalSoldier))
			return;
	
		ClientSoldierEntity::BreathControlHandler* pBreath= p_LocalSoldier->m_breathControlHandler;
		if(!IsValidPtr(pBreath))
			return;

		if(p_LocalSoldier->m_pHealthComponent->m_Health<=0.1f)
			return;
	
		ClientSoldierWeaponsComponent* SoldierWepComp=p_LocalSoldier->m_soldierWeaponsComponent;
		if(!IsValidPtr(SoldierWepComp))
			return;

		ClientSoldierWeapon* SoldierWeapon=SoldierWepComp->GetActiveSoldierWeapon();
		if(!IsValidPtr(SoldierWeapon))
			return;
		
		WeaponFiring* WepFiring=SoldierWeapon->m_pPrimary;
		if(!IsValidPtr(WepFiring))
			return;
		
		WeaponSway* WepSway=WepFiring->m_pSway;
		if(!IsValidPtr(WepSway))
			return;
		
		ClientSoldierAimingSimulation* pAimSim=SoldierWeapon->m_authorativeAiming;
		if(!IsValidPtr(pAimSim))
			return;

		SoldierAimingSimulationData* pAimSimData=pAimSim->m_data;
		if(!IsValidPtr(pAimSimData))
			return;

		ZoomLevelData* zoomData=pAimSimData->m_ZoomLevels[0];
		if(!IsValidPtr(zoomData))
			return;

		ZoomLevelData* zoomData1=pAimSimData->m_ZoomLevels[1];
		if(!IsValidPtr(zoomData))
			return;

		if(norecoil)
		{
			WepSway->m_currentDispersionPitch=0.0f;
			WepSway->m_currentDispersionRoll=0.0f;
			WepSway->m_currentDispersionTransY=0.0f;
			WepSway->m_currentDispersionYaw=0.0f;
			WepSway->m_deviationPitch=0.0f;
			WepSway->m_deviationRoll=0.0f;
			WepSway->m_deviationTransY=0.0f;
			WepSway->m_deviationYaw=0.0f;
		}

		if(noSway)
		{
			if(zoomData->m_SwayPitchMagnitude>0)
				zoomData->m_SwayPitchMagnitude=0.0f;

			if(zoomData->m_SwayYawMagnitude>0)
				zoomData->m_SwayYawMagnitude=0.0f;

			if(zoomData->m_SupportedSwayPitchMagnitude>0)
				zoomData->m_SupportedSwayPitchMagnitude=0.0f;

			if(zoomData->m_SupportedSwayYawMagnitude>0)
				zoomData->m_SupportedSwayYawMagnitude=0.0f;

			if(zoomData->m_SuppressedSwayPitchMagnitude>0)
				zoomData->m_SuppressedSwayPitchMagnitude=0.0f;

			if(zoomData->m_SuppressedSwayYawMagnitude>0)
				zoomData->m_SuppressedSwayYawMagnitude=0.0f;

			if(zoomData->m_SuppressedSwayMinFactor>0)
				zoomData->m_SuppressedSwayMinFactor=0.0f;
		//	-------------------------------------------------
			if(zoomData1->m_SwayPitchMagnitude>0)
				zoomData1->m_SwayPitchMagnitude=0.0f;

			if(zoomData1->m_SwayYawMagnitude>0)
				zoomData1->m_SwayYawMagnitude=0.0f;

			if(zoomData1->m_SupportedSwayPitchMagnitude>0)
				zoomData1->m_SupportedSwayPitchMagnitude=0.0f;

			if(zoomData1->m_SupportedSwayYawMagnitude>0)
				zoomData1->m_SupportedSwayYawMagnitude=0.0f;

			if(zoomData1->m_SuppressedSwayPitchMagnitude>0)
				zoomData1->m_SuppressedSwayPitchMagnitude=0.0f;

			if(zoomData1->m_SuppressedSwayYawMagnitude>0)
				zoomData1->m_SuppressedSwayYawMagnitude=0.0f;

			if(zoomData1->m_SuppressedSwayMinFactor>0)
				zoomData1->m_SuppressedSwayMinFactor=0.0f;

			pBreath->m_Enabled=NULL;
		}
		if(noheat)
		{
			WeaponFiring* pWeaponFiring = *( WeaponFiring** )OFFSET_PPCURENTWEAPONFIRING;
			if(!IsValidPtr(pWeaponFiring))
				return;

			PrimaryFire* pPrimaryFire=pWeaponFiring->m_pPrimaryFire;
			if(!IsValidPtr(pPrimaryFire))
				return;

			FiringFunctionData* pFFD=pPrimaryFire->m_FiringData;
			if(!IsValidPtr(pFFD))
				return;

			pFFD->m_OverHeatData.m_HeatDropPerSecond=99.0f;
			pFFD->m_OverHeatData.m_OverHeatPenaltyTime=0.0f;
			pFFD->m_OverHeatData.m_HeatPerBullet=0.0f;
			pWeaponFiring->m_recoilAngleX=0.0f;
			pWeaponFiring->m_recoilAngleY=0.0f;
			pWeaponFiring->m_recoilAngleZ=0.0f;
			pFFD->m_AmmoConfigData.m_AutoReplenishDelay=0.0f;
		}

	return;
}

void __stdcall ESP()
{
	
	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return;

	ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
	if(!IsValidPtr(p_PlayerManager))
		return;
	
	ClientPlayer* p_LocalPlayer=p_PlayerManager->m_pLocalPlayer;
	if(!IsValidPtr(p_LocalPlayer))
		return;

	ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
	if(!IsValidPtr(p_LocalSoldier))
		return;

	if(p_LocalSoldier->m_pHealthComponent->m_Health<=0.1f)
		return;

	D3DXMATRIX tran;
	p_LocalSoldier->GetTransform(&tran);
	D3DXVECTOR3 forward=D3DXVECTOR3(tran._31,tran._32,tran._33);

	for(int i=0;i<70;i++)
	{
		ClientPlayer* pEnemyPlayer=p_PlayerManager->GetPlayerById(i);
		if(!IsValidPtr(pEnemyPlayer))
			continue;

		ClientSoldierEntity* pEnemySoldier=pEnemyPlayer->GetClientSoldier();
		if(!IsValidPtr(pEnemySoldier))
			continue;

		ClientCharacterEntity* pEnemyChar=(ClientCharacterEntity*)pEnemyPlayer->GetCharacterEntity();
		if(!IsValidPtr(pEnemyChar))
			continue;

		if(pEnemyPlayer->m_teamId==p_LocalPlayer->m_teamId)
			continue;
		
		if(pEnemySoldier->m_pHealthComponent->m_Health <=0.1f)
			continue;

		D3DXVECTOR3 EnemyVec,EnemyVecScreen;
		if(!GetBone(pEnemySoldier,&EnemyVec,headshot ? UpdatePoseResultData::BONE_HEAD:UpdatePoseResultData::BONE_SPINE))
			continue;

		if(!WorldToScreen(EnemyVec,EnemyVecScreen))
			continue;
		
		if(EnemyVecScreen.x>Width || EnemyVecScreen.y>Height)
			continue;

		if(EnemyVecScreen.x<2.00f && EnemyVecScreen.y<2.00f)
			continue;

		bool visible=!pEnemySoldier->m_occluded;

		if(names)
		{
			if(visible){
				DrawTextFormat(EnemyVecScreen.x,EnemyVecScreen.y,D3DCOLOR_RGBA(0,255,0,255),CText,"%s",pEnemyPlayer->szName);
			}else{
				DrawTextFormat(EnemyVecScreen.x,EnemyVecScreen.y,D3DCOLOR_RGBA(240,240,250,255),CText,"%s",pEnemyPlayer->szName);
			}
		}
		
		
		if(snaplines)
		{
			DrawSnapLine(D3DXVECTOR2(EnemyVecScreen.x,EnemyVecScreen.y),D3DCOLOR_RGBA(0,0,255,255));
		}
		
		if(visible)
		{
			D3DXVECTOR3 AimLoc=EnemyVec;
			DoAimCorrection(p_LocalPlayer,pEnemyPlayer,AimLoc);
			WorldToScreen(AimLoc);
		
			D3DDrawLineCircle(D3DXVECTOR2(AimLoc.x,AimLoc.y),5,D3DCOLOR_RGBA(255,0,0,255),30,p_Device);
			D3DDrawLineCircle(D3DXVECTOR2(AimLoc.x,AimLoc.y),2,D3DCOLOR_RGBA(255,0,0,255),30,p_Device);
		}
		

		if(esp)
		{
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_HEAD,UpdatePoseResultData::BONE_NECK,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_NECK,UpdatePoseResultData::BONE_SPINE2,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_SPINE2,UpdatePoseResultData::BONE_SPINE1,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_SPINE1,UpdatePoseResultData::BONE_SPINE,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_NECK,UpdatePoseResultData::BONE_LEFTSHOULDER,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_NECK,UpdatePoseResultData::BONE_RIGHTSHOULDER,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_LEFTSHOULDER,UpdatePoseResultData::BONE_LEFTELBOWROLL,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_RIGHTSHOULDER,UpdatePoseResultData::BONE_RIGHTELBOWROLL,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_LEFTELBOWROLL,UpdatePoseResultData::BONE_LEFTHAND,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_RIGHTELBOWROLL,UpdatePoseResultData::BONE_RIGHTHAND,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_SPINE,UpdatePoseResultData::BONE_RIGHTKNEEROLL,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_SPINE,UpdatePoseResultData::BONE_LEFTKNEEROLL,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_RIGHTKNEEROLL,UpdatePoseResultData::BONE_RIGHTFOOT,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
			ConnectBones(pEnemySoldier,UpdatePoseResultData::BONE_LEFTKNEEROLL,UpdatePoseResultData::BONE_LEFTFOOT,visible? D3DCOLOR_RGBA(255,0,0,255):D3DCOLOR_RGBA(0,255,0,255));
		}//End Esp Check
	}
	AddVectoredExceptionHandler(1, EH);
	CObjectList* pObjectList=CObjectList::GetInstance();
	if(!IsValidPtr(pObjectList))
		return;

	for(int i=0;i<pObjectList->Size();i++) //vehicles
	{
		__try{
			CObjectEntry Entity=pObjectList->m_Collection[i];

			D3DXVECTOR4 temppos=Entity.m_position;
			D3DXVECTOR3 pos=D3DXVECTOR3(temppos.x,temppos.y,temppos.z);
			GameObject* pEnt=Entity.m_pEntity;
			bool isVehicle=true;
			bool isExplosive=true;
			if(!IsValidPtr(pEnt))
				continue;

			//we do the ptr checks so we don't throw alot of excetiptions because they have a high overhead, evne though we can handle them all
			/////////////////////////Vehicle Ptr Checks/////////////////////
			if(!IsValidPtr(pEnt->pClientVehicle) || !IsValidPtr(pEnt->LocalPlayer) || !IsValidPtr(pEnt->Ptr3))
				isVehicle=false;

			if(!IsValidPtr(pEnt->m_name2))
				isVehicle=false;
			////////////////////////End Vehicle Ptr Checks///////////////////////

			if(isVehicle && strstr(pEnt->m_name2,"vehicles")) //we have to shortcircuit here so we don't error on string read
			{
				if(pEnt->PlayerInVehicle != p_LocalPlayer) //dont draw box for our own vehicle
				{
					ClientVehicleEntity* pVehicle=(ClientVehicleEntity*)pEnt->pClientVehicle;
					if(!IsValidPtr(pVehicle))
						continue;
					
					D3DXMATRIX temp;
					D3DXVECTOR3 origin;
					pVehicle->GetTransform(&temp);
					origin=D3DXVECTOR3(temp._41,temp._42,temp._43);
					DoAimCorrection(p_LocalPlayer,pEnt->PlayerInVehicle,origin);

					if(!WorldToScreen(origin))
						continue;

					D3DDrawLineCircle(D3DXVECTOR2(origin.x,origin.y),5,D3DCOLOR_RGBA(255,0,0,255),30,p_Device);
					D3DDrawLineCircle(D3DXVECTOR2(origin.x,origin.y),2,D3DCOLOR_RGBA(255,0,0,255),30,p_Device);

					AxisAlignedBox2 box;
					if(GetVehicleAABB(pVehicle,box))
					{
						DWORD Color;
						if(!IsValidPtr(pEnt->PlayerInVehicle))
						{
							Color=D3DCOLOR_RGBA(0,0,255,255);
						}else{
							ClientPlayer* pEnemyPlayer=pEnt->PlayerInVehicle;
							if(!IsValidPtr(pEnemyPlayer))
								continue;

							if(pEnemyPlayer->m_teamId== p_LocalPlayer->m_teamId) //is on our team
							{
								Color=D3DCOLOR_RGBA(0,255,0,255);
							}else{
								Color=D3DCOLOR_RGBA(255,0,0,255);
							}
						}
						DrawAABB(box,Color);
					}	
				}
			}else{
				///////////////////////Explosive Ptr Checks/////////////////////////
				if(!IsValidPtr(pEnt->Ptr1) || !IsValidPtr(pEnt->Ptr2) || !IsValidPtr(pEnt->m_name2) || IsValidPtr(pEnt->LocalPlayer))
					isExplosive=false;
				///////////////////////EndExplosive Ptr Checks//////////////////////

				if(isExplosive && strstr((char*)pEnt->Ptr1,"explosives")) //again short circuit
				{
					ExplosiveEntity* ExpEnt=(ExplosiveEntity*) pEnt->Ptr2;
					if(!IsValidPtr(ExpEnt))
						continue;

					D3DXMATRIX temp;
					ExpEnt->GetTransform(&temp);

					D3DXVECTOR3 vec=D3DXVECTOR3(temp._41,temp._42,temp._43);
					if(!WorldToScreen(vec))
						continue;

					DrawTextFormat(vec.x,vec.y,D3DCOLOR_RGBA(240,240,250,255),CText,"%s","Explosive");
				}
			}
		}__except(1){
			//nothing we just need to catch it
		}
	}
	return;
}
void __stdcall GetSpectators()
{
	ClientGameContext* pGameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(pGameContext))
		return;

	ClientPlayerManager* pPlayerManager=pGameContext->m_pPlayerManager;
	if(!IsValidPtr(pPlayerManager))
		return;

	ClientPlayer* pLocalPlayer=pPlayerManager->m_pLocalPlayer;

	eastl::vector<ClientPlayer*>* Spectators=pPlayerManager->getSpectators();
	if(!IsValidPtr(Spectators))
		return;

	
	for(int i=0;i<Spectators->size();i++)
	{
		ClientPlayer* pPlayer=Spectators->at(i);
		if(!IsValidPtr(pPlayer))
			continue;

		ClientPlayer::ClientPlayerView* pView=pPlayer->m_PlayerView;
		
		char temp[512];
		if(IsValidPtr(pLocalPlayer) && IsValidPtr(pView)&& pView->m_Owner==pLocalPlayer)
		{
			sprintf_s(temp,"Spectator at:%d Name:%s\n Is Spectating You",i,pPlayer->szName);
			DrawShadowString(temp,0,200+(20*i),255,0,0,pFontSmall);
		}else{
			sprintf_s(temp,"Spectator at:%d Name:%s\n",i,pPlayer->szName);
			DrawShadowString(temp,0,200+(20*i),240,240,250,pFontSmall);
		}
	
	}
}
void __stdcall Aimbot()
{
	ClientGameContext* p_GameContext=ClientGameContext::GetInstance();
	if(!IsValidPtr(p_GameContext))
		return;

	ClientPlayerManager* p_PlayerManager=p_GameContext->m_pPlayerManager;
	if(!IsValidPtr(p_PlayerManager))
		return;

	ClientPlayer* p_LocalPlayer=p_PlayerManager->m_pLocalPlayer;
	if(!IsValidPtr(p_LocalPlayer))
		return;

	ClientSoldierEntity* p_LocalSoldier=p_LocalPlayer->GetClientSoldier();
	if(!IsValidPtr(p_LocalSoldier))
		return;

	if(p_LocalPlayer->InVehicle())
	{
		if(!(GetAsyncKeyState(VK_LCONTROL) & 0x8000))
			return;
	}else{
		if(!(GetAsyncKeyState(VK_RBUTTON) & 0x8000))
			return;
	}
	
	ClientSoldierWeapon* pWep;
	ClientWeapon* pClientWep;
	ClientSoldierAimingSimulation* pSim;
	AimAssist* pAimAssist;
	D3DXMATRIX trans;
	D3DXVECTOR3 shootspace,shootspaceforward;

	if(!p_LocalPlayer->InVehicle())
	{

		if(p_LocalSoldier->m_pHealthComponent->m_Health<=0.1f)
			return;

		pWep=p_LocalSoldier->GetActiveWeapon();
		if(!IsValidPtr(pWep))
			return;

		pClientWep=pWep->m_pWeapon;
		if(!IsValidPtr(pClientWep))
			return;

		pSim=GetAimAssist(p_LocalSoldier);
		if(!IsValidPtr(pSim))
			return;

		pAimAssist=pSim->m_fpsAimer;
		if(!IsValidPtr(pAimAssist))
			return;

		trans=pClientWep->m_shootSpace;
		shootspace=D3DXVECTOR3(trans._41,trans._42,trans._43);//for ray tracing
		shootspaceforward=D3DXVECTOR3(trans._31,trans._32,trans._33);
	}

	if(p_LocalPlayer->InVehicle())
	{
		p_LocalPlayer->GetClientVehicleEntity()->GetTransform(&trans);
	
	}else{
		p_LocalSoldier->GetTransform(&trans);
	}

	D3DXVECTOR3 forward=D3DXVECTOR3(trans._31,trans._32,trans._33);//for fov calcs
	D3DXVECTOR3 left=D3DXVECTOR3(trans._11,trans._12,trans._13);
	D3DXVECTOR3 up=D3DXVECTOR3(trans._21,trans._22,trans._23);

	float closestdistance=9999.0f;
	ClientPlayer* ClosestClient=NULL;
	ClientSoldierEntity* ClosestSold=NULL;
	D3DXVECTOR3 EnemyAimVec;
	int index=0;

	for(int i=0;i<70;i++)
	{
		ClientPlayer* pEnemyPlayer=p_PlayerManager->GetPlayerById(i);
		if(!IsValidPtr(pEnemyPlayer))
			continue;

		ClientSoldierEntity* pEnemySoldier=pEnemyPlayer->GetClientSoldier();
		if(!IsValidPtr(pEnemySoldier))
			continue;

		ClientCharacterEntity* pEnemyChar=(ClientCharacterEntity*)pEnemyPlayer->GetCharacterEntity();
		if(!IsValidPtr(pEnemyChar))
			continue;

		if(pEnemyPlayer->m_teamId==p_LocalPlayer->m_teamId)
			continue;

		if(pEnemySoldier->m_pHealthComponent->m_Health <=0.1f)
			continue;

		D3DXVECTOR3 EnemyVec,EnemyScreen;
		if(!GetBone(pEnemySoldier,&EnemyVec,headshot ? UpdatePoseResultData::BONE_HEAD:UpdatePoseResultData::BONE_SPINE))
			continue;

		if(!WorldToScreen(EnemyVec,EnemyScreen))
			continue;

		if(EnemyScreen.x>Width || EnemyScreen.y>Height)
			continue;

		if(EnemyScreen.x<2.00f && EnemyScreen.y<2.00f)
			continue;

		bool visible;
		if(!p_LocalPlayer->InVehicle())
		{
			if(!IsVisible(&shootspace,&EnemyVec,visible))
				continue;

			if(!visible)
				continue;

			if(!IsInFOV(shootspaceforward,EnemyVec, shootspace,fov))
			continue;
		}
		
		float ScreenX=DxRenderer::GetInstance()->m_pScreen->m_Height/2;
		float ScreenY=DxRenderer::GetInstance()->m_pScreen->m_Width/2;

		float PosX = abs(EnemyScreen.x - ScreenX);
		float PosY = abs(EnemyScreen.y - ScreenY);

		float flScreenDistance=sqrt(PosX*PosX+PosY*PosY);
		
		if(flScreenDistance<closestdistance)
		{
			ClosestClient=pEnemyPlayer;
			ClosestSold=pEnemySoldier;
			closestdistance=flScreenDistance;
			EnemyAimVec=EnemyVec;
			index=i;
		}
	}
	//	endpoint.y+=Opposite;

	if(!IsValidPtr(ClosestClient))
		return;

	if(!IsValidPtr(ClosestSold))
		return;
	
	DoAimCorrection(p_LocalPlayer,ClosestClient,EnemyAimVec);
	D3DXMATRIX InvMatrix=GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse;
	D3DXVECTOR3 Origin=D3DXVECTOR3(InvMatrix._41,InvMatrix._42,InvMatrix._43);
	D3DXVECTOR3 vDirTemp=EnemyAimVec-Origin;
	D3DXVECTOR3 vDir;
	D3DXVec3Normalize(&vDir,&vDirTemp);
	

	if(p_LocalPlayer->InVehicle())
	{
		float fov=GameRenderer::GetInstance()->m_pRenderView->m_FovX/2.0f;
		
		float flYaw=asinf(D3DXVec3Dot(&left,&vDir)) / fov;
		float flPitch=asinf(D3DXVec3Dot(&up,&vDir))/fov;
		float flRoll=flYaw;
		//float flYaw = -atan2(vDir.x, vDir.z);  //x
		//float flPitch = atan2(vDir.y, VectorLength2D(&vDir)); //y
		//float flRoll=flYaw;

		g_pInputBuffers[ConceptYaw]=flPitch*12.0f;
		g_pInputBuffers[ConceptPitch]=flYaw*12.0f;
		g_pInputBuffers[ConceptRoll]=flRoll*12.0f;
	}else{
		float flYaw = -atan2(vDir.x, vDir.z);  //x
		float flPitch = atan2(vDir.y, VectorLength2D(&vDir)); //y

		float YawDelta=pSim->m_sway.x;
		float PitchDelta=pSim->m_sway.y;
		pAimAssist->m_yaw=(flYaw-YawDelta);
		pAimAssist->m_pitch=(flPitch-PitchDelta);

	}
}
signed int __stdcall hkPresent(IDXGISwapChain* pSwapchain, UINT SyncInterval, UINT Flags)
{
	if(GetAsyncKeyState(VK_P))
	{
		__try
		{
			DumpSigs();
		}__except(1){

		}
		PrintVehicle();
		PrintVals();
		PrintWeaponType();

		Sleep(500);
	}
	__try{
		noRecoil();
	}__except(1){

	}
	
	GameTimer->Present();
	return oPresent(pSwapchain,SyncInterval,Flags);
}
signed int __stdcall hkPreFrame(float DeltaTime)
{
	float returnval=oPreFrame(DeltaTime);
	if(GetAsyncKeyState(0xDC))//   \ character
	{
		if(!windowcreated)
		{
			std::cout<<"Making window \n";
			HANDLE hThread2 = CreateThread(NULL, NULL, Create, NULL, NULL, NULL);
			std::cout<<"Making window 2\n";
		}
		Sleep(500);
	}

	if(aimbot) //Right Mouse
	{
		__try{
			Aimbot();
		}__except(1){

		}
	}

	for(int i = 0; i < 123; i++)
	{
		g_pBorderInputNode->m_inputCache->flInputBuffer[i] += g_pInputBuffers[i];
		g_pInputBuffers[i] = 0.0f;
	}
	return returnval;
}
DWORD_PTR hkUpdate( DWORD_PTR a1, DWORD_PTR a2, DWORD_PTR a3  )//ICY
{
	if ( a1 )
		*( bool* )( a1 + 0xEC ) = true;

	if ( a2 )
		*( bool* )( a2 + 0x8A ) = true;

	return oUpdate( a1, a2, a3 );    
} 
BOOL WINAPI DllMain (HINSTANCE hModule, DWORD dwAttached, LPVOID lpvReserved)
{

	if (dwAttached == DLL_PROCESS_ATTACH)
	{	
		CreateConsole();
		DisableThreadLibraryCalls(hModule);
		Handle=hModule;
		
		inst=hModule;
	
		HANDLE hThread = CreateThread(NULL, NULL, InputThread, NULL, NULL, NULL);
		CloseHandle(hThread);
		
		OverlayTimer=new dhFPSTimer("Overlay");
		GameTimer=new dhFPSTimer("Game");
		//oPreFrame=(tPreFrameUpdate)HookVTableFunction((PDWORD64*)BorderInputNode::GetInstance()->vtable_class_40,(PBYTE)&hkPreFrame,INPUTCACHEHOOK);
		//oPresent=(tPresent)HookVTableFunction((PDWORD64*)DxRenderer::GetInstance()->m_pScreen->m_pSwapChain,(PBYTE)&hkPresent,8);
		//oUpdate=(tUpdate)HookVTableFunction((PDWORD64*)pAntVtable,(PBYTE)&hkUpdate,11);

		PreFrameHook=new CVMTHookManager64((DWORD64**)BorderInputNode::GetInstance()->vtable_class_40);
		oPreFrame=(tPreFrameUpdate)PreFrameHook->dwGetMethodAddress(INPUTCACHEHOOK);
		PreFrameHook->dwHookMethod((DWORD64)hkPreFrame,INPUTCACHEHOOK);

		PresentHook=new CVMTHookManager64((DWORD64**)DxRenderer::GetInstance()->m_pScreen->m_pSwapChain);
		oPresent=(tPresent)PresentHook->dwGetMethodAddress(8);
		PresentHook->dwHookMethod((DWORD64)hkPresent,8);

	    oUpdate=(tUpdate)DetourVTable(pAntVtable,11,(PBYTE)&hkUpdate);
	/*	UpdateHook=new CVMTHookManager64((DWORD64**)pAntVtable);
		oUpdate=(tUpdate)UpdateHook->dwGetMethodAddress(11);
		UpdateHook->dwHookMethod((DWORD64)hkUpdate,11);*/
		
		//ScanSigs((HMODULE)Handle);
		//DumpSigs();
	}
	return 1;
} 
