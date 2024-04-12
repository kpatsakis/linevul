static ssize_t defrag_store(struct kobject *kobj,
			    struct kobj_attribute *attr,
			    const char *buf, size_t count)
{
	return double_flag_store(kobj, attr, buf, count,
				 TRANSPARENT_HUGEPAGE_DEFRAG_FLAG,
				 TRANSPARENT_HUGEPAGE_DEFRAG_REQ_MADV_FLAG);
}
