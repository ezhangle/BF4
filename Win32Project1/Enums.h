#define VK_0	0x30
#define VK_1	0x31
#define VK_2	0x32
#define VK_3	0x33
#define VK_4	0x34
#define VK_5	0x35
#define VK_6	0x36
#define VK_7	0x37
#define VK_8	0x38
#define VK_9	0x39
///////
#define VK_A	0x041
#define VK_B	0x042
#define VK_C	0x043
#define VK_D	0x044
#define VK_E	0x045
#define VK_F	0x046
#define VK_G	0x047
#define VK_H	0x048
#define VK_I	0x049
#define VK_J	0x04A
#define VK_K	0x04B
#define VK_L	0x04C
#define VK_M	0x04D
#define VK_N	0x04E
#define VK_O	0x04F
#define VK_P	0x050
#define VK_Q	0x051
#define VK_R    0x052
#define VK_S	0x053
#define VK_T	0x054
#define VK_U	0x055
#define VK_V	0x056
#define VK_W	0x057
#define VK_X	0x058
#define VK_Y	0x059
#define VK_Z	0x05A

enum InputConceptIdentifiers
{
	ConceptMoveFB=0,
	ConceptMoveLR=1,
	ConceptMoveForward=2,
	ConceptMoveBackward=3,
	ConceptMoveLeft=4,
	ConceptMoveRight=5,
	ConceptYaw=6,
	ConceptPitch=7,
	ConceptRoll=8,
	ConceptRecenterCamera=9,
	ConceptFire=10,
	ConceptAltFire=11,
	ConceptFireCountermeasure=12,
	ConceptReload=13,
	ConceptZoom=14,
	ConceptToggleCamera=15,
	ConceptSprint=16,
	ConceptCrawl=17,
	ConceptToggleWeaponLight=18,
	ConceptSelectPartyMember0=19,
	ConceptSelectPartyMember1=20,
	ConceptSelectPartyMember2=21,
	ConceptSelectPartyMember3=22,
	ConceptLockTarget=23,
	ConceptCrosshairMoveX=24,
	ConceptCrosshairMoveY=25,
	ConceptTacticalMenu=26,
	ConceptConversationSelect=27,
	ConceptConversationSkip=28,
	ConceptConversationChangeSelection=29,
	ConceptJump=30,
	ConceptCrouch=31,
	ConceptCrouchOnHold=32,
	ConceptProne=33,
	ConceptInteract=34,
	ConceptPickUp=35,
	ConceptDrop=36,
	ConceptBreathControl=37,
	ConceptParachute=38,
	ConceptSwitchInventoryItem=39,
	ConceptSelectInventoryItem1=40,
	ConceptSelectInventoryItem2=41,
	ConceptSelectInventoryItem3=42,
	ConceptSelectInventoryItem4=43,
	ConceptSelectInventoryItem5=44,
	ConceptSelectInventoryItem6=45,
	ConceptSelectInventoryItem7=46,
	ConceptSelectInventoryItem8=47,
	ConceptSelectInventoryItem9=48,
	ConceptSwitchToPrimaryWeapon=49,
	ConceptSwitchToGrenadeLauncher=50,
	ConceptSwitchToStaticGadget=51,
	ConceptSwitchToDynamicGadget1=52,
	ConceptSwitchToDynamicGadget2=53,
	ConceptMeleeAttack=54,
	ConceptThrowGrenade=55,
	ConceptCycleFireMode=56,
	ConceptChangeVehicle=57,
	ConceptBrake=58,
	ConceptHandBrake=59,
	ConceptClutch=60,
	ConceptGearUp=61,
	ConceptGearDown=62,
	ConceptGearSwitch=63,
	ConceptNextPosition=64,
	ConceptSelectPosition1=65,
	ConceptSelectPosition2=66,
	ConceptSelectPosition3=67,
	ConceptSelectPosition4=68,
	ConceptSelectPosition5=69,
	ConceptSelectPosition6=70,
	ConceptSelectPosition7=71,
	ConceptSelectPosition8=72,
	ConceptCameraPitch=73,
	ConceptCameraYaw=74,
	ConceptMapZoom=75,
	ConceptMapInnerZoom=76,
	ConceptMapSize=77,
	ConceptMapThreeDimensional=78,
	ConceptScoreboard=79,
	ConceptScoreboardAndMenuCombo=80,
	ConceptMenu=81,
	ConceptSpawnMenu=82,
	ConceptCancel=83,
	ConceptCommMenu1=84,
	ConceptCommMenu2=85,
	ConceptCommMenu3=86,
	ConceptAccept=87,
	ConceptDecline=88,
	ConceptSelect=89,
	ConceptBack=90,
	ConceptActivate=91,
	ConceptDeactivate=92,
	ConceptEdit=93,
	ConceptView=94,
	ConceptParentNavigateLeft=95,
	ConceptParentNavigateRight=96,
	ConceptMenuZoomIn=97,
	ConceptMenuZoomOut=98,
	ConceptPanX=99,
	ConceptPanY=100,
	ConceptBattledashToggle=101,
	ConceptVoiceFunction1=102,
	ConceptSquadVoice=103,
	ConceptSayAllChat=104,
	ConceptTeamChat=105,
	ConceptSquadChat=106,
	ConceptSquadLeaderChat=107,
	ConceptToggleChat=108,
	ConceptQuicktimeInteractDrag=109,
	ConceptQuicktimeFire=110,
	ConceptQuicktimeBlock=111,
	ConceptQuicktimeFastMelee=112,
	ConceptQuicktimeJumpClimb=113,
	ConceptQuicktimeCrouchDuck=114,
	ConceptFreeCameraMoveUp=115,
	ConceptFreeCameraMoveDown=116,
	ConceptFreeCameraMoveLR=117,
	ConceptFreeCameraMoveFB=118,
	ConceptFreeCameraMoveUD=119,
	ConceptFreeCameraRotateX=120,
	ConceptFreeCameraRotateY=121,
	ConceptFreeCameraRotateZ=122,
	ConceptFreeCameraIncreaseSpeed=123,
	ConceptFreeCameraDecreaseSpeed=124,
	ConceptFreeCameraFOVModifier=125,
	ConceptFreeCameraChangeFOV=126,
	ConceptFreeCameraSwitchSpeed=127,
	ConceptFreeCameraTurboSpeed=128,
	ConceptFreeCameraActivator1=129,
	ConceptFreeCameraActivator2=130,
	ConceptFreeCameraActivator3=131,
	ConceptFreeCameraMayaInputActivator=132,
	ConceptTargetedCameraDistance=133,
	ConceptTargetedCameraRotateX=134,
	ConceptTargetedCameraRotateY=135,
	ConceptTargetedCameraChangeSpeed=136,
	ConceptLThumb=137,
	ConceptRThumb=138,
	ConceptLeftStickX=139,
	ConceptLeftStickY=140,
	ConceptRightStickX=141,
	ConceptRightStickY=142,
	ConceptButtonDPadLeft=143,
	ConceptButtonDPadRight=144,
	ConceptButtonDPadUp=145,
	ConceptButtonDPadDown=146,
	ConceptButtonA=147,
	ConceptButtonB=148,
	ConceptButtonX=149,
	ConceptButtonY=150,
	ConceptButtonSelect=151,
	ConceptButtonStart=152,
	ConceptButtonL1=153,
	ConceptButtonL2=154,
	ConceptButtonR1=155,
	ConceptButtonR2=156,
	ConceptButtonLeftThumb=157,
	ConceptButtonRightThumb=158,
	ConceptToggleMinimapType=159,
	ConceptDeployZoom=160,
	ConceptMenuDigitalUp=161,
	ConceptMenuDigitalDown=162,
	ConceptMenuDigitalLeft=163,
	ConceptMenuDigitalRight=164,
	ConceptRightStickUp=165,
	ConceptRightStickDown=166,
	ConceptRightStickLeft=167,
	ConceptRightStickRight=168,
	ConceptMultipleSelect=169,
	ConceptMoveCameraUp=170,
	ConceptMoveCameraDown=171,
	ConceptMoveCameraLeft=172,
	ConceptMoveCameraRight=173,
	ConceptSpectatorViewPrev=174,
	ConceptSpectatorViewNext=175,
	ConceptSpectatorTargetPrev=176,
	ConceptSpectatorTargetNext=177,
	ConceptSpectatorViewTableTop=178,
	ConceptSpectatorViewFirstPerson=179,
	ConceptSpectatorViewThirdPerson=180,
	ConceptSpectatorViewFreeCam=181,
	ConceptSpectatorViewPlayer1=182,
	ConceptSpectatorViewPlayer2=183,
	//ConceptSpectatorViewPlayer3=184
	//ConceptSpectatorViewPlayer4=185
	//ConceptSpectatorViewPlayer5=186
	//ConceptSpectatorViewPlayer6=187
	//ConceptSpectatorViewPlayer7=188
	//ConceptSpectatorViewPlayer8=189
	//ConceptSpectatorViewPlayer9=190
	//ConceptSpectatorViewPlayer10=191
	//ConceptSpectatorViewPlayer11=192
	//ConceptSpectatorViewPlayer12=193
	//ConceptSpectatorViewPlayer13=194
	//ConceptSpectatorViewPlayer14=195
	//ConceptSpectatorViewPlayer15=196
	//ConceptSpectatorViewPlayer16=197
	//ConceptSpectatorViewOptions=198
	//ConceptSpectatorHudVisibility=199
	//ConceptAnalogZoom=200
	//ConceptSpectatorTargetPrevInSquad=201
	//ConceptSpectatorTargetNextInSquad=202
	//ConceptSpectatorTargetPrevOnTeam=203
	//ConceptSpectatorTargetNextOnTeam=204
	//ConceptSpectatorFreeCameraIncreaseSpeed=205
	//ConceptSpectatorFreeCameraDecreaseSpeed=206
	//ConceptSpectatorFreeCameraSwitchSpeed=207
	//ConceptSpectatorFreeCameraMoveLR=208
	//ConceptSpectatorFreeCameraMoveUD=209
	//ConceptSpectatorFreeCameraMoveFB=210
	//ConceptSpectatorFreeCameraRotateX=211
	//ConceptSpectatorFreeCameraRotateY=212
	//ConceptSpectatorFreeCameraRotateZ=213
	//ConceptSpectatorFreeCameraTurboSpeed=214
	//ConceptSpectatorFreeCameraFOVModifier=215
	//ConceptSpectatorFreeCameraChangeFOV=216
	//ConceptSpectatorSquadLeft=217
	//ConceptSpectatorSquadRight=218
	//ConceptSpectatorSquadUp=219
	//ConceptSpectatorSquadDown=220
	//ConceptSpectatorSquadActivate=221
	//ConceptUndefined=222
	//ConceptSize=223
};
struct AxisAlignedBox2
{
	D3DXVECTOR3 min;             
	D3DXVECTOR3 max;
	D3DXVECTOR3 crnr2;
	D3DXVECTOR3 crnr3;
	D3DXVECTOR3 crnr4;
	D3DXVECTOR3 crnr5;
	D3DXVECTOR3 crnr6;
	D3DXVECTOR3 crnr7;

	/*
       .5------8
     .' |    .'|
    6---+--7'  |
    |   |  |   |
    |  ,4--+---3
    |.'    | .'
    1------2'

    1 = min
    8 = max
*/
};
enum colour 
{ 
	DARKBLUE = 1, 
	DARKGREEN,
	DARKTEAL, 
	DARKRED, 
	DARKPINK,
	DARKYELLOW, 
	GRAY,
	DARKGRAY, 
	BLUE,
	GREEN, 
	TEAL,
	RED, 
	PINK, 
	YELLOW,
	WHITE
};

enum QualityLevel
{
	QualityLevel_Low = 0,
	QualityLevel_Medium = 1,
	QualityLevel_High = 2,
	QualityLevel_Ultra = 3,
	QualityLevel_All = 4,
	QualityLevel_Invalid = 5
};

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

enum WeaponClassEnum
{
	wc12gauge = 0,
	wc338Magnum = 1,
	wc357Magnum = 2,
	wc44Magnum = 3,
	wc45cal = 4,
	wc46x30mm = 5,
	wc50cal = 6,
	wc545x45mmWP = 7,
	wc556x45mmNATO = 8,
	wc57x28mm = 9,
	wc58x42mm = 10,
	wc762x39mmWP = 11,
	wc762x51mmNATO = 12,
	wc762x54mmR = 13,
	wc9x19mm = 14,
	wc9x39mm = 15,
	wcAssault = 16,
	wcShotgun = 17,
	wcSmg = 18,
	wcLmg = 19,
	wcSniper = 20,
	wcUgl = 21,
	wcHgr = 22,
	wcAt = 23,
	wcATMine = 24,
	wcC4 = 25,
	wcAutoInjector = 26,
	wcKnife = 27,
	wcLaserDesignator = 28,
	wcLaserPainter = 29,
	wcMedKit = 30,
	wcMortarStrike = 31,
	wcPowerTool = 32,
	wcTracerDart = 33,
	wcRadioBeacon = 34,
	wcEodBot = 35,
	wcReconMav = 36,
	wcUGS = 37,
	wcUnarmed = 38,
	wcCount = 39,
	wcNone = 40
};
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
enum FireLogicType
{
	fltSingleFire = 0,
	fltSingleFireWithBoltAction = 1,
	fltAutomaticFire = 2,
	fltBurstFire = 3,
	fltHoldAndRelease = 4,
	fltDetonatedFiring = 5,
	fltCount = 6
};
enum UISystemType
{
	UISystem_None = 0,
	UISystem_Standard = 1
};
enum LanguageFormat
{
	LanguageFormat_English = 0,
	LanguageFormat_French = 1,
	LanguageFormat_German = 2,
	LanguageFormat_Spanish = 3,
	LanguageFormat_Italian = 4,
	LanguageFormat_Japanese = 5,
	LanguageFormat_Russian = 6,
	LanguageFormat_Polish = 7,
	LanguageFormat_Dutch = 8,
	LanguageFormat_Portuguese = 9,
	LanguageFormat_TraditionalChinese = 10,
	LanguageFormat_Korean = 11,
	LanguageFormat_Czech = 12,
	LanguageFormat_BrazilianPortuguese = 13,
	LanguageFormat_Count = 14,
	LanguageFormat_Undefined = 15
};
enum DamageIndicationType
{
	DamageIndicationType_GiverPlayer = 0,
	DamageIndicationType_ExplosionCenter = 1
};
enum TeamId
{
	TeamNeutral = 0,
	Team1 = 1,
	Team2 = 2,
	Team3 = 3,
	Team4 = 4,
	Team5 = 5,
	Team6 = 6,
	Team7 = 7,
	Team8 = 8,
	Team9 = 9,
	Team10 = 10,
	Team11 = 11,
	Team12 = 12,
	Team13 = 13,
	Team14 = 14,
	Team15 = 15,
	Team16 = 16,
	TeamIdCount = 17
};
enum WarnTarget
{
	wtWarnSoldierAndVehicle = 0,
	wtWarnSoldier = 1,
	wtWarnVehicle = 2,
	wtWarnNone = 3
};