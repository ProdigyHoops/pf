#ifndef phMakers_h
#include "prodigy.h"
#endif



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


