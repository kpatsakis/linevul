static int del_instruction_bp(struct task_struct *child, int slot)
{
	switch (slot) {
	case 1:
		if ((child->thread.dbcr0 & DBCR0_IAC1) == 0)
			return -ENOENT;

		if (dbcr_iac_range(child) & DBCR_IAC12MODE) {
			/* address range - clear slots 1 & 2 */
			child->thread.iac2 = 0;
			dbcr_iac_range(child) &= ~DBCR_IAC12MODE;
		}
		child->thread.iac1 = 0;
		child->thread.dbcr0 &= ~DBCR0_IAC1;
		break;
	case 2:
		if ((child->thread.dbcr0 & DBCR0_IAC2) == 0)
			return -ENOENT;

		if (dbcr_iac_range(child) & DBCR_IAC12MODE)
			/* used in a range */
			return -EINVAL;
		child->thread.iac2 = 0;
		child->thread.dbcr0 &= ~DBCR0_IAC2;
		break;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	case 3:
		if ((child->thread.dbcr0 & DBCR0_IAC3) == 0)
			return -ENOENT;

		if (dbcr_iac_range(child) & DBCR_IAC34MODE) {
			/* address range - clear slots 3 & 4 */
			child->thread.iac4 = 0;
			dbcr_iac_range(child) &= ~DBCR_IAC34MODE;
		}
		child->thread.iac3 = 0;
		child->thread.dbcr0 &= ~DBCR0_IAC3;
		break;
	case 4:
		if ((child->thread.dbcr0 & DBCR0_IAC4) == 0)
			return -ENOENT;

		if (dbcr_iac_range(child) & DBCR_IAC34MODE)
			/* Used in a range */
			return -EINVAL;
		child->thread.iac4 = 0;
		child->thread.dbcr0 &= ~DBCR0_IAC4;
		break;
#endif
	default:
		return -EINVAL;
	}
	return 0;
}
