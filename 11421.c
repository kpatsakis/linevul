void xenvif_get(struct xenvif *vif)
{
	atomic_inc(&vif->refcnt);
}
