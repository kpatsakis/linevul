static int __videobuf_iolock (struct videobuf_queue* q,
			      struct videobuf_buffer *vb,
			      struct v4l2_framebuffer *fbuf)
{
	int pages;

	struct videbuf_vmalloc_memory *mem=vb->priv;


	BUG_ON(!mem);

	MAGIC_CHECK(mem->magic,MAGIC_VMAL_MEM);

	pages = PAGE_ALIGN(vb->size) >> PAGE_SHIFT;

	/* Currently, doesn't support V4L2_MEMORY_OVERLAY */
	if ((vb->memory != V4L2_MEMORY_MMAP) &&
				(vb->memory != V4L2_MEMORY_USERPTR) ) {
		printk(KERN_ERR "Method currently unsupported.\n");
		return -EINVAL;
	}

	/* FIXME: should be tested with kernel mmap mem */
	mem->vmalloc=vmalloc_user (PAGE_ALIGN(vb->size));
	if (NULL == mem->vmalloc) {
		printk(KERN_ERR "vmalloc (%d pages) failed\n",pages);
		return -ENOMEM;
	}

	dprintk(1,"vmalloc is at addr 0x%08lx, size=%d\n",
				(unsigned long)mem->vmalloc,
				pages << PAGE_SHIFT);

	/* It seems that some kernel versions need to do remap *after*
	   the mmap() call
	 */
	if (mem->vma) {
		int retval=remap_vmalloc_range(mem->vma, mem->vmalloc,0);
		kfree(mem->vma);
		mem->vma=NULL;
		if (retval<0) {
			dprintk(1,"mmap app bug: remap_vmalloc_range area %p error %d\n",
				mem->vmalloc,retval);
			return retval;
		}
	}

	return 0;
}
