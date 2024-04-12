__ap_send(ap_qid_t qid, unsigned long long psmid, void *msg, size_t length,
	  unsigned int special)
{
	typedef struct { char _[length]; } msgblock;
	register unsigned long reg0 asm ("0") = qid | 0x40000000UL;
	register struct ap_queue_status reg1 asm ("1");
	register unsigned long reg2 asm ("2") = (unsigned long) msg;
	register unsigned long reg3 asm ("3") = (unsigned long) length;
	register unsigned long reg4 asm ("4") = (unsigned int) (psmid >> 32);
	register unsigned long reg5 asm ("5") = psmid & 0xffffffff;

	if (special == 1)
		reg0 |= 0x400000UL;

	asm volatile (
		"0: .long 0xb2ad0042\n"		/* NQAP */
		"   brc   2,0b"
		: "+d" (reg0), "=d" (reg1), "+d" (reg2), "+d" (reg3)
		: "d" (reg4), "d" (reg5), "m" (*(msgblock *) msg)
		: "cc" );
	return reg1;
}
