//#include "Arduino.h"

#ifndef prodigy_h
#include "prodigy.h"
//#include <TeensyTransfer.h>

#endif



prodigy2::prodigy2():ir(3){
	phRemote ir(3);

	ODsetUserBrightness.setSettings(2000,OD_SET_BRIGHTNESS);
	ODsetBPM.setSettings(2000,OD_SET_BPM);


	every1000ms.setMillis(1000);
	every1000ms.start();
	every10000ms.setMillis(10000);
	every10000ms.start();
};

//PRODIGY SETUP
	void prodigy2::configure(){

		//Initialize all hardware
		Serial.println("Config started");
		settings.loadCheck();
		setupLEDS(settings.hwf.data.LEDCount);
		setupIR();
		//setupIMU();
		initProp();

		//settings.hwf.data.LEDCount = 130;
		//hwFile setPoint = *settings.hwf;
		//settings.updateLEDCount(130);
		
		//bootUpAnimate();
		//waver2.rev = true;
		//waver3.width= LEDCount;
	};


	void prodigy2::setupLEDS(int _LEDCount){
		Serial.println(F("Starting LED Setup"));
		
		userBrightnessLevel = settings.user.data.brightLevelOnStartUp;
		LEDCount = _LEDCount;
		LEDMid=LEDCount/2;

		leds = new CRGB[LEDCount];
		//TmpLED = new CRGB[LEDCount];

		FastLED.addLeds<APA102,11,13,GBR,DATA_RATE_MHZ(12)>(leds,LEDCount);
		FastLED.setMaxPowerInVoltsAndMilliamps(settings.hwf.data.maxVoltage,100); 
		FastLED.setCorrection( TypicalSMD5050 );
		FastLED.setDither(0);
		setUserBrightness();		
	};
	void prodigy2::setupIR(){
		Serial.println("Starting IR In");
		ir.start();
	};
	void prodigy2::initProp(){

		prop.configure();
	};
//END


void prodigy2::bootUpAnimate(){
	Serial.println(F("Starting Boot Up Animate"));
	int t = millis();

	FastLED.clear();
	t=millis();
	while(millis()<t+2000){
		
		//FastLED.clear();
		//int mark = map((t+2000)-millis(),2000,0,0,LEDCount);
		int prog = map((t+2000)-millis(),2000,0,0,255);	
		int prog2 = phEase(prog,.9);
		int prog5= phEase(prog,.8);
		fadeToBlackBy(leds,LEDCount,prog5);

		int mark1 = map(prog2,0,255,0,LEDMid);
		int mark2 = map(prog2,0,255,LEDCount,LEDMid);
		
		int rand1 = random8(LEDCount);
		int rand2 = random8(LEDCount);

		if(rand1<mark1){
		leds[(rand1+18)%LEDCount]=CHSV(random8(),255,255);
		}
		if(rand2>mark2){
		leds[(rand2+18)%LEDCount]=CHSV(random8(),255,255);
		}
		FastLED.show();
		delay((255-prog5)/10);
	}

	t=millis();
	while(millis()<t+2000){
		
		//int mark = map((t+2000)-millis(),2000,0,0,LEDCount);
		int prog = map((t+2000)-millis(),2000,0,0,255);	
		int prog2 = phEase(prog,.9);
		int prog5= phEase(prog,.9);
		fadeToBlackBy(leds,LEDCount,10);

		int mark1 = map(prog2,0,255,LEDMid,0);
		int mark2 = map(prog2,0,255,LEDMid,LEDCount);
		
		leds[(mark1+18)%LEDCount]=CRGB(prog5,prog5,prog5);
		leds[(mark2+18)%LEDCount]=CRGB(prog5,prog5,prog5);
		FastLED.show();
		delay(10);
	}
	t=millis();
	while(t+500>millis()){
		fadeToBlackBy(leds,LEDCount,1);
		FastLED.show();
		delay(1);
	}
};
void prodigy2::setUserBrightness(){
	uint8_t mapBright = map(userBrightnessLevel,0,255,15,settings.hwf.data.maxBrightLevel);
	mapBright = phGamma8[mapBright];

	FastLED.setBrightness(mapBright);

	//TO-DO Add a limiterFlash here at low&high limit of bright level
};
void prodigy2::changeUserBrightnessLevel(int valToAdd){
	u8AddLimSafe(userBrightnessLevel,valToAdd,0,255);
	setUserBrightness();
};


void prodigy2::Run(){

	doEveryCycle();

	if(optionDisplayActive){
		prop.displayOption(activeOptionDisplay);
	}
	else{
		prop.play();
		prop.postFX();
		prop.show();
	}

};

/**
 * @brief      { function_description }
 */
void prodigy2::doEveryCycle(){
	updateIR();
	//beater.update(settings.run.data.BPM,settings.run.data.bpmTimebase);


	if(!every1000ms.running()){

		doEvery1000Millis();
		every1000ms.reSet();
	}
	if(!every10000ms.running()){
		batLevel = 2*4.2*analogRead(A1)/1024;
		doEvery10000Millis();
		every10000ms.reSet();
	}
};

/**
 * @brief      { function_description }
 */
void prodigy2::doEvery1000Millis(){
	batLevel = 2*4.2*analogRead(A1)/1024;
	Serial.print(F("batLevel : "));
	Serial.print(batLevel);
	//Serial.print();
	Serial.print(F("freeMemory() = "));
	Serial.print(freeMemory());
	Serial.print(F(" | millis() Time = : "));
	Serial.print(millis());
	//Serial.print();
	Serial.print(F(" | frameDelay ="));
	Serial.print(prop.frameDelay);
	Serial.println();
	
	
};

void prodigy2::doEvery10000Millis(){
	Serial.print(F("Every10SecStarted "));
	Serial.println();
	prop.director.makerChangeTrigger=true;


	
	
};

/**
 * @brief      { function_description }
 */
void prodigy2::updateIR(){
	
	ir.update();
};

/**
 * @brief      Sends a command.
 *
 * @param[in]  _action  The action
 */
void prodigy2::sendCommand(uint8_t _action){
	Serial.println("Command received by pflow.  Sending to prop");
	prop.control(_action);
};


/**
 * @brief      Constructs the object.
 */
protege::protege(){
	//phConfig sets;
	//maker make;
	//phRemote ir;
};


/**
 * @brief      Destroys the object.
 */
protege::~protege(){
};

/**
 * @brief      { function_description }
 */
void protege::configure(){

	
	//maker.load();
	//maker.prep();

	//maker2.load();
	//maker2.prep();
	blendy.load();
	blendy.prep();
	director.load();
	director.prep();
	director.makersDo(SIMPLE_BLUE,LOAD_W_DUMMY);
	
	director.currentMaker = SIMPLE_BLUE;
	director.nextMaker=SIMPLE_PINK_REV;

};


void protege::createMenu(){
};


void protege::displayOption(uint8_t activeOptionDisplay){
	switch(activeOptionDisplay){
		case OD_SET_BRIGHTNESS:
			if (pflow2.ODsetUserBrightness.isActive()){
				setUserBrightnessGUI(pflow2.ODsetUserBrightness);
			}
		break;
		case OD_SET_BPM:
			if (pflow2.ODsetBPM.isActive()){
				setBPMGUI(pflow2.ODsetBPM);
			}
		break;
	}
};

/**
 * @brief      { function_description }
 */
void protege::play(){

	//Temporary Test Pattern

	//pflow2.shaper.play();


	director.run();
	FastLED.show();
	director.clear();

	};


	
	/*
	uint8_t beatMarker = u8beat2l(40);
	FastLED.clear();
	pflow2.leds[beatMarker]=CHSV(123,255,255);
	*/

	//blendy.run();
	
	
		



void protege::postFX(){
};


void protege::show(){
	FastLED.show();
	delayMicroseconds(100);
	frameDelay=micros()-lastFrameTime;
	lastFrameTime=micros();
};


void protege::control(uint8_t _action){
	Serial.print("Prop received request to perform action with id: ");
	Serial.println(_action);
	switch(_action){
		case DISPLAY_MENU_ITEM:

		break;

		case MENU_NEXT_ITEM:
		/*
			Serial.println("GoNextMenu triggered");
			activeMenu->menuItemNext();
			menuItemDisplay();
			//Serial.println("Next Menu Item : ");
			//Serial.println(activeMenu.itemCount);
			*/
		break;

		case MENU_SELECT_OPTION:/*
			Serial.println("SelectMenuOption triggered");
			activeMenu = &activeMenu->menuItemSelect();
			menuItemDisplay();
			*/
		break;

		default:
			Serial.println("Unknown Command Action");
		break;


	}
};

void protege::setUserBrightnessGUI(optionsDisplay &displayControl){
	FastLED.clear();

	
	uint8_t timeProgress = phEase(displayControl.timer.progress8(),.4);
	uint8_t timeTillExit=255-timeProgress;
	uint8_t ledBrightLevelMark = u82l(pflow2.userBrightnessLevel,pflow2.LEDCount);

	CHSV ledColor = CHSV(128,255,timeTillExit);
	ledDoRangeCHSV(0,ledBrightLevelMark,ledColor);
	pflow2.leds[ledBrightLevelMark]=CHSV(64,255,timeTillExit);

	FastLED.show();
	delay(1);
	//Serial.println(timeTillExit);
};

void protege::setBPMGUI(optionsDisplay &displayControl){
	FastLED.clear();
	CHSV color = CHSV(220,255,255);
	pflow2.beater.update(pflow2.settings.run.data.BPM,pflow2.settings.run.data.bpmTimebase);
	pflow2.leds[pflow2.beater.u82lBeat]=CHSV(164,255,255);
	

	uint8_t barBright=(pflow2.beater.beatCountDown*7)%255;	
	CHSV color3 = CHSV(pflow2.beater.beatCountDown,255,barBright);
	CHSV color4 = CHSV(pflow2.beater.beatCountDown,255,pflow2.beater.beatCountDown);
	CHSV color1 = CHSV(116,255,255);
	CHSV color2 = CHSV(180,255,255);
	CHSV color5 = CHSV(225,255,255);
	CHSV color6 = CHSV(0,0,0);
	uint8_t barLED=0;
	CHSV barCHSV = color4;

	pflow2.beater.barDownBeat1 ? barLED = 11 : 0;
	pflow2.beater.barDownBeat2 ? barLED = 13 : 0;
	pflow2.beater.barDownBeat3 ? barLED = 15 : 0;
	pflow2.beater.barDownBeat4 ? barLED = 17 : 0;
	pflow2.beater.barUpBeat1 ? barLED = 12 : 0;
	pflow2.beater.barUpBeat2 ? barLED = 14 : 0;
	pflow2.beater.barUpBeat3 ? barLED = 16 : 0;
	pflow2.beater.barUpBeat4 ? barLED = 18 : 0;
	barLED--;


	
	pflow2.leds[barLED]=color2;
	(barLED == 0) ? (pflow2.leds[barLED]=color1) : color2;
	
	pflow2.leds[18+pflow2.beater.bar8Counter]=color5;
	(pflow2.beater.bar8Counter == 0) ? (pflow2.leds[18+pflow2.beater.bar8Counter]=color2) :color5;

	if(pflow2.beater.bar8Counter==7){
		ledDoCHSV(color3);
	}
	
	if(pflow2.beater.bar8Counter==7){
		//if(pflow2.beater.beat64==0){ledDoCRGB(CRGB(255,255,255));}//ledDoCHSV(color3);
	}

	if(pflow2.beater.barDownBeat1){ledDoCHSV(color);}
	
	if(pflow2.beater.barDownBeat3){ledDoCHSV(color1);}

	FastLED.show();
};

/*

prodigy::prodigy() : ir(3){
	//Run phConfig routine
	//-- Checks for fresh install
	//-- loads setting files into memory
	//Serial.printf("b=%03d.", newInstall);
	Serial.print("LEDCount = ");
	Serial.println(54);

	//ledCount = 54;
	//ledMid = ledCount/2;
	//ledQuarter = ledCount / 4;
	//Serial.println("Preparing LEDS");
	//leds = new CRGB[54];
	//tmpLED = new CRGB[54];


	ir.passProdigy(this);
	//make.passProdigy(this);
	//phRemote ir;
	//this->ir=phRemote ir(sets.hw.IRReceivePin);
	//ir.start();
};

*/



/*
prodigy::~prodigy(){
};
void prodigy::configure(){

	//sets.loadCheck();
	//delay(100);
	//setupIMU();
	//setupLED();
	// irrecv.enableIRIn(); // Start the receiver
};
void prodigy::setupIMU(){
	imu.startUp();
};
void prodigy::setupLED(){
	
	FastLED.addLeds<APA102,11,13,GBR,DATA_RATE_MHZ(12)>(leds,54);
	FastLED.setMaxPowerInVoltsAndMilliamps(sets.hw.maxVoltage,sets.hw.maxMilliAmp); 
	FastLED.setDither( 0 );
	FastLED.setCorrection( TypicalSMD5050 );
	leds[0]=CHSV(128,255,255);	
	FastLED.show();
	delay(3000);
	FastLED.clear();
	FastLED.show();		
	make.ledCount = 54;
	make.leds = leds;
	make.sets = sets;
};

void prodigy::postFX(){

	blur1d(leds,ledCount,postBlurAmount);
};

void prodigy::cycleChecks(){
	//Serial.println("running cycle");
	//Serial.println("Try Play");
	
	//	play();
	//Serial.println("Try postFX");
	//	postFX();
	//Serial.println("Try show");
	
	//	show();
	//Serial.println("Try IRUpdate");
 	// 	ir.update();
  	//Serial.println("Try imuUpdate");
 	// 	imu.update();
};

void prodigy::play(){
	//make.makeThis(0);
	/*switch(sets.run.data.currentProgram){
		case ANIMATION_PLAYER:
			make.makeThis(sets.params.data.makerIndex);
		break;
	};
}

void prodigy::show(){
	//play();
	
	FastLED.show();
	//cycleChecks();

	//FastLED.clear();
};

uint8_t prodigy::u82l(uint8_t val){

	return map(val,0,255,0,54);
};

void prodigy::rollLED(uint8_t rollVal){

	for(int i=0;i<54;i++)
	{
	tmpLED[i]=leds[i];
	}
	for(int i=0;i<54;i++)
	{
	leds[i]=tmpLED[(i+rollVal)%(54)];
	}	
};

void prodigy::setBrightness(){
};

void prodigy::brightUp(){
};

void prodigy::brightDown(){
};

void prodigy::checkBattery(){

	batLevel = 2*4.2*analogRead(A1)/1024;
};

void prodigy::flash(uint8_t flashOnTime, uint8_t flashOffTime, uint8_t flashRepeats, uint8_t hue){
	for(int i=0;i<54;i++)
	{
	tmpLED[i]=leds[i];
	}
	
	FastLED.clear();
	//FastLED.show();
	//delay(250);

	CRGB color = CRGB(0,255,255);
	FastLED.showColor(color,255);
	delay(flashOnTime);

	FastLED.clear();
	FastLED.show();
	delay(flashOffTime);	

	for(int i=0;i<54;i++)
	{
	leds[i]=tmpLED[i];
	}

	FastLED.show();
};

void prodigy::animatedLevel(){
	phTimer timer;
	timer.setMillis(250);
	timer.start();

	while( timer.running() )
	{
		int ledMark = map(timer.progress8(),0,255,0,54);
		FastLED.clear();
		for (int i = 0; i < ledMark ; ++i){
			leds[i]=CRGB(255,0,0);				
		}
		FastLED.show();
	}
};

void prodigy::splitChaseUp(int chaseTime,int postWaitTime){
	FastLED.clear();
	phTimer timer;
	timer.setMillis(1000);
	timer.start();

	while( timer.running() )
	{
		int mark1 = timer.progress8(0,ledCount-1);
		//int mark2 = timer.progress8(ledMid,ledCount-1);
		int prog = timer.progress8();
		leds[mark1]=CRGB(prog,prog,prog);
		//leds[mark2]=CRGB(prog,prog,prog);

		Serial.print("progMapped,prog: ");
		Serial.print(mark1);
		Serial.print(":");
		Serial.println(prog);
		
		FastLED.show();
		FastLED.clear();
	}
	delay(postWaitTime);
};

*/

/**
 * @brief      Constructs the object.
 */
optionsDisplay::optionsDisplay(){
};

/**
 * @brief      Sets the settings.
 *
 * @param[in]  _timeoutMillis  The timeout millis
 * @param[in]  _odTracker      The od tracker
 */
void optionsDisplay::setSettings(uint32_t _timeoutMillis, uint32_t _odTracker){
	setTimeOutMillis(_timeoutMillis);
	setODTracker(_odTracker);
	deactivate();
	//timer.start();
	//activate();
};

/**
 * @brief      Determines if active.
 *
 * @return     True if active, False otherwise.
 */
bool optionsDisplay::isActive(){
	if(timer.running()){
		return true;
	}
	else{
		deactivate();
		return false;
	}
};


/**
 * @brief      { function_description }
 */
void optionsDisplay::activate(){	
	pflow2.optionDisplayActive = true;
	pflow2.activeOptionDisplay = odTracker;
	timer.reSet();
};

/**
 * @brief      { function_description }
 */
void optionsDisplay::deactivate(){
	pflow2.optionDisplayActive = false;
	timer.activated=false;
};

/**
 * @brief      Sets the time out millis.
 *
 * @param[in]  _timeoutMillis  The timeout millis
 */
void optionsDisplay::setTimeOutMillis(uint32_t _timeoutMillis){
	timer.setMillis(_timeoutMillis);
	timer.start();
};

/**
 * @brief      Sets the od tracker.
 *
 * @param[in]  _odTracker  The od tracker
 */
void optionsDisplay::setODTracker(uint32_t _odTracker){

	odTracker = _odTracker;
};

/**
 * @brief      { function_description }
 */
void optionsDisplay::pulse(){
	if(timer.running()){
		timer.reSet();
	}
	else{
		activate();
		timer.reSet();
	}
};


prodigy2 pflow2;














/*

//PHData is a class mostly used by motion data OR 
//any data that is constantly monitored and can be 
//better used as a normalized uint8_t with smoothing 
//and activity monitoring
phData::phData(long minVal, long maxVal,uint8_t intSamples,int NUM_LEDS)
{
	min = minVal;
	max = maxVal;
	led_count = NUM_LEDS;
	samples = intSamples;
	smoothData = new uint8_t[ samples ]{0}; 
	changeSmoothData = new uint8_t[ samples ]{0}; 
	changeSamples = intSamples;
	thisChange=0;
	millisTillSettled = 3000;
	settleThreshold = 5;
	lastPost = millis();
	postRate=100;

} 

void phData::setActiveThresholds(long settlingTime, uint8_t threshold)
{
	millisTillSettled = settlingTime;
	settleThreshold = threshold;

}

void phData::post(float val)
{
	postRun(val);
	if ( (millis()-lastPost)  > postRate )
	{
		changeMonitor();
	}
}

void phData::changeMonitor()
{
	thisChange=abs(int8-lastInt8); //calculate difference from last
	lastInt8=int8;	//save this to last

	if (changeSmooth < settleThreshold)
	{	
		if (!settled)
		{	
			if (isSettling)
			{
				settlingTimer=millis()-settleInitated;
			}
			else
			{
				isSettling=true;
				settleInitated=millis();
				settlingTimer=millis()-settleInitated;
			}

			if (settlingTimer > millisTillSettled)
			{
				settled = true;
				isSettling=false;
			}


		}
		


	}
	else
	{
		isSettling=false;
		settled=false;
		settlingTimer=0;
	}
	lastPost=millis();

}


void phData::postRun(float val)
{
	raw = val;
	microStart=micros();		//benchmarking timer
	int8 = map(val,min,max-1,0,255);
	

	intLED = map(int8,0,255,0,led_count-1);  //map val to led_count
	abs8 = map(abs(val),0,max,0,255);	//abs val 
	
	//Rev maps, useful for directional animations
	int8Rev = map(val,min,max,255,0);	
	intLEDRev = map(int8,0,255,led_count-1,0);

	// direction indicator and axis split
	if (val >= 0)
	{
		posi = true; 
		splitHighInt8 = map(val,0,max,0,255);
		splitLowInt8=0;
	}
	else
	{
		posi = false;
		splitHighInt8=0;
		splitLowInt8=map(val,min,0,0,255);
	}

	//Smoothing filters for int8 & intChange
	smooth();

	postMicroTime=micros()-microStart;
	intLEDSmooth=map(int8Smooth,0,255,0,led_count-1);

	// Analyse change over time for inactivity level

	

}

void phData::debug()
{
	Serial.println();
	Serial.print("|  raw : ");
	Serial.print(raw);
	Serial.print("|  int8 : ");
	Serial.print(int8);
	Serial.print("|  intLED  :  ");
	Serial.print(intLED);
	Serial.print("|  abs8  :  ");
	Serial.print(abs8);
	Serial.print("|  smoothInt8 :  ");
	Serial.print(int8Smooth);	
	Serial.print("|  changeSmooth :  ");
	Serial.print(changeSmooth);	
	Serial.print("|  settled :  ");
	Serial.print(settled);	
	Serial.print("|  postMicroTime :  ");
	Serial.print(postMicroTime);	

}

void phData::smooth()
{

  smoothTotal = smoothTotal - smoothData[smoothIndex];
  smoothData[smoothIndex] = int8;
  smoothTotal = smoothTotal + smoothData[smoothIndex];
  smoothIndex = smoothIndex + 1;
  if (smoothIndex >= samples){
   	smoothIndex = 0;
   }
  int8Smooth = smoothTotal / samples;

  changeSmoothTotal = changeSmoothTotal - changeSmoothData[changeSmoothIndex];
  changeSmoothData[changeSmoothIndex] = thisChange;
  changeSmoothTotal = changeSmoothTotal + changeSmoothData[changeSmoothIndex];
  changeSmoothIndex = changeSmoothIndex + 1;
  if (changeSmoothIndex >= changeSamples){
   	changeSmoothIndex = 0;
   }
  changeSmooth = changeSmoothTotal / changeSamples;

}

*/



 	





