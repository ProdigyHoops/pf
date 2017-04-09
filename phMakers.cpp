#ifndef phMakers_h
#include "prodigy.h"
#endif




void stripRepeatAll(CRGB *_leds,uint16_t _LEDCount, uint16_t _numFrom0ToCopy,bool _revIt=false){
	uint8_t gap = _numFrom0ToCopy;
	

	uint8_t repeatTiles = (_LEDCount/_numFrom0ToCopy)-1;
	uint8_t remainderLEDs = _LEDCount - (repeatTiles*_numFrom0ToCopy);

	bool revTile = true;
	for(int t=0;t<repeatTiles;t++){
		for(int l=0;l<(_numFrom0ToCopy);l++){
			if(_revIt){
				if(revTile){
					_leds[((gap-1)-l)+(gap*(t+1))] = _leds[l];
				}
				else{
					_leds[l+(gap*(t+1))] = _leds[l];
				}
				revTile=!revTile;
			}
			else{
				_leds[l+(gap*(t+1))] = _leds[l];
			}
			
		}
	}

	for(int r=0; r<remainderLEDs;r++){
		if(_revIt){
			if(revTile){
				_leds[ r+ (gap*repeatTiles)]=_leds[r];
			}
			else{
				_leds[r+ (gap*repeatTiles)]=_leds[r];
			}
		}
		else{
			_leds[r+ (gap*repeatTiles)]=_leds[r];
		}
		
	}	
};
void stripMirrorV(CRGB *_leds,uint16_t _LEDCount){
	bool isOdd = _LEDCount%2;
	uint16_t midLED = _LEDCount/2;

	for(int l=0;l<midLED;l++){
		_leds[(_LEDCount-1)-l]=_leds[l];
	};
};
void stripMirrorH(CRGB *_leds,uint16_t _LEDCount){
	bool isOdd = _LEDCount%2;
	uint16_t midLED = _LEDCount/2;
	uint16_t quarterLED = _LEDCount/4;
	uint16_t three4LED = midLED+quarterLED;

	for(int l=0;l<midLED;l++){
		_leds[(quarterLED)+l]=_leds[(three4LED+l)%_LEDCount];
	};
};



void testAnimation(){
		FastLED.clear();
};

void testSave1(){
	uint8_t beatMark;// = beat8(255);
		//uint8_t beatMark = beat8(255);
		//uint8_t sin1 = sin8((millis()*4)%255);
		uint8_t timeMark=(millis()/4)%10;
		//beatMark = map8(beatMark,0,14);
		//beatMark = map8(sin1,0,9);
		beatMark=timeMark;
		//pflow2.leds[beatMark]=CHSV(beatMark+160,255,255);
		pflow2.leds[9-beatMark]=CHSV((beatMark*5)+60,255,255);

		stripRepeatAll(pflow2.leds,pflow2.LEDCount,10);
		stripMirrorV(pflow2.leds,pflow2.LEDCount);
		stripMirrorH(pflow2.leds,pflow2.LEDCount);
			//delayMicroseconds(500);
};

void testSaveWaves(){
		FastLED.clear();
		uint8_t wave1 = sin8(millis()*2);;
		uint8_t wave2 = sin8(millis()*1);
		
		uint8_t wave81=wave1;
		uint8_t wave82 = wave2;
		wave2 = u8Rev(wave2);

		u82lbRef(wave1);
		u82lbRef(wave2);

			uint8_t seg = pflow2.LEDCount/8;

			uint8_t snip = map8(wave81,0,seg);
			uint8_t snip2 = map8(wave82,0,seg);

					pflow2.leds[snip]=CHSV(72,255,wave82);
					pflow2.leds[(seg-1)-snip]=CHSV(124,255,wave81);

					pflow2.leds[snip2]=CHSV(180,255,wave82);
					pflow2.leds[(seg-1)-snip2]=CHSV(40,255,wave81);
					

					stripRepeatAll(pflow2.leds,pflow2.LEDCount,seg);
					stripMirrorV(pflow2.leds,pflow2.LEDCount);
					stripMirrorH(pflow2.leds,pflow2.LEDCount);
		//pflow2.leds[wave2]=CHSV(200,150,100);
		//delay(1);	
		if(wave1 == wave2){
			
			

			//pflow2.leds[wave1]=CHSV(222,255,255);
		}	
};



bool phMakerBase::load(){
	leds = pflow2.leds;
	isDummy = false;
	getPFRefs();
};

bool phMakerBase::load(CRGB *_dummyLEDs){
	leds = _dummyLEDs;
	isDummy = true;
	getPFRefs();
};

void phMakerBase::getPFRefs(){
	beat = &pflow2.beater;
	params = &pflow2.settings.params;
	BPM = &pflow2.settings.run.data.BPM;
	LEDCount = pflow2.LEDCount;
};

void phMakerBase::clear(){
	if(!isDummy){ FastLED.clear(); }
	else{
	for(int l=0;l<LEDCount;l++){leds[l]=CRGB(0,0,0);}
	}

};

void phMakerBase::blendPrep(CRGB *_dummyLEDs, paramPacket * _pbuIn){
	leds = _dummyLEDs;
	/*for(int b=0;b<sizeof(pbu);b++){
		pbu.bytes[b]=params->bytes[b];
	}*/
	params = _pbuIn;
	isDummy = true;
}





void phMakerExample::prep(){

		seg=6;
};
void phMakerExample::run(){
	if(!isDummy){ FastLED.clear(); }
	
	uint8_t markPoint = map8(beat8(160),0,seg-1);

	leds[markPoint] = CHSV(128,255,255);
	stripRepeatAll(leds,LEDCount,seg);
};



void simplePinkRevMaker::prep(){

	seg = 6;
};
void simplePinkRevMaker::run(){
	if(!isDummy){ FastLED.clear(); }
	
	uint8_t markPoint = map8(u8Rev(beat8(250)),0,seg-1);

	leds[markPoint] = CHSV(64,255,255);
	stripRepeatAll(leds,LEDCount,seg);
	//delay(1);
};


void simpleBlueMaker::prep(){

		seg=6;
};
void simpleBlueMaker::run(){
	if(!isDummy){ FastLED.clear(); }
	
	uint8_t markPoint = map8(beat8(250),0,seg-1);

	leds[markPoint] = CHSV(128,255,255);
	leds[(seg-1)-markPoint] = CHSV(128,255,255);
	stripRepeatAll(leds,LEDCount,seg);
};










void phMaker::prep(){

	seg = 6;
};

void phMaker::run(){
	if(!isDummy){ FastLED.clear(); }
	
	uint8_t markPoint = map8(u8Rev(beat8(250)),0,seg-1);

	leds[markPoint] = CHSV(64,255,255);
	stripRepeatAll(leds,LEDCount,seg);
	//delay(1);
};

void blender::prep(){
	pat1.prep();
	pat2.prep();

	leds1 = new CRGB[LEDCount];
	leds2 = new CRGB[LEDCount];

	pat1.load(leds1);
	pat2.load(leds2);
};

void blender::run(){
	if(!isDummy){ FastLED.clear(); }

	/**@todo DoItBetterFasterStronger
	 * There is a better way to wipe out the array then this.
	 * Figure it out. Fix it. 
	 */
 	for(int l=0;l<LEDCount;l++){leds1[l]=CRGB(0,0,0);}

 	for(int l=0;l<LEDCount;l++){leds2[l]=CRGB(0,0,0);}

	pat1.run();
	pat2.run();
	uint8_t blendAmount = ease8InOutApprox(beatsin8(2));
	blend (leds1, leds2,leds,LEDCount,blendAmount);

	/*for(int l=0;l<LEDCount;l++){
		leds[l]=leds1[l];
	}
	*/
}





void phDirector::prep(){
	leds = pflow2.leds;
	ledsRunning = new CRGB[LEDCount];
	ledsBlendOut = new CRGB[LEDCount];
	ledsTmp = new CRGB[LEDCount];
};

void phDirector::run(){
	if(makerChangeTrigger){
		//Serial.print(F("MakerCHange trigger "));
		//Serial.println();
		
		prepBlender();
		isBlending=true;
		blendStart = millis();
		blendEnd = blendStart+blendingTime;
		makerChangeTrigger=false;
		
	}
	if(isBlending){
		//Serial.print(F("Im blending "));
		//Serial.println();
		
		if(millis()>blendEnd){
			/*Serial.print(F("millis() "));
			Serial.print(millis());
			Serial.print("  |  ");
			Serial.print(F("blendEnd "));
			Serial.print(blendEnd);
			Serial.println();
			*/
			
			isBlending=false;
			uint16_t tmp = currentMaker;
			currentMaker = nextMaker;
			nextMaker = tmp;
		}
		else{
	
			
		blendCounter = millis() - blendStart;
		//Serial.print(F("blendCounter "));
		//Serial.print(blendCounter);
		//Serial.println();
		blenderCrossFader=map(blendCounter,0,blendingTime,0,255);
		makersDo(currentMaker,MAKER_CLEAR);
		makersDo(nextMaker,MAKER_CLEAR);
		makersDo(currentMaker,MAKER_RUN);
		makersDo(nextMaker,MAKER_RUN);
		blend (ledsBlendOut,ledsRunning,leds,LEDCount,ease8InOutApprox(blenderCrossFader));

		}	
	}
	else{
	//	Serial.print(F("Im running "));
		//Serial.println();
		
		makersDo(currentMaker,MAKER_CLEAR);
		makersDo(currentMaker,MAKER_RUN);
		for(int l=0;l<LEDCount;l++){leds[l]=ledsRunning[l];}
		
	}
};


void phDirector::prepBlender(){
	makersDo(currentMaker, START_BLEND);
	makersDo(nextMaker, LOAD_W_DUMMY);

};

void phDirector::makersDo(uint16_t _MAKER, uint16_t MAKER_ACTIONS){
	switch(_MAKER){
	
		case SIMPLE_PINK_REV:
			makersDoTemp(&simplePinkRev,MAKER_ACTIONS);
		break;

		case SIMPLE_BLUE:
			makersDoTemp(&simpleBlue,MAKER_ACTIONS);
		break;

		case 9:

		break;

	}
}

template <typename M>
void phDirector::makersDoTemp(M *maker,uint16_t MAKER_ACTIONS){
	switch(MAKER_ACTIONS){

		case LOAD_W_REAL_LEDS:
			maker->load();
			maker->prep();
		break;

		case LOAD_W_DUMMY:
			maker->load(ledsRunning);
			maker->prep();
		break;

		case START_BLEND:
			buParams();
			maker->blendPrep(ledsBlendOut,&pbu);
		break;

		case MAKER_RUN:
			maker->run();
		break;

		case MAKER_CLEAR:
			maker->clear();
		break;

		case MAKER_PREP:
			maker->prep();
		break;
	}
}


void phDirector::pushLEDSets(CRGB *_LEDsGiver, CRGB *_LEDsTaker){

};

void phDirector::buParams(){
	for(int b=0;b<sizeof(pbu);b++){
		pbu.bytes[b]=pflow2.settings.run.bytes[b];
	}
};







/*


maker::maker(){
	
	makingNow=0;	
};
 
maker::~maker(){
};



void maker::makeThis(int _maker){
	switch(_maker){

		case DUAL_STRIPES:
			dualStripes();
		break;
	};

}
 /*
void maker::passProdigy(prodigy *phIn){
	ph = phIn;
	ledCount = ph->ledCount;
};



void maker::dualStripes(){	

	uint8_t width1	= 	u8Lim(ph->sets.params.data.params[1].val[0],2,20);
	uint8_t hue1 	=	ph->sets.params.data.params[1].val[1];

	uint8_t sat1 	=  	ph->sets.params.data.params[2].val[0]; 
	uint8_t bright1 = 	ph->sets.params.data.params[2].val[1];

	uint8_t width2 	= 	u8Lim(ph->sets.params.data.params[3].val[0],2,20);
	uint8_t hue2 =		ph->sets.params.data.params[3].val[1];

	uint8_t sat2 	=  	ph->sets.params.data.params[4].val[0]; 
	uint8_t bright2 = 	ph->sets.params.data.params[4].val[1];

	uint8_t hueShift1Speed = ph->sets.params.data.params[5].val[0];
	uint8_t hueShift2Speed = ph->sets.params.data.params[5].val[1];
	uint8_t stripeSpinSpeedBy10 	=	u8Lim(ph->sets.params.data.params[6].val[0],0,22);
	uint8_t stripeSpinSpeedFine	= 	u8Lim(ph->sets.params.data.params[6].val[1],0,25);
	
	
	bool motionOn 		= ph->sets.params.data.phToggle1;
	bool dirFlipOnly 	= ph->sets.params.data.phToggle2;
	bool stripRotationSpeedManual		= ph->sets.params.data.phToggle3;
	bool dirReverse		= ph->sets.params.data.phToggle4;



	//Calculate total StripeSpinSpeed
	uint8_t stripeSpinSpeed = (stripeSpinSpeedBy10 *10)+stripeSpinSpeedFine;
	u8Lim(stripeSpinSpeed,0,255);


	uint8_t stripeShifter;
	uint8_t hue1Shifter = beat8(hueShift1Speed);
	uint8_t hue2Shifter = beat8(hueShift2Speed);

	if(stripRotationSpeedManual){
		stripeShifter = beat8(stripeSpinSpeed);
	}
	else{
		stripeShifter = beat8(ph->sets.run.data.BPM);
	};

	
	//Get & set motion options 
	if(motionOn){
		if(dirFlipOnly){
			ph->sets.run.data.postIMURoll = false;
		}
		else{
			ph->sets.run.data.postIMURoll = true;
		};
	}
	else{
		ph->sets.run.data.postIMURoll=false;
	};
	
	
	uint8_t mark1=0;
	uint8_t mark2=0;


	
	FastLED.clear();	
	for(int i=0;i<ledCount;i=i)	{
		for(int w1 = 0;w1<width1;w1++){
			mark1 = u8WTF(i,stripeShifter,ledCount,dirReverse);			
			leds[mark1]=CHSV(hue1,sat1,bright1); i++;
		}
		for(int w2 = 0;w2<width2;w2++){
			mark2=u8WTF(i,stripeShifter,ledCount,dirReverse);
			leds[mark2]=CHSV(hue2,sat2,bright2); i++;
		}		
	}
};

void maker::beatScan(uint8_t bpm){
	uint8_t u825p = (255/4);
	uint8_t u850p = (255/2);
	uint8_t u875p = u825p + u850p;

	uint8_t beatMark = beat8(bpm,ph->bpmTimebase);
	uint8_t barBeat = beat8(bpm/4,ph->bpmTimebase);	
	uint8_t halfBar = beat8(bpm/2,ph->bpmTimebase);	
	uint8_t fourBar = beat8(bpm/16,ph->bpmTimebase);
	uint8_t bar16 = beat8(bpm/32,ph->bpmTimebase);
	uint8_t revFourBar = u8Rev(fourBar);

	uint8_t beat1 = barBeat;
	uint8_t beat2 = addmod8(barBeat,u825p,255);
	uint8_t beat3 = addmod8(barBeat,u850p,255);
	uint8_t beat4 = addmod8(barBeat,u875p,255);


	uint8_t beat1Trigger = squarewave8(beatMark,64);
	uint8_t beat2Trigger = squarewave8(beat2,50);
	uint8_t beat3Trigger = squarewave8(beat3,128);
	uint8_t beat4Trigger = squarewave8(beat4,50);

	

	uint8_t ledBeatMark = ph->u82l(barBeat);
	uint8_t revBeatMark = ph->u82l(u8Rev(barBeat));
	uint8_t revHalfBar = ph->u82l(u8Rev(halfBar));


	uint8_t beater = map8(barBeat,0,31);

	FastLED.clear();

	//leds[ph->u82l(beat1)]=CHSV(255,255,beat2Trigger);
	uint8_t easeBeat = phEase(beatMark,.6);
	//uint8_t easeBeatSlow = phEase(beatMark,.05);
	uint8_t easeFourBar = phEase(fourBar,.4);
	uint8_t revEaseFourBar = phEase(revFourBar,.4);
	uint8_t bar16ease = phEase(bar16,.2);
	uint8_t halfBarLEDease = ph->u82l(phEase(halfBar,.6));
	
	//uint8_t bar16Led = ph->u82l(bar16ease);
	
	//leds[addmod8(ledBeatMark,32,130)]=CHSV(120,150,easeBeat);
	
	//leds[addmod8(ledBeatMark,97,130)]=CHSV(120,150,easeBeat);
	
	leds[revBeatMark]=CHSV(150,250,easeBeat);
	leds[revHalfBar]=CHSV(barBeat,175,easeFourBar);
	leds[ledBeatMark]=CHSV(75,255,easeBeat);

	leds[addmod8(ledBeatMark,65,130)]=CHSV(beatMark,255,revEaseFourBar);

	//leds[halfBarLEDease ]=CHSV(beatMark,255,255);

	
	
	if (beater == 0){
		delay(1);
		FastLED.clear();
		uint8_t randBeat = random8(ledCount);
		leds[randBeat]=CRGB(255,255,255);
		
	}

	if (beater == 15){
		delay(1);
		FastLED.clear();
		uint8_t randBeat = random8(ledCount);
		leds[randBeat]=CRGB(255,255,255); 
		//delay(1);
	}

	int beaterFlip = beater % 16;
	
	if (!beaterFlip){
		//uint8_t randBeat = random8(ledCount);
		//leds[randBeat]=CRGB(255,255,255);
	}

	fadeToBlackBy(leds,ledCount,revEaseFourBar);
	//leds[ph->u82l(beatMark)]=CHSV(barBeat,255,bar16ease);




	
	//leds[ph->u82l(beat2)]=CHSV(255,255,beat2Trigger);
	//leds[ph->u82l(beat3)]=CHSV(255,255,beat3Trigger);
	//leds[ph->u82l(beat4)]=CHSV(255,255,beat4Trigger);
};


void maker::glitterBasic(){
	//int t = ph.sets.hw.LEDCount;
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, ledCount, 255);
  
  if(random8()<200){
  	int pos = random16(ledCount);
  	leds[pos] += CRGB(255,255,255);
	}

//blur1d(leds,ledCount,1);
};
*/


