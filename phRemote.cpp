
#ifndef phRemote_h
#include "prodigy.h"
#endif



phRemote::phRemote(int pin)  : irrecv(pin){

	loadProfile(phIR);
	bpmDetector irBPM;
	doublePause.setTapIntervalMillis(300);
}

phRemote::~phRemote(){
};

/*
void phRemote::passProdigy(prodigy *phIn){
	
	//ph = phIn;
}
*/

void phRemote::loadProfile(irProfile profile){
	irKeys[phIR.repeatKey]=irRepeatKey;
	irKeys[phIR.power]=irPower;
	irKeys[phIR.settings]=irSettings;
	irKeys[phIR.lock]=irLock;
	irKeys[phIR.favorite]=irFavorite;
	irKeys[phIR.playlist]=irPlaylist;
	irKeys[phIR.bpmSet]=irBPMSet;
	irKeys[phIR.motion]=irMotion;
	irKeys[phIR.brightUp]=irBrightUp;
	irKeys[phIR.kickstart]=irKickstart;
	irKeys[phIR.battery]=irBattery;
	irKeys[phIR.powerMode]=irPowerMode;
	irKeys[phIR.brightDown]=irBrightDown;
	irKeys[phIR.digit1]=irDigit1;
	irKeys[phIR.digit2]=irDigit2;
	irKeys[phIR.digit3]=irDigit3;
	irKeys[phIR.digit4]=irDigit4;
	irKeys[phIR.digit5]=irDigit5;
	irKeys[phIR.digit6]=irDigit6;
	irKeys[phIR.digit7]=irDigit7;
	irKeys[phIR.digit8]=irDigit8;
	irKeys[phIR.digit9]=irDigit9;
	irKeys[phIR.m1]=irM1;
	irKeys[phIR.m2]=irM2;
	irKeys[phIR.m3]=irM3;
	irKeys[phIR.m4]=irM4;
	irKeys[phIR.m5]=irM5;
	irKeys[phIR.m6]=irM6;
	irKeys[phIR.navUp]=irNavUp;
	irKeys[phIR.navDown]=irNavDown;
	irKeys[phIR.navRight]=irNavRight;
	irKeys[phIR.navLeft]=irNavLeft;
	irKeys[phIR.navEnter]=irNavEnter;
	irKeys[phIR.navReturn]=irNavReturn;
	irKeys[phIR.program]=irProgram;
	irKeys[phIR.overBright]=irOverBright;
	irKeys[phIR.repeat]=irRepeat;
	irKeys[phIR.pause]=irPause;
	irKeys[phIR.play]=irPlay;
	irKeys[phIR.shuffle]=irShuffle;
	irKeys[phIR.phSet]=irPHSet;
	irKeys[phIR.userSet]=irUserSet;
	irKeys[phIR.makerSet]=irMakerSet;
	irKeys[phIR.save]=irSave;
}

void phRemote::start(){

		irrecv.enableIRIn();
}

void phRemote::update(){
	 if (irrecv.decode(&results)) {
	 		prevKey = activeKey;
	 		 activeKey = (results.value);
	 		 
	 		 if (irKeys[activeKey] == irRepeatKey){activeKey=prevKey; isRepeat = true;}
	 		// Serial.println("Got IR");
	 		 processIR(irKeys[activeKey]);	 		  
	 		 //ph->flash(10,10);	
	 		 //Serial.println("Restarting IR"); 	
	 		 irrecv.resume();	
	 }
};

void phRemote::processIR(uint32_t irCommand){
	
	bool isMaking =0;//ph->sets.run.data.isMaking;

	switch(irCommand) {

	    case irRepeatKey:
	    	//Serial.println("Problem: Should never get repeatKey");
        break;  
	                 // and exits the switch
	    case irPower: 
	    	//ph->splitChaseUp(1000,2000);
	    	pflow2.sendCommand(USER_BRIGHTNESS_UP);
	    	
	    break;

	    case irSettings:
	    
	    break;
	    
	    case irLock:
	    	pflow2.settings.updateLEDCount(54);
	    
	    break;
	    
	    case irFavorite:
	    
	    break;
	    
	    case irPlaylist:
	    	digitDoCount=true;
	    	runningDigit=0;
	    	digitDoCountFor = PLAY_LIST;
	    
	    break;
	    
	    case irBPMSet:
	    	//Serial.println("irBeating");
	    	pflow2.ODsetBPM.pulse();
	    	pflow2.settings.run.data.BPM = bpmTap.beatIt();
	    	pflow2.settings.run.data.bpmTimebase = bpmTap.timeBase;
	    	pflow2.beater.update(pflow2.settings.run.data.BPM,pflow2.settings.run.data.bpmTimebase);
	    	delay(15);
	    	Serial.println(pflow2.settings.run.data.BPM);
	    
	    break;
	    
	    case irMotion:
	   //ph->motionOn = !ph->motionOn;
	    
	    break;
	    
	    case irBrightUp: 	//ph->brightUp();	    break;
	    	pflow2.ODsetUserBrightness.pulse();
	    	pflow2.changeUserBrightnessLevel(5);



	    case irKickstart:
	    
	    break;
	    
	    case irBattery:
	    	//ph->checkBattery();
	    	//ph->animatedLevel();	    
	    break;
	    
	    case irPowerMode:
	    	
	    break;
	    
	    case irBrightDown: //ph->brightDown();  break;
	    	pflow2.ODsetUserBrightness.pulse();
	    	pflow2.changeUserBrightnessLevel(-5);
	    break;
	    
	    case irDigit1:	digitIn(1);	 break;	    
	    case irDigit2:	digitIn(2);  break;
	    case irDigit3: 	digitIn(3);  break;
	    case irDigit4: 	digitIn(4);  break;
	    case irDigit5: 	digitIn(5);  break;
	    case irDigit6: 	digitIn(6);  break;
	    case irDigit7: 	digitIn(7);  break;
	    case irDigit8:	digitIn(8);  break;
	    case irDigit9: 	digitIn(9);  break;
	    case irDigit0: 	digitIn(0);  break;
	    
	    case irM1: break; // togIf(//ph->sets.params.data.phToggle1,isMaking);  break;
	    case irM2:break;// togIf(//ph->sets.params.data.phToggle1,isMaking);  break;
	    case irM3:break; //togIf(//ph->sets.params.data.phToggle1,isMaking);  break;
	    case irM4: break;//togIf(//ph->sets.params.data.phToggle1,isMaking);  break;
	    case irM5:break; //togIf(//ph->sets.params.data.phToggle1,isMaking);  break;
	    case irM6:break; //togIf(//ph->sets.params.data.phToggle1,isMaking);  break;
	    
	    case irNavUp:
	    	if(isMaking){
	    		//u8AddLim();//ph->sets.params.data.params[activeParamSet].val[0],1,0,255);
	    		
	    	}
	    break;
	    
	    case irNavDown:
	    	if(isMaking){
	    		//u8AddLim();//ph->sets.params.data.params[activeParamSet].val[1],-1,0,255);
	    	}
	    
	    break;
	    
	    case irNavLeft:

	    	pflow2.sendCommand(MENU_PREV_ITEM);
	    	//if(isMaking){
	    		//u8AddLim();//ph->sets.params.data.params[activeParamSet].val[0],-1,0,255);
	    	//}
	    
	    break;
	    
	    case irNavRight:
	    	Serial.println("Got Nav Right. Submitting command to pflow2");
	    	pflow2.sendCommand(MENU_NEXT_ITEM);
	    	//if(isMaking){
	    		//u8AddLim();//ph->sets.params.data.params[activeParamSet].val[1],1,0,255);
	    	//}
	    
	    break;

	    case irNavEnter:
	    	pflow2.sendCommand(MENU_SELECT_OPTION);	   
	    	//if(digitDoCount){	    		
	    	//	digitDoCount=false;	    		
	    	//	doThingsWithThisDigit(runningDigit);	
	    	//}

	    break;
	    
	    case irNavReturn:
	    	//if(digitDoCount){
		    //	digitDoCount=false;
		    	//ph->sets.run.data.isMaking = false;
		    //	runningDigit=0;
		    	// systemGoBack();
		   // }
	    
	    break;
	    
	    case irProgram:
	    	digitDoCount=true;
	    	runningDigit=0;
	    	digitDoCountFor = PRGM;
	    
	    break;
	    
	    case irOverBright:
	    	
	    
	    break;
	    
	    case irRepeat:
	    
	    break;
	    
	    case irPause:
	    	//ph->doPlay  = false;
	    	//ph->doPause = true;
	    	if(doublePause.tapIt()){
	    		//Serial.println(F("Pause DoubleTap Detected")); 
	    		//ph->sets.run.data.isMaking = true;
	    	}

	    break;
	    
	    case irPlay:
	    	//ph->doPlay  = true;
	    	//ph->doPause = false;
	    break;
	    
	    case irShuffle:

	    
	    break;
	    
	    case irPHSet:
	    	digitDoCount=true;
	    	runningDigit=0;
	    	digitDoCountFor = PLAYER_PHGROUP;
	    
	    break;
	    
	    case irUserSet:
	    	digitDoCount=true;
	    	runningDigit=0;
	    	digitDoCountFor = PLAYER_USERGROUP;
	    
	    break;
	    
	    case irMakerSet:
	    	digitDoCount=true;
	    	runningDigit=0;
	    	digitDoCountFor = PLAYER_MAKERS;

	    
	    break;
	    
	    case irSave:
	    	if(0){//ph->sets.run.data.isMaking){	    		
	    		digitDoCount=false;
	    		runningDigit=0;	    		
	    	}

	    
	    break;

	    default:
	    	//Serial.print("NewIRCode  |  ");
	    	//Serial.println(activeKey);
	    break;
	    
	}
}


void phRemote::digitIn(int _inDigit){
	//phDebug(F("Digit In"));
	
	if(digitDoCount){
		//phDebug(F("DigitDo On, Processing running digit"));		
		runningDigit = (runningDigit*10)+_inDigit;
	}
	/*
	if(0){//ph->sets.run.data.isMaking){
	//phDebug(F("Current Program = MAKING. Setting activeParamSet"));
		    			    		
	    		activeParamSet = _inDigit;   		
	    	}
	    	*/
};



void phRemote::doThingsWithThisDigit(int _digitIn){
	//phDebug(F("I'm doing things with them digits"));
	
	
	/*
	 switch(digitDoCountFor){

		case PLAYER_PHGROUP:
		//phDebug(F("DigitDoFor PHGROUP"));
		
			//ph->sets.loadPlayList(_digitIn,PRODIGY_SET,0);
		break;

		case PLAYER_USERGROUP:
		//phDebug(F("digit do for user"));
		
			//ph->sets.loadPlayList(_digitIn,USER_SET,0);
		break;

		case  PLAYER_PLAYLIST:
		//phDebug(F("digit do for playlist"));
		
			//ph->sets.loadPlayList(_digitIn,PLAY_LIST,0);
		break;

		case PLAYER_MAKERS:
		//phDebug(F("digit do for Makers"));
		
			//ph->sets.loadPlayList(_digitIn,MAKER_LIST,0);
		break;

		case PRGM:
		break;

		case SAVER:
		break;

		runningDigit=0;
	}
	*/
};




