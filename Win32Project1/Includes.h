#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <windows.h>
#include <fcntl.h>
#include <stdio.h>
#include <io.h>
#include <iostream>
#include <vector>
#include <d3d11.h>
#include <d3dx11.h>
#include <D3DX11core.h>
#include <D3DX11tex.h>
#include <d3d9.h>
#include <d3dx10.h>
#include <D3DX10math.h>
#include <d3dx9core.h>
#include <DirectXMath.h>
#include <FW1FontWrapper.h>


#pragma comment(lib,"FW1FontWrapper.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

// 48 8B 01      mov   rax, [rcx]
// C3            retn
#pragma code_seg(push, ".text")
__declspec(allocate(".text"))
	UCHAR return_bytes[4] = { 0x48, 0x8B, 0x01, 0xC3 };
#pragma code_seg()

typedef PVOID (*tPtrReadChk)(PVOID);
static const tPtrReadChk ChkPtrRead = (tPtrReadChk)&return_bytes;

#define InvalidPtrAccess ((PVOID)0x1338cafebabef00d)

#ifdef _AMD64_
#define _PTR_MAX_VALUE ((PVOID)0x000F000000000000)
#define _VALUE ULONG_PTR
#define _Allign 0x7
#else
#define _PTR_MAX_VALUE ((PVOID)0xFFF00000)
#define _VALUE ULONG
#define _Allign 0x3
#endif
__forceinline bool IsValidPtr(PVOID p)    { return (p >= (PVOID)0x10000) && (p < _PTR_MAX_VALUE) && ChkPtrRead(p) != InvalidPtrAccess ;}//&& !((_VALUE)p & _Allign)

LONG NTAPI EH(_EXCEPTION_POINTERS *ExceptionInfo)
{
	if(ExceptionInfo->ContextRecord->Rip != (ULONG_PTR)return_bytes) //don't go yet
		return EXCEPTION_CONTINUE_SEARCH;

	ExceptionInfo->ContextRecord->Rip += 3;
	ExceptionInfo->ContextRecord->Rax = (ULONG_PTR)return_bytes; //we crashed so return

	return EXCEPTION_CONTINUE_EXECUTION;
}
#include "TypeInfoStuff.h"
#include "Enums.h"
#include "NewClasses.h"
#include "MathSolver.h"
#include "Tools.h"
#include "Functions.h"
#include "DXDrawing.h"
#include "VMTHook64.h"
#include <MinHook.h>
#include <math.h>
#include "dhFPSTimer.h"
#include <time.h>
