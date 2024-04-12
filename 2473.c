newSWFGlyphShape()
{
	SWFShape shape = (SWFShape)malloc(sizeof(struct SWFShape_s));

	/* If malloc failed, return NULL to signify this */
	if (NULL == shape)
		return NULL;

	SWFCharacterInit((SWFCharacter)shape);

	BLOCK(shape)->writeBlock = NULL;
	BLOCK(shape)->complete = NULL;
	BLOCK(shape)->dtor = NULL;
	BLOCK(shape)->type = SWF_UNUSEDBLOCK;
	
	shape->out = newSWFOutput();
	CHARACTER(shape)->bounds = newSWFRect(0,0,0,0);
	shape->edgeBounds = newSWFRect(0,0,0,0);

	shape->records = NULL;
	shape->lines = NULL;
	shape->fills = NULL;

	shape->nRecords = 0;
	shape->xpos = 0;
	shape->ypos = 0;
	shape->nLines = 0;
	shape->nFills = 0;
	shape->lineWidth = 0;
	shape->isMorph = FALSE;
	shape->isEnded = FALSE;
	shape->flags = 0;
	shape->useVersion = 0;

	SWFOutput_writeUInt8(shape->out, 0); /* space for nFillBits, nLineBits */

#if TRACK_ALLOCS
	shape->gcnode = ming_gc_add_node(shape, (dtorfunctype) destroySWFShape);
#endif

	return shape;
}