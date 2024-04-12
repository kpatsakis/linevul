void CL_NextDemo( void ) {
	char	v[MAX_STRING_CHARS];

	Q_strncpyz( v, Cvar_VariableString( "nextdemo" ), sizeof( v ) );
	v[MAX_STRING_CHARS - 1] = 0;
	Com_DPrintf( "CL_NextDemo: %s\n", v );
	if ( !v[0] ) {
		return;
	}

	Cvar_Set( "nextdemo","" );
	Cbuf_AddText( v );
	Cbuf_AddText( "\n" );
	Cbuf_Execute();
}
