// WARNING: this file is not under the GNU General Public License.
// It may be distributed and used with SeldonData however.
// The original file has been modified with the agreement of its author,
// Bob Dattore (see below), but questions about this modified version
// must *not* be sent to him.

/*
** File: unpackgrib.c
**
** Author:  Bob Dattore
**          NCAR/DSS
**          dattore@ucar.edu
**          (303) 497-1825
**
** Revisions:
**          21 Feb 01 - modified unpackIS to search for next GRIB message in
**                      files where the GRIB messages are not contiguous
**          22 Feb 01 - modified routine to handle grids with data
**                      representation of 10
**          26 Feb 01 - modified to run under Linux - added byteSwap routine to
**                      handle byte-swapping
**
** Purpose: to provide a single C-routine for unpacking GRIB grids
**
** Notes:   1) There are several routines defined in this file, any of which can
**             be called independently.  However, to unpack a GRIB record with
**             one function call, use only "unpackgrib".
**
**          2) The user is expected to have some understanding of the GRIB
**             format, as some of the information consists of codes, etc. that
**             are defined by the GRIB format.  You can find a description of
**             the GRIB format at http://www.scd.ucar.edu/dss/docs/gribdoc, or
**             you can get it by anonymous FTP at ncardata.ucar.edu, under
**             "datasets/ds083.0".
**
**          3) These routines have been tested on a Sun running Solaris, an SGI
**             running IRIX, and a PC running Linux - please report any problems
**             to dattore@ucar.edu.
**
**          4) As of this version, these routines unpack the following types of
**             grids:
**
**             Latitude/Longitude (data representation = 0)
**             Gaussian Latitude/Longitude (data representation = 4)
**             Polar Stereographic (data representation = 5)
**             Rotated Latitude/Longitude (data representation = 10)
**
**             please contact dattore@ucar.edu to get a grid type added
**
**
** example C syntax for using unpackgrib:
**    FILE *fp;
**    GRIBRecord grib_record;
**    int status;
**
**    ** initializations, which need to be done only once **
**    grib_record.buffer=NULL;
**    grib_record.pds_ext=NULL;
**    grib_record.gridpoints=NULL;
** 
**    fp=fopen("my_GRIB_file","r");
**    while ( (status=unpackgrib(fp,&grib_record)) == 0) {
**      if (status == -1)
**        printf("Found EOF\n");
**      else if (status == 1)
**        printf("Error reading GRIB record\n");
**
**      ...
**
**    }
** 
** where:
**   fp            is a FILE pointer to an open GRIB data file
**   GRIBRecord    is a structure used to hold the data in a GRIB record
**
** On return:
**   unpackgrib returns 0 for a successful read, -1 for an EOF, and 1 for a read
**   error
**
** 
** Overview of GRIBRecord:
**   total_len:     Total length of the GRIB record, in octets (8-bit bytes)
**   pds_len:       Length in octets of the Product Definition Section (PDS)
**   pds_ext_len:   Length in octets of any extension to the PDS
**   gds_len:       Length in octets of the Grid Definition Section (GDS)
**   bds_len:       Length in octets of the Binary Data Section (BDS)
**   ed_num:        GRIB Edition number
**   table_ver:     GRIB Parameter Table version
**   center_id:     Center ID
**   gen_proc:      Generating Process ID number
**   grid_type:     Grid Identification
**   param:         GRIB Parameter code
**   level_type:    Level Type Code
**   lvl1:          Value for First Level
**   lvl2:          Value for Second Level (or 0)
**   fcst_units:    Forecast Time Unit
**   p1:            P1 (or 0)
**   p2:            P2 (or 0)
**   t_range:       Time Range Indicator
**   navg:          Number included in Average (or 0)
**   nmiss:         Number of Missing Grids in Average
**   sub_center_id: Sub-center ID
**   bds_flag:      Binary Data Section flag
**   pack_width:    Width in bits of a packed data point
**   gds_included:  Indication of GDS (0 = no GDS; 1 = GDS in GRIB record)
**   bms_included:  Indication of Bitmap Section (BMS)
**                    (0 = no BMS; 1 = BMS in GRIB record)
**   yr:            Year (4-digits - YYYY)
**   mo:            Month
**   dy:            Day
**   time:          Time (HHMM - HH=hour, MM=minutes)
**   offset:        For Internal Use Only (offset in bytes to next GRIB section
**                    from the beginning of current section)
**   D:             Decimal scale factor
**   data_rep:      Data representation type
** 
**   For Latitude/Longitude and Gaussian Lat/Lon Grids:
**     nx:         Number of points along a latitude circle
**     ny:         Number of points along a longitude meridian
**     slat:       Latitude of the first gridpoint
**     slon:       Longitude of the first gridpoint
**     rescomp:    Resolution and component flags
**     elat:       Latitude of the last gridpoint
**     elon:       Longitude of the last gridpoint
**     lainc:      Latitude increment (*1000) for Lat/Lon grid
**                 -OR-
**                 Number of latitude circles between equator and pole for
**                   Gaussian Lat/Lon grid
**     loinc:      Longitude increment (*1000)
**     scan_mode:  Scanning mode flags
**
**   For Polar Stereographic Grids:
**     nx:         Number of points in the X-direction
**     ny:         Number of points in the Y-direction
**     slat:       Latitude of the first gridpoint (*1000)
**     slon:       Longitude of the first gridpoint (*1000)
**     rescomp:    Resolution and component flags
**     olon:       Longitude of grid orientation (*1000)
**     xlen:       X-direction grid length in meters
**     ylen:       Y-direction grid length in meters
**     proj:       Projection center flag
**     scan_mode:  Scanning mode flags
** 
** 
**   buffer:        For Internal Use Only (used to hold the GRIB record that was
**                    read from the GRIB data file)
**   pds_ext:       This array is free-form and contains any 8-bit values that
**                    were found after the end of the standard PDS, but before
**                    the beginning of the next GRIB seciton.
**   ref_val:       GRIB Reference Value
**   gridpoints:    Two-dimensional array of gridpoints with dimensions [ny][nx]
**   ngy:           For Internal Use Only (used to keep track of the first
**                    dimension of gridpoints so that memory used by the array
**                    can be freed properly)
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

const double GRIB_MISSING_VALUE=1.e30;
typedef struct {
  size_t total_len,pds_len,pds_ext_len,gds_len,bds_len;
  size_t ed_num,table_ver,center_id,gen_proc,grid_type,param,level_type,lvl1,
    lvl2,fcst_units,p1,p2,t_range,navg,nmiss,sub_center_id,bds_flag,pack_width;
  size_t gds_included,bms_included;
  size_t yr,mo,dy,time;
  size_t offset;  /* offset in bytes to next GRIB section */
  int D;
  size_t data_rep,nx,ny,rescomp,scan_mode,proj;
  double slat,slon,elat,elon,lainc,loinc,olon;
  size_t xlen,ylen;
  unsigned char *buffer,*pds_ext;
  double ref_val,*gridpoints;
  size_t ngy;
} GRIBRecord;

/* getBits gets the contents of the various GRIB octets
**   buf is the GRIB buffer
**   loc is the variable to hold the octet contents
**   off is the offset in BITS from the beginning of the buffer to the beginning
**       of the octet(s) to be unpacked
**   bits is the number of BITS to unpack - will be a multiple of 8 since GRIB
**        octets are 8 bits long
*/
void getBits(size_t *buf,int *loc,size_t off,size_t bits)
{
  size_t mask=0;
  size_t size=sizeof(size_t)*8,wskip;
  int rshift;
  size_t n;

  /* no work to do */
  if (bits == 0)
    return;

  /* create a mask to use when right-shifting (necessary because different
     compilers do different things when right-shifting a signed bit-field) */
  mask=1;
  for (n=1; n < size; n++) {
    mask<<=1;
    mask++;
  }

  if (bits > size) {
    fprintf(stderr,"Error: unpacking %d bits into a %d-bit field\n",bits,size);
    exit(1);
  }
  else {
    /* get number of words to skip before unpacking begins */
    wskip=off/size;
    /* right shift the bits in the packed buffer word to eliminate unneeded bits */
    rshift=size-(off % size)-bits;
    /* check for a packed field spanning two words */
    if (rshift < 0) {
      *loc=(buf[wskip]<<-rshift);
      *loc+=(buf[++wskip]>>(size+rshift))&~(mask<<-rshift);
    }
    else
      *loc=(buf[wskip]>>rshift);
    /* remove any unneeded leading bits */
    if (bits != size) *loc&=~(mask<<bits);
  }
}

/* most machines are big-endian, meaning that the most significant byte in a
** word comes first, but VAXs and PCs are little-endian, so the bytes in each
** word need to be swapped before unpacking of the octets can be done
*/
void byteSwap(unsigned char *buf,size_t num_chars,size_t word_len)
{
  size_t n;
  unsigned char temp;

  for (n=0; n < num_chars; n+=word_len) {
    temp=buf[n];
    buf[n]=buf[n+3];
    buf[n+3]=temp;
    temp=buf[n+1];
    buf[n+1]=buf[n+2];
    buf[n+2]=temp;
  }
}

double ibm2real(size_t *buf,size_t off)
{
  int sign,exp,fr;
  double native_real;

  getBits(buf,&sign,off,1);
  getBits(buf,&exp,off+1,7);
  exp-=64;
  getBits(buf,&fr,off+8,24);
  native_real=pow(2.,-24.)*(double)fr*pow(16.,(double)exp);

  return (sign == 1) ? -native_real : native_real;
}

int unpackIS(FILE *fp,GRIBRecord *grib_rec)
{
  unsigned char temp[8];
  int status;
  size_t n,num;

  if (grib_rec->buffer != NULL)
    free(grib_rec->buffer);
  if ( (status=fread(temp,1,4,fp)) != 4) {
    if (status == 0)
      return -1;
    else
      return 1;
  }

  /* search for the beginning of the next GRIB message */
  if (strncmp((char *)temp,"GRIB",4) != 0) {
    while (temp[0] != 0x47 || temp[1] != 0x52 || temp[2] != 0x49 || temp[3] !=
           0x42) {
      switch (temp[1]) {
      case 0x47:
	for (n=0; n < 3; n++)
	  temp[n]=temp[n+1];
	if ( (status=fread(&temp[3],1,1,fp)) == 0)
	  return -1;
	break;
      default:
	switch(temp[2]) {
	case 0x47:
	  for (n=0; n < 2; n++)
	    temp[n]=temp[n+2];
	  if ( (status=fread(&temp[2],1,2,fp)) == 0)
	    return -1;
	  break;
	default:
	  switch(temp[3]) {
	  case 0x47:
	    temp[0]=temp[3];
	    if ( (status=fread(&temp[1],1,3,fp)) == 0)
	      return -1;
	    break;
	  default:
	    if ( (status=fread(temp,1,4,fp)) == 0)
	      return -1;
	  }
	}
      }
    }
  }

  if ( (status=fread(&temp[4],1,4,fp)) == 0)
    return 1;
#ifdef linux
  byteSwap(&temp[4],4,4);
#endif
  getBits((size_t *)temp,(int *)&grib_rec->total_len,32,24);
  if (grib_rec->total_len == 24) {
    grib_rec->ed_num=0;
    grib_rec->pds_len=grib_rec->total_len;

    /* add the four bytes for 'GRIB' + 3 bytes for the length of the section
    ** following the PDS */
    grib_rec->total_len+=7;
  }
  else
    grib_rec->ed_num=1;

  grib_rec->nx=grib_rec->ny=0;
  grib_rec->buffer=(unsigned char *)malloc(grib_rec->total_len+4);
  memcpy(grib_rec->buffer,temp,8);
  num=grib_rec->total_len-8;
  status=fread(&grib_rec->buffer[8],1,num,fp);
  if (size_t(status) != num)
    return 1;
  else {
    if (strncmp(&((char *)grib_rec->buffer)[grib_rec->total_len-4],"7777",4) != 0)
      fprintf(stderr,"Warning: no end section found\n");
#ifdef linux
    byteSwap(&grib_rec->buffer[8],num,4);
#endif
    return 0;
  }
}

void unpackPDS(GRIBRecord *grib_rec)
{
  size_t n;
  int flag,min,cent,sign;
  size_t *buf=(size_t *)grib_rec->buffer;
  char *c_buf=(char *)grib_rec->buffer;

  if (grib_rec->ed_num == 0)
    grib_rec->offset=32;
  else {
    grib_rec->offset=64;
    /* length of PDS */
    getBits(buf,(int *)&grib_rec->pds_len,grib_rec->offset,24);
    /* table version */
    getBits(buf,(int *)&grib_rec->table_ver,grib_rec->offset+24,8);
  }
  /* center ID */
  getBits(buf,(int *)&grib_rec->center_id,grib_rec->offset+32,8);
  /* generating process */
  getBits(buf,(int *)&grib_rec->gen_proc,grib_rec->offset+40,8);
  /* grid type */
  getBits(buf,(int *)&grib_rec->grid_type,grib_rec->offset+48,8);
  getBits(buf,&flag,grib_rec->offset+56,8);
  /* indication of GDS */
  grib_rec->gds_included= ( (flag & 0x80) == 0x80) ? 1 : 0;
  /* indication of BMS */
  grib_rec->bms_included= ( (flag & 0x40) == 0x40) ? 1 : 0;
  /* parameter code */
  getBits(buf,(int *)&grib_rec->param,grib_rec->offset+64,8);
  /* level type */
  getBits(buf,(int *)&grib_rec->level_type,grib_rec->offset+72,8);
  switch (grib_rec->level_type) {
  case 100:
  case 103:
  case 105:
  case 107:
  case 109:
  case 111:
  case 113:
  case 115:
  case 125:
  case 160:
  case 200:
  case 201:
    /* first level */
    getBits(buf,(int *)&grib_rec->lvl1,grib_rec->offset+80,16);
    grib_rec->lvl2=0;
    break;
  default:
    /* first level */
    getBits(buf,(int *)&grib_rec->lvl1,grib_rec->offset+80,8);
    /* second level */
    getBits(buf,(int *)&grib_rec->lvl2,grib_rec->offset+88,8);
  }
  /* year of the century */
  getBits(buf,(int *)&grib_rec->yr,grib_rec->offset+96,8);
  /* month */
  getBits(buf,(int *)&grib_rec->mo,grib_rec->offset+104,8);
  /* day */
  getBits(buf,(int *)&grib_rec->dy,grib_rec->offset+112,8);
  /* hour */
  getBits(buf,(int *)&grib_rec->time,grib_rec->offset+120,8);
  /* minutes */
  getBits(buf,&min,grib_rec->offset+128,8);
  /* complete time */
  grib_rec->time=grib_rec->time*100+min;
  /* forecast time units */
  getBits(buf,(int *)&grib_rec->fcst_units,grib_rec->offset+136,8);
  /* P1 */
  getBits(buf,(int *)&grib_rec->p1,grib_rec->offset+144,8);
  /* P2 */
  getBits(buf,(int *)&grib_rec->p2,grib_rec->offset+152,8);
  /* time range indicator*/
  getBits(buf,(int *)&grib_rec->t_range,grib_rec->offset+160,8);
  switch (grib_rec->p2) {
  case 3:
  case 4:
  case 51:
  case 113:
  case 114:
  case 115:
  case 116:
  case 117:
  case 123:
  case 124:
    /* number in average */
    getBits(buf,(int *)&grib_rec->navg,grib_rec->offset+168,16);
    break;
  default:
    /* number in average */
    grib_rec->navg=0;
  }
  /* missing grids in average */
  getBits(buf,(int *)&grib_rec->nmiss,grib_rec->offset+184,8);

  /* if GRIB0, done with PDS */
  if (grib_rec->ed_num == 0) {
    grib_rec->pds_ext_len=0;
    grib_rec->offset+=192;
    return;
  }

  getBits(buf,&cent,grib_rec->offset+192,8);  /* century */
  grib_rec->yr+=(cent-1)*100;
  /* sub-center ID */
  getBits(buf,(int *)&grib_rec->sub_center_id,grib_rec->offset+200,8);
  getBits(buf,&sign,grib_rec->offset+208,1);
  /* decimal scale factor */
  getBits(buf,&grib_rec->D,grib_rec->offset+209,15);
  if (sign == 1)
    grib_rec->D=-grib_rec->D;

  grib_rec->offset+=224;
  if (grib_rec->pds_len > 28) {
    if (grib_rec->pds_ext != NULL) {
      free(grib_rec->pds_ext);
      grib_rec->pds_ext=NULL;
    }
    if (grib_rec->pds_len < 40) {
      fprintf(stderr,"Warning: PDS extension is in wrong location\n");
      grib_rec->pds_ext_len=grib_rec->pds_len-28;
      grib_rec->pds_ext=(unsigned char *)malloc(grib_rec->pds_ext_len);
      for (n=0; n < grib_rec->pds_ext_len; n++)
	grib_rec->pds_ext[n]=c_buf[36+n];
      grib_rec->offset+=grib_rec->pds_ext_len*8;
    }
    else {
      grib_rec->pds_ext_len=grib_rec->pds_len-40;
      grib_rec->pds_ext=(unsigned char *)malloc(grib_rec->pds_ext_len);
      for (n=0; n < grib_rec->pds_ext_len; n++)
	grib_rec->pds_ext[n]=c_buf[48+n];
      grib_rec->offset+=(grib_rec->pds_ext_len+12)*8;
    }
  }
  else
    grib_rec->pds_ext_len=0;
}

void unpackGDS(GRIBRecord *grib_rec)
{
  int sign,dum;
  size_t *buf=(size_t *)grib_rec->buffer;

  /* length of the GDS */
  getBits(buf,(int *)&grib_rec->gds_len,grib_rec->offset,24);

  if (grib_rec->ed_num == 0)
    grib_rec->total_len+=grib_rec->gds_len;
  /* data representation type */
  getBits(buf,(int *)&grib_rec->data_rep,grib_rec->offset+40,8);
  switch (grib_rec->data_rep) {
    /* Latitude/Longitude grid */
  case 0:
    /* Gaussian Lat/Lon grid */
  case 4:
    /* Rotated Lat/Lon grid */
  case 10:
    /* number of latitudes */
    getBits(buf,(int *)&grib_rec->nx,grib_rec->offset+48,16);
    /* number of longitudes */
    getBits(buf,(int *)&grib_rec->ny,grib_rec->offset+64,16);
    getBits(buf,&sign,grib_rec->offset+80,1);
    getBits(buf,&dum,grib_rec->offset+81,23);
    /* latitude of first gridpoint */
    grib_rec->slat=dum*0.001;
    if (sign == 1)
      grib_rec->slat=-grib_rec->slat;
    getBits(buf,&sign,grib_rec->offset+104,1);
    getBits(buf,&dum,grib_rec->offset+105,23);
    /* longitude of first gridpoint */
    grib_rec->slon=dum*0.001;
    if (sign == 1)
      grib_rec->slon=-grib_rec->slon;
    /* resolution and component flags */
    getBits(buf,(int *)&grib_rec->rescomp,grib_rec->offset+128,8);
    getBits(buf,&sign,grib_rec->offset+136,1);
    getBits(buf,&dum,grib_rec->offset+137,23);
    /* latitude of last gridpoint */
    grib_rec->elat=dum*0.001;
    if (sign == 1)
      grib_rec->elat=-grib_rec->elat;
    getBits(buf,&sign,grib_rec->offset+160,1);
    getBits(buf,&dum,grib_rec->offset+161,23);
    /* longitude of last gridpoint */
    grib_rec->elon=dum*0.001;
    if (sign == 1)
      grib_rec->elon=-grib_rec->elon;
    getBits(buf,&dum,grib_rec->offset+184,16);
    /* longitude increment */
    grib_rec->loinc=dum*0.001;
    getBits(buf,&dum,grib_rec->offset+200,16);
    /* latitude increment */
    if (grib_rec->data_rep == 0)
      grib_rec->lainc=dum*0.001;
    else
      grib_rec->lainc=dum;
    /* scanning mode flag */
    getBits(buf,(int *)&grib_rec->scan_mode,grib_rec->offset+216,8);
    break;
    /* Lambert Conformal grid */
  case 3:
    /* Polar Stereographic grid */
  case 5:
    /* number of x-points */
    getBits(buf,(int *)&grib_rec->nx,grib_rec->offset+48,16);
    /* number of y-points */
    getBits(buf,(int *)&grib_rec->ny,grib_rec->offset+64,16);
    getBits(buf,&sign,grib_rec->offset+80,1);
    getBits(buf,&dum,grib_rec->offset+81,23);
    /* latitude of first gridpoint */
    grib_rec->slat=dum*0.001;
    if (sign == 1)
      grib_rec->slat=-grib_rec->slat;
    getBits(buf,&sign,grib_rec->offset+104,1);
    getBits(buf,&dum,grib_rec->offset+105,23);
    /* longitude of first gridpoint */
    grib_rec->slon=dum*0.001;
    if (sign == 1)
      grib_rec->slon=-grib_rec->slon;
    /* resolution and component flags */
    getBits(buf,(int *)&grib_rec->rescomp,grib_rec->offset+128,8);
    getBits(buf,&sign,grib_rec->offset+136,1);
    getBits(buf,&dum,grib_rec->offset+137,23);
    /* longitude of grid orientation */
    grib_rec->olon=dum*0.001;
    if (sign == 1)
      grib_rec->olon=-grib_rec->olon;
    /* x-direction grid length */
    getBits(buf,(int *)&grib_rec->xlen,grib_rec->offset+160,24);
    /* y-direction grid length */
    getBits(buf,(int *)&grib_rec->ylen,grib_rec->offset+184,24);
    /* projection center flag */
    getBits(buf,(int *)&grib_rec->proj,grib_rec->offset+208,8);
    /* scanning mode flag */
    getBits(buf,(int *)&grib_rec->scan_mode,grib_rec->offset+216,8);
    break;
  default:
    fprintf(stderr,"Grid type %d is not understood\n",grib_rec->data_rep);
    exit(1);
  }
  grib_rec->offset+=grib_rec->gds_len*8;
}

void unpackBDS(GRIBRecord *grib_rec)
{
  size_t n,m;
  size_t boff,bcnt=0;
  size_t num_packed;
  int bms_length,sign,ub;
  int tref,*bitmap=NULL;
  int E,*packed,cnt;
  double e,d=pow(10.,grib_rec->D);
  size_t *buf=(size_t *)grib_rec->buffer;

  if (grib_rec->bms_included == 1) {
    getBits(buf,&bms_length,grib_rec->offset,24);

    if (grib_rec->ed_num == 0)
      grib_rec->total_len+=bms_length;
    getBits(buf,&ub,grib_rec->offset+24,8);
    getBits(buf,&tref,grib_rec->offset+32,16);
    if (tref != 0) {
      fprintf(stderr,"Error: unknown pre-defined bit-map %d\n",tref);
      exit(1);
    }
    num_packed=(bms_length-6)*8-ub;
    bitmap=(int *)malloc(sizeof(int)*num_packed);
    boff=grib_rec->offset+48;
    for (n=0; n < num_packed; n++) {
      getBits(buf,&bitmap[n],boff,1);
      boff++;
    }
    grib_rec->offset+=bms_length*8;
  }

  /* length of the BDS */
  getBits(buf,(int *)&grib_rec->bds_len,grib_rec->offset,24);

  if (grib_rec->ed_num == 0)
    grib_rec->total_len+=(grib_rec->bds_len+1);
  /* flag */
  getBits(buf,(int *)&grib_rec->bds_flag,grib_rec->offset+24,4);
  getBits(buf,&ub,grib_rec->offset+28,4);
  /* bit width of the packed data points */
  getBits(buf,(int *)&grib_rec->pack_width,grib_rec->offset+80,8);

  getBits(buf,&sign,grib_rec->offset+32,1);
  /* binary scale factor */
  getBits(buf,&E,grib_rec->offset+33,15);
  if (sign == 1)
    E=-E;
  e=pow(2.,E);
  /* reference value */
  grib_rec->ref_val=ibm2real(buf,grib_rec->offset+48)/d;

  if ((grib_rec->bds_flag & 0x40) == 0) {
    /* simple packing */
    grib_rec->offset+=88;
    num_packed=(grib_rec->bds_len*8-88-ub)/grib_rec->pack_width;
    packed=(int *)malloc(sizeof(int)*num_packed);
    cnt=0;
    switch (grib_rec->data_rep) {
      /* Latitude/Longitude grid */
    case 0:
      /* Gaussian Lat/Lon grid */
      /* Rotated Lat/Lon grid */
    case 4:
    case 10:
      switch (grib_rec->grid_type) {
      case 23:
      case 24:
      case 26:
      case 63:
      case 64:
	grib_rec->offset+=grib_rec->pack_width;
	break;
      }
      /* Lambert Conformal grid */
    case 3:
      /* Polar Stereographic grid */
    case 5:
      for (n=0; n < num_packed; n++) {
	getBits(buf,&packed[n],grib_rec->offset,grib_rec->pack_width);
	grib_rec->offset+=grib_rec->pack_width;
      }

      grib_rec->ngy=grib_rec->ny;
      for (n=0; n < grib_rec->ny; n++) {
	for (m=0; m < grib_rec->nx; m++) {
	  if (bitmap == NULL || (bitmap != NULL && bitmap[bcnt++] == 1))
	    grib_rec->gridpoints[n * grib_rec->nx + m]=grib_rec->ref_val+packed[cnt++]*e/d;
	  else
	    grib_rec->gridpoints[n * grib_rec->nx + m]=GRIB_MISSING_VALUE;
	}
      }
      break;
      /* no recognized GDS, so just unpack the stream of gridpoints */
    default:
      grib_rec->ngy=grib_rec->ny=1;
      for (n=0; n < num_packed; n++) {
	if (bitmap == NULL || (bitmap != NULL && bitmap[bcnt++] == 1))
	  grib_rec->gridpoints[n]=grib_rec->ref_val+packed[n]*e/d;
	else
	  grib_rec->gridpoints[n]=GRIB_MISSING_VALUE;
	grib_rec->nx++;
      }
    }
  }
  else {
    /* second-order packing */
    fprintf(stderr,"Error: complex packing not currently supported\n");
    exit(1);
  }

  free(packed);
}

void skipBDS(GRIBRecord *grib_rec)
{
  size_t num_packed;
  int bms_length,ub;
  int tref;
  size_t *buf=(size_t *)grib_rec->buffer;

  if (grib_rec->bms_included == 1) {
    getBits(buf,&bms_length,grib_rec->offset,24);

    if (grib_rec->ed_num == 0)
      grib_rec->total_len+=bms_length;
    getBits(buf,&ub,grib_rec->offset+24,8);
    getBits(buf,&tref,grib_rec->offset+32,16);
    if (tref != 0) {
      fprintf(stderr,"Error: unknown pre-defined bit-map %d\n",tref);
      exit(1);
    }
    num_packed=(bms_length-6)*8-ub;
    grib_rec->offset+=bms_length*8;
  }

  /* length of the BDS */
  getBits(buf,(int *)&grib_rec->bds_len,grib_rec->offset,24);

  if (grib_rec->ed_num == 0)
    grib_rec->total_len+=(grib_rec->bds_len+1);
  /* bit width of the packed data points */
  getBits(buf,(int *)&grib_rec->pack_width,grib_rec->offset+80,8);

  if ((grib_rec->bds_flag & 0x40) == 0) {
    /* simple packing */
    grib_rec->offset+=88;
    num_packed=(grib_rec->bds_len*8-88-ub)/grib_rec->pack_width;
    switch (grib_rec->data_rep) {
      /* Latitude/Longitude grid */
    case 0:
      /* Gaussian Lat/Lon grid */
      /* Rotated Lat/Lon grid */
    case 4:
    case 10:
      switch (grib_rec->grid_type) {
      case 23:
      case 24:
      case 26:
      case 63:
      case 64:
	grib_rec->offset+=grib_rec->pack_width;
	break;
      }
      /* Lambert Conformal grid */
    case 3:
      /* Polar Stereographic grid */
    case 5:
      grib_rec->offset += num_packed * grib_rec->pack_width;

      grib_rec->ngy=grib_rec->ny;
      break;
      /* no recognized GDS, so just unpack the stream of gridpoints */
    default:
      grib_rec->ngy=grib_rec->ny=1;
    }
  }
  else {
    /* second-order packing */
    fprintf(stderr,"Error: complex packing not currently supported\n");
    exit(1);
  }
}

int unpackgrib(FILE *fp, int variable, double** data,
	       int max_length, GRIBRecord *grib_rec)
{
  int status;

  if ( (status=unpackIS(fp,grib_rec)) != 0)
    return status;
  unpackPDS(grib_rec);
  if (grib_rec->gds_included == 1) unpackGDS(grib_rec);
  if (grib_rec->param == size_t(variable))
    {
      if (size_t(max_length) < grib_rec->nx * grib_rec->ny)
	return -2;
      if (*data != NULL)
	grib_rec->gridpoints = *data;
      else
	*data = grib_rec->gridpoints = new double[grib_rec->nx * grib_rec->ny];
      unpackBDS(grib_rec);
    }
  else
    skipBDS(grib_rec);

  return 0;
}
