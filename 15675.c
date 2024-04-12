void WriteOutput(char *filename, u8 *data, u32 picSize)
{

 /* foutput is global file pointer */
 if (foutput == NULL)
 {
 /* open output file for writing, can be disabled with define.
         * If file open fails -> exit */
 if (strcmp(filename, "none") != 0)
 {
#if !defined(_NO_OUT)
            foutput = fopen(filename, "wb");
 if (foutput == NULL)
 {
                DEBUG(("UNABLE TO OPEN OUTPUT FILE\n"));
                exit(100);
 }
#endif
 }
 }

 if (foutput && data)
        fwrite(data, 1, picSize, foutput);
}
