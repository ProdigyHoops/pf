/*
 
*/

#ifndef phBITMAP_H_
#define phBITMAP_H_

enum BMP_Status {
  BMP_OK = 0,                          // Image Displayed OK
  BMP_INVALID_FORMAT = 1,              // Not a BMP file
  BMP_UNSUPPORTED_HEADER = 2,          // Has a rare BMP header format (not v2 or v3)
  BMP_TOO_MANY_COLOURS = 3,            // Is a 32bpp image (not supported)
  BMP_COMPRESSION_NOT_SUPPORTED = 4,   // Uses RLE or another unsupported compression format
  BMP_UNSUPPORTED_COLOURS = 5,         // Uses non-standard colour format
  BMP_ORIGIN_OUTSIDE_IMAGE = 6,        // You've asked to crop a section that doesn't exist in the image
  BMP_OK2 = 9
};

class phBMP
{
public:
    phBMP();
    ~phBMP();
    void next();

    // Specs of bitmap file
    // Obtained from file header during load
    uint16_t width, height, bpp, compression;
    
    // Offset of header & palette data
    // Start of pixel data in file
    uint32_t data_offs;

    // Total bytes per row
    // Calculated after determining type
    // of bitmap format
    uint16_t row_bits, row_bytes;

    //Pointer for location to hold pixel data
    char * image=0;
    CRGB *palette;  

    // Address of SerialFlash holding bitmap file
    uint32_t address; 

    // Size of currently loaded bitmap file
    uint32_t fileSize;

    uint32_t tracker; 
    

    bool rgb565, loaded, halfByte;  
    int tiles;      
        

    
    void load(const char *filename);
    SerialFlashFile file;
    
    BMP_Status verify();
    CRGB getPix(int X, int Y);


    uint32_t stepByte();
    void moveTo(uint32_t pos);
    void read(uint8_t *buf, uint16_t size);
    uint16_t readShort();
    uint32_t readLong();
    uint32_t litEnd(uint32_t);
  

};

#endif
