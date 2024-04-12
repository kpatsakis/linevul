static EAS_RESULT Parse_cdl (SDLS_SYNTHESIZER_DATA *pDLSData, EAS_I32 size, EAS_U32 *pValue)
{
    EAS_RESULT result;
    EAS_U32 stack[CDL_STACK_SIZE];
    EAS_U16 opcode;
    EAS_INT stackPtr;
    EAS_U32 x, y;
    DLSID dlsid;

    stackPtr = -1;
 *pValue = 0;
    x = 0;
 while (size)
 {
 /* read the opcode */
 if ((result = EAS_HWGetWord(pDLSData->hwInstData, pDLSData->fileHandle, &opcode, EAS_FALSE)) != EAS_SUCCESS)
 return result;

 /* handle binary opcodes */
 if (opcode <= DLS_CDL_EQ)
 {
 /* pop X and Y */
 if ((result = PopcdlStack(stack, &stackPtr, &x)) != EAS_SUCCESS)
 return result;
 if ((result = PopcdlStack(stack, &stackPtr, &y)) != EAS_SUCCESS)
 return result;
 switch (opcode)
 {
 case DLS_CDL_AND:
                    x = x & y;
 break;
 case DLS_CDL_OR:
                    x = x | y;
 break;
 case DLS_CDL_XOR:
                    x = x ^ y;
 break;
 case DLS_CDL_ADD:
                    x = x + y;
 break;
 case DLS_CDL_SUBTRACT:
                    x = x - y;
 break;
 case DLS_CDL_MULTIPLY:
                    x = x * y;
 break;
 case DLS_CDL_DIVIDE:
 if (!y)
 return EAS_ERROR_FILE_FORMAT;
                    x = x / y;
 break;
 case DLS_CDL_LOGICAL_AND:
                    x = (x && y);
 break;
 case DLS_CDL_LOGICAL_OR:
                    x = (x || y);
 break;
 case DLS_CDL_LT:
                    x = (x < y);
 break;
 case DLS_CDL_LE:
                    x = (x <= y);
 break;
 case DLS_CDL_GT:
                    x = (x > y);
 break;
 case DLS_CDL_GE:
                    x = (x >= y);
 break;
 case DLS_CDL_EQ:
                    x = (x == y);
 break;
 default:
 break;
 }
 }

 else if (opcode == DLS_CDL_NOT)
 {
 if ((result = PopcdlStack(stack, &stackPtr, &x)) != EAS_SUCCESS)
 return result;
            x = !x;
 }

 else if (opcode == DLS_CDL_CONST)
 {
 if ((result = EAS_HWGetDWord(pDLSData->hwInstData, pDLSData->fileHandle, &x, EAS_FALSE)) != EAS_SUCCESS)
 return result;
 }

 else if (opcode == DLS_CDL_QUERY)
 {
 if ((result = ReadDLSID(pDLSData, &dlsid)) != EAS_SUCCESS)
 return result;
 QueryGUID(&dlsid, &x);
 }

 else if (opcode == DLS_CDL_QUERYSUPPORTED)
 {
 if ((result = ReadDLSID(pDLSData, &dlsid)) != EAS_SUCCESS)
 return result;
            x = QueryGUID(&dlsid, &y);
 }
 else
 { /* dpp: EAS_ReportEx(_EAS_SEVERITY_WARNING, "Unsupported opcode %d in DLS file\n", opcode); */ }

 /* push the result on the stack */
 if ((result = PushcdlStack(stack, &stackPtr, x)) != EAS_SUCCESS)
 return result;
 }

 /* pop the last result off the stack */
 return PopcdlStack(stack, &stackPtr, pValue);
}
