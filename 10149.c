void WT_UpdateLFO (S_LFO_CONTROL *pLFO, EAS_I16 phaseInc)
{

 /* To save memory, if m_nPhaseValue is negative, we are in the
     * delay phase, and m_nPhaseValue represents the time left
     * in the delay.
     */
 if (pLFO->lfoPhase < 0)
 {
        pLFO->lfoPhase++;
 return;
 }

 /* calculate LFO output from phase value */
 /*lint -e{701} Use shift for performance */
    pLFO->lfoValue = (EAS_I16) (pLFO->lfoPhase << 2);
 /*lint -e{502} <shortcut to turn sawtooth into triangle wave> */
 if ((pLFO->lfoPhase > 0x1fff) && (pLFO->lfoPhase < 0x6000))
        pLFO->lfoValue = ~pLFO->lfoValue;

 /* update LFO phase */
    pLFO->lfoPhase = (pLFO->lfoPhase + phaseInc) & 0x7fff;
}
