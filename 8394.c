static EAS_I16 ConvertLFOPhaseIncrement (EAS_I32 pitchCents)
{

 /* check range */
 if (pitchCents > MAX_LFO_FREQUENCY_IN_PITCHCENTS)
        pitchCents = MAX_LFO_FREQUENCY_IN_PITCHCENTS;
 if (pitchCents < MIN_LFO_FREQUENCY_IN_PITCHCENTS)
        pitchCents = MIN_LFO_FREQUENCY_IN_PITCHCENTS;

 /* double the rate and divide by frame rate by subtracting in log domain */
    pitchCents = pitchCents - dlsLFOFrequencyConvert;

 /* convert to phase increment */
 return (EAS_I16) EAS_Calculate2toX(pitchCents);
}
