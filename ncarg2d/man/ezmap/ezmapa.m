.TH Ezmap 3NCARG "March 1993" UNIX "NCAR GRAPHICS"
.na
.nh
.SH NAME
Ezmap - Allows one to plot maps of the earth according 
to any of ten different
projections, with parallels, meridians, 
and continental, international,
and/or U.S. state outlines. 
.sp
Ezmapa was the name of a supplement to the Ezmap utility that
allowed users to produce solid-filled maps of the earth. All
Ezmapa routines are now organized under the Ezmap utility.
.SH SYNOPSIS
.IP "Routines Used to Draw a Simple Map" 
.sp
To draw a simple map (one not involving solid fill of areas), 
as directed
by the current values of Ezmap's internal parameters, one need only
execute the single FORTRAN 
statement "CALL MAPDRW". Thus, the principal
Ezmap routine is this:
.RS 
.IP "\(bu" 4
MAPDRW - Draws a complete simple map.
.RE
.IP ""
All that MAPDRW does is call four lower-level routines. In some
situations, the user may wish to call these routines directly; they are
as follows (in the order in which they are called by MAPDRW):
.RS
.IP "\(bu" 4
MAPINT - Initializes. MAPINT must be called at least once before calling
any routine that depends on mapping lat/lon coordinates into u/v
coordinates. After one or more of MAPPOS, MAPROJ, and MAPSET has been
called, MAPINT must be called again.
.IP "\(bu" 4
MAPGRD - Draws selected parallels and meridians.
.IP "\(bu" 4
MAPLBL - Labels the international date line, the equator, the Greenwich
meridian, and the poles, and draws the perimeter.
.IP "\(bu" 4
MAPLOT - Draws selected geographic outlines.
.RE
.IP "Routines Used to Change the Values of Internal Parameters"
.sp
The following routines are called to change the values of internal
parameters of Ezmap, and thus change the behavior of other Ezmap
routines:
.RS
.IP "\(bu" 4
MAPPOS - Determines what portion of the plotter frame is to be used.
.IP "\(bu" 4
MAPROJ - Determines the projection to be used.
.IP "\(bu" 4
MAPSET - Determines what portion of the u/v plane is to be viewed.
.IP "\(bu" 4
MAPSTC - Sets a parameter value of type CHARACTER.
.IP "\(bu" 4
MAPSTI - Sets a parameter value of type INTEGER.
.IP "\(bu" 4
MAPSTL - Sets a parameter value of type LOGICAL.
.IP "\(bu" 4
MAPSTR - Sets a parameter value of type REAL.
.RE
.IP "Routines Used to Retrieve the Values of Internal Parameters"
.sp
The following routines are used to retrieve the current values of Ezmap
parameters:
.RS
.IP "\(bu" 4
MAPGTC - Gets a parameter value of type CHARACTER.
.IP "\(bu" 4
MAPGTI - Gets a parameter value of type INTEGER.
.IP "\(bu" 4
MAPGTL - Gets a parameter value of type LOGICAL.
.IP "\(bu" 4
MAPGTR - Gets a parameter value of type REAL.
.RE
.IP "Routines Used to Save and Restore Internal Parameters"
.sp
To save/restore the current values of the internal parameters of Ezmap,
use the following:
.RS
.IP "\(bu" 4
MAPSAV - Saves the values (by writing a record on a user-specified unit).
.IP "\(bu" 4
MAPRST - Restores saved values (by reading a record from a user-specified
unit).
.RE
.IP "Routines Used to Draw Objects on a Map"
.sp
To draw objects on the map, use the following routines:
.RS
.IP "\(bu" 4
MAPTRA - Computes the u/v coordinates of a point from its latitude and
longitude. If the point is unprojectable or its projection lies outside
the current perimeter, a special value is returned to signal this.
.IP "\(bu" 4
MAPTRN - Computes the u/v coordinates of a point from its latitude and
longitude. If the point is unprojectable, a special value is returned to
signal this, but no check is made for the projected value being outside
the perimeter.
.IP "\(bu" 4
MAPFST - Does a "pen-up" move defining the start of a line to be
projected and drawn. The line is defined by a series of lat/lon
coordinates.
.IP "\(bu" 4
MAPVEC - Does a "pen-down" move defining the continuation of a line to be
projected and drawn. The line is defined by a series of lat/lon
coordinates.
.IP "\(bu" 4
MAPIT - Does "pen-up" or "pen-down" moves. This routine is called by
MAPFST and MAPVEC.
.IP "\(bu" 4
MAPIQ - Signals the end of a string of calls to MAPIT and causes its
buffers to be flushed.
.RE
.IP "Routines Used to Do Inverse Transformations"
.sp
The following routine was added to Ezmap early in 1992:
.RS
.IP "\(bu" 4
MAPTRI - Computes the latitude and longitude of a point from its u/v
coordinates. If the point is outside the boundary of the map, a special
value is returned.
.RE
.IP ""
The example named "mpex10" shows one of the ways in which this routine
may be used; it draws what is essentially a colored contour plot of a
data field defined on the surface of the globe, using an orthographic
projection.
.IP "Routines Used to Draw Solid-Filled Maps (Ezmapa)"
.sp
In late 1986 or early 1987, a package of routines was written allowing a
user to draw solid-filled maps of the globe. This package was named
Ezmapa and was first advertised in the NCAR Graphics User's Guide
(Version 2.00), published in August, 1987. Conceptually, the routines in
this package are really part of Ezmap; they use the same common blocks
and many of the same underlying low-level routines and they are affected
by the same set of internal parameters as the routines in Ezmap proper.
The routines of Ezmapa will be described in this document; to use them
effectively, it will be necessary to understand also the package AREAS,
which is described in a separate document. The Ezmapa routines are as
follows:
.RS
.IP "\(bu" 4
MAPBLA - Adds boundary lines to an existing area map. Routines in the
package AREAS may then be used to process that area map in various ways.
(Example: drawing a map of Europe with each country in a different
color.)
.IP "\(bu" 4
MAPGRM - Draws lines of latitude and longitude "masked" by an existing
area map. (Example: drawing these lines over water, but not over land.)
.IP "\(bu" 4
MAPITA and MAPIQA - Adds to an area map the projections of arbitrary
lines defined by lat/lon coordinates of points on the surface of the
globe. MAPBLA uses these routines to add boundary lines to an area map;
they may be called directly by the user to add his/her own set of
boundary lines to the area map.
.IP "\(bu" 4
MAPITM and MAPIQM - Draws, masked by an area map, the projections of
arbitrary lines defined by lat/lon coordinates of points on the surface
of the globe. MAPGRM uses these routines to draw masked lines of latitude
and longitude; they may be called directly by the user to draw other
masked lines.
.IP "\(bu" 4
MAPACI - A function which, given the "area identifier" for a particular
area defined by the boundaries in one of the Ezmap outline datasets,
returns a suggested color index for that area; it is guaranteed that, if
the suggested color indices are used, no two areas having a boundary in
common will have the same color.
.RE
.IP "Miscellaneous Other Routines"
.sp
The following Ezmap routines are used for the purposes stated:
.RS
.IP "\(bu" 4
MAPRS - Re-executes the "CALL SET" done during the last call to MAPINT.
This is useful when there has been an intervening call to a utility that
calls SET. It is quite common for a background drawn by Ezmap to be
placed in a flash buffer (as created by the package "GFLASH"). When the
contents of the flash buffer are copied to the metafile being created, if
it is desired to draw something on the Ezmap background, MAPRS may first
have to be called to ensure that the correct SET call is in effect.
.IP "\(bu" 4
MAPUSR - This routine is called by various Ezmap routines just before and
just after drawing parts of the map. By default, grid lines are drawn
using software dashed lines and geographical outlines are drawn using
either solid lines or dotted lines. The dash pattern used for the grid
lines, the flag which says whether outlines are solid or dotted, and the
color indices of various parts of the map are all user-settable
parameters, but more complete control of color indices, spot size, dash
pattern, etc., may be achieved by supplying one's own version of MAPUSR;
a user version may be as complicated as is required to achieve a desired
effect.
.IP "\(bu" 4
MAPEOD - This routine is called by the Ezmap routine MAPLOT and the
Ezmap routine MAPBLA; in each case, it is called once for each segment
in the outline dataset. The user may supply a version which examines the
segment to see if it ought to be plotted and, if not, to delete it. This
can be used (for example) to reduce the clutter in northern Canada.
.IP "\(bu" 4
SUPMAP - This is the routine from which Ezmap grew. A version of SUPMAP
is implemented within it and allows one to draw a complete map with a
single, rather lengthy, call. The routine SUPCON, which is the old
analogue of MAPTRN, is also implemented.
.SH C-BINDING SYNOPSIS
#include <ncarg/ncargC.h>
.sp
c_mapdrw
.br
c_mapfst
.br
c_mapgrd
.br
c_mapgtc
.br
c_mapgti
.br
c_mapgtl
.br
c_mapgtr
.br
c_mapint
.br
c_mapiq
.br
c_mapit
.br
c_maplbl
.br
c_maplot
.br
c_mappos
.br
c_maproj
.br
c_maprs
.br
c_maprst
.br
c_mapsav
.br
c_mapset
.br
c_mapstc
.br
c_mapsti
.br
c_mapstl
.br
c_mapstr
.br
c_maptrn
.br
c_mapusr
.br
c_mapvec
.br
c_supmap
.SH USER-MODIFIABLE INTERNAL ROUTINES
MAPEOD
.br
MAPUSR
.SH ACCESS 
To use Ezmap routines, load the NCAR Graphics libraries ncarg,
ncarg_gks, and ncarg_c, preferably in that order.  To use the 
C-bindings, load the NCAR Graphics libraries ncargC, ncarg_gksC, ncarg,
ncarg_gks, and ncarg_c, preferably in that order.
.SH MESSAGES
Possible error-flag values are as shown in the following table:
.RS 4
.IP "Error" 8
Associated error message
.IP "1" 8
MAPGTC - UNKNOWN PARAMETER NAME xx
.IP "2" 8
MAPGTI - UNKNOWN PARAMETER NAME xx
.IP "3" 8
MAPGTL - UNKNOWN PARAMETER NAME xx
.IP "4" 8
MAPGTR - UNKNOWN PARAMETER NAME xx
.IP "5" 8
MAPINT - ATTEMPT TO USE NON-EXISTENT PROJECTION
.IP "6" 8
MAPINT - ANGULAR LIMITS TOO GREAT
.IP "7" 8
MAPINT - MAP HAS ZERO AREA
.IP "8" 8
MAP LIMITS INAPPROPRIATE
.IP "9" 8
MAPROJ - UNKNOWN PROJECTION NAME xx
.IP "10" 8
MAPSET - UNKNOWN MAP AREA SPECIFIER xx
.IP "11" 8
MAPSTC - UNKNOWN OUTLINE NAME xx
.IP "12" 8
MAPSTC - UNKNOWN PARAMETER NAME xx
.IP "13" 8
MAPSTI - UNKNOWN PARAMETER NAME xx
.IP "14" 8
MAPSTL - UNKNOWN PARAMETER NAME xx
.IP "15" 8
MAPSTR - UNKNOWN PARAMETER NAME xx
.IP "16" 8
MAPTRN - ATTEMPT TO USE NON-EXISTENT PROJECTION
.IP "17" 8
MAPIO - OUTLINE DATASET IS UNREADABLE
.IP "18" 8
MAPIO - EOF ENCOUNTERED IN OUTLINE DATASET
.IP "19" 8
MAPPOS - ARGUMENTS ARE INCORRECT
.IP "20" 8
MAPRST - ERROR ON READ
.IP "21" 8
MAPRST - EOF ON READ
.IP "22" 8
MAPSAV - ERROR ON WRITE
.RE
.SH SEE ALSO
Online:
ezmap_params,
mapaci,
mapbla,
mapblm,
mapdrw,
mapeod,
mapfst,
mapgci,
mapgrd,
mapgrm,
mapgtc,
mapgti,
mapgtl,
mapgtr,
mapint,
mapiq,
mapiqa,
mapiqm,
mapit,
mapita,
mapitm,
maplbl,
maplmb,
maplot,
mappos,
maproj,
maprs,
maprst,
mapsav,
mapset,
mapstc,
mapsti,
mapstl,
mapstr,
maptra,
maptri,
maptrn,
mapusr,
mapvec,
mpgetc,
mpgeti,
mpgetl,
mpgetr,
mpsetc,
mpseti,
mpsetl,
mpsetr,
supmap,
supcon,
ncarg_cbind
.sp
Hardcopy: 
NCAR Graphics Contouring and Mapping Tutorial 
.SH COPYRIGHT
Copyright (C) 1987-1996
.br
University Corporation for Atmospheric Research
.br
The use of this Software is governed by a License Agreement.
