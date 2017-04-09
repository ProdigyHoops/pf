


#ifndef phRemote_h
#define phRemote_h



#define irRepeatKey 0
#define irPower 1
#define irSettings 2
#define irLock 3
#define irFavorite 4
#define irPlaylist 5
#define irBPMSet 6
#define irMotion 7
#define irBrightUp 8
#define irKickstart 9
#define irBattery 10
#define irPowerMode 11
#define irBrightDown 12

#define irDigit1 13
#define irDigit2 14
#define irDigit3 15
#define irDigit4 16
#define irDigit5 17
#define irDigit6 18
#define irDigit7 19
#define irDigit8 20
#define irDigit9 21
#define irDigit0 22

#define irM1 23
#define irM2 24
#define irM3 25
#define irM4 26
#define irM5 27
#define irM6 28

#define irNavUp 29
#define irNavDown 30
#define irNavLeft 31
#define irNavRight 32
#define irNavEnter 33
#define irNavReturn 34

#define irProgram 35
#define irOverBright 36
#define irRepeat 37
#define irPause 38
#define irPlay 39
#define irShuffle 40
#define irPHSet 41
#define irUserSet 42
#define irMakerSet 43
#define irSave 44


class prodigy;




struct irProfile{
	uint32_t repeatKey = 4294967295;
	uint32_t power = 16726725;
	uint32_t settings = 16759365;	
	uint32_t lock = 16745085;
	uint32_t favorite = 16712445;
	uint32_t playlist = 16718565;
	uint32_t bpmSet = 16751205;
	uint32_t motion = 16753245;
	uint32_t brightUp = 16720605;
	uint32_t kickstart = 16722645;
	uint32_t battery = 16755285;
	uint32_t powerMode = 16749165;
	uint32_t brightDown = 16716525;

	uint32_t digit1 = 16714485;
	uint32_t digit2 = 16747125;
	uint32_t digit3 = 16757325;
	uint32_t digit4 = 16726215;
	uint32_t digit5 = 16758855;
	uint32_t digit6 = 16742535;
	uint32_t digit7 = 16718055;
	uint32_t digit8 = 16750695;
	uint32_t digit9 = 16734375;
	uint32_t digit0 = 16722135;

	uint32_t m1 = 16724685;
	uint32_t m2 = 16775175;
	uint32_t m3 = 16767015;
	uint32_t m4 = 16771095;
	uint32_t m5 = 16762935;
	uint32_t m6 = 16773135;

	uint32_t navUp = 16754775;
	uint32_t navDown = 16756815;
	uint32_t navRight = 16730295;
	uint32_t navLeft = 16713975;
	uint32_t navEnter = 16746615;
	uint32_t navReturn = 16724175;
	
	uint32_t program = 16738455;
	uint32_t overBright = 16740495;
	
	uint32_t repeat = 16716015;
	uint32_t pause = 16748655;
	uint32_t play = 16732335;
	uint32_t shuffle = 16764975;
	
	uint32_t phSet = 16720095;
	uint32_t userSet = 16752735;
	uint32_t makerSet = 16736415;
	uint32_t save = 16769055;
};




class phRemote{
	public:
	phRemote(int pin);
	~phRemote();

	bpmDetector bpmTap;
	uint32_t irBPM;

	bool isRepeat;
	doubleTapper doublePause;

	int activeParamSet=1;	
	
	void passProdigy(prodigy *phIn);

	IRrecv irrecv;
	decode_results results;


	void loadProfile(irProfile profile);
	void start();
	void update();

	void processIR(uint32_t irCommand);


	//Remote pre-processing functions
	//void calcDigits(int inDigit);


	
	void 	digitIn(int _inDigit);

	int 	runningDigit=0;
	bool 	digitDoCount;
	uint8_t digitDoCountFor;






	void doThingsWithThisDigit(int _digitIn);


	std::map<long,int> irKeys;
	irProfile phIR;
	
	//Holds IR codes received
	uint32_t activeKey;
	long prevKey;
	//irProfile activeRemote;

	// Flags that are checked by prodigy 
	// each cycle
	bool commandWaiting;
	long commandCode;

	bool clearKeyFlag;

	uint8_t activeM;
};



#endif
