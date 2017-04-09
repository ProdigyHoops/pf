

#ifndef phHelpers_h
#define phHelpers_h



/**
 * @brief      { function_description }
 *
 * @param[in]  i     { parameter_description }
 * @param[in]  s     { parameter_description }
 * @param[in]  l     { parameter_description }
 * @param[in]  r     { parameter_description }
 *
 * @return     { description_of_the_return_value }
 */
uint8_t u8WTF(int i, uint8_t s, int l, bool r);

/**
 * @fn         u8Rev
 *
 * @brief      Simple reverse of uint8_t
 *
 * @param[in]  val   val to reverse
 *
 * @return     reverse of val ie: 255-val
 *
 * @ingroup    u8Transforms
 */
uint8_t u8Rev(uint8_t val);

/**
 * @brief      Scales uint8_t from 0-255 to 0-LEDCount
 *
 * @param[in]  val     The value
 * @param[in]  lcount  The lcount
 *
 * @return     val scaled to 0-LEDCount
 *
 * @ingroup    u8LTransforms
 */
uint8_t u82l(uint8_t val, int lcount);

uint8_t u82lbRef(uint8_t &val);

/**
 * @brief      generates sawtooth wave set to desired bpm, scaled betwen
 *             0-LEDCount
 *
 * @param[in]  _bpm  desired BPM of sawtooth wave
 *
 * @return     value representing sawtooth wave scaled between 0-LEDCount
 */
uint8_t u8beat2l(uint8_t _bpm);

/**
 * @brief      helper bool toggle (Just to cut down on repetive coding)
 *
 * @param      togit  the bool val to compare and possible toggle
 *
 * @return     returns opposite of &togit; also sets &togit to NOT &togit
 */
bool tog(bool &togit);

/**
 * @brief      helper function; Toggles &tog if condition is met
 *
 * @param      tog        bool to compare and possibly toggle
 * @param[in]  condition  will toggle bool if this condition is met
 *
 * @return     returns &tog unchanged if condition not met; returns !&togif
 *             condition is met
 */
bool togIf(bool &tog,bool condition);

/**
 * @brief      constrains an uint8_t between to bounds
 *
 * @param      _val      uint8_t to be constrained (ACTUAL VARIABLE MODIFIED!)
 * @param[in]  _loLim    The lower limit
 * @param[in]  _highLim  The high limit
 *
 * @return     _val unchanged, or _val bound to one of the two limits
 *
 * @ingroup    u8Transforms
 */
uint8_t u8Lim(uint8_t  & _val, uint8_t _loLim, uint8_t _highLim);

/** @todo Change these math functions to ones provided by FastLED for 1Byte vals
 *
 *
 * @brief      adds an amount to an uint8_t, limiting the result between high & low
 *             bounds
 *
 * @param      _val      uint8_t to modify/limit  (ACTUAL VARIABLE MODIFIED!)
 * @param[in]  _toAdd    amount to add (negative value to sub)
 * @param[in]  _lowLim   The low limit
 * @param[in]  _highLim  The high limit
 *
 * @return     _val with amount added and constrained within bounds (ACTUAL
 *             VARIABLE MODIFIED!)
 *
 * @ingroup    u8Transforms
 */
uint8_t u8AddLim(uint8_t  & _val, int _toAdd, uint8_t _lowLim, uint8_t _highLim);

	
/** @todo  get rid of u8AddLim, replace with u8AddLimSafe, change name to u8AddLim()
 *	8AddLim created to debug and fix issue with u8AddLim, needs some inspection before
 *	removing
**/

/**
 * @brief      { function_description }
 *
 * @param      _val      The value
 * @param[in]  _toAdd    To add
 * @param[in]  _lowLim   The low limit
 * @param[in]  _highLim  The high limit
 *
 * @return     { description_of_the_return_value }
 *
 * @ingroup    u8Transforms
 */
uint8_t u8AddLimSafe(uint8_t & _val, int _toAdd, uint8_t _lowLim, uint8_t _highLim);

/** @todo replace all instances of "lcount" with pflow2.LEDCount 
 *	and remove need to have "lcount" as function param
 *	
**/	

/**
 * @brief      Reversed value of variable already scaled between 0-LEDCount
 *
 * @param[in]  lval    The lval
 * @param[in]  lcount  The lcount
 *
 * @return     reverese of LED scaled value ie: (LEDCount-lval);
 *
 * @ingroup    u8LTransforms
 */
uint8_t lRev(uint8_t lval,uint8_t lcount);

/**
 * @brief      EaseIn function, No ease out;(Most likely very insufficient and
 *             slow)
 *
 * @param[in]  val    value to ease
 * @param[in]  power  amount to easy val by (0 - .99)
 *
 * @return     value returned easing val by power
 * 
 * 
 * 
 */
uint8_t phEase(uint8_t val, float power);

/**
 * @fn         ledDoCHSV(CHSV _chsv)
 *
 * @brief      Set all leds to this CHSV (typing reduction function)
 *
 * @param[in]  _chsv  The chsv to set all LEDs to
 *
 * @ingroup    DisplayBuilders
 */
void ledDoCHSV(CHSV _chsv);

/**
 * @brief      Set all leds to this CRGB (typing reduction function)
 *
 * @param[in]  _crgb  The crgb
 *
 * @ingroup    DisplayBuilders
 */
void ledDoCRGB(CRGB _crgb);

/**
 * @brief      Set all leds within a range to this CHSV (typing reduction
 *             function)
 *
 * @param[in]  _start  The start led
 * @param[in]  _end    The end led
 * @param[in]  _chsv   The chsv to set range of LEDs to
 *
 * @ingroup    DisplayBuilders
 */
void ledDoRangeCHSV(uint8_t _start, uint8_t _end, CHSV _chsv);

/**
 * @brief      Set all leds within a range to this CRGB (typing reduction
 *             function)
 *
 * @param[in]  _start  The start led
 * @param[in]  _end    The end led
 * @param[in]  _crgb   The crgb to set range of LEDs to
 *
 * @ingroup    DisplayBuilders
 */
void ledDoRangeCRGB(uint8_t _start, uint8_t _end, CRGB _crgb);




/**
 * @brief      Class for ph ticker.
 *
 * @ingroup    Workers
 */
class phTicker{
	public:
	phTicker();
	

	enum TICK_MODES{
		TPS_MODE=0,
		BPM_IN,
		BPM_U8BeatVal
	};
	
	bool tickCheck();

	/**
	 * @brief      calculates and returns the current ticker value
	 *
	 * @return     Returns the current tick
	 */
	uint16_t getTick();

	int16_t getTickSigned();

	/**
	 * @brief      Sets the Ticks Per Second.
	 *
	 * @param[in]  tps  TicksPerSecond
	 */
	void setTPS(uint32_t _tps);

	void setBPM(uint8_t _BPM);

	void setMode(uint8_t _mode);

	void setTimebase(uint32_t _timebase);

	void setTimebase();

	void setTickRange(uint32_t _tickLow,uint32_t _tickHigh);

	void setTickLimit(uint32_t _tickHigh);
	
	uint32_t tick=0;
	int16_t  signedTick=0;

	uint32_t elapsed;
	uint32_t rawTick;

	uint32_t tickLow = 0;
	uint32_t tickHigh;
	uint32_t tickWidth;

	uint32_t timebase = 0;
	uint32_t ticksPerSecond = 512;  //Nicer if TPS is multiple of tickRange
	uint8_t ticksBPM = 40;  //40BPM = Full bar of 160BPM <- The perfect tempo
	
	uint8_t tickMode=TPS_MODE;
	

	
	private:	//WOOT! I used my privates    
		
		
		uint32_t lastTick;

};

const uint8_t phGamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };



/**
 * @class      phTimer
 *
 * @brief      timer object with easy alarm checking and percent
 *             completed/remaining returned as uint8_t
 *
 * @ingroup    Workers
 */
class phTimer{

	public:

	phTimer();

	/**
	 * @fn         setMillis();	 *
	 * @brief      Set time interval of timer in milliseconds	 *
	 * @param[in]  millis  time interval in milliseconds
	 */
	void setMillis(uint32_t millis);

	/**
	 * @fn         setMicros();	 *
	 * @brief      Set time interval of timer in microseconds	 *
	 * @param[in]  micros  timer interval in microseconds
	 */
	void setMicros(uint32_t micros);

	/**
	 * @fn         start();	 *
	 * @brief      Starts the timer running
	 */
	void start();


	/**
	 * @brief      Restart timer with same settings
	 */
	void reSet();

	/**
	 * @brief      Check to see if timer is still running
	 *
	 * @return     Returns false if timer has not reached time interval; True if
	 *             timer reached
	 */	
	bool alarm();

	/**
	 * @brief      Check to see if timer is still running
	 *
	 * @return     Returns true if timer has not reached time interval; False if
	 *             timer reached
	 */
	bool running();

	/**
	 * @brief      Get percent of time interval completed
	 *
	 * @param[in]  scaleLow   The scale low
	 * @param[in]  scaleHigh  The scale high
	 *
	 * @return     Returns uint8_t with value 0-255 representing percent
	 *             completed
	 */
	uint8_t progress8(uint8_t scaleLow=0, uint8_t scaleHigh=255);

	/**
	 * @brief      Get percent of time interval remaining
	 *
	 * @param[in]  scaleLow   The scale low
	 * @param[in]  scaleHigh  The scale high
	 *
	 * @return     Returns uint8_t with value 0-255 representing percent
	 *             remaining
	 */
	uint8_t remaining8(uint8_t scaleLow=0, uint8_t scaleHigh=255);

		uint32_t timeMicros;
		uint32_t timeMillis;
		uint32_t startTime;
		uint32_t endTime;
		bool activated = true;
	};


/*
/**
 * @brief      Version 2 Timer. Once timer is started, timer can not be reset.
 *             Timer must run out. Timer can be called with
 *             phTimer2.setAndGo(uint32_t _timerMillis); Timer will activate
 *             itself, and will ignore following calls to set&go until timer has
 *             ran out.
 *
 *             Timer can be manually killed early with phTimer2.deactivate();
 *             Timer can also have additional "coolDown" time period that must
 *             run out before it can be set again
 *
 * @ingroup    Workers
 
class phTimer2{

	/**
	 * @brief      { function_description }
	 
	phTimer2();


	/**
	 * @brief      Sets and go.
	 *
	 * @return     { description_of_the_return_value }

	uint32_t setAndGo();


	/**
	 * @brief      Starts a time.
	 *
	 * @return     { description_of_the_return_value }
	
	uint32_t startTime();

	/**
	 * @brief      { function_description }
	
	void activate();


	/**
	 * @brief      { function_description }

	void deactivate();


	bool isActivated;
};
*/

/**
 * @brief      Class for double tapper.
 *
 * @ingroup    Workers
 */
class doubleTapper{
	public:

	/**
	 * @brief      { function_description }
	 */
	doubleTapper();


	/**
	 * @brief      Sets the tap interval millis.
	 *
	 * @param[in]  millisIn  The millis in
	 */
	void setTapIntervalMillis(uint32_t millisIn);


	/**
	 * @brief      Sets the tap interval micros.
	 *
	 * @param[in]  microsIn  The micros in
	 */
	void setTapIntervalMicros(uint32_t microsIn);


	/**
	 * @brief      { function_description }
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool tapIt();


	uint32_t tapIntervalMicros;
	
	uint32_t lastTapTime;
	uint32_t thisTapTime;
	uint32_t thisTimeDiff;

	bool doubleTapped = false;
};

/**
 * @brief      Calculates BPM based on beat triggers called
 * 			   by .beatIt();
 *
 * @ingroup    Workers
 */
class bpmDetector{
	public:

	/**
	 * @brief      { function_description }
	 */
	bpmDetector();

	/**
	 * @brief      Destroys the object.
	 */
	~bpmDetector();

	/**
	 * @brief      Sets how long between .beatIt() triggers
	 * 			   before wiping current running average and
	 * 			   recalculating BPM on next .beatIt() call 
	 */
	void setTimeOutMillis(uint32_t _millis);

	/**
	 * @brief      Used to reset timebase offset while maintaining
	 * 				current BPM;
	 */
	void reSetTimebase();

	/**
	 * @brief      Triggers a beat mark and uses time since last beat trigger to calculate
	 * 				BPM based on running average of time differences
	 *			  	 
	 * @return     Returns current BPM; 
	 */
	uint32_t beatIt();



	uint32_t secMilli =1000*60; 	/*!< 1 second in millis */

	uint32_t beatItCounter=0; 		/*!< #of beatTriggers in current array*/

	uint32_t timeOutMillis=2000;	/*!< millis between triggers before restaring running average*/

	uint32_t lastBeatItTime;		/*!< holds millis() of last beatIt trigger */	
	
	uint32_t thisBeatItTime;		/*!< time in millis of previous beatIt trigger */

	uint32_t timeDiff;				/*!< time difference between last trigger and current trigger */
	
	uint32_t currentBPM=0;			/*!< current BPM calculated by keeping running average of triggerTimes */

	uint32_t timeAverage;			/*< running average of beatIt() time differences */

	uint32_t timeBase;				/*< time in millis() of last beatIt() trigger. Used as offset for beatXX() */ 
};


/**	@todo
 *	STOP MAKING ALL THE THNGS PUBLIC! At some point all members
 *	should be placed where they properly belong.
 */

/**
 * @brief      accepts BPM value and generates multiple beat related
 * 				values based off specified BPM
 *
 * @ingroup    Workers
 */
class phBeater{

	public:
	/**
	 * @brief      Constructs the object
	 */
	phBeater();
	/**
	 * @brief      Destroys the object.
	 */
	~phBeater();
	

	/** @todo : HIGH_PRIORITY
	 *@brief   Move fine control to BPMDetector.
	 * 
	 * @more	Implementation of fine control over BPM calculation really
	 * belongs in the BPMDetector() object.  Remove from here, and implement
	 * in BPMDetector() before it gets used to much (AKA ASAP)
	 * 
 	 */

	/***** ENUMS *****/ 
	/**
	 * @enum
	 * @brief      For those who want fine control over how BPM is calculated 
	 * BPMType specifies the beatTrigger method used to set BPM.
	 * ie: triggering to the beat at 1,2,3,4... is quarterNote method
	 * ie: triggering on the "clap" would be a whole_note method and
	 * the triggerBeat would be DOWNBEAT_3.
	 * 
	 * Effects the speed of the output and allows for proper calculation of 
	 * bar counters and triggers used for BPM effects
	 * 
	 */	
	enum BPMTypes{
		QUARTER_NOTE = 0,
		HALF_NOTE,
		WHOLE_NOTE
	};
	/**
	 * @enum
	 * @brief      specifies which beat in a 4beat bar was used as trigger for
	 * for BPM calculation.  Can be set for personal preference of beat trigger
	 * method. Effects the shifting of start of bars for bar counters.
	 * 
	 * ie: triggering off first down beat of a bar(4beats) would = DOWNBEAT1.
	 * ie: triggering on the "clap" would most likely = DOWNBEAT3.
	 * ie: quarterNote doesn't matter. Half note should use first beat in bar triggered.
	 */	
	enum triggerBeat{
		DOWNBEAT1=0,
		DOWNBEAT2,
		DOWNBEAT3,
		DOWNBEAT4
	};


	/***** Functions *****/ 
	/**
	 * @brief       Updates the BPM & timeBase value that
	 * 				are used for beaters output
	 *
	 * @param[in]  _bpm       The BPM to be used
	 * @param[in]  _timeBase  The timebase to use as offset
	 */
	void update(uint32_t _bpm, uint32_t _timeBase);
	void updateGlobal();
	
	/**
	 * @brief      Circular shift through BPMTypes;
	 */
	void shiftBPMType();

	/**
	 * @brief      Circular shift through triggerBeat options;
	 */
	void shiftTriggerBeat();

	
	/***** Vars *****/ 
	uint8_t bpmType;		/*!< BPM technique used for beatTriggers */	
	uint8_t triggerBeat;	/*!< the downbeat triggered in a 4beat bar */

	uint32_t BPM;		/*!< BPM all values are derived from */	
	uint32_t bpm88;		/*!< (BPM * 256) for use with beat16(); */
	uint32_t timebase;	/*!< time offset from which to calc beats */

	uint8_t beatCountDown; 	/*!< time till next beat, scaled 255-0 */

	uint16_t u16Beat;  	/*!< beat scaled to uint16_t */
	uint16_t u8Beat;  	/*!< beat scaled to uint8_t */
	uint16_t u82lBeat;	/*!< u8Beat scaled 0-LEDCount */
	uint8_t  beat64; 	/*!< u8Beat scaled 0-64 (16th note) */

	uint8_t bar8Counter; 	/*!< Circular counter of 8 bars */
	uint8_t bar8Counted;	/*!< Flag for counter */
	uint8_t	bar16Counter;	/*!< Circular counter of 16 bars */
	uint8_t	bar16Counted;	/*!< Flag for counter */

	bool bar1;		/*!< bar1 Active Flag */
	bool bar4;		/*!< bar2 Active Flag */
	bool bar8;		/*!< bar3 Active Flag */
	bool bar16;		/*!< bar4 Active Flag */

	bool barDownBeat1;	/*!< downBeat Active Flag */
	bool barDownBeat2;	/*!< downBeat Active Flag */
	bool barDownBeat3;	/*!< downBeat Active Flag */
	bool barDownBeat4;	/*!< downBeat Active Flag */

	bool barUpBeat1;	/*!< upBeat Active Flag */
	bool barUpBeat2;	/*!< upBeat Active Flag */
	bool barUpBeat3;	/*!< upBeat Active Flag */
	bool barUpBeat4;	/*!< upBeat Active Flag */
};



/**
  *@union phLong
  * @brief      object for easy access to individual bytes of long var
  * 
  * @ingroup DataHelpers
  *  
  */
union phLong {
	uint32_t val;
	uint8_t bytes[sizeof(val)];
};

/**
  *@union phShort
  * @brief      object for easy access to individual bytes of short var
  * 
  * 
  * @ingroup DataHelpers 
  *  
  */
union phShort {
	uint32_t val;
	uint8_t bytes[sizeof(val)];
};



/**
 * @brief      Class for ph data float.
 */
class phDataFloat{
	public:

	/**
	 * @brief      { function_description }
	 */
	phDataFloat();

	/**
	 * @brief      Destroys the object.
	 */
	~phDataFloat();


	/**
	 * @brief      { function_description }
	 *
	 * @param[in]  _rawIn  The raw in
	 */
	void update(float _rawIn );
	

	// Min & Max possilbe for this data type
	// Set in constructor or monitored
	// if monitored, some functions may need
	// data samples before operating correctly
	float fMin;
	float fMax;

	//# of 1 Byte samples to keep for averaging
	uint8_t numSamples = 20;
	uint8_t activeThreshold;

	//Min/Max scaled to 1Byte values
	uint8_t u8Min;
	uint8_t u8Max;

	float rawIn; 	// current value
	uint8_t u8;		//calc u8 val for every sample
	





	//Returns current value with helpful conversions

	/**
	 * @brief      { function_description }
	 *
	 * @param[in]  u82l  The u 82 l
	 *
	 * @return     { description_of_the_return_value }
	 */
	uint8_t u8Rev(bool u82l);	// Current val scaled to 1 Byte and reversed
	
	
	/**
	 * @brief      { function_description }
	 *
	 * @param[in]  u82l  The u 82 l
	 *
	 * @return     { description_of_the_return_value }
	 */
	uint8_t u8High(bool u82l); 


	/**
	 * @brief      { function_description }
	 *
	 * @param[in]  u82l  The u 82 l
	 *
	 * @return     { description_of_the_return_value }
	 */
	uint8_t u8Low(bool u82l);


	/**
	 * @brief      { function_description }
	 *
	 * @return     { description_of_the_return_value }
	 */
	uint8_t u82l();		// Current 1 Byte val scaled to 0,ledCount
	


	/**
	 * @brief      { function_description }
	 *
	 * @return     { description_of_the_return_value }
	 */
	uint8_t u82lRev();	// Current 1 Byte val scaled to 0,ledCount & reversed
  	
  	/**
  	 * @brief      { function_description }
  	 *
  	 * @return     { description_of_the_return_value }
  	 */
  	uint8_t u8Abs();  	// 
};


class shapeGenerator
{
	public:
	shapeGenerator();
	~shapeGenerator();

	phTicker ticker;

	void play();

	void resizeMatrix(uint8_t x, uint8_t y);
	uint8_t columns =10;
	uint8_t rows = 10;
	uint8_t initialValue=0;

	

	//std::vector<std::vector<uint8_t>> matrix;	
	std::vector<std::vector<uint8_t>> matrix;

	//matrix.resize(rows, std::vector<uint8_t>(columns, initialValue) );

};



class phWave{
	public:
	phWave();
	

	uint8_t doWave(uint8_t);

	uint8_t width=255;
	uint8_t amp=130;
	uint8_t easeOut;
	uint8_t phaseShift;
	bool rev=false;
};





/**@todo REMAKE
 * optionsDisplay is really just acting as an activator.  Complete activator
 * class with timer based triggers and manual triggers.  Include activator object
 * in default "maker" class and use makers for all display options. 
 */
/*
class phActivator{
 public:
     phActivator(){};
     ~phActivator(){};

    enum activatorModes{
        TIMER_PULSE_ACTIVATE_RESET,
        MANUAL_KILL
    };

     bool isActive();     
     void activate();
     void deactivate();
     void touch();
     void start();

     //phTimer timer;

 private:
    uint8_t activatorMode;
};
*/









void changeLEDCount(uint16_t _newCount);

#endif