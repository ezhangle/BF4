class Tempclass
{
public:
	virtual DWORD_PTR GetType(); //
};//Size=0x0040

class Components
{
public:
	__int64 unk1; //0x0000 
	__int64 unk2; //0x0008 
	char _0x0010[16];
	Tempclass** m_ppComponents; //0x0020 
	char _0x0028[76];
	float m_timeElapsed; //0x0074 

	void Dump( )
	{
		int sectionCount = 0;
		int numSections = 0;

		for( int i = 0; i < 281; i++ )
		{
			if ( m_ppComponents[i] )
			{
				printf( "Object %I64X",	m_ppComponents[i] ); // Pointer
				printf( " Type: %I64X",	m_ppComponents[i]->GetType( ) );
				printf( " (%s)\n", **( char*** )m_ppComponents[i]->GetType( ) );
				sectionCount++;
			} else {
				printf( "--section size: %d\n\n", sectionCount );
				sectionCount = 0;
				numSections++;
			}
		}

		printf( "TOTAL SECTIONS: %d\n", numSections );
	}
};