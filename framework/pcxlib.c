#include <stdio.h>
#include <string.h>
#include <io.h>

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;

typedef struct tagPCXFILEHEADER {
  BYTE	Manufacturer;	  // Constant Flag, 0x0A = ZSoft PCX
  BYTE	Version;		    // Version information
                        // 0 = Version 2.5 of PC Paintbrush
                        // 2 = Version 2.8 w/palette information
                        // 3 = Version 2.8 w/o palette information
                        // 4 = PC Paintbrush for Windows(Plus for Windows uses Ver 5)
                        // 5 = Version 3.0 and > of PC Paintbrush and PC Paintbrush +,
                        // includes Publisher's Paintbrush. Includes 24-bit PCX files
  BYTE	Encoding;		    // 1 = PCX run length encoding
  BYTE	BitsPerPixel;	  // Number of bits to represent a pixel(per Plane) - 1, 2, 4, or 8
  WORD	Xmin;			      // Image Dimensions Xmin
  WORD	Ymin;			      // Image Dimensions Ymin
  WORD	Xmax;			      // Image Dimensions Xmax
  WORD	Ymax;			      // Image Dimensions Ymax
  WORD	HDpi;			      // Horizontal Resolution of image in DPI
  WORD	VDpi;			      // Vertical Resolution of image in DPI
  BYTE	Colormap[48];	  // Color palette setting, see text
  BYTE	Reserved;		    // Should be set to 0.
  BYTE	NPlanes;		    // Number of color planes
  WORD	BytesPerLine;	  // Number of bytes to allocate for a scanline
                        // plane.  MUST be an EVEN number.  Do NOT
                        // calculate from Xmax-Xmin.
  WORD	PaletteInfo;	  // How to interpret palette
                        // 1 = Color/BW,
                        // 2 = Grayscale (ignored in PB IV/ IV +)
  WORD	HScreenSize;	  // Horizontal screen size in pixels.
                        // New field found only in PB IV/IV Plus
  WORD	VScreenSize;	  // Vertical screen size in pixels.
                        // New field found only in PB IV/IV Plus
  BYTE	Filler[54];		  // Blank to fill out 128 byte header.  Set all bytes to 0
} PCXFILEHEADER;


typedef struct tagPCXPALETTE {
  BYTE	Ident;			    // Palette-Identifier, must be 12 (0x0C)
  struct {				      // palette entries
    BYTE red;
    BYTE green;
    BYTE blue;
  } Palette[256];
} PCXPALETTE;

#define   PCX_WIDTH(p)				      (p.Xmax - p.Xmin + 1)
#define   PCX_HEIGHT(p)				      (p.Ymax - p.Ymin + 1)
#define   PCX_BITPERPIX(p)			    (p.BitsPerPixel * p.NPlanes)
#define   PCX_BYTESPERSCANLINE(p)	  (p.BytesPerLine * p.NPlanes)
#define   PCX_SIZE(p)				        ((DWORD)((PCX_BYTESPERSCANLINE(p)+3) & ~3) * (DWORD)PCX_HEIGHT(p))
#define   PCX_NUMCOLORS(p)			    (1 << PCX_BITPERPIX(p))

static int iEncodeLine(unsigned char*, int, FILE*);

int iPcxGetByte(int* byte, size_t* next, FILE* fp)
{
  if (feof(fp))
    return 0;

  *byte = getc(fp) & 0xFF;

  if ((*byte & 0xc0) == 0xc0)
  {
    *next = *byte & 0x3f;

    if (feof(fp))
      return 0;

    *byte = getc(fp) & 0xFF;
  }
  else
    *next = 1;

  return 1;
}


static int PutEncodedByte(unsigned char byt, unsigned char cnt, FILE* fid)
{
  if (cnt)
  {
    if ((cnt == 1) && (0xC0 != (0xC0 & byt)))
    {
      if (putc((int)byt, fid) == EOF)
        return(0);     /* disk write error (probably full) */

      return(1);
    }
    else
    {
      if (EOF == putc((int)0xC0 | cnt, fid))
        return (0);      /* disk write error */

      if (EOF == putc((int)byt, fid))
        return (0);      /* disk write error */

      return (2);
    }
  }

  return (0);
}

int iEncodeLine(unsigned char* inBuff, int inLen, FILE* fp)
{
  unsigned char achar, last;
  int srcIndex, i;
  register int total;
  register unsigned char runCount;     /* max single runlength is 63 */

  total = 0;
  runCount = 1;
  last = *(inBuff);

  for (srcIndex = 1; srcIndex < inLen; srcIndex++)
  {
    achar = *(++inBuff);

    if (achar == last)     /* There is a "run" in the data, encode it */
    {
      runCount++;

      if (runCount == 63)
      {
        if (!(i = PutEncodedByte(last, runCount, fp)))
          return (0);

        total += i;
        runCount = 0;
      }
    }
    else                /* No "run"  -  achar != last */
    {
      if (runCount)
      {
        if (!(i = PutEncodedByte(last, runCount, fp)))
          return(0);

        total += i;
      }

      last = achar;
      runCount = 1;
    }
  }        /* endloop */

  if (runCount)        /* finish up */
  {
    if (!(i = PutEncodedByte(last, runCount, fp)))
      return (0);

    return (total + i);
  }

  return (total);
}

int LoadPcxFile(const char* filename, unsigned char* buffer, size_t length)              
{
  PCXFILEHEADER header;
  size_t len;
  int col;
  long flen;
  FILE* fp;

  if (filename == NULL || buffer == NULL) {
    return 0;
  }

  if (fopen_s(&fp, filename, "rb") == 0) {
    return 0;
  }

  if (fp == NULL) {
    return 0;
  }

  if (fread(&header, sizeof(header), 1, fp) != 1) {
    return 0;
  }

  if (header.Manufacturer != 0x0A || header.Version != 0x05) {
    return 0;
  }

  if (header.BitsPerPixel != 8) {
    return 0;
  }

  flen  = (header.Xmax - header.Xmin + 1);
  flen *= (header.Ymax - header.Ymin + 1);
  length = flen < length ? flen : length;

  for (size_t i = 0; i < length; i += len)
  {
    if (!iPcxGetByte(&col, &len, fp))
      break;

    memset(buffer + i, col, len);
  }

  return 1;
}

int SavePcxFile(char* filename, 
  unsigned char* buffer,                
  unsigned long screen_x,
  unsigned long screen_y,
  unsigned long left,
  unsigned long top,
  unsigned long right,
  unsigned long bottom,
  unsigned char* palette)
{
  FILE* fp;
  PCXFILEHEADER header;
  unsigned long width;
  unsigned long height;
  unsigned char* ptr;

  if (left >= right || top >= bottom) {
    return 0;
  }

  width = right - left + 1;
  height = bottom - top + 1;

  if (width > screen_x || height > screen_y) {
    return 0;
  }
    
  if (filename == NULL || buffer == NULL) {
    return 0;
  }

  if ((fopen_s(&fp, filename, "wb")) == 0) {
    return 0;
  }

  if (fp == NULL) {
    return 0;
  }

  memset(&header, 0, sizeof(header));

  header.Manufacturer = 0x0A;
  header.Version = 0x05;
  header.Encoding = 1;
  header.BitsPerPixel = 8;

  header.Xmin = 0;
  header.Ymin = 0;
  header.Xmax = (WORD)(right - left);
  header.Ymax = (WORD)(bottom - top);
  header.HDpi = (WORD)width;
  header.VDpi = (WORD)height;

  for (int i = 0; i < sizeof(header.Colormap); i++) {
    header.Colormap[i] = palette[i];
  }

  header.Reserved = 0;
  header.NPlanes = 1;
  header.BytesPerLine = (WORD)width;
  header.PaletteInfo = 1;
  header.HScreenSize = 0;
  header.VScreenSize = 0;

  if (fwrite(&header, sizeof(header), 1, fp) != 1)
  {
    fclose(fp);
    remove(filename);
    return 0;
  }

  for (size_t i = 0; i < height; i++)
  {
    ptr = buffer + (i + top) * screen_x + left;
    iEncodeLine(ptr, width, fp);
  }

  /* Palette schreiben */
  fputc(0x0C, fp);
  for (size_t i = 0; i < 768; i++) {
    fputc(palette[i] << 2, fp);
  }

  fclose(fp);
  return 1;
}

int LoadPcxPalette(char* filename, unsigned char* palette)               
{
  FILE* fp;
  PCXFILEHEADER header;

  if (filename == NULL || palette == NULL) {
    return 0;
  }

  if (fopen_s(&fp, filename, "rb") == 0) {
    return 0;
  }

  if (fp == NULL) {
    return 0;
  }

  if (fread(&header, sizeof(header), 1, fp) != 1) {
    return 0;
  }

  if (header.Manufacturer != 0x0A || header.Version != 0x05) {
    return 0;
  }

  if (header.BitsPerPixel != 8) {
    return 0;
  }

  fseek(fp, -769L, SEEK_END);
  if (fgetc(fp) != 0x0C) {
    return 0;
  }

  for (size_t i = 0; i < 768; i++) {
    palette[i] = (char)(fgetc(fp) >> 2);
  }

  fclose(fp);
  return 1;
}
