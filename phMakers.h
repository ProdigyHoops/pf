
#ifndef phMakers_h
#define phMakers_h



class prodigy;



class maker{
    public:
        maker();
        ~maker();

        void makeThis(int _maker);
        
        //prodigy ph;
        int ledCount;
        int makingNow;
        CRGB *leds;
        phConfig sets;

        prodigy *ph;
		void passProdigy(prodigy *phIn);

        //void loadPH();
        void beatScan(uint8_t bpm);
        void dualStripes();
        void glitterBasic();
        void debugMotin();
};



#endif

/*  Just here for easy reference while programming
 *  
 *  params.data.params[0].val[0]
 *  

struct phAnimationParams{
    uint32_t animationType;     // animation mode index
    uint32_t resourceIndex;     // 32bit address of 
    uint32_t resourceIndex2;    // 32bit address of 

    phParamSets params[10];

    uint32_t palletIndex;       // index of phPallet to use

 
    uint8_t colorShiftRed;      // User color adjustment 
    uint8_t colorShiftBlue;     // User color adjustment 
    uint8_t colorShiftGreen;    // User color adjustment 
 
    uint8_t bpm;
    uint32_t fps;    

    bool phToggle1;     // User toggle option 1
    bool phToggle2;     // User toggle option 2
    bool phToggle3;     // User toggle option 3
    bool phToggle4;     // User toggle option 4
    bool phToggle5;     // User toggle option 5
    bool phToggle6;     // User toggle option 6
    bool phToggle7;     // User toggle option 7
    bool phToggle8;     // User toggle option 8
};

*/