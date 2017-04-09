/*
  Prodigy.h - Library for Prodigy Props
  Created by Jonathan Clark. 2015
  Released into the public domain.
*/
//uint32_t testInt;


/**
 * @todo BUG:MAJOR Something is causing entire system to hang after 
 * a short time of running. Controller is completeley locked and
 * must have bootloader button manually pressed to recorver.
 * 
 * Have already completed memoryLeak test, no memory leak at time
 * of system hang
 */

#ifndef prodigy_h
#define prodigy_h
#include "Arduino.h"

#include <SerialFlash.h>
#ifndef __INC_FASTSPI_LED2_H
#include <FastLED.h>
#endif

#include <i2c_t3.h>
#include <SPI.h>
#include <map>
 #include <vector>
#include <EEPROM.h>
#include <stdint.h>
#include <IRremote.h>
#include <MemoryFree.h>
 


enum tubeColors{
  CLEAR_TUBE=0,
  AQUA_TUBE
};
enum propTypes{
  PROTEGE_HOOP_V1 =0,
  PROTEGE_POI_V1,
  PROTEGE_STAFF,
  PRO_LITE_HOOP,
  PRO_LITE_POI,
  TESLA_HOOP,
  TESLA_POI
};
enum powerSourceTypes{
  REMOVABLE_BATT=0,
  INTERNAL_BATT,
  HYBRID_POWER
};


enum transitionTypes{
  TIME_IN_MILLIS=0,
  TIME_BY_BPM,
  MOTION_TRIGGER,
  HYBRID_MOTION_AFTER_TIME
};
enum transitionMode{
  TRANSITION_CUT=0,
  TRANSITION_BLEND,
  TRANSITION_MULTIPLY
};
enum patternGroups{
  PRODIGY_SET=0,
  USER_SET,
  PLAY_LIST,
  MAKER_LIST
};


/**
 *
 * @brief      Available "Makers" supported by "Prop" class
 * 
 * @ingroup    RunTimeControls
 * 
 */
enum makerPrograms{
  DUAL_STRIPES=0,   /*!< Basic Dual Stripe generator  */
  GLITTER_BASIC,    /*!< Basic Glitter generator */
  CHASER_BASIC,     /*!< Basic Chaser generator */
  IMAGE_BASIC       /*!< Baisc Bitmap2Pattern generator  */
};

/**
 * @brief       Commands used to control "Prop" class
 * 
 * @ingroup     RunTimeControls
 */
enum propControls{
    PLAYER_PLAY=0,
    PLAYER_PAUSE,
    GO_TO_PLAYLIST,
    GO_TO_PH_SET,
    GO_TO_USER_SET,
    GO_TO_MAKER_SET,
    GO_TO_PRGM,

    ACTIVATE_MAKER,
    SAVE_TO_USER_SET,
    SAVE_TO_PH_SET,
    SET_DEFAULT_MAKER_FILE,

    PLAYER_NEXT_ENTRY,
    PLAYER_NEXT_LIST,
    PLAYER_SHUFFLE_LIST,
    PLAYER_REPEAT_LIST,
    PLAYER_GO_BACK,

    SHOW_USER_MENU,
    SHOW_DEFAULTS_MENU,
    SHOW_ADVANCED_MENU,
    SHOW_ADMIN_MENU,
    SHOW_POWER_OPTIONS_MENU,
   

    SHOW_BATTERY_LEVEL,

    //USER MENU - ACTIVE RUNTIME SETTINGS
    SET_USER_BRIGHTNESS,
    DISABLE_POWER_USAGE_LIMIT,
    DISABLE_POSTFX_IMU_ROLL,
    DISABLE_POSTFX_MOTION_SWITCH_PLAYLIST,
    DISABLE_POSTFX_BEAT_OVERLAY,
    

    //DEFAULTS MENU - DEFAULT POWER ON SETTINGS
    SET_DEFAULT_BRIGHTNESS_LEVEL,
    SET_DEFAULT_OVERBRIGHT_PROTECTION_ON,
    SET_DEFAULT_POWERLEVEL_WARNING,
    SET_DEFAULT_POWERLEVEL_CRITICAL,
    SET_DEFAULT_POWER_ON_PLAYLIST,
    SET_DEFAULT_LOW_IMPACT_PLAYLIST,

    //LOCK MENU COMMANDS
    SHOW_LOCK_OPTIONS_MENU,
    LOCK_PROP,
    CHANGE_LOCK_CODE,
    TOGGLE_REQUIRE_LOCK_CODE_ON_STARTUP,
    TOGGLE_REQUIRE_LOCK_CODE_ON_RESUME,
    DISABLE_WIPE_LOCK_CODE,
    

    //ADMIN MENU
    SET_LED_COUNT,
    REGEN_BITMAP_PLAYLIST,

    UNLOCK_PROP,


    USER_BRIGHTNESS_UP,
    USER_BRIGHTNESS_DOWN,
    




    DISPLAY_MENU_ITEM,
    MENU_NEXT_ITEM,
    MENU_PREV_ITEM,
    MENU_SELECT_OPTION,
    MENU_GO_TO_PARENT,
    MENU_GO_TO_SUB,
    
    MENU_VAL_UP,
    MENU_VAL_DOWN,
    MENU_SET_VAL_TO,

    
    SAVE_TO_PLAYLIST,
    DELETE_ENTRY,
    WIPE_PLAYLIST,
    WIPE_USER_SET    
};

/**

 *
 * @brief      Specialty interfaces supported by "Prop" class
 * 
 * @ingroup     RunTimeControls
 * 
 */
enum optionDisplays{
    OD_SET_BRIGHTNESS=0,
    OD_SET_BPM,

    OD_LOCK_OPTIONS_MENU,
    OD_CHANGE_LOCK_CODE,


    OD_POWER_OPTIONS_MENU,
    OD_SET_LOW_POWER_WARNING_LEVEL
};

/**

 *
 * @brief      Primary programs supported by "Prop" class
 * 
 * @ingroup    RunTimeControls
 * 
 */
enum phPrograms{
  ANIMATION_PLAYER = 0,
  SUB_PROGRAM,
  SPECIAL_PROGRAM
};

/**

 *
 * @brief      Secondary programs supported by "Prop" class
 * 
 * @ingroup    RunTimeControls
 */
enum subPrograms{
  PLAYER_PHGROUP=0,
  PLAYER_USERGROUP,
  PLAYER_PLAYLIST,
  PLAYER_MAKERS,
  PRGM,
  SAVER,
  KICKSTARTER,
  MAKING,
  USER_MENU,
  BEAT_SETTER,
  BATTERY_CHECK,
  SYSTEM_SOFT_LOCK,
  SYSTEM_HARD_LOCK
};

/**

 *
 * @brief      Specialty programs supported by "Prop" class
 * 
 * @ingroup    RunTimeControls
 * 
 */
enum specialPrograms{
  FULL_TEST,
  STORAGE_TEST,
  IMU_TEST,
  LED_TEST,
  IR_IN_TEST,
  IR_OUT_TEST,
  TWIN_IR_TEST,

  CALIBRATE_LOW_MOTION_PLAYLIST_TRIGGER_THRESHOLD,

  IR_LEARN_REMOTE,
  COLOR_CORRECTOR,
  SET_LEDCOUNT,
  SYSTEM_REBOOT,  
  SOFT_FACTORY_RESET,

  PROP_DISPLAY_ERRORS,
  PROP_DISPLAY_PROP_INFO,    

  SERIAL_PROP_INFO_OUT,
  SERIAL_DEBUG_ALL_OUT,
  SERIAL_FILE_TRANSFERS,
  SERIAL_BACKUP_ALL,
  SERIAL_LOAD_BACKUP,
  SERIAL_CONTROL_PROP,
  SERIAL_DUMP_CURRENT_PARAMS,
  SERIAL_DUMP_MOTION_SAMPLES,

  STORAGE_OPTIMIZE,

  GENERATE_LOW_POWER_PLAYLIST,
  GENERATE_IMAGE_DIRECTORY_FILE,
  GENERATE_IMAGE_BASIC_PHLIST,
  ACTIVATE_PATTERN_POWER_LOGGER,
  SET_PARAMS_AS_MAKER_DEFAULT,

  SYNC_WITH_HYPIE,
  SYNC_WITH_FLUX,
  SYNC_WITH_MOODHOOP,
  SYNCH_WITH_PHEONIX,  
  
  PH_RESET_LOCKCODE_IR,
  PH_RESET_LOCKCODE_SERIAL,
  PH_FULL_WIPE_RESET,

  ACTIVATE_HOOP_JESUS,
  ACTIVATE_BLACKOUT,
};


enum phAlerts{
    INVALID_ENTRY=0,
    BAT_LOW_WARNING,
    BAT_CRITCIAL_WARNING,

    PLAYLIST_FULL,
    CONFIRM_DELETE,

    IMU_ERROR,
    FILE_ERROR,
    INVALID_LOCK_CODE,
    IR_BLINK,
    PROP_BUSY,
    USER_SET_FULL
};
enum errorCodes{

  IMU_ERROR_INIT,
  IMU_ERROR_COM_LOSS,

  EXTERNAL_STORAGE_ERROR_INIT,
  EXTERNAL_STORAGE_FILE_CREATE_FAIL,
  EXTERNAL_STOAGE_FILE_READ_FAIL,
  EXTERNAL_STORAGE_FILE_MISSING,
  EXTERNAL_STORAGE_SYSTEM_CORRUPTION,
  EXTERNAL_STORAGE_FILE_SPACE_WARNING,

  POWER_SHUTDOWN_MIN_POWER,

  BOOT_FAILURE,
  SYSTEM_SOFT_LOCKED,
  SYSTEM_HARD_LOCKED,

  IR_LEARNING_FAIL_DETECT_IR,
  IR_TWIN_LINK_FAILURE
};



#ifndef phConfig_h
#include "phConfig.h"
#endif

#ifndef phHelpers_h
#include "phHelpers.h"
#endif



#ifndef phMakers_h
#include "phMakers.h"
#endif

#ifndef phBitmap_h
#include "phBitmap2.h"
#endif

#ifndef phIMU_h
#include "phIMU.h"
#endif  

#ifndef phRemote_h
#include "phRemote.h"
#endif




/**
 * @brief      Class for options display.
 */
class optionsDisplay{
    public:

    /**
     * @brief      { function_description }
     */
    optionsDisplay();

    /**
     * @brief      Sets the settings.
     *
     * @param[in]  _timeoutMillis  The timeout millis
     * @param[in]  _odTracker      The od tracker
     */
    void setSettings(uint32_t _timeoutMillis, uint32_t _odTracker);

    
    phTimer timer;

    /**
     * @brief      Determines if active.
     *
     * @return     True if active, False otherwise.
     */
    bool isActive();

    /**
     * @brief      { function_description }
     */
    void pulse();

    /**
     * @brief      { function_description }
     */
    void activate();

    /**
     * @brief      { function_description }
     */
    void deactivate();

    /**
     * @brief      Sets the time out millis.
     *
     * @param[in]  _timeoutMillis  The timeout millis
     */
    void setTimeOutMillis(uint32_t _timeoutMillis);

    /**
     * @brief      Sets the od tracker.
     *
     * @param[in]  _odTracker  The od tracker
     */
    void setODTracker(uint32_t _odTracker);

    uint8_t odTracker;

    /**
     * @brief      { function_description }
     */
    void activateDisplay();
};

/**
 * @brief      Class for protege.
 */
class protege{

    public:

        /**
         * @brief      { function_description }
         */
        protege();

        /**
         * @brief      Destroys the object.
         */
        ~protege();

        /**
         * @brief      { function_description }
         */
        void configure(); 

        /**
         * @brief      Creates a menu.
         */
        void createMenu();

        /**
         * @brief      { function_description }
         *
         * @param[in]  _action  The action
         */
        void control(uint8_t _action);

        std::map<int,uint8_t> lockMenu;

        
     
        /**
         * @brief      { function_description }
         *
         * @param[in]  activeOptionDisplay  The active option display
         */
        void displayOption(uint8_t activeOptionDisplay);

        /**
         * @brief      { function_description }
         */
        void play();

        /**
         * @brief      { function_description }
         */
        void show();

        /**
         * @brief      Posts a fx.
         */
        void postFX();

        /**
         * @brief      { function_description }
         */
        void postfx_IMURoll();

        /**
         * @brief      { function_description }
         */
        void postfx_IMUSpin();

        /**
         * @brief      { function_description }
         */
        void postfx_Blur();

        /**
         * @brief      { function_description }
         */
        void postfx_MotionPatternSwitch();

        /**
         * @brief      { function_description }
         */
        void postfx_MotionBright();

        /**
         * @brief      Sets the user brightness gui.
         *
         * @param      displayControl  The display control
         */
        void setUserBrightnessGUI(optionsDisplay &displayControl);

        /**
         * @brief      Sets the bpmgui.
         *
         * @param      displayControl  The display control
         */
        void setBPMGUI(optionsDisplay & displayControl);
};


/**
 * @brief      Class for prodigy 2.
 */
class prodigy2{
    public:

    /**
     * @brief      { function_description }
     */
    prodigy2();

    /**
     * @brief      Destroys the object.
     */
    ~prodigy2();

    /**
     * @brief      { function_description }
     */
    void configure();

    /**
     * @brief      { function_description }
     *
     * @param[in]  _LEDCount  The led count
     */
    void setupLEDS(int _LEDCount);

    /**
     * @brief      { function_description }
     */
    void setupIMU();

    /**
     * @brief      { function_description }
     */
    void setupIR();   

    /**
     * @brief      { function_description }
     */
    void initProp();

    /**
     * @brief      { function_description }
     */
    void bootUpAnimate();

    /**
     * @brief      { function_description }
     */
    void Run();

    /**
     * @brief      { function_description }
     */
    void doEveryCycle();

    /**
     * @brief      { function_description }
     */
    void updateIR();

    /**
     * @brief      { function_description }
     */
    void updateIMU();

    /**
     * @brief      Sends a command.
     *
     * @param[in]  _action  The action
     */
    void sendCommand(uint8_t _action);       


    /**
     * @brief      { function_description }
     */
    void doEvery1000Millis();

    /**
     * @brief      { function_description }
     */
    void doEvery100000millis();

    /**
     * @brief      { function_description }
     */
    void updateBatteryLevel();


    uint8_t userBrightnessLevel;

    /**
     * @brief      Sets the user brightness.
     */
    void setUserBrightness();

    /**
     * @brief      { function_description }
     *
     * @param[in]  valToAdd  The value to add
     */
    void changeUserBrightnessLevel(int valToAdd);


    //-- Function to reduce repetive math
    int LEDCount;
    int LEDMid;

   
    phConfig settings;
    phRemote ir;
    protege prop;
    phBeater beater;

    //Needed for runtime management
    phTimer every1000ms;
    phTimer every10000ms;


    //Needed for hardware
    CRGB *leds;
    CRGB *tmpLED; 
    uint8_t batLevel;

    //Needed to track state of special interfaces
    bool optionDisplayActive = false;
    uint8_t activeOptionDisplay;
    uint16_t currentOptionVal;

    //special interfaces for managing settings
    optionsDisplay ODsetUserBrightness;
    optionsDisplay ODsetBPM;
    optionsDisplay ODchangeLockCode;


    //Misc
    uint32_t lastIRKey;



    phWave waver;
    phWave waver2;
    phWave waver3;
    shapeGenerator shaper;
};
extern prodigy2 pflow2;






/**
 * @brief      Class for prodigy.
 */
class prodigy{
    
    public:
    prodigy();
    ~prodigy();

    // Initial configuration routing
    //
    void configure();
    

    /**
     * @brief      { function_description }
     */
    void setupLED();
    void setupIMU();

    /**
     * @brief      { function_description }
     */
    void cycleChecks();
    void play();
    void postFX();
    void show();
    

    
    /**
     * @brief      { function_description }
     *
     * @param[in]  rollVal  The roll value
     */
    void rollLED(uint8_t rollVal);
    void flash(uint8_t flashOnTime, uint8_t flashOffTime, uint8_t flashRepeats=1, uint8_t hue=32);


    // RunFunctions
    //
    void setBrightness();
    void brightUp();
    void brightDown();
    void checkBattery();
    void animatedLevel();
    void splitChaseUp(int chaseTime,int postWaitTime);


    uint8_t runningProgram = ANIMATION_PLAYER;


    /**
     * @brief      { function_description }
     *
     * @param[in]  val   The value
     *
     * @return     { description_of_the_return_value }
     */
    uint8_t u82l(uint8_t val);
    
    phConfig sets;
    maker make;
    phRemote ir;
    IMU imu;

    //static int const LEDCount;        
    int ledCount;


    CRGB *leds;
    CRGB *tmpLED; 
    
    uint8_t ledMid;   
    uint8_t ledQuarter;

    bool postRoll;
    uint8_t postRollValue;       

    bool postBlur;
    uint8_t postBlurAmount = 10;

    bool postClear;

    bool doPlay = true;
    bool doPause = false;
    bool repeatOn;
    bool shuffleOn;
    bool menuActive;
    bool prgmActive;

    bool powerOff;
    bool lockOn;
    bool motionOn;

    uint8_t phBright;
    uint8_t activeM;

    float batLevel;

    int animatorTimer1;

    uint8_t bpm=10;
    uint32_t bpmTimebase;   

    private:
};


//extern prodigy ph;

#endif



