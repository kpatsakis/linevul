void deactivate_super(struct super_block *s)
{
        if (!atomic_add_unless(&s->s_active, -1, 1)) {
		down_write(&s->s_umount);
		deactivate_locked_super(s);
	}
}
