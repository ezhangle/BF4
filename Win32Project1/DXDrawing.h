

int Width = 800;
int Height = 600;


const MARGINS Margin = { 0, 0, Width, Height };

char lWindowName[256] = "BF4 Stevemk14ebr";
HWND hWnd;

char tWindowName[256] = "Battlefield 4"; /* tWindowName ? Target Window Name  Battlefield 4™*/
HWND tWnd;
RECT tSize;
RECT tClient;
UINT nMsgID;
MSG Message;

IDirect3D9Ex* p_Object = 0;
IDirect3DDevice9Ex* p_Device = 0;
D3DPRESENT_PARAMETERS p_Params;

ID3DXLine* p_Line;
ID3DXLine* p_LineNoAA;
ID3DXFont* pFontSmall = 0;
IFW1FontWrapper* m_pFontWrapper;
IFW1Factory* m_pFW1Factory;
D3DXVECTOR2 Pos;
std::vector<D3DXVECTOR2> BonePosVec;

static std::string asciiEncode( const std::wstring & w ); 
static std::wstring asciiDecode( const std::string & s ); 

#define CText (DT_CENTER|DT_NOCLIP)
#define LText (DT_LEFT|DT_NOCLIP) 
#define RText (DT_RIGHT|DT_NOCLIP)
//forward declaring
BOOL WINAPI D3DDrawLine( FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, DWORD COLOR, LPDIRECT3DDEVICE9 pDev );
BOOL WINAPI D3DDrawFillRect( FLOAT X, FLOAT Y, DWORD COLOR, UINT Width, UINT Height, LPDIRECT3DDEVICE9 pDev);
BOOL WINAPI D3DDrawCircle( FLOAT X, FLOAT Y, DWORD COLOR,LPDIRECT3DDEVICE9 pDev, FLOAT Radius );
typedef struct _D3DTLVERTEX{
	FLOAT fX;
	FLOAT fY;
	FLOAT fZ;
	FLOAT fRHW;
	D3DCOLOR Color;
	FLOAT fU;
	FLOAT fV;
}D3DTLVERTEX,*PD3DTLVERTEX;
void FillRGBNOAA(float x, float y, float w, float h, int r, int g, int b, int a) 
{ 
	D3DXVECTOR2 vLine[2]; 

	p_LineNoAA->SetWidth( w ); 

	vLine[0].x = x + w/2; 
	vLine[0].y = y; 
	vLine[1].x = x + w/2; 
	vLine[1].y = y + h; 

	p_LineNoAA->Begin( ); 
	p_LineNoAA->Draw( vLine, 2, D3DCOLOR_RGBA( r, g, b, a ) ); 
	p_LineNoAA->End( ); 
} 
void FillRGB(float x, float y, float w, float h, int r, int g, int b, int a) 
{ 
	D3DXVECTOR2 vLine[2]; 

	p_Line->SetWidth( w ); 

	vLine[0].x = x + w/2; 
	vLine[0].y = y; 
	vLine[1].x = x + w/2; 
	vLine[1].y = y + h; 

	p_Line->Begin( ); 
	p_Line->Draw( vLine, 2, D3DCOLOR_RGBA( r, g, b, a ) ); 
	p_Line->End( ); 
} 
void DrawHealthBar(float x, float y, float w, float h, int r, int g) 
{     
	FillRGB(x,y,w,h,r,g,0,255);      
} 
int DrawString(char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT ShadowPos;
	ShadowPos.left = x + 1;
	ShadowPos.top = y + 1;
	RECT FontPos;
	FontPos.left = x;
	FontPos.top = y;
	ifont->DrawTextA(0, String, strlen(String), &ShadowPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r / 3, g / 3, b / 3));
	ifont->DrawTextA(0, String, strlen(String), &FontPos, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
}
int DrawShadowString(const char* String, int x, int y, int r, int g, int b, ID3DXFont* ifont)
{
	RECT Font;
	Font.left = x;
	Font.top = y;
	RECT Fonts;
	Fonts.left = x+1;
	Fonts.top = y;
	RECT Fonts1;
	Fonts1.left = x-1;
	Fonts1.top = y;
	RECT Fonts2;
	Fonts2.left = x;
	Fonts2.top = y+1;
	RECT Fonts3;
	Fonts3.left = x;
	Fonts3.top = y-1;
	ifont->DrawTextA(0, String, strlen(String), &Fonts3, DT_NOCLIP , D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts2, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts1, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Fonts, DT_NOCLIP, D3DCOLOR_ARGB(255, 1, 1, 1));
	ifont->DrawTextA(0, String, strlen(String), &Font, DT_NOCLIP, D3DCOLOR_ARGB(255, r, g, b));
	return 0;
}

void GradientFunc(int x, int y, int w, int h,int r, int g, int b, int a)
{
	int iColorr,iColorg,iColorb;
	for(int i = 1; i < h; i++)
	{
		iColorr = (int)((float)i/h*r);
		iColorg = (int)((float)i/h*g);
		iColorb = (int)((float)i/h*b);
		FillRGB(x ,y+ i,w,1,r-iColorr,g-iColorg,b-iColorb,a);
	}
}
void DrawLine(float x, float y, float xx, float yy, int r, int g, int b, int a)
{
	D3DXVECTOR2 dLine[2];

	p_Line->SetWidth( 1 );

	dLine[0].x = x;
	dLine[0].y = y;

	dLine[1].x = xx;
	dLine[1].y = yy;

	p_Line->Draw( dLine, 2, D3DCOLOR_ARGB(a, r , g, b));

} 

void DrawBox(float x, float y, float width, float height, int r, int g, int b, int a) 
{ 
	D3DXVECTOR2 points[5];  
	points[0] = D3DXVECTOR2(x,		y);  
	points[1] = D3DXVECTOR2(x+width,	y);  
	points[2] = D3DXVECTOR2(x+width,	y+height);  
	points[3] = D3DXVECTOR2(x,		y+height);  
	points[4] = D3DXVECTOR2(x,		y);  
	p_Line->SetWidth(1);
	p_Line->Draw(points, 5, D3DCOLOR_RGBA(r,g,b,a));
} 
void DrawGUIBox(float x, float y, float w, float h, int r, int g, int b, int a, int rr, int gg, int bb, int aa) 
{ 
	DrawBox(x,y,w,h,r ,g ,b ,a);    
	FillRGB(x,y,w,h,rr,gg,bb,a);   
} 

void DrawHealthBarBack(float x, float y, float w, float h) 
{     
	FillRGB(x,y,w,h,0,0,0,255);      
} 
void DrawCenterLine(float x, float y, int width, int r, int g, int b)
{
	D3DXVECTOR2 dPoints[2];
	dPoints[0] = D3DXVECTOR2(x, y);
	dPoints[1] = D3DXVECTOR2(Width / 2, Height);
	p_Line->SetWidth(width);
	p_Line->Draw(dPoints, 2, D3DCOLOR_RGBA(r, g, b, 255));
} 
void DrawSnapLine(D3DXVECTOR2 target,DWORD dColor)
{
	D3DXVECTOR2 linestart;
	float height=DxRenderer::GetInstance()->m_pScreen->m_Height;
	linestart.x = DxRenderer::GetInstance()->m_pScreen->m_Width / 2;
	linestart.y = height-(height*.05f);

	D3DDrawLine(linestart.x,linestart.y,target.x,target.y,dColor,p_Device);
}

void ConnectBones(ClientSoldierEntity* pEnemy,UpdatePoseResultData::BONES bone1,UpdatePoseResultData::BONES bone2,DWORD dColor)
{
	if(!IsValidPtr(pEnemy))
		return;

	D3DXVECTOR3 bonevec1,bonevec2,bonescreen1,bonescreen2;
	//try everything twice
	if(!GetBone(pEnemy,&bonevec1,bone1))
	{
		if(!GetBone(pEnemy,&bonevec1,bone1))
			return;
	}
	if(!GetBone(pEnemy,&bonevec2,bone2))
	{
		if(!GetBone(pEnemy,&bonevec2,bone2))
			return;
	}
	if(!WorldToScreen(bonevec1,bonescreen1))
	{
		if(!WorldToScreen(bonevec1,bonescreen1))
			return;	
	}
	if(!WorldToScreen(bonevec2,bonescreen2))
	{
		if(!WorldToScreen(bonevec2,bonescreen2))
			return;
	}
	D3DDrawLine(bonescreen1.x,bonescreen1.y,bonescreen2.x,bonescreen2.y,dColor,p_Device);
}
void DrawAABB(AxisAlignedBox2 AABB,DWORD Color)
{
	/*DrawShadowString("min",AABB.min.x,AABB.min.y,255,0,0,pFontSmall);
	DrawShadowString("max",AABB.max.x,AABB.max.y,255,0,0,pFontSmall);
	DrawShadowString("2",AABB.crnr2.x,AABB.crnr2.y,255,0,0,pFontSmall);
	DrawShadowString("3",AABB.crnr3.x,AABB.crnr3.y,255,0,0,pFontSmall);
	DrawShadowString("4",AABB.crnr4.x,AABB.crnr4.y,255,0,0,pFontSmall);
	DrawShadowString("5",AABB.crnr5.x,AABB.crnr5.y,255,0,0,pFontSmall);
	DrawShadowString("6",AABB.crnr6.x,AABB.crnr6.y,255,0,0,pFontSmall);
	DrawShadowString("7",AABB.crnr7.x,AABB.crnr7.y,255,0,0,pFontSmall);*/

	//min to 2,4,6
	D3DDrawLine(AABB.min.x,AABB.min.y,AABB.crnr2.x,AABB.crnr2.y,Color,p_Device);
	D3DDrawLine(AABB.min.x,AABB.min.y,AABB.crnr4.x,AABB.crnr4.y,Color,p_Device);
	D3DDrawLine(AABB.min.x,AABB.min.y,AABB.crnr6.x,AABB.crnr6.y,Color,p_Device);

	//max to 5,7,3
	D3DDrawLine(AABB.max.x,AABB.max.y,AABB.crnr5.x,AABB.crnr5.y,Color,p_Device);
	D3DDrawLine(AABB.max.x,AABB.max.y,AABB.crnr7.x,AABB.crnr7.y,Color,p_Device);
	D3DDrawLine(AABB.max.x,AABB.max.y,AABB.crnr3.x,AABB.crnr3.y,Color,p_Device);
	
	//2 to 7,3
	D3DDrawLine(AABB.crnr2.x,AABB.crnr2.y,AABB.crnr3.x,AABB.crnr3.y,Color,p_Device);
	D3DDrawLine(AABB.crnr2.x,AABB.crnr2.y,AABB.crnr7.x,AABB.crnr7.y,Color,p_Device);

	//4 to 5,3
	D3DDrawLine(AABB.crnr4.x,AABB.crnr4.y,AABB.crnr5.x,AABB.crnr5.y,Color,p_Device);
	D3DDrawLine(AABB.crnr4.x,AABB.crnr4.y,AABB.crnr3.x,AABB.crnr3.y,Color,p_Device);

	//6 to 5,7
	D3DDrawLine(AABB.crnr6.x,AABB.crnr6.y,AABB.crnr5.x,AABB.crnr5.y,Color,p_Device);
	D3DDrawLine(AABB.crnr6.x,AABB.crnr6.y,AABB.crnr7.x,AABB.crnr7.y,Color,p_Device);
}
int DirectXInit(HWND hWnd)
{
	
	Direct3DCreate9Ex(D3D_SDK_VERSION, &p_Object);
	
	ZeroMemory(&p_Params, sizeof(p_Params));    
	p_Params.Windowed = TRUE;   
	p_Params.SwapEffect = D3DSWAPEFFECT_DISCARD;    
	p_Params.hDeviceWindow = hWnd;    
	p_Params.MultiSampleQuality   = D3DMULTISAMPLE_NONE;
	p_Params.BackBufferFormat = D3DFMT_A8R8G8B8 ;     
	p_Params.BackBufferWidth = Width;    
	p_Params.BackBufferHeight = Height;    
	p_Params.EnableAutoDepthStencil = TRUE;
	p_Params.AutoDepthStencilFormat = D3DFMT_D16;

	p_Object->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &p_Params, 0, &p_Device);


	if(!p_Line)
		D3DXCreateLine(p_Device, &p_Line);
	p_Line->SetAntialias(1); 
	if(!p_LineNoAA)
		D3DXCreateLine(p_Device, &p_LineNoAA);
	p_LineNoAA->SetAntialias(0);

	D3DXCreateFontA(p_Device, 18, 0, 0, 0, false, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Calibri", &pFontSmall);

	return 0;
}

VOID WINAPI BuildVertex( FLOAT X, FLOAT Y, DWORD COLOR, PD3DTLVERTEX PD3DTLV, UINT Index )
{
	PD3DTLV[Index].fX			= X;
	PD3DTLV[Index].fY				= Y;
	PD3DTLV[Index].fZ			= 0.0f;
	PD3DTLV[Index].fU			= 0.0f;
	PD3DTLV[Index].fV			= 0.0f;
	PD3DTLV[Index].fRHW		= 1.0f;
	PD3DTLV[Index].Color		= COLOR;
}

BOOL WINAPI D3DDrawLine( FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, DWORD COLOR, LPDIRECT3DDEVICE9 pDev )
{
	D3DTLVERTEX D3DTLV[20];

	BuildVertex( X1, Y1, COLOR, PD3DTLVERTEX(&D3DTLV), 0 );
	BuildVertex( X2, Y2, COLOR, PD3DTLVERTEX(&D3DTLV), 1 );

	pDev->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	pDev->DrawPrimitiveUP( D3DPT_LINELIST, 2, &D3DTLV, sizeof(D3DTLVERTEX) );

	return TRUE;
}

BOOL WINAPI D3DDrawFillRect( FLOAT X, FLOAT Y, DWORD COLOR, UINT Width, UINT Height, LPDIRECT3DDEVICE9 pDev)
{
	D3DTLVERTEX D3DTLV[20];

	BuildVertex( X-Width, Y+Height, COLOR, PD3DTLVERTEX(&D3DTLV), 0 );
	BuildVertex( X-Width, Y-Height, COLOR, PD3DTLVERTEX(&D3DTLV), 1 );
	BuildVertex( X+Width, Y-Height, COLOR, PD3DTLVERTEX(&D3DTLV), 2 );

	BuildVertex( X+Width, Y-Height, COLOR, PD3DTLVERTEX(&D3DTLV), 3 );
	BuildVertex( X+Width, Y+Height, COLOR, PD3DTLVERTEX(&D3DTLV), 4 );
	BuildVertex( X-Width, Y+Height, COLOR, PD3DTLVERTEX(&D3DTLV), 5 );

	pDev->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );

	pDev->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 6, &D3DTLV, sizeof(D3DTLVERTEX) );

	return TRUE;
}

BOOL WINAPI D3DDrawFillCircle( FLOAT X, FLOAT Y, DWORD COLOR,LPDIRECT3DDEVICE9 pDev, FLOAT Radius)
{
	D3DTLVERTEX D3DTLV[400];

	FLOAT X1	= X;
	FLOAT Y1	= Y;

	for( int i=0;i<=363;i+=3 )
	{
		FLOAT angle		= ( i / 57.3f );   

		FLOAT X2		= X + ( Radius * sin( angle ) );
		FLOAT Y2		= Y + ( Radius * cos( angle ) );        

		BuildVertex( X, Y, COLOR, PD3DTLVERTEX(&D3DTLV), i );
		BuildVertex( X1, Y1, COLOR, PD3DTLVERTEX(&D3DTLV), i + 1 );
		BuildVertex( X2, Y2, COLOR, PD3DTLVERTEX(&D3DTLV), i + 2 );

		Y1 = Y2;
		X1 = X2;
	}

	pDev->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	pDev->SetFVF( D3DFVF_XYZRHW | D3DFVF_DIFFUSE );
	pDev->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 363, &D3DTLV, sizeof(D3DTLVERTEX) );

	return TRUE;
}

BOOL WINAPI D3DDrawLineCircle( const D3DXVECTOR2 &Center,float Radius,DWORD color,unsigned short Sides /*= 30*/,LPDIRECT3DDEVICE9 pDev )
{
	float Angle = (360.0f/Sides)*(3.1415926f/180); //to radians

	float Cos = cos(Angle);
	float Sin = sin(Angle);

	D3DXVECTOR2 vec(Radius,0);

	for(unsigned short i = 0;i < Sides;++i)
	{
		D3DXVECTOR2 rot( Cos*vec.x - Sin*vec.y , Sin*vec.x + Cos*vec.y );
		rot += Center;
		vec += Center;
	//	DrawLine(vec,rot,color);
		D3DDrawLine(vec.x,vec.y,rot.x,rot.y,color,pDev);
		vec = rot - Center;
	}
	return TRUE;
}

D3DXVECTOR3 GetCirclePoint( D3DXVECTOR3 center, float radius, int index, int vertexCount )
{
	D3DXVECTOR3 point = center;
	point.x += sin( index * ( 2.0f * D3DX_PI ) / vertexCount ) * radius;
	point.z += cos( index * ( 2.0f * D3DX_PI ) / vertexCount ) * radius;

	return point;
}

void DrawTextFormat(int x, int y, DWORD Color, DWORD Style, const char *Format, ...)
{
	RECT rect,temprect;

	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	int height=	pFontSmall->DrawTextA(NULL,Buffer,-1,NULL, DT_CALCRECT,0xFFFFFFFF);
	SetRect(&rect, x, y-(height/2), x, y);
	pFontSmall ->DrawTextA(NULL, Buffer, -1, &rect, Style, Color);
	return;
}

