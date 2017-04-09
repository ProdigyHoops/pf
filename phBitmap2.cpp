/*  WORK IN PROGRESS

bitmap class modified to read bitmap file saved to external Flash
using SerialFlash library. Currently working and displaying image
row by row around 2000fps

-- Need to remove and seperate all functionality related to
displaying pixels.  Bitmap class shold strictly deal with processing
bitmap file and providing a way to easily retrieve RGB data for X,Y

-- bitmap class should accept filename and use SerialFlash to access
and process file data

-- Need to implement functionality for calling bitmap class with 
bitmap.getPix(X,Y) that returns CRGB data type for given cordinates. 
Can be used with bitmap.Width & bitmap.Height

-- Helpful functionality if bitmap.getPix(X,Y) automatically handled
rotating value given for X,Y from 0-Width, 0-Height
*/
#ifndef phIMU_h
#include "prodigy.h"
#endif






enum BMP_Compression {
  BMP_NoCompression = 0,
  BMP_RLE8bpp = 1,
  BMP_RLE4bpp = 2,
  BMP_BITFIELDS = 3,
  // ... lots more methods that aren't supported :)
};


// Offset of file header
// File header is always 14 bytes
const uint8_t OFFS_DIB_HEADER = 0x0e;


phBMP::phBMP(){
};

phBMP::~phBMP(){
    free(image); 
  free(palette);
}

// Returns current mark after
// increasing mark by one
uint32_t phBMP::stepByte(){
  uint32_t current = tracker;  
  tracker++; 
  return current;
}

// Moves tracker to specific location
// Equivalent of seek();
void phBMP::moveTo(uint32_t pos){
  tracker=pos;
}

// Fills buf with values from image[]
// while increasing tracker
// Get rid of later and use 1 method
// for accessing data
void phBMP::read(uint8_t *buf, uint16_t size){
  for(int i=0;i<size;i++){
    buf[i]=image[stepByte()];
    //return image[stepByte()];
  }
}

// Read a little-endian short word from
// values in image[]
uint16_t phBMP::readShort(){
  uint16_t val = (uint16_t)image[stepByte()] | (uint16_t)image[stepByte()] << 8;
  //Serial.print("short val = "); Serial.println(val);
  return val;
}

// Read a little-endian long from
// values in image[]
uint32_t phBMP::readLong(){
  uint32_t val = (uint32_t)readShort() | (uint32_t)readShort() << 16;
  return  val;
}


// Use in final version
/*
void phBMP::load(char *filename){  
  // Use SerialFlash to verify file exist
  // Get filename address
  // Get filename size
  // Read all data into image[]
}
*/


void phBMP::next(){

    free(image); 
    free(palette);
  //free(image); 
 // free(palette);
  SerialFlashFile file2 = SerialFlash.open("a22.bmp");
  address = file2.getFlashAddress();
  fileSize = file2.size();
  image = (char*) realloc(image,fileSize);  
  SerialFlash.read(address,image,fileSize);
  tracker = 0;
  file2.close();

  verify();
}

void phBMP::load(const char *filename){
  Serial.println("Fine after function call");
  //free [] image;
  free(image); 
 
  Serial.println("Fine after free");
  file.close();
  Serial.println("Fine after file close");
  SerialFlash.begin(16);
  file = SerialFlash.open(filename);
  Serial.println("Fine after serial open");
  address = file.getFlashAddress();
  fileSize = file.size();
  image = (char*) malloc(fileSize);  
    Serial.println("fine after realloc");
  SerialFlash.read(address,image,fileSize);   
  file.close();
  Serial.println("Fine after flash read");
  tracker = 0;
 

  verify();
  
};


// Messy implementation of previous library
// Working but needs changed for better use with SerialFlash

// Merge this into the final "load" function
BMP_Status phBMP::verify()
{ 
  // Check image data for magic "BM" to verify bitmap file
  if(image[stepByte()] != 'B' || image[stepByte()] != 'M'){
    return BMP_INVALID_FORMAT;
  }
  
  // Bitmap starts with 14 Byte file header,
  // Move past file header to bitmap header (byte 15)
  moveTo(OFFS_DIB_HEADER);
 
  // First 4 bytes in header are size of header
  // Size of header tells us what type of bitmap format
  // this file is using
  uint32_t dib_headersize = readLong();

  // Check if v2header; v2Header always = 12Bytes
  bool v2header = (dib_headersize == 12); 

  // First 2 values in v2Header are width & height
  // v2Header uses short/word for width and height
  if(v2header){
    width = readShort();
    height = readShort();

    // Next short/word should always = 1;
    // If not 1, then something is wrong with format
    if(readShort() != 1){
      return BMP_UNSUPPORTED_HEADER;
    }

    // Next two values are bpp & compression
    bpp = readShort();
    compression = BMP_NoCompression;
  }

  // Not v2Header, Verify using alternative 
  // header format
  else{
    // Width and Heeight are saved as long/DWORD
    width = readLong();    
    height = readLong();

    //Next short/WORD should always be 1;
    if(readShort() != 1)
      return BMP_UNSUPPORTED_HEADER;

    // Next two values are bpp & compression
    bpp = readShort();
    compression = readLong();
  }

  // Verify image properties from header
  // Currently supporting 1,4,8,16 & 24
  if(bpp > 24)
    return BMP_TOO_MANY_COLOURS;
  if(bpp != 1 && bpp != 4 && bpp != 8 && bpp != 16 && bpp != 24)
    return BMP_UNSUPPORTED_COLOURS;

  if(!(compression == BMP_NoCompression
       || (compression == BMP_BITFIELDS && bpp == 16))) {
    return BMP_COMPRESSION_NOT_SUPPORTED;
  }

  //rgb565 = true;
  if(compression == BMP_BITFIELDS){
    moveTo(0x36);
    uint16_t b = readLong();
    uint16_t g = readLong();
    uint16_t r = readLong();
    if(r == 0x001f && g == 0x07e0 && b == 0xf800)
      rgb565 = true;
    else if(r != 0x001f && g != 0x03e0 && b != 0x7c00)
      return BMP_UNSUPPORTED_COLOURS; // Not RGB555 either
  }

  // Move to valus in header specifying 
  // offset to pixel data
  moveTo(0x0a);
  data_offs = readLong();

  // Calculate the width in bits of each row 
  // (rounded up to nearest byte)
  row_bits = (width*bpp + 7) & ~7;

  // Calculate width in bytes (4-byte boundary aligned)
  row_bytes = (row_bits/8 + 3) & ~3;

  // Load palette data to Ram if < 16 bpp
  // > 16 bpp means pixel data contains actual 
  // RGB values (no palette)
  // Previous implementation when data was
  // stored on SD card.  Needs changed.
  if(bpp < 16) {  
  uint16_t palette_size = 1<<bpp;

  //Allocating space in memory for palette data
  free(palette);
  palette = (CRGB*)malloc(sizeof(CRGB)*palette_size);
  moveTo(OFFS_DIB_HEADER + dib_headersize);
  for(uint16_t i = 0; i < palette_size; i++) {
    uint8_t pal[4];
    read(pal, v2header ? 4 : 4);
    palette[i].blue = pal[0]; // >> 3;
    palette[i].green = pal[1]; // >> 2;
    palette[i].red = pal[2]; // >> 3;
  }
    loaded = true;
    return BMP_OK2;
  }
}


CRGB phBMP::getPix(int X, int Y){
  uint16_t row = X % (height);
  uint16_t col = Y % (width);
  CRGB px;
  if(bpp == 24) {
    moveTo((data_offs + (row*row_bytes))+(col*3));      
      px.blue = image[stepByte()];
      px.green = image[stepByte()];
      px.red = image[stepByte()];
    return px;
  }

  else if(bpp == 8) { 
      px = palette[image[((data_offs + (row*row_bytes))+(col))]];
    return px;
  }

  else if(bpp == 4) {
    if(col % 2){
      px = palette[image[((data_offs + (row*row_bytes))+(col/2))] & 0x0F];
      return px;      
    }
    else{      
      px = palette[image[((data_offs + (row*row_bytes))+(col/2))] >> 4];
      return px;
    }

  }
};






