#include <map>
#include <string>
	class TestList;
	struct MemberInfoFlags;
	class ModuleInfo;
	class MemberInfo;
	class TypeInfo;
	class FieldInfo;
	class ClassInfo;
	class ITypedObject;
	class DataContainer;

	class TestList
	{
	public:
		typedef void* Test;

		Test* m_head; //0x0000 
		Test* m_tail; //0x0008 

	};//Size=0x0010

	struct MemberInfoFlags
	{
		unsigned short m_flagBits; //0x0000 

	};//Size=0x0002

	class ModuleInfo
	{
	public:
		char* m_moduleName; //0x0000 
		ModuleInfo* m_nextModule; //0x0008 
		TestList* m_testList; //0x0010 

	};//Size=0x0018

	class MemberInfo
	{
	public:
#pragma pack(push, 2)
		struct MemberInfoData
		{
			char* m_name; //0x0000
			MemberInfoFlags m_flags; //0x0008

		};//Size=0x000A
#pragma pack(pop)

		MemberInfoData* m_infoData; //0x0000

		bool isClass();
		MemberInfoData* getMemberInfoData();

	};//Size=0x0008

	class TypeInfo : public MemberInfo
	{
	public:
		struct TypeInfoData : public MemberInfoData
		{
			unsigned short m_totalSize; //0x000A 
			char _0x000C[4];
			ModuleInfo* m_module; //0x0010 
			unsigned char m_alignment; //0x0018 
			unsigned char m_fieldCount; //0x0019 
			char _0x001A[6];

		};//Size=0x0020

		TypeInfo* m_pNext; //0x0008
		unsigned short m_runtimeId; //0x0010
		unsigned short m_flags; //0x0012
		char _0x0014[4];

		TypeInfoData* getTypeInfoData();

	};//Size=0x0018

	class FieldInfo : public MemberInfo
	{
	public:
		struct FieldInfoData : public MemberInfo::MemberInfoData
		{
			unsigned short m_fieldOffset; //0x000A
			char _0x000C[4];
			TypeInfo* m_fieldTypePtr; //0x0010

		};//Size=0x0018

		virtual TypeInfo* getDeclaringType();
		virtual unsigned short getFieldIndex();

		TypeInfo* m_declaringType; //0x0010 
		unsigned short m_fieldIndex; //0x0018 
		unsigned short m_attributeMask; //0x001A 
		char _0x001C[4];

		FieldInfoData* getFieldInfoData();

	};//Size=0x0020

	class ClassInfo : public TypeInfo
	{
	public:
		struct ClassInfoData : TypeInfo::TypeInfoData
		{
			ClassInfo* m_superClass; //0x0020 
			void* m_createFun; //0x0028 
			FieldInfo::FieldInfoData* m_fields; //0x0030     

		};//Size=0x0038

		ClassInfo* m_super; //0x0018 
		DataContainer* m_defaultInstance; //0x0020 
		unsigned short m_classId; //0x0028 
		unsigned short m_lastSubClassId; //0x002A 
		char _0x002C[4];
		ClassInfo* m_firstDerivedClass; //0x0030 
		ClassInfo* m_nextSiblingClass; //0x0038 
		FieldInfo** m_fieldInfos; //0x0040 
		unsigned int m_totalFieldCount; //0x0048 
		char _0x004C[4];

		ClassInfoData* getClassInfoData();

	};//Size=0x0050

	class ITypedObject
	{
	public:
		virtual TypeInfo* getType();
	};//Size=0x0008

	class DataContainer : public ITypedObject
	{
	public:
		union
		{
			struct
			{
				unsigned short m_refCnt; //0x0008
				unsigned short m_flags; //0x000A
			};
			int m_refCountAndId; //0x0008 
		};
		char _0x000C[4];

	};//Size=0x0010
	//////////////////////////////////////////Functions/////////////////////////////////////////
	bool MemberInfo::isClass()
	{
		MemberInfo::MemberInfoData* memberInfoData = getMemberInfoData();
		if (memberInfoData)
		{
			return (memberInfoData->m_flags.m_flagBits & 0x1F0) == 0x30;
		}
		return false;
	}


	MemberInfo::MemberInfoData* MemberInfo::getMemberInfoData()
	{
		return ((MemberInfoData*)m_infoData);
	}


	TypeInfo::TypeInfoData* TypeInfo::getTypeInfoData()
	{
		return ((TypeInfoData*)m_infoData);
	}


	FieldInfo::FieldInfoData* FieldInfo::getFieldInfoData()
	{
		return ((FieldInfoData*)m_infoData);
	}


	ClassInfo::ClassInfoData* ClassInfo::getClassInfoData()
	{
		return ((ClassInfoData*)m_infoData);
	}


bool printInfo(TypeInfo * typeInfo)
{
	if (!typeInfo->isClass()) return false;
	ClassInfo* classInfo = (ClassInfo*)typeInfo;
	if (!IsValidPtr(classInfo))
		return false;

	TypeInfo::TypeInfoData *typeInfoData = typeInfo->getTypeInfoData();
	if (!IsValidPtr(typeInfoData))
		return false;

	printf("Class Name: %s\nSize 0x%x\n", typeInfoData->m_name, typeInfoData->m_totalSize);
	printf("TypeInfoData location: 0x1%x\n", typeInfoData);

	ClassInfo *classInfo2 = reinterpret_cast< ClassInfo* > (typeInfo);
	if(!IsValidPtr(classInfo2))
		return false;

	ClassInfo *classInfoSuper = classInfo2->m_super;
	if(!IsValidPtr(classInfoSuper))
		return false;
	printf("Super Name: %s\nSuper Size 0x%x\n", classInfoSuper->getTypeInfoData()->m_name, classInfoSuper->getTypeInfoData()->m_totalSize);

	ClassInfo::TypeInfoData *classTypeInfo = classInfo->getClassInfoData();
	if(!IsValidPtr(classTypeInfo))
		return false;

	if (classTypeInfo && classTypeInfo->m_fieldCount != 0)
		printf("Class Members: %d\n", classTypeInfo->m_fieldCount);

	ModuleInfo *module = typeInfoData->m_module;
	if (module)
		printf("Module Name: %s\n\n", module->m_moduleName);

	printf("class %s\n{\npublic:\n", typeInfoData->m_name);

	std::map<DWORD, std::string>m;

	for (int i = 0; i < classInfo->m_totalFieldCount; i++) {
		FieldInfo* fieldInfo = classInfo->m_fieldInfos[i];
		if(!IsValidPtr(fieldInfo))
		{
			printf("No Field Info: Member %d",i);
			continue;
		}
		FieldInfo::FieldInfoData* fieldInfoData = fieldInfo->getFieldInfoData();
		if(!IsValidPtr(fieldInfoData))
		{
			printf("No Field InfoData: Member %d",i);
			continue;
		}else{
			printf("Got FieldInfoData \n");
		}
		std::string type = fieldInfoData->m_fieldTypePtr->m_infoData->m_name;
		std::string name = fieldInfoData->m_name;
		std::string info = "";
		if (type == "CString") {
			info = "char* m_" + name;
		}else if (type == "float"){
			info = "float m_" + name;
		}else if (type == "bool") {
			info = "bool m_" + name;
		}else if (type == "int") {
			info = "int m_" + name;
		}else if (type == "unsigned int") {
			info = "unsigned int m_" + name; 
		}else if (type =="Vec3"){
			info= "D3DXVector3 m_"+name;
		}else if (type=="Vec2")
		{
			info="D3DXVECTOR2 m_"+name;
		}else {
			info = type + " m_" + name;
		}
		m[fieldInfoData->m_fieldOffset] = info;

	}
	printf("\tchar inherited%s[0x%x]; //+0x00\n", classInfoSuper->getTypeInfoData()->m_name, classInfo->m_fieldInfos[0]->getFieldInfoData()->m_fieldOffset);
	for (std::map<DWORD, std::string>::iterator i = m.begin(); i != m.end(); i++)
	{
		printf("\t%s; //+0x%x\n", i->second.c_str(), i->first);
	}
	printf("};\n");

	return true;
}