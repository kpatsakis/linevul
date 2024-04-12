clamp_pattern_bbox(gs_pattern1_instance_t * pinst, gs_rect * pbbox,
                    int width, int height, const gs_matrix * pmat)
{
    double xstep = pinst->templat.XStep;
    double ystep = pinst->templat.YStep;
    double xmin = pbbox->q.x;
    double xmax = pbbox->p.x;
    double ymin = pbbox->q.y;
    double ymax = pbbox->p.y;
    int ixpat, iypat, iystart;
    double xpat, ypat;
    double xlower, xupper, ylower, yupper;
    double xdev, ydev;
    gs_rect dev_page, pat_page;
    gs_point dev_pat_origin, dev_step;
    int code;

    double xepsilon = FLT_EPSILON * width;
    double yepsilon = FLT_EPSILON * height;

    /*
     * Scan across the page.  We determine the region to be scanned
     * by working in the pattern coordinate space.  This is logically
     * simpler since XStep and YStep are on axis in the pattern space.
     */
    /* But, since we are starting below bottom left, and 'incrementing' by
     * xstep and ystep, make sure they are not negative, or we will be in
     * a very long loop indeed.
     */
    if (xstep < 0)
        xstep *= -1;
    if (ystep < 0)
        ystep *= -1;
    /*
     * Convert the page dimensions from device coordinates into the
     * pattern coordinate frame.
     */
    dev_page.p.x = dev_page.p.y = 0;
    dev_page.q.x = width;
    dev_page.q.y = height;
    code = gs_bbox_transform_inverse(&dev_page, pmat, &pat_page);
    if (code < 0)
        return code;
    /*
     * Determine the location of the pattern origin in device coordinates.
     */
    gs_point_transform(0.0, 0.0, pmat, &dev_pat_origin);
    /*
     * Determine our starting point.  We start with a postion that puts the
     * pattern below and to the left of the page (in pattern space) and scan
     * until the pattern is above and right of the page.
     */
    ixpat = (int) floor((pat_page.p.x - pinst->templat.BBox.q.x) / xstep);
    iystart = (int) floor((pat_page.p.y - pinst->templat.BBox.q.y) / ystep);

    /* Now do the scan */
    for (; ; ixpat++) {
        xpat = ixpat * xstep;
        for (iypat = iystart; ; iypat++) {
            ypat = iypat * ystep;
            /*
             * Calculate the shift in the pattern's location.
             */
            gs_point_transform(xpat, ypat, pmat, &dev_step);
            xdev = dev_step.x - dev_pat_origin.x;
            ydev = dev_step.y - dev_pat_origin.y;
            /*
             * Check if the pattern bounding box intersects the page.
             */
            xlower = (xdev + pbbox->p.x > 0) ? pbbox->p.x : -xdev;
            xupper = (xdev + pbbox->q.x < width) ? pbbox->q.x : -xdev + width;
            ylower = (ydev + pbbox->p.y > 0) ? pbbox->p.y : -ydev;
            yupper = (ydev + pbbox->q.y < height) ? pbbox->q.y : -ydev + height;

            /* The use of floating point in these calculations causes us
             * problems. Values which go through the calculation without ever
             * being 'large' retain more accuracy in the lower bits than ones
             * which momentarily become large. This is seen in bug 694528
             * where a y value of 0.00017... becomes either 0 when 8000 is
             * first added to it, then subtracted. This can lead to yupper
             * and ylower being different.
             *
             * The "fix" implemented here is to amend the following test to
             * ensure that the region found is larger that 'epsilon'. The
             * epsilon values are calculated to reflect the floating point
             * innacuracies at the appropriate range.
             */
            if (xlower + xepsilon < xupper && ylower + yepsilon < yupper) {
                /*
                 * The pattern intersects the page.  Expand required area if
                 * needed.
                 */
                if (xlower < xmin)
                    xmin = xlower;
                if (xupper > xmax)
                    xmax = xupper;
                if (ylower < ymin)
                    ymin = ylower;
                if (yupper > ymax)
                    ymax = yupper;
            }
            if (ypat > pat_page.q.y - pinst->templat.BBox.p.y)
                break;
        }
        if (xpat > pat_page.q.x - pinst->templat.BBox.p.x)
            break;
    }
    /* Update the bounding box. */
    if (xmin < xmax && ymin < ymax) {
        pbbox->p.x = xmin;
        pbbox->q.x = xmax;
        pbbox->p.y = ymin;
        pbbox->q.y = ymax;
    } else {
        /* The pattern is never on the page.  Set bbox = 1, 1 */
        pbbox->p.x = pbbox->p.y = 0;
        pbbox->q.x = pbbox->q.y = 1;
    }
    return 0;
}
