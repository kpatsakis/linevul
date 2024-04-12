asmlinkage void __kprobes do_page_fault(struct pt_regs *regs, unsigned long write,
unsigned long address)
{
struct vm_area_struct * vma = NULL;
struct task_struct *tsk = current;
struct mm_struct *mm = tsk->mm;
const int field = sizeof(unsigned long) * 2;
siginfo_t info;
int fault;

#if 0
printk("Cpu%d[%s:%d:%0*lx:%ld:%0*lx]\n", raw_smp_processor_id(),
current->comm, current->pid, field, address, write,
field, regs->cp0_epc);
#endif

#ifdef CONFIG_KPROBES
/*
* This is to notify the fault handler of the kprobes.  The
* exception code is redundant as it is also carried in REGS,
* but we pass it anyhow.
*/
if (notify_die(DIE_PAGE_FAULT, "page fault", regs, -1,
(regs->cp0_cause >> 2) & 0x1f, SIGSEGV) == NOTIFY_STOP)
return;
#endif

info.si_code = SEGV_MAPERR;

/*
* We fault-in kernel-space virtual memory on-demand. The
* 'reference' page table is init_mm.pgd.
*
* NOTE! We MUST NOT take any locks for this case. We may
* be in an interrupt or a critical region, and should
* only copy the information from the master page table,
* nothing more.
*/
#ifdef CONFIG_64BIT
# define VMALLOC_FAULT_TARGET no_context
#else
# define VMALLOC_FAULT_TARGET vmalloc_fault
#endif

if (unlikely(address >= VMALLOC_START && address <= VMALLOC_END))
goto VMALLOC_FAULT_TARGET;
#ifdef MODULE_START
if (unlikely(address >= MODULE_START && address < MODULE_END))
goto VMALLOC_FAULT_TARGET;
#endif

/*
* If we're in an interrupt or have no user
* context, we must not take the fault..
*/
if (in_atomic() || !mm)
goto bad_area_nosemaphore;

down_read(&mm->mmap_sem);
vma = find_vma(mm, address);
if (!vma)
goto bad_area;
if (vma->vm_start <= address)
goto good_area;
if (!(vma->vm_flags & VM_GROWSDOWN))
goto bad_area;
if (expand_stack(vma, address))
goto bad_area;
/*
* Ok, we have a good vm_area for this memory access, so
* we can handle it..
*/
good_area:
info.si_code = SEGV_ACCERR;

if (write) {
if (!(vma->vm_flags & VM_WRITE))
goto bad_area;
} else {
if (kernel_uses_smartmips_rixi) {
if (address == regs->cp0_epc && !(vma->vm_flags & VM_EXEC)) {
#if 0
pr_notice("Cpu%d[%s:%d:%0*lx:%ld:%0*lx] XI violation\n",
raw_smp_processor_id(),
current->comm, current->pid,
field, address, write,
field, regs->cp0_epc);
#endif
goto bad_area;
}
if (!(vma->vm_flags & VM_READ)) {
#if 0
pr_notice("Cpu%d[%s:%d:%0*lx:%ld:%0*lx] RI violation\n",
raw_smp_processor_id(),
current->comm, current->pid,
field, address, write,
field, regs->cp0_epc);
#endif
goto bad_area;
}
} else {
if (!(vma->vm_flags & (VM_READ | VM_WRITE | VM_EXEC)))
goto bad_area;
}
}

/*
* If for any reason at all we couldn't handle the fault,
* make sure we exit gracefully rather than endlessly redo
* the fault.
*/
fault = handle_mm_fault(mm, vma, address, write ? FAULT_FLAG_WRITE : 0);
	perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS, 1, 0, regs, address);
if (unlikely(fault & VM_FAULT_ERROR)) {
if (fault & VM_FAULT_OOM)
goto out_of_memory;
else if (fault & VM_FAULT_SIGBUS)
goto do_sigbus;
BUG();
}
if (fault & VM_FAULT_MAJOR) {
		perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MAJ,
				1, 0, regs, address);
tsk->maj_flt++;
} else {
		perf_sw_event(PERF_COUNT_SW_PAGE_FAULTS_MIN,
				1, 0, regs, address);
tsk->min_flt++;
}

up_read(&mm->mmap_sem);
return;

/*
* Something tried to access memory that isn't in our memory map..
* Fix it, but check if it's kernel or user first..
*/
bad_area:
up_read(&mm->mmap_sem);

bad_area_nosemaphore:
/* User mode accesses just cause a SIGSEGV */
if (user_mode(regs)) {
tsk->thread.cp0_badvaddr = address;
tsk->thread.error_code = write;
#if 0
printk("do_page_fault() #2: sending SIGSEGV to %s for "
"invalid %s\n%0*lx (epc == %0*lx, ra == %0*lx)\n",
tsk->comm,
write ? "write access to" : "read access from",
field, address,
field, (unsigned long) regs->cp0_epc,
field, (unsigned long) regs->regs[31]);
#endif
info.si_signo = SIGSEGV;
info.si_errno = 0;
/* info.si_code has been set above */
info.si_addr = (void __user *) address;
force_sig_info(SIGSEGV, &info, tsk);
return;
}

no_context:
/* Are we prepared to handle this kernel fault?  */
if (fixup_exception(regs)) {
current->thread.cp0_baduaddr = address;
return;
}

/*
* Oops. The kernel tried to access some bad page. We'll have to
* terminate things with extreme prejudice.
*/
bust_spinlocks(1);

printk(KERN_ALERT "CPU %d Unable to handle kernel paging request at "
"virtual address %0*lx, epc == %0*lx, ra == %0*lx\n",
raw_smp_processor_id(), field, address, field, regs->cp0_epc,
field,  regs->regs[31]);
die("Oops", regs);

out_of_memory:
/*
* We ran out of memory, call the OOM killer, and return the userspace
* (which will retry the fault, or kill us if we got oom-killed).
*/
up_read(&mm->mmap_sem);
pagefault_out_of_memory();
return;

do_sigbus:
up_read(&mm->mmap_sem);

/* Kernel mode? Handle exceptions or die */
if (!user_mode(regs))
goto no_context;
else
/*
* Send a sigbus, regardless of whether we were in kernel
* or user mode.
*/
#if 0
printk("do_page_fault() #3: sending SIGBUS to %s for "
"invalid %s\n%0*lx (epc == %0*lx, ra == %0*lx)\n",
tsk->comm,
write ? "write access to" : "read access from",
field, address,
field, (unsigned long) regs->cp0_epc,
field, (unsigned long) regs->regs[31]);
#endif
tsk->thread.cp0_badvaddr = address;
info.si_signo = SIGBUS;
info.si_errno = 0;
info.si_code = BUS_ADRERR;
info.si_addr = (void __user *) address;
force_sig_info(SIGBUS, &info, tsk);

return;
#ifndef CONFIG_64BIT
vmalloc_fault:
{
/*
* Synchronize this task's top level page-table
* with the 'reference' page table.
*
* Do _not_ use "tsk" here. We might be inside
* an interrupt in the middle of a task switch..
*/
int offset = __pgd_offset(address);
pgd_t *pgd, *pgd_k;
pud_t *pud, *pud_k;
pmd_t *pmd, *pmd_k;
pte_t *pte_k;

pgd = (pgd_t *) pgd_current[raw_smp_processor_id()] + offset;
pgd_k = init_mm.pgd + offset;

if (!pgd_present(*pgd_k))
goto no_context;
set_pgd(pgd, *pgd_k);

pud = pud_offset(pgd, address);
pud_k = pud_offset(pgd_k, address);
if (!pud_present(*pud_k))
goto no_context;

pmd = pmd_offset(pud, address);
pmd_k = pmd_offset(pud_k, address);
if (!pmd_present(*pmd_k))
goto no_context;
set_pmd(pmd, *pmd_k);

pte_k = pte_offset_kernel(pmd_k, address);
if (!pte_present(*pte_k))
goto no_context;
return;
}
#endif
}
