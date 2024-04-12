static int oz_usb_vendor_class_req(void *hpd, u8 req_id, u8 req_type,
	u8 request, __le16 value, __le16 index, const u8 *data, int data_len)
{
	struct oz_usb_ctx *usb_ctx = hpd;
	struct oz_pd *pd = usb_ctx->pd;
	struct oz_elt *elt;
	struct oz_elt_buf *eb = &pd->elt_buff;
	struct oz_elt_info *ei = oz_elt_info_alloc(&pd->elt_buff);
	struct oz_vendor_class_req *body;

	if (ei == NULL)
		return -1;
	elt = (struct oz_elt *)ei->data;
	elt->length = sizeof(struct oz_vendor_class_req) - 1 + data_len;
	body = (struct oz_vendor_class_req *)(elt+1);
	body->type = OZ_VENDOR_CLASS_REQ;
	body->req_id = req_id;
	body->req_type = req_type;
	body->request = request;
	put_unaligned(value, &body->value);
	put_unaligned(index, &body->index);
	if (data_len)
		memcpy(body->data, data, data_len);
	return oz_usb_submit_elt(eb, ei, usb_ctx, 0, 0);
}
