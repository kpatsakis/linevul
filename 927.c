static void proto_seq_printf(struct seq_file *seq, struct proto *proto)
{

	seq_printf(seq, "%-9s %4u %6d  %6ld   %-3s %6u   %-3s  %-10s "
			"%2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c %2c\n",
		   proto->name,
		   proto->obj_size,
		   sock_prot_inuse_get(seq_file_net(seq), proto),
		   sock_prot_memory_allocated(proto),
		   sock_prot_memory_pressure(proto),
		   proto->max_header,
		   proto->slab == NULL ? "no" : "yes",
		   module_name(proto->owner),
		   proto_method_implemented(proto->close),
		   proto_method_implemented(proto->connect),
		   proto_method_implemented(proto->disconnect),
		   proto_method_implemented(proto->accept),
		   proto_method_implemented(proto->ioctl),
		   proto_method_implemented(proto->init),
		   proto_method_implemented(proto->destroy),
		   proto_method_implemented(proto->shutdown),
		   proto_method_implemented(proto->setsockopt),
		   proto_method_implemented(proto->getsockopt),
		   proto_method_implemented(proto->sendmsg),
		   proto_method_implemented(proto->recvmsg),
		   proto_method_implemented(proto->sendpage),
		   proto_method_implemented(proto->bind),
		   proto_method_implemented(proto->backlog_rcv),
		   proto_method_implemented(proto->hash),
		   proto_method_implemented(proto->unhash),
		   proto_method_implemented(proto->get_port),
		   proto_method_implemented(proto->enter_memory_pressure));
}
