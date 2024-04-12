static void SVGStartElement(void *context,const xmlChar *name,
  const xmlChar **attributes)
{
  char
    *color,
    id[MaxTextExtent],
    token[MaxTextExtent],
    **tokens,
    *units;

  const char
    *keyword,
    *p,
    *value;

  int
    number_tokens;

  SVGInfo
    *svg_info;

  register ssize_t
    i,
    j;

  /*
    Called when an opening tag has been processed.
  */
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),"  SAX.startElement(%s",
    name);
  svg_info=(SVGInfo *) context;
  svg_info->n++;
  svg_info->scale=(double *) ResizeQuantumMemory(svg_info->scale,
    svg_info->n+1UL,sizeof(*svg_info->scale));
  if (svg_info->scale == (double *) NULL)
    {
      (void) ThrowMagickException(svg_info->exception,GetMagickModule(),
        ResourceLimitError,"MemoryAllocationFailed","`%s'",name);
      return;
    }
  svg_info->scale[svg_info->n]=svg_info->scale[svg_info->n-1];
  color=AcquireString("none");
  units=AcquireString("userSpaceOnUse");
  value=(const char *) NULL;
  if (attributes != (const xmlChar **) NULL)
    for (i=0; (attributes[i] != (const xmlChar *) NULL); i+=2)
    {
      keyword=(const char *) attributes[i];
      value=(const char *) attributes[i+1];
      switch (*keyword)
      {
        case 'C':
        case 'c':
        {
          if (LocaleCompare(keyword,"cx") == 0)
            {
              svg_info->element.cx=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"cy") == 0)
            {
              svg_info->element.cy=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'F':
        case 'f':
        {
          if (LocaleCompare(keyword,"fx") == 0)
            {
              svg_info->element.major=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"fy") == 0)
            {
              svg_info->element.minor=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'H':
        case 'h':
        {
          if (LocaleCompare(keyword,"height") == 0)
            {
              svg_info->bounds.height=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'I':
        case 'i':
        {
          if (LocaleCompare(keyword,"id") == 0)
            {
              (void) CopyMagickString(id,value,MaxTextExtent);
              break;
            }
          break;
        }
        case 'R':
        case 'r':
        {
          if (LocaleCompare(keyword,"r") == 0)
            {
              svg_info->element.angle=
                GetUserSpaceCoordinateValue(svg_info,0,value);
              break;
            }
          break;
        }
        case 'W':
        case 'w':
        {
          if (LocaleCompare(keyword,"width") == 0)
            {
              svg_info->bounds.width=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          break;
        }
        case 'X':
        case 'x':
        {
          if (LocaleCompare(keyword,"x") == 0)
            {
              svg_info->bounds.x=GetUserSpaceCoordinateValue(svg_info,1,value)-
                svg_info->center.x;
              break;
            }
          if (LocaleCompare(keyword,"x1") == 0)
            {
              svg_info->segment.x1=GetUserSpaceCoordinateValue(svg_info,1,
                value);
              break;
            }
          if (LocaleCompare(keyword,"x2") == 0)
            {
              svg_info->segment.x2=GetUserSpaceCoordinateValue(svg_info,1,
                value);
              break;
            }
          break;
        }
        case 'Y':
        case 'y':
        {
          if (LocaleCompare(keyword,"y") == 0)
            {
              svg_info->bounds.y=GetUserSpaceCoordinateValue(svg_info,-1,value)-
                svg_info->center.y;
              break;
            }
          if (LocaleCompare(keyword,"y1") == 0)
            {
              svg_info->segment.y1=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          if (LocaleCompare(keyword,"y2") == 0)
            {
              svg_info->segment.y2=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        default:
          break;
      }
    }
  if (strchr((char *) name,':') != (char *) NULL)
    {
      /*
        Skip over namespace.
      */
      for ( ; *name != ':'; name++) ;
      name++;
    }
  switch (*name)
  {
    case 'C':
    case 'c':
    {
      if (LocaleCompare((const char *) name,"circle") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      if (LocaleCompare((const char *) name,"clipPath") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push clip-path '%s'\n",id);
          break;
        }
      break;
    }
    case 'D':
    case 'd':
    {
      if (LocaleCompare((const char *) name,"defs") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push defs\n");
          break;
        }
      break;
    }
    case 'E':
    case 'e':
    {
      if (LocaleCompare((const char *) name,"ellipse") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    case 'G':
    case 'g':
    {
      if (LocaleCompare((const char *) name,"g") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    case 'I':
    case 'i':
    {
      if (LocaleCompare((const char *) name,"image") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    case 'L':
    case 'l':
    {
      if (LocaleCompare((const char *) name,"line") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      if (LocaleCompare((const char *) name,"linearGradient") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,
            "push gradient '%s' linear %g,%g %g,%g\n",id,
            svg_info->segment.x1,svg_info->segment.y1,svg_info->segment.x2,
            svg_info->segment.y2);
          break;
        }
      break;
    }
    case 'P':
    case 'p':
    {
      if (LocaleCompare((const char *) name,"path") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      if (LocaleCompare((const char *) name,"pattern") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,
            "push pattern '%s' %g,%g %g,%g\n",id,
            svg_info->bounds.x,svg_info->bounds.y,svg_info->bounds.width,
            svg_info->bounds.height);
          break;
        }
      if (LocaleCompare((const char *) name,"polygon") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      if (LocaleCompare((const char *) name,"polyline") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    case 'R':
    case 'r':
    {
      if (LocaleCompare((const char *) name,"radialGradient") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,
            "push gradient '%s' radial %g,%g %g,%g %g\n",
            id,svg_info->element.cx,svg_info->element.cy,
            svg_info->element.major,svg_info->element.minor,
            svg_info->element.angle);
          break;
        }
      if (LocaleCompare((const char *) name,"rect") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    case 'S':
    case 's':
    {
      if (LocaleCompare((const char *) name,"svg") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    case 'T':
    case 't':
    {
      if (LocaleCompare((const char *) name,"text") == 0)
        {
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          svg_info->bounds.x=0.0;
          svg_info->bounds.y=0.0;
          svg_info->bounds.width=0.0;
          svg_info->bounds.height=0.0;
          break;
        }
      if (LocaleCompare((const char *) name,"tspan") == 0)
        {
          if (*svg_info->text != '\0')
            {
              DrawInfo
                *draw_info;

              TypeMetric
                metrics;

              char
                *text;

              text=EscapeString(svg_info->text,'\'');
              (void) FormatLocaleFile(svg_info->file,"text %g,%g '%s'\n",
                svg_info->bounds.x-svg_info->center.x,svg_info->bounds.y-
                svg_info->center.y,text);
              text=DestroyString(text);
              draw_info=CloneDrawInfo(svg_info->image_info,(DrawInfo *) NULL);
              draw_info->pointsize=svg_info->pointsize;
              draw_info->text=AcquireString(svg_info->text);
              (void) ConcatenateString(&draw_info->text," ");
              GetTypeMetrics(svg_info->image,draw_info,&metrics);
              svg_info->bounds.x+=metrics.width;
              draw_info=DestroyDrawInfo(draw_info);
              *svg_info->text='\0';
            }
          (void) FormatLocaleFile(svg_info->file,"push graphic-context\n");
          break;
        }
      break;
    }
    default:
      break;
  }
  if (attributes != (const xmlChar **) NULL)
    for (i=0; (attributes[i] != (const xmlChar *) NULL); i+=2)
    {
      keyword=(const char *) attributes[i];
      value=(const char *) attributes[i+1];
      (void) LogMagickEvent(CoderEvent,GetMagickModule(),
        "    %s = %s",keyword,value);
      switch (*keyword)
      {
        case 'A':
        case 'a':
        {
          if (LocaleCompare(keyword,"angle") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"angle %g\n",
                GetUserSpaceCoordinateValue(svg_info,0,value));
              break;
            }
          break;
        }
        case 'C':
        case 'c':
        {
          if (LocaleCompare(keyword,"clip-path") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"clip-path '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"clip-rule") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"clip-rule '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"clipPathUnits") == 0)
            {
              (void) CloneString(&units,value);
              (void) FormatLocaleFile(svg_info->file,"clip-units '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"color") == 0)
            {
              (void) CloneString(&color,value);
              break;
            }
          if (LocaleCompare(keyword,"cx") == 0)
            {
              svg_info->element.cx=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"cy") == 0)
            {
              svg_info->element.cy=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'D':
        case 'd':
        {
          if (LocaleCompare(keyword,"d") == 0)
            {
              (void) CloneString(&svg_info->vertices,value);
              break;
            }
          if (LocaleCompare(keyword,"dx") == 0)
            {
              svg_info->bounds.x+=GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"dy") == 0)
            {
              svg_info->bounds.y+=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'F':
        case 'f':
        {
          if (LocaleCompare(keyword,"fill") == 0)
            {
              if (LocaleCompare(value,"currentColor") == 0)
                {
                  (void) FormatLocaleFile(svg_info->file,"fill '%s'\n",color);
                  break;
                }
              (void) FormatLocaleFile(svg_info->file,"fill '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"fillcolor") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"fill '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"fill-rule") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"fill-rule '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"fill-opacity") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"fill-opacity '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"font-family") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"font-family '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"font-stretch") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"font-stretch '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"font-style") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"font-style '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"font-size") == 0)
            {
              svg_info->pointsize=GetUserSpaceCoordinateValue(svg_info,0,value);
              (void) FormatLocaleFile(svg_info->file,"font-size %g\n",
                svg_info->pointsize);
              break;
            }
          if (LocaleCompare(keyword,"font-weight") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"font-weight '%s'\n",
                value);
              break;
            }
          break;
        }
        case 'G':
        case 'g':
        {
          if (LocaleCompare(keyword,"gradientTransform") == 0)
            {
              AffineMatrix
                affine,
                current,
                transform;

              GetAffineMatrix(&transform);
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),"  ");
              tokens=GetTransformTokens(context,value,&number_tokens);
              for (j=0; j < (number_tokens-1); j+=2)
              {
                keyword=(char *) tokens[j];
                if (keyword == (char *) NULL)
                  continue;
                value=(char *) tokens[j+1];
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                  "    %s: %s",keyword,value);
                current=transform;
                GetAffineMatrix(&affine);
                switch (*keyword)
                {
                  case 'M':
                  case 'm':
                  {
                    if (LocaleCompare(keyword,"matrix") == 0)
                      {
                        p=(const char *) value;
                        GetMagickToken(p,&p,token);
                        affine.sx=StringToDouble(value,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.rx=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.ry=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.sy=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.tx=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.ty=StringToDouble(token,(char **) NULL);
                        break;
                      }
                    break;
                  }
                  case 'R':
                  case 'r':
                  {
                    if (LocaleCompare(keyword,"rotate") == 0)
                      {
                        double
                          angle;

                        angle=GetUserSpaceCoordinateValue(svg_info,0,value);
                        affine.sx=cos(DegreesToRadians(fmod(angle,360.0)));
                        affine.rx=sin(DegreesToRadians(fmod(angle,360.0)));
                        affine.ry=(-sin(DegreesToRadians(fmod(angle,360.0))));
                        affine.sy=cos(DegreesToRadians(fmod(angle,360.0)));
                        break;
                      }
                    break;
                  }
                  case 'S':
                  case 's':
                  {
                    if (LocaleCompare(keyword,"scale") == 0)
                      {
                        for (p=(const char *) value; *p != '\0'; p++)
                          if ((isspace((int) ((unsigned char) *p)) != 0) ||
                              (*p == ','))
                            break;
                        affine.sx=GetUserSpaceCoordinateValue(svg_info,1,value);
                        affine.sy=affine.sx;
                        if (*p != '\0')
                          affine.sy=
                            GetUserSpaceCoordinateValue(svg_info,-1,p+1);
                        svg_info->scale[svg_info->n]=ExpandAffine(&affine);
                        break;
                      }
                    if (LocaleCompare(keyword,"skewX") == 0)
                      {
                        affine.sx=svg_info->affine.sx;
                        affine.ry=tan(DegreesToRadians(fmod(
                          GetUserSpaceCoordinateValue(svg_info,1,value),
                          360.0)));
                        affine.sy=svg_info->affine.sy;
                        break;
                      }
                    if (LocaleCompare(keyword,"skewY") == 0)
                      {
                        affine.sx=svg_info->affine.sx;
                        affine.rx=tan(DegreesToRadians(fmod(
                          GetUserSpaceCoordinateValue(svg_info,-1,value),
                          360.0)));
                        affine.sy=svg_info->affine.sy;
                        break;
                      }
                    break;
                  }
                  case 'T':
                  case 't':
                  {
                    if (LocaleCompare(keyword,"translate") == 0)
                      {
                        for (p=(const char *) value; *p != '\0'; p++)
                          if ((isspace((int) ((unsigned char) *p)) != 0) ||
                              (*p == ','))
                            break;
                        affine.tx=GetUserSpaceCoordinateValue(svg_info,1,value);
                        affine.ty=affine.tx;
                        if (*p != '\0')
                          affine.ty=
                            GetUserSpaceCoordinateValue(svg_info,-1,p+1);
                        break;
                      }
                    break;
                  }
                  default:
                    break;
                }
                transform.sx=affine.sx*current.sx+affine.ry*current.rx;
                transform.rx=affine.rx*current.sx+affine.sy*current.rx;
                transform.ry=affine.sx*current.ry+affine.ry*current.sy;
                transform.sy=affine.rx*current.ry+affine.sy*current.sy;
                transform.tx=affine.tx*current.sx+affine.ty*current.ry+
                  current.tx;
                transform.ty=affine.tx*current.rx+affine.ty*current.sy+
                  current.ty;
              }
              (void) FormatLocaleFile(svg_info->file,
                "affine %g %g %g %g %g %g\n",transform.sx,
                transform.rx,transform.ry,transform.sy,transform.tx,
                transform.ty);
              for (j=0; tokens[j] != (char *) NULL; j++)
                tokens[j]=DestroyString(tokens[j]);
              tokens=(char **) RelinquishMagickMemory(tokens);
              break;
            }
          if (LocaleCompare(keyword,"gradientUnits") == 0)
            {
              (void) CloneString(&units,value);
              (void) FormatLocaleFile(svg_info->file,"gradient-units '%s'\n",
                value);
              break;
            }
          break;
        }
        case 'H':
        case 'h':
        {
          if (LocaleCompare(keyword,"height") == 0)
            {
              svg_info->bounds.height=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          if (LocaleCompare(keyword,"href") == 0)
            {
              (void) CloneString(&svg_info->url,value);
              break;
            }
          break;
        }
        case 'M':
        case 'm':
        {
          if (LocaleCompare(keyword,"major") == 0)
            {
              svg_info->element.major=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"minor") == 0)
            {
              svg_info->element.minor=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'O':
        case 'o':
        {
          if (LocaleCompare(keyword,"offset") == 0)
            {
              (void) CloneString(&svg_info->offset,value);
              break;
            }
          if (LocaleCompare(keyword,"opacity") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"opacity '%s'\n",value);
              break;
            }
          break;
        }
        case 'P':
        case 'p':
        {
          if (LocaleCompare(keyword,"path") == 0)
            {
              (void) CloneString(&svg_info->url,value);
              break;
            }
          if (LocaleCompare(keyword,"points") == 0)
            {
              (void) CloneString(&svg_info->vertices,value);
              break;
            }
          break;
        }
        case 'R':
        case 'r':
        {
          if (LocaleCompare(keyword,"r") == 0)
            {
              svg_info->element.major=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              svg_info->element.minor=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          if (LocaleCompare(keyword,"rotate") == 0)
            {
              double
                angle;

              angle=GetUserSpaceCoordinateValue(svg_info,0,value);
              (void) FormatLocaleFile(svg_info->file,"translate %g,%g\n",
                svg_info->bounds.x,svg_info->bounds.y);
              svg_info->bounds.x=0;
              svg_info->bounds.y=0;
              (void) FormatLocaleFile(svg_info->file,"rotate %g\n",angle);
              break;
            }
          if (LocaleCompare(keyword,"rx") == 0)
            {
              if (LocaleCompare((const char *) name,"ellipse") == 0)
                svg_info->element.major=
                  GetUserSpaceCoordinateValue(svg_info,1,value);
              else
                svg_info->radius.x=
                  GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"ry") == 0)
            {
              if (LocaleCompare((const char *) name,"ellipse") == 0)
                svg_info->element.minor=
                  GetUserSpaceCoordinateValue(svg_info,-1,value);
              else
                svg_info->radius.y=
                  GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        case 'S':
        case 's':
        {
          if (LocaleCompare(keyword,"stop-color") == 0)
            {
              (void) CloneString(&svg_info->stop_color,value);
              break;
            }
          if (LocaleCompare(keyword,"stroke") == 0)
            {
              if (LocaleCompare(value,"currentColor") == 0)
                {
                  (void) FormatLocaleFile(svg_info->file,"stroke '%s'\n",color);
                  break;
                }
              (void) FormatLocaleFile(svg_info->file,"stroke '%s'\n",value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-antialiasing") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-antialias %d\n",
                LocaleCompare(value,"true") == 0);
              break;
            }
          if (LocaleCompare(keyword,"stroke-dasharray") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-dasharray %s\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-dashoffset") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-dashoffset %s\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-linecap") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-linecap '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-linejoin") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-linejoin '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-miterlimit") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-miterlimit '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-opacity") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-opacity '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"stroke-width") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"stroke-width %g\n",
                GetUserSpaceCoordinateValue(svg_info,1,value));
              break;
            }
          if (LocaleCompare(keyword,"style") == 0)
            {
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),"  ");
              tokens=GetStyleTokens(context,value,&number_tokens);
              for (j=0; j < (number_tokens-1); j+=2)
              {
                keyword=(char *) tokens[j];
                value=(char *) tokens[j+1];
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                  "    %s: %s",keyword,value);
                switch (*keyword)
                {
                  case 'C':
                  case 'c':
                  {
                     if (LocaleCompare(keyword,"clip-path") == 0)
                       {
                         (void) FormatLocaleFile(svg_info->file,
                           "clip-path '%s'\n",value);
                         break;
                       }
                    if (LocaleCompare(keyword,"clip-rule") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "clip-rule '%s'\n",value);
                        break;
                      }
                     if (LocaleCompare(keyword,"clipPathUnits") == 0)
                       {
                         (void) CloneString(&units,value);
                         (void) FormatLocaleFile(svg_info->file,
                          "clip-units '%s'\n",value);
                         break;
                       }
                    if (LocaleCompare(keyword,"color") == 0)
                      {
                        (void) CloneString(&color,value);
                        break;
                      }
                    break;
                  }
                  case 'F':
                  case 'f':
                  {
                    if (LocaleCompare(keyword,"fill") == 0)
                      {
                         if (LocaleCompare(value,"currentColor") == 0)
                           {
                             (void) FormatLocaleFile(svg_info->file,
                               "fill '%s'\n",color);
                             break;
                           }
                        if (LocaleCompare(value,"#00000000") == 0)
                          (void) FormatLocaleFile(svg_info->file,
                            "fill '#000000'\n");
                        else
                          (void) FormatLocaleFile(svg_info->file,"fill '%s'\n",
                            value);
                        break;
                      }
                    if (LocaleCompare(keyword,"fillcolor") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,"fill '%s'\n",
                          value);
                        break;
                      }
                    if (LocaleCompare(keyword,"fill-rule") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "fill-rule '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"fill-opacity") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "fill-opacity '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"font-family") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "font-family '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"font-stretch") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "font-stretch '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"font-style") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "font-style '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"font-size") == 0)
                      {
                        svg_info->pointsize=GetUserSpaceCoordinateValue(
                          svg_info,0,value);
                        (void) FormatLocaleFile(svg_info->file,"font-size %g\n",
                          svg_info->pointsize);
                        break;
                      }
                    if (LocaleCompare(keyword,"font-weight") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "font-weight '%s'\n",value);
                        break;
                      }
                    break;
                  }
                  case 'O':
                  case 'o':
                  {
                    if (LocaleCompare(keyword,"offset") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,"offset %g\n",
                          GetUserSpaceCoordinateValue(svg_info,1,value));
                        break;
                      }
                    if (LocaleCompare(keyword,"opacity") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "opacity '%s'\n",value);
                        break;
                      }
                    break;
                  }
                  case 'S':
                  case 's':
                  {
                    if (LocaleCompare(keyword,"stop-color") == 0)
                      {
                        (void) CloneString(&svg_info->stop_color,value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke") == 0)
                      {
                        if (LocaleCompare(value,"currentColor") == 0)
                          {
                            (void) FormatLocaleFile(svg_info->file,
                              "stroke '%s'\n",color);
                            break;
                          }
                        if (LocaleCompare(value,"#00000000") == 0)
                          (void) FormatLocaleFile(svg_info->file,
                            "fill '#000000'\n");
                        else
                          (void) FormatLocaleFile(svg_info->file,
                            "stroke '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-antialiasing") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-antialias %d\n",
                          LocaleCompare(value,"true") == 0);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-dasharray") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-dasharray %s\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-dashoffset") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-dashoffset %s\n",
                          value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-linecap") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-linecap '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-linejoin") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-linejoin '%s'\n",
                          value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-miterlimit") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-miterlimit '%s'\n",
                          value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-opacity") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-opacity '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"stroke-width") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "stroke-width %g\n",
                          GetUserSpaceCoordinateValue(svg_info,1,value));
                        break;
                      }
                    break;
                  }
                  case 't':
                  case 'T':
                  {
                    if (LocaleCompare(keyword,"text-align") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "text-align '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"text-anchor") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "text-anchor '%s'\n",value);
                        break;
                      }
                    if (LocaleCompare(keyword,"text-decoration") == 0)
                      {
                        if (LocaleCompare(value,"underline") == 0)
                          (void) FormatLocaleFile(svg_info->file,
                          "decorate underline\n");
                        if (LocaleCompare(value,"line-through") == 0)
                          (void) FormatLocaleFile(svg_info->file,
                          "decorate line-through\n");
                        if (LocaleCompare(value,"overline") == 0)
                          (void) FormatLocaleFile(svg_info->file,
                          "decorate overline\n");
                        break;
                      }
                    if (LocaleCompare(keyword,"text-antialiasing") == 0)
                      {
                        (void) FormatLocaleFile(svg_info->file,
                          "text-antialias %d\n",
                          LocaleCompare(value,"true") == 0);
                        break;
                      }
                    break;
                  }
                  default:
                    break;
                }
              }
              for (j=0; tokens[j] != (char *) NULL; j++)
                tokens[j]=DestroyString(tokens[j]);
              tokens=(char **) RelinquishMagickMemory(tokens);
              break;
            }
          break;
        }
        case 'T':
        case 't':
        {
          if (LocaleCompare(keyword,"text-align") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"text-align '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"text-anchor") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"text-anchor '%s'\n",
                value);
              break;
            }
          if (LocaleCompare(keyword,"text-decoration") == 0)
            {
              if (LocaleCompare(value,"underline") == 0)
                (void) FormatLocaleFile(svg_info->file,"decorate underline\n");
              if (LocaleCompare(value,"line-through") == 0)
                (void) FormatLocaleFile(svg_info->file,
                  "decorate line-through\n");
              if (LocaleCompare(value,"overline") == 0)
                (void) FormatLocaleFile(svg_info->file,"decorate overline\n");
              break;
            }
          if (LocaleCompare(keyword,"text-antialiasing") == 0)
            {
              (void) FormatLocaleFile(svg_info->file,"text-antialias %d\n",
                LocaleCompare(value,"true") == 0);
              break;
            }
          if (LocaleCompare(keyword,"transform") == 0)
            {
              AffineMatrix
                affine,
                current,
                transform;

              GetAffineMatrix(&transform);
              (void) LogMagickEvent(CoderEvent,GetMagickModule(),"  ");
              tokens=GetTransformTokens(context,value,&number_tokens);
              for (j=0; j < (number_tokens-1); j+=2)
              {
                keyword=(char *) tokens[j];
                value=(char *) tokens[j+1];
                (void) LogMagickEvent(CoderEvent,GetMagickModule(),
                  "    %s: %s",keyword,value);
                current=transform;
                GetAffineMatrix(&affine);
                switch (*keyword)
                {
                  case 'M':
                  case 'm':
                  {
                    if (LocaleCompare(keyword,"matrix") == 0)
                      {
                        p=(const char *) value;
                        GetMagickToken(p,&p,token);
                        affine.sx=StringToDouble(value,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.rx=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.ry=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.sy=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.tx=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        affine.ty=StringToDouble(token,(char **) NULL);
                        break;
                      }
                    break;
                  }
                  case 'R':
                  case 'r':
                  {
                    if (LocaleCompare(keyword,"rotate") == 0)
                      {
                        double
                          angle,
                          x,
                          y;

                        p=(const char *) value;
                        GetMagickToken(p,&p,token);
                        angle=StringToDouble(value,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        x=StringToDouble(token,(char **) NULL);
                        GetMagickToken(p,&p,token);
                        if (*token == ',')
                          GetMagickToken(p,&p,token);
                        y=StringToDouble(token,(char **) NULL);
                        affine.sx=cos(DegreesToRadians(fmod(angle,360.0)));
                        affine.rx=sin(DegreesToRadians(fmod(angle,360.0)));
                        affine.ry=(-sin(DegreesToRadians(fmod(angle,360.0))));
                        affine.sy=cos(DegreesToRadians(fmod(angle,360.0)));
                        affine.tx=x;
                        affine.ty=y;
                        svg_info->center.x=x;
                        svg_info->center.y=y;
                        break;
                      }
                    break;
                  }
                  case 'S':
                  case 's':
                  {
                    if (LocaleCompare(keyword,"scale") == 0)
                      {
                        for (p=(const char *) value; *p != '\0'; p++)
                          if ((isspace((int) ((unsigned char) *p)) != 0) ||
                              (*p == ','))
                            break;
                        affine.sx=GetUserSpaceCoordinateValue(svg_info,1,value);
                        affine.sy=affine.sx;
                        if (*p != '\0')
                          affine.sy=GetUserSpaceCoordinateValue(svg_info,-1,
                            p+1);
                        svg_info->scale[svg_info->n]=ExpandAffine(&affine);
                        break;
                      }
                    if (LocaleCompare(keyword,"skewX") == 0)
                      {
                        affine.sx=svg_info->affine.sx;
                        affine.ry=tan(DegreesToRadians(fmod(
                          GetUserSpaceCoordinateValue(svg_info,1,value),
                          360.0)));
                        affine.sy=svg_info->affine.sy;
                        break;
                      }
                    if (LocaleCompare(keyword,"skewY") == 0)
                      {
                        affine.sx=svg_info->affine.sx;
                        affine.rx=tan(DegreesToRadians(fmod(
                          GetUserSpaceCoordinateValue(svg_info,-1,value),
                          360.0)));
                        affine.sy=svg_info->affine.sy;
                        break;
                      }
                    break;
                  }
                  case 'T':
                  case 't':
                  {
                    if (LocaleCompare(keyword,"translate") == 0)
                      {
                        for (p=(const char *) value; *p != '\0'; p++)
                          if ((isspace((int) ((unsigned char) *p)) != 0) ||
                              (*p == ','))
                            break;
                        affine.tx=GetUserSpaceCoordinateValue(svg_info,1,value);
                        affine.ty=affine.tx;
                        if (*p != '\0')
                          affine.ty=GetUserSpaceCoordinateValue(svg_info,-1,
                            p+1);
                        break;
                      }
                    break;
                  }
                  default:
                    break;
                }
                transform.sx=affine.sx*current.sx+affine.ry*current.rx;
                transform.rx=affine.rx*current.sx+affine.sy*current.rx;
                transform.ry=affine.sx*current.ry+affine.ry*current.sy;
                transform.sy=affine.rx*current.ry+affine.sy*current.sy;
                transform.tx=affine.tx*current.sx+affine.ty*current.ry+
                  current.tx;
                transform.ty=affine.tx*current.rx+affine.ty*current.sy+
                  current.ty;
              }
              (void) FormatLocaleFile(svg_info->file,
                "affine %g %g %g %g %g %g\n",transform.sx,transform.rx,
                transform.ry,transform.sy,transform.tx,transform.ty);
              for (j=0; tokens[j] != (char *) NULL; j++)
                tokens[j]=DestroyString(tokens[j]);
              tokens=(char **) RelinquishMagickMemory(tokens);
              break;
            }
          break;
        }
        case 'V':
        case 'v':
        {
          if (LocaleCompare(keyword,"verts") == 0)
            {
              (void) CloneString(&svg_info->vertices,value);
              break;
            }
          if (LocaleCompare(keyword,"viewBox") == 0)
            {
              p=(const char *) value;
              GetMagickToken(p,&p,token);
              svg_info->view_box.x=StringToDouble(token,(char **) NULL);
              GetMagickToken(p,&p,token);
              if (*token == ',')
                GetMagickToken(p,&p,token);
              svg_info->view_box.y=StringToDouble(token,(char **) NULL);
              GetMagickToken(p,&p,token);
              if (*token == ',')
                GetMagickToken(p,&p,token);
              svg_info->view_box.width=StringToDouble(token,
                (char **) NULL);
              if (svg_info->bounds.width == 0)
                svg_info->bounds.width=svg_info->view_box.width;
              GetMagickToken(p,&p,token);
              if (*token == ',')
                GetMagickToken(p,&p,token);
              svg_info->view_box.height=StringToDouble(token,
                (char **) NULL);
              if (svg_info->bounds.height == 0)
                svg_info->bounds.height=svg_info->view_box.height;
              break;
            }
          break;
        }
        case 'W':
        case 'w':
        {
          if (LocaleCompare(keyword,"width") == 0)
            {
              svg_info->bounds.width=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          break;
        }
        case 'X':
        case 'x':
        {
          if (LocaleCompare(keyword,"x") == 0)
            {
              svg_info->bounds.x=GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"xlink:href") == 0)
            {
              (void) CloneString(&svg_info->url,value);
              break;
            }
          if (LocaleCompare(keyword,"x1") == 0)
            {
              svg_info->segment.x1=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          if (LocaleCompare(keyword,"x2") == 0)
            {
              svg_info->segment.x2=
                GetUserSpaceCoordinateValue(svg_info,1,value);
              break;
            }
          break;
        }
        case 'Y':
        case 'y':
        {
          if (LocaleCompare(keyword,"y") == 0)
            {
              svg_info->bounds.y=GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          if (LocaleCompare(keyword,"y1") == 0)
            {
              svg_info->segment.y1=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          if (LocaleCompare(keyword,"y2") == 0)
            {
              svg_info->segment.y2=
                GetUserSpaceCoordinateValue(svg_info,-1,value);
              break;
            }
          break;
        }
        default:
          break;
      }
    }
  if (LocaleCompare((const char *) name,"svg") == 0)
    {
      if (svg_info->document->encoding != (const xmlChar *) NULL)
        (void) FormatLocaleFile(svg_info->file,"encoding \"%s\"\n",
          (const char *) svg_info->document->encoding);
      if (attributes != (const xmlChar **) NULL)
        {
          double
            sx,
            sy,
            tx,
            ty;

          if ((svg_info->view_box.width == 0.0) ||
              (svg_info->view_box.height == 0.0))
            svg_info->view_box=svg_info->bounds;
          svg_info->width=(size_t) floor(svg_info->bounds.width+0.5);
          svg_info->height=(size_t) floor(svg_info->bounds.height+0.5);
          (void) FormatLocaleFile(svg_info->file,"viewbox 0 0 %.20g %.20g\n",
            (double) svg_info->width,(double) svg_info->height);
          sx=(double) svg_info->width/svg_info->view_box.width;
          sy=(double) svg_info->height/svg_info->view_box.height;
          tx=svg_info->view_box.x != 0.0 ? (double) -sx*svg_info->view_box.x :
            0.0;
          ty=svg_info->view_box.y != 0.0 ? (double) -sy*svg_info->view_box.y :
            0.0;
          (void) FormatLocaleFile(svg_info->file,"affine %g 0 0 %g %g %g\n",
            sx,sy,tx,ty);
        }
    }
  (void) LogMagickEvent(CoderEvent,GetMagickModule(),"  )");
  units=DestroyString(units);
  if (color != (char *) NULL)
    color=DestroyString(color);
}
