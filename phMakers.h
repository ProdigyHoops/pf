
#ifndef phMakers_h
#define phMakers_h


void stripRepeatAll(CRGB &leds,uint16_t _LEDCount, uint16_t _numFrom0ToCopy,bool _revIt);
void stripMirrorV(CRGB *_leds,uint16_t _LEDCount);
void stripMirrorH(CRGB *_leds,uint16_t _LEDCount);
void testAnimation();
void testSave1();
void testSaveWaves();

/**@todo MAKETHIS
 * Psuedo EQ pattern!
 * Use global beater, wide bars, easing, etc to make an
 * animated EQ with freq spikes accorded to beater data
 *
 */

/**@todo RESEARCH
 *  Figure out how to load the current animation by making a new
 *  instance ot the animations class, and then passing a pointer to
 *  the player controller. This would let the player controller handle
 *  the calls to .load(), run(), and deconstructing before loading next;
 *  
 */
class phMakerBase{
	public:
		phMakerBase(){};
		~phMakerBase(){};

		bool load();
		bool load(CRGB *_dummyLEDs);
		void getPFRefs();


		//prep() is inteded to be used in derived classes.
		//Included here in case derived class does not implement it.
		//Prop class always calls .load(),.prep(),.run()
		//Derived class's .prep() should overide this one.  
		void prep(){};

		void clear();
		void run(){};

		void blendPrep(CRGB *_dummyLEDs, paramPacket * _pbuIn);
		

		bool isDummy;
		bool doClear=true;
		

	protected:
		//phActivator status;
		phBeater * beat;
		paramPacket * params;
		paramPacket pbu;
		CRGB * leds;
		uint16_t LEDCount;
		paramPacket *pbu2;

		//Gives easy access to IR Key presses
		//The value only lives for the cycle in which it was
		//detected and is wiped during cycle maintenance. 
		//
		//Keep in mind that using this value in an animation 
		//does not stop the IRkey pressed from performing any
		//default action it's assigned to, so make sure you 
		//aren't using a key that will have confliting results
		//
		//Intended for implementing very simple ir response.
		//See remote or control class if you need more elaborate
		//Remote integration.
		uint32_t *irIn;
		uint32_t *BPM;
};







class phMakerExample : public phMakerBase{
	public:
		phMakerExample(){};
		~phMakerExample(){};
		uint16_t seg;
		/**
		 * @brief      called upon activating this maker.
		 * Use as needed to setup members of this class.
		 * The maker base class has a .load() function that gets
		 * called before this function. 
		 * .load() provides this class with access to global values
		 * and controls usefull for generating animations. 
		 * 
		 */
		void prep();

		//Is called after .prep() & allows for loading the paramPacket
		//with a set of default values to be used when maker is called
		//from "Make" menu.
		void loadDefaults(){};

		/**
		 * @brief     This is where the actual maker code should exist. 
		 * .run() is looped by the prop class for the duration of time
		 * this maker is active. Do NOT use timeblocking functions 
		 * unless absolutely needed. 
		 * 
		 * Prop class manages the actual output to the leds so you
		 * shouldn't have any calls to FastLED.show().
		 * 
		 * HOWEVER, the maker classes DO decide how the clearing
		 * of the previous frame is handled, so you need to atleast 
		 * include FastLED.clear(); at the beginning of .run()
		 * Free to use any other method desired. ie: fadeToBlackBy();
		 * 
		 * 
		 */
		void run();

		// Not sure if this is needed, or has any benefit. 
		// Is there ever a benifit from a class knowing
		// it's about to be deconstructed?
		void prepareForDeath(){};
};

class phMaker : public phMakerBase{
	public:
		phMaker(){};
		~phMaker(){};

		void prep();
		void run();
		void prepareForDeath(){};

		uint8_t seg;
};



class simplePinkRevMaker : public phMakerBase{
	public:
		simplePinkRevMaker (){};
		~simplePinkRevMaker (){};

		void prep();
		void run();
		void prepareForDeath(){};

		uint8_t seg;
};

class simpleBlueMaker : public phMakerBase{
	public:
		simpleBlueMaker(){};
		~simpleBlueMaker(){};
		uint16_t seg;

		void prep();

		void loadDefaults(){};

		void run();

		void prepareForDeath(){};
};






class blender : public phMakerBase{
	public:
		blender(){};
		~blender(){};

		void prep();
		void run();
		void prepareForDeath(){};

		phMakerExample pat1;
		phMaker pat2;

		CRGB *leds1;
		CRGB *leds2;
};




enum MAKERS2{
	SIMPLE_BLUE = 0,
	SIMPLE_PINK_REV = 1
};

enum MAKER_ACTIONS{
	LOAD_W_REAL_LEDS=0,
	LOAD_W_DUMMY,
	START_BLEND,
	KILL_MAKER,
	MAKER_RUN,
	MAKER_CLEAR,
	MAKER_PREP
};

class phDirector : public phMakerBase {
public:



	phDirector(){};
	~phDirector(){};

	void prep();	

	
 	bool makerChangeTrigger=false;

 	void prepBlender();
 	void buParams();
 	void pushLEDSets(CRGB *_LEDsGiver, CRGB *_LEDsTaker);
 	void startBlending(){};
 	void endBlend(){};
 	void run();


 	void makersDo(uint16_t _MAKER, uint16_t MAKER_ACTIONS);

 	template <typename M>
	void makersDoTemp(M *maker,uint16_t MAKER_ACTIONS);

	
	bool isBlending=false;
	uint8_t blenderCrossFader;
	uint32_t blendingTime=5000;
	uint32_t blendStart;
	uint32_t blendEnd;
	uint32_t blendCounter;

	
	

	CRGB *leds;
	CRGB *ledsRunning;
	CRGB *ledsBlendOut;	
	CRGB *ledsTmp; //used as a temp parking spot for CRGB vals

	
	uint16_t currentMaker;
	uint16_t nextMaker;
	bool makerLoaded;

	bool blendEasingOn;	
	bool blendingOn=true;
	bool beaterMixOn;
	bool beaterMixUseMotion;

	
	paramPacket pbu;


	//@todo URGENT! 
	//Implement this correctly
	//
	//Instance of each maker.
	// YES! I DO KNOW HOW HORRIBLE THIS IS!
	simplePinkRevMaker simplePinkRev;
	simpleBlueMaker simpleBlue;
	
	
};





#endif
