#define OFFSET_SIG_TABLE 0x9CE08
#include <ShlObj.h>
#include <iosfwd>
#include <stdio.h>
#include <fstream>
#include <Psapi.h>
#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))
DWORD FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern );
void SetConsoleColor(colour PreColor,colour PostColor,char* text);
void GetModuleAddressAndSize(const char* dllName, DWORD* base, DWORD* size,HMODULE ModuleHandle);
class PBScanSignature
{
public:
	DWORD Code;            //0x00
	DWORD Offset;        //0x04
	//  WORD Type;            //0x08 
	char Type[2];   //0x08
	WORD Length;        //0x0A
	WORD Sig[128];     //0x0C
	DWORD Arg1;            //0x10C
	DWORD Arg2;            //0x110
	DWORD Arg3;            //0x114
	DWORD Enabled;      //0x118
	DWORD Arg5;            //0x11C
}; //0x120

class PBSigTable
{
public:
	__int64  qwSigBase; //0x0000
	DWORD    dwTableSize; //0x0004 
	DWORD    dwSigSize; //0x0008

	static PBSigTable* GetInstance( )
	{
		__int64 qwPBCLd64 = ( __int64 )GetModuleHandle( "pbcl.d64" );

		if ( qwPBCLd64 )
			return ( PBSigTable* )( qwPBCLd64 + OFFSET_SIG_TABLE );
		else
			return NULL;
	}

	PBScanSignature* GetScanSignature( unsigned int sigID )
	{
		PBScanSignature* pSig = NULL;

		if ( sigID >= 0 )
		{
			if ( sigID < this->qwSigBase )
				pSig = ( PBScanSignature* )( this->qwSigBase + sigID * this->dwSigSize );
		}
		return pSig;
	}
};  
std::string GetSig(PBScanSignature *p)
{

	static char szSig[512]={0};
	if(!p)return "   ";

	int len  = p->Length;
	if(len>128)len = 128;
	for ( UINT i=0; i<len; i++ )
	{

		int iOffset = i * 2;
		int iBufSpace = 256 - iOffset;
		{
			if (p->Sig[i] > 0xFF)
				strcat_s( (char*)&szSig, 256, "??" );
			else
				sprintf_s( (char*)&szSig + iOffset, iBufSpace, "%02X", p->Sig[i] );
		}

	}
	std::string returnval(szSig);
	return returnval;
}
void DumpSigs()
{
	std::ofstream myfile;
	char path[MAX_PATH];
	SHGetFolderPath(NULL,CSIDL_DESKTOPDIRECTORY,0,NULL,path); //get desktop folder
	strcat(path,"\\BF4_Sigs.txt");//add Sigs.text to path
	myfile.open(path,std::ios::trunc|std::ios::out);

	PBSigTable* pPBTable=PBSigTable::GetInstance();
	if(!IsValidPtr(pPBTable))
		return;
	printf("Table at:%X\n",pPBTable);
	printf("dwSigSize: %d \n",pPBTable->dwSigSize);
	printf("dwTableSize: %d \n",pPBTable->dwTableSize);
	printf("dqSigBase: %X \n",pPBTable->qwSigBase);

	for(int i=0;i<pPBTable->dwTableSize;i++)
	{
		printf("Got Scan at: %d\n",i);
		PBScanSignature* pScan=pPBTable->GetScanSignature(i);
		std::string sig=GetSig(pScan);

		for(int i=2;i<sig.size();i+=3)
		{
			sig.insert(i," "); //insert space every 2 characters
		}

		myfile <<"ID:["<<pScan->Code<<"] "<<"Type["<<pScan->Type<<"] "<<"Offset["<<pScan->Offset<<"] "<<"Sig["<<sig<<"]\n";
	}
	myfile.close();
}
void ScanSigs(HMODULE ModuleHandle=NULL)
{
	DWORD Base,Size; //get base and size of our dll module
	GetModuleAddressAndSize("BF4.dll",&Base,&Size,ModuleHandle);
	printf("Dll Is: %X to %X \n",Base,Base+Size);

	PBSigTable* pPBTable=PBSigTable::GetInstance();
	printf("dwSigSize: %d \n",pPBTable->dwSigSize);
	printf("dwTableSize: %d \n",pPBTable->dwTableSize);
	printf("dqSigBase: %d \n",pPBTable->qwSigBase);

	for(int i=0;i<pPBTable->dwTableSize;i++)
	{
		if(GetSig(pPBTable->GetScanSignature(i)).size()<=5) //don't want to scan on an empty sig
			continue;

		DWORD address=FindPattern(Base,Base+Size,GetSig(pPBTable->GetScanSignature(i)).c_str());
		if(address)
		{
			std::ofstream myfile;
			char path[MAX_PATH];
			SHGetFolderPath(NULL,CSIDL_DESKTOPDIRECTORY,0,NULL,path); //get desktop folder
			strcat(path,"\\BF4_Match.txt");//add Sigs.text to path
			myfile.open(path,std::ios::trunc|std::ios::out);

			char output[120];
			sprintf_s(output,"Found Match at %d Sig: [%s]",i,GetSig(pPBTable->GetScanSignature(i)));
			myfile<<output<<"\n";
			myfile.close();

			SetConsoleColor(colour::RED,colour::GRAY,output);
			ExitProcess(0);
		}else{
			std::cout<<"Sig Index: "<<i;
			SetConsoleColor(colour::GREEN,colour::GRAY," :No Match");
		}
	}
	printf("Scanned %d Sigs 0x%X to 0x%X No Matches: ",pPBTable->dwTableSize,Base,Base+Size);
	SetConsoleColor(colour::GREEN,colour::GRAY,"Undetected");
}
DWORD FindPattern( DWORD rangeStart, DWORD rangeEnd, const char* pattern )//Learn_more
{
	const char* pat = pattern;
	DWORD firstMatch = 0;
	for( DWORD pCur = rangeStart; pCur < rangeEnd; pCur++ )
	{
		if( !*pat ) return firstMatch;
		if( *(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte( pat ) ) {
			if( !firstMatch ) firstMatch = pCur;
			if( !pat[2] ) return firstMatch;
			if( *(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?' ) pat += 3;
			else pat += 2;    //one ?
		} else {
			pat = pattern;
			firstMatch = 0;
		}
	}
	return NULL;
} 
void GetModuleAddressAndSize(const char* dllName, DWORD* base, DWORD* size,HMODULE ModuleHandle=NULL) //zoomgod http://www.unknowncheats.me/forum/633534-post5.html
{

	MODULEINFO module;

	ZeroMemory(&module, sizeof(module));

	*base = 0;
	*size = 0;

	if(!ModuleHandle)
	{
		ModuleHandle=GetModuleHandleA(dllName);
	}
	if (GetModuleInformation(GetCurrentProcess(), ModuleHandle, &module, sizeof(module)))
	{
		*base = (DWORD)module.lpBaseOfDll;
		*size = (DWORD)module.SizeOfImage;
	}

}
void SetConsoleColor(colour PreColor,colour PostColor,char* text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),PreColor);
	std::cout<<text<<"\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),PostColor);
}
