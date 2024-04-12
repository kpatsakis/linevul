static CPLXMLNode* FLTFindGeometryNode(CPLXMLNode* psXMLNode,
                                       int* pbPoint,
                                       int* pbLine,
                                       int* pbPolygon)
{
    CPLXMLNode *psGMLElement = NULL;

    psGMLElement = CPLGetXMLNode(psXMLNode, "Point");
    if (!psGMLElement)
        psGMLElement =  CPLGetXMLNode(psXMLNode, "PointType");
    if (psGMLElement)
        *pbPoint =1;
    else {
      psGMLElement= CPLGetXMLNode(psXMLNode, "Polygon");
      if (psGMLElement)
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "MultiPolygon")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "Surface")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "MultiSurface")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "Box")))
        *pbPolygon = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "LineString")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "MultiLineString")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "Curve")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "MultiCurve")))
        *pbLine = 1;
      else if ((psGMLElement= CPLGetXMLNode(psXMLNode, "MultiPoint")))
        *pbPoint = 1;
    }
    return psGMLElement;
}
