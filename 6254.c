static INLINE void IncrementX963KdfCounter(byte* inOutCtr)
{
    int i;

    /* in network byte order so start at end and work back */
    for (i = 3; i >= 0; i--) {
        if (++inOutCtr[i])  /* we're done unless we overflow */
            return;
    }
}
