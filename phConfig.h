
#ifndef phConfig_h
#define phConfig_h


/*! \addtogroup Configuration
   *  configuration data, file management, and settings
   *  @{
   */

//-- makerPrograms can be added to
//-- but should NEVER have existing
//-- values removed or changed


#define phListCount       15
#define userListCount     30
#define playListCount     20
#define entriesPerList    200
#define activeMakerCount  1

void phDebug(const __FlashStringHelper *string);


struct fileData{
    uint32_t address;
    char name[16];
};

struct phParamSets{

    uint8_t val[2];
};






/** @struct initConfig
 * @brief     Data containing initial core settings
 * Data is loaded and accessed through  uFile
 */
struct initConfigData {
    uint32_t address;
    char name[16]; 
    fileData hwFile;
    fileData userFile;
    fileData runFile;

    fileData phSets[phListCount];
    fileData userSets[userListCount];
    fileData playList[playListCount];
    fileData makerFile;
    fileData paramFile;
};
union initConfig {
  initConfigData data;
  uint8_t bytes[sizeof(data)];
};


/** @struct hwSettings 
 * @brief     Data containing hardware related settings.
 * Data is loaded and accessed through hw uFile
 */
struct hwSettingsUnion{

    //FileData
    char name[16];
    uint32_t address;

    //Prop Values
    uint32_t  propID;
    uint8_t   propType;
    uint8_t   propSize;
    uint8_t   tubeColor;

    // LED Strip Settings
    int LEDCount;
    uint8_t LEDDataPin;
    uint8_t LEDClockPin;
    uint8_t LEDColorOrder;
    uint8_t LEDGapCount;

    // Color correction to compensate
    // for colored tubing
    bool LEDcolorCorrectTubing;
    bool LEDcolorCorrectLED;

    uint8_t LEDCorrectRed;
    uint8_t LEDCorrectBlue;
    uint8_t LEDCorrectGreen;

    
    //IR Settings
    bool hasIRTransmit;
    bool hasIRReceive;
    int IRReceivePin;
    uint8_t IRTransmitPin;

    //IMU Settings
    bool hasIMU;
    uint8_t IMUInterruptPin;

    //Voltage Settings
    bool regulatePower;
    uint8_t voltageRefPin;
    uint32_t maxMilliAmp;
    float maxVoltage;

    //FlashStorage Settings
    uint8_t FRAMCSPin;

    //Program Settings
    uint8_t maxBrightLevel;    
};
union hwFile {
  hwSettingsUnion data;
  uint8_t bytes[sizeof(data)];
};


/** @struct phUserSettings
 * @brief     Data containing user related settings.
 * Data is loaded and accessed through user uFile
 */
struct phUserSettings{
    uint32_t address;
    char name[16]; 

    uint8_t brightLevelOnStartUp;

    uint8_t userLEDCorrectRed;
    uint8_t userLEDCorrectBlue;
    uint8_t userLEDCorrectGreen;

    bool      bootToLast;
    uint8_t   powerOnPatternGroup;
    uint8_t   powerOnGroupList;
    uint      powerOnGroupListEntry;
    
    uint32_t maxMillAmpOverride;

    uint8_t defaultTransitionTrigger;
    uint    defaultTransitionTimeMillis;
    uint8_t defaultTransitionMode;

    uint32_t  remoteLockCode;
    bool      lockOnPowerUp;
    bool      lockOnStandBy;
    bool      LEDCorrectOverride;

    bool postIMURollDefaultOn;
    bool postBlurDefaultOn;
    bool postMotionBrightDefaultOn;
    uint8_t defaultPostBlurAmount;

    bool motionTriggeredPlaylistActive; 
    uint8_t motionTriggeredPlaylistID;
    uint8_t motionPlaylistThreshold;

    bool motionIgnoreIRActive;
    bool motionIRIgnoreThreshold;

    bool motionStandyActive;
    bool motionStandbyThreshold;

    int  millisNoMotionToStandby;
    bool standByWakeThreshold;

    float warningPowerLevel;
    float shutDownPowerLevel;

    bool twinSearchOnStartup;
    bool twinSearchTimeOut;
    bool defaultTwinModePlaylist;
    bool favoritePlaylist;

    uint8_t bootAnimation;
};
union userFile {
  phUserSettings data;
  uint8_t bytes[sizeof(data)];
};


/** @struct phRuntTimeSettings
 * @brief     Data containing run time related settings.
 * Data is loaded and accessed through run uFile
 */
struct phRunTimeSettings{
    uint32_t address;
    char name[16]; 

    uint8_t currentProgram;

    uint8_t currentPatternGroup;
    uint8_t currentGroupList;
    uint8_t currentListEntry;

    uint8_t prevPatternGroup;
    uint8_t prevGroupList;
    uint8_t prevListEntry;

    bool isMaking;


    uint32_t BPM;
    uint32_t bpmTimebase;
    uint8_t tps;
    uint currentTick;
    bool firstMakeRun;


    uint32_t transitionTimeMillis;
    uint32_t transitionTimer;

    
    //PostEffects
    bool postIMURoll;
    bool doFade;
    bool doBlur;
    bool postBeater;

    uint8_t postBlurAmount;    
   
    //Player settings
    bool paused;
    bool play;
};
union runFile {
  phRunTimeSettings data;
  uint8_t bytes[sizeof(data)];
};


/** @struct playListData
 * @brief     Data containing run playlist entries
 * Data is loaded and accessed through uFile
 */
struct playListData{
    uint32_t address;
    char name[16]; 
    uint32_t nextEntryPos;
    uint32_t entries[200];
};
union plFile{
    playListData data;
    uint8_t bytes[sizeof(data)];
};


struct makerData{
    uint32_t address;
    char name[16]; 
    uint32_t defaultConfig[99];
};
union makerFile{
  makerData data;
  uint8_t bytes[sizeof(data)];
};

/** @struct phAnimationParams
 * @brief     Data containing run playlist entries
 * Data is loaded and accessed through uFile
 */
struct phAnimationParams{
    uint16_t makerIndex;     // animation mode index
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
    
    uint32_t averageMWDraw;
    uint8_t averageSamplesCount;
    uint32_t averageMWSamplesTotal;
};
union paramPacket{
    phAnimationParams data;
    uint8_t bytes[sizeof(data)];
};


union _paramFile{

    fileData data;
};

struct hwSettings{

    //FileData
    char name[16];
    uint32_t address;

    //Prop Values
    uint32_t propID;
    uint8_t propSize;

    // LED Strip Settings
    int LEDCount = 130;
    uint8_t LEDDataPin = 11;
    uint8_t LEDClockPin = 13;
    uint8_t LEDColorOrder;
    uint8_t LEDGapCount = 0;
    uint8_t LEDCorrectRed = 0;
    uint8_t LEDCorrectBlue = 0;
    uint8_t LEDCorrectGreen = 0;

    bool LEDcolorCorrect;


    //IR Settings
    int IRReceivePin = 3;
    uint8_t IRTransmitPin = 5;

    //IMU Settings
    uint8_t IMUInterruptPin = 9;

    //Voltage Settings
    uint8_t voltageRefPin;
    uint32_t maxMilliAmp=500;
    float maxVoltage=4.2;

    //FlashStorage Settings
    uint8_t chipSelectPin = 16;

    //Program Settings
    uint8_t maxBrightLevel = 200;    
};


 /**
      * @class phConfig
      * @brief      class for managing config and settings data.
      * 
      *  phConfig manages all configuration, runtime, and user settings
      *  Manages management of file data on external storage
      *  Manages synching current data with saved data in files
      */
class phConfig{
    public:
  

    phConfig();

    initConfig    init;         /**<  uFile containing initial config settings */

    hwFile        hwf;          /**<  uFile containing hardware settings */
    userFile      user;         /**<  uFile containing user settings */
    runFile       run;          /**<  uFile containing runTime settings */
    makerFile     maker;

    _paramFile    paramFile;
    plFile        playlist;     /**<  uFile containing current playlist values */
    paramPacket   params;       /**<  uFile containing current animation params */

    hwSettings    hw;


  
    /**
     * @fn loadCheck();
     * @brief      Checks to see if this is first time run.
     * 
     * If first run genFiles() is called to setup filesystem and configuration.
     */
    void loadCheck();

    /**
     * @brief      Loads defaults.
     */
    void loadDefaults();

    /**
     * @fn genFiles();
     * @brief      Performs initial setup of file system and all data
     * 
     * Sets value in eeprom to indicate initial config complete
     */
    bool genFiles();
  
    /**
     * @brief      { function_description }
     */
    void bootLoad();

    /**
     * @brief      { function_description }
     */
    void pflowPrep();

   

    /**
     * @brief      procArray()
     *
     * @param      array  pList Array
     *
     * @return     nextEntryPos
     */
    uint16_t procArray(uint32_t *array);

    /**
     * @brief      Saves to playlist.
     *
     * @param[in]  _playListIndex  The play list index
     */
    void saveToPlaylist(uint8_t _playListIndex, uint8_t _patternGroup);

    /**
     * @brief      Saves a parameter packet.
     */
    void saveParamPacket();

    /**
     * @brief      Loads a parameter packet.
     *
     * @param[in]  _address  The address
     */
    void loadParamPacket(uint32_t _address);

    /**
     * @brief      { function_description }
     */
    void deletePlayListEntry();

    /**
     * @brief      Loads a play list.
     */
    void loadPlayList(uint8_t _playListIndex,uint8_t _patternGroup,uint8_t _listEntry);
    void updateLEDCount(uint8_t _ledCount);


    /**
     * @fn saveData()
     * @brief      Saves current data in uFile to corrosponding file on external flash.
     *
     * @param      uFile  The u file to copy data from
     *
     * @tparam     U      template to handle various uFile types.
     */
    template <typename U>
    void saveData(U *uFile);

    /**
     * @fn loadData()
     * @brief      retrieves data from saved file on external flash.
     * loads data to corrosponding uFile in system RAM
     * Name and location of external file found in uFile data
     *
     * @param      uFile  The u file to load data into
     *
     * @tparam     U      template to handle various uFile types.
     */
    template <typename U>
    void loadData(U *uFile);

    /**
     * @fn   createFile(U *uFile)
     * @brief      Initial creation of file on external flash.
     *
     * @param      uFile  The ufile object containing initial data
     *
     * @tparam     U      typename for various uFile objects
     *
     * @return     returns uint32_t address of new file
     */
    template <typename U>
    uint32_t createFile(U *uFile);
};


 /*! @} */

#endif

