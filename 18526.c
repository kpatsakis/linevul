static float CL_DemoFrameDurationSDev( void )
{
	int i;
	int numFrames;
	float mean = 0.0f;
	float variance = 0.0f;

	if( ( clc.timeDemoFrames - 1 ) > MAX_TIMEDEMO_DURATIONS )
		numFrames = MAX_TIMEDEMO_DURATIONS;
	else
		numFrames = clc.timeDemoFrames - 1;

	for( i = 0; i < numFrames; i++ )
		mean += clc.timeDemoDurations[ i ];
	mean /= numFrames;

	for( i = 0; i < numFrames; i++ )
	{
		float x = clc.timeDemoDurations[ i ];

		variance += ( ( x - mean ) * ( x - mean ) );
	}
	variance /= numFrames;

	return sqrt( variance );
}
