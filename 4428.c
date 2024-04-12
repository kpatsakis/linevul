static int opdiv(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;

	if ( op->operands[0].type & OT_QWORD ) {
		data[l++] = 0x48;
	}
	switch (op->operands_count) {
	case 1:
		if ( op->operands[0].type & OT_WORD ) {
			data[l++] = 0x66;
		}
		if (op->operands[0].type & OT_BYTE) {
			data[l++] = 0xf6;
		} else {
			data[l++] = 0xf7;
		}
		if (op->operands[0].type & OT_MEMORY) {
			data[l++] = 0x30 | op->operands[0].regs[0];
		} else {
			data[l++] = 0xf0 | op->operands[0].reg;
		}
		break;
	default:
		return -1;
	}
	return l;
}
