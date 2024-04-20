#ifdef __cplusplus
extern "C" {
#endif
extern int LoadPcxFile (char* filename,      /* Filename */
       unsigned char* buffer,                /* image destination buffer */
       unsigned long length);                /* buffer length */

extern int SavePcxFile (char* filename,      /* Filename */
       unsigned char* buffer,                /* image source buffer */
       unsigned long  screen_x,              /* buffer width */
       unsigned long  screen_y,              /* buffer height */
       unsigned long  top,
       unsigned long  left,
       unsigned long  bottom,
       unsigned long  right,
       unsigned char* palette);

extern int LoadPcxPalette (char *filename,   /* Filename */
       unsigned char* palette);              /* palette buffer */
#ifdef __cplusplus
}
#endif
