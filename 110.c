void Field_CompletePlayerName( const char **names, int nameCount )
{
	qboolean whitespace;

	matchCount = 0;
	shortestMatch[ 0 ] = 0;

	if( nameCount <= 0 )
		return;

	Name_PlayerNameCompletion( names, nameCount, FindMatches );

	if( completionString[0] == '\0' )
	{
		Com_PlayerNameToFieldString( shortestMatch, sizeof( shortestMatch ), names[ 0 ] );
	}

	if( completionString[0] != '\0'
		&& Q_stricmp( shortestMatch, completionString ) == 0 
		&& nameCount > 1 ) 
	{
		int i;

		for( i = 0; i < nameCount; i++ ) {
			if( Q_stricmp( names[ i ], completionString ) == 0 ) 
			{
				i++;
				if( i >= nameCount )
				{
					i = 0;
				}

				Com_PlayerNameToFieldString( shortestMatch, sizeof( shortestMatch ), names[ i ] );
				break;
			}
		}
	}

	if( matchCount > 1 )
	{
		Com_Printf( "]%s\n", completionField->buffer );
		
		Name_PlayerNameCompletion( names, nameCount, PrintMatches );
	}

	whitespace = nameCount == 1? qtrue: qfalse;
	if( !Field_CompletePlayerNameFinal( whitespace ) )
	{

	}
}
