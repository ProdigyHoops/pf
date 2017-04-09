

#ifndef phConfig_h
#include "prodigy.h"
#endif




phConfig::phConfig(){
  hwSettings hw;

  //phDebug(F("Test"));
 // phUserSettings usr;
  //phAnimationParams ani;
  //phRunTimeSettings run;
  

 // SerialFlashFile savedConfig;
 //savedConfig = SerialFlash.open("config.ph");
 // savedConfig.read(settings,256);
};


//Initial loading and setup
void phConfig::loadCheck(){
	//EEPROM.write(0,4);
	
	int newInstall = EEPROM.read(0);
	
	if(newInstall != 128){
			
	
		
		Serial.println(F("newInstall - preparing for initial config"));
		//Serial.println(F("Searching for external storage"));
		

		if (!SerialFlash.begin(16)) {
		    Serial.println(F("Unable to access SPI Flash chip"));
		  }
		  else{
		       Serial.println("Serial Flash alive!");
	  	}

	  	//while(!SerialFlash.ready()){Serial.println("FLASH NOT READY");}

		Serial.println("Erasing external flash. May take a minute");
		delay(100);
		SerialFlash.eraseAll();
		  unsigned long dotMillis = millis();
		    unsigned char dotcount = 0;
	    while (SerialFlash.ready() == false) {
	      if (millis() - dotMillis > 1000) {
	        dotMillis = dotMillis + 1000;
	        Serial.print(".");
	        dotcount = dotcount + 1;
	        if (dotcount >= 60) {
	          Serial.println();
	          dotcount = 0;
	        }
	      }
	    }
	    if (dotcount > 0) Serial.println();
	    Serial.println("Flash should be erased");


		if(genFiles()){
				Serial.println("Config completed ok");
				EEPROM.write(0,128);
				Serial.println("loading saved data");
				bootLoad();
				Serial.println("Data Loaded: Checking magic number");
				Serial.print("Magic should be: 99228833 | magic =");
				Serial.println(hwf.data.propID);
				}	
	}
	else {
		  if (!SerialFlash.begin(16)) {
		    Serial.println(F("Unable to access SPI Flash chip"));
		  }
		  else{
		       Serial.println("Serial Flash alive!");
	  }
		Serial.println("Config Exist");
		Serial.println("loading saved data");
		bootLoad();
		Serial.println("Data Loaded: Checking magic number");
		Serial.print("Magic should be: 99228833 | magic =");
		Serial.println(hwf.data.propID);
	};
};

void phConfig::bootLoad(){
	String initfilename= String("phICF.ph");
	String userfilename= String("phUSR.ph");
	String runfilename= String("phRUN.ph");
	String hwfilename= String("phHWF.ph");
	String makerfilename= String("MAKER.ph");

	initfilename.toCharArray(init.data.name,sizeof(initfilename));
	userfilename.toCharArray(user.data.name,sizeof(userfilename));
	runfilename.toCharArray(run.data.name,sizeof(runfilename));
	hwfilename.toCharArray(hwf.data.name,sizeof(hwfilename));
	makerfilename.toCharArray(maker.data.name,sizeof(makerfilename));

	loadData(&init);
	loadData(&user);	
	loadData(&run);
	loadData(&hwf);
	loadData(&maker);
};

void phConfig::pflowPrep(){

};

bool phConfig::genFiles(){

	//-- set name to init config file
	String initfilename= String("phICF.ph");
	initfilename.toCharArray(init.data.name,sizeof(initfilename));
	
	loadDefaults();

	//** generate HW File
	//-- Set file name; save name to config; save name to uFile
	String hwfilename = String("phHWF.ph");
	hwfilename.toCharArray(hwf.data.name,sizeof(hwfilename));
	hwfilename.toCharArray(init.data.hwFile.name,sizeof(hwfilename));

	Serial.print("Checking magic # before saving to file: Magic = ");
	Serial.println(hwf.data.propID);

	uint32_t hwfaddress = createFile(&hwf);
	
	if(hwfaddress){
		init.data.hwFile.address = hwfaddress;
	}
	else{
		Serial.println("Problem creating hardware file");
		return false;
	};

	//** generate userFile
	//-- Set file name; save name to config; save name to uFile
	String userfilename = String("phUSR.ph");
	userfilename.toCharArray(user.data.name,sizeof(userfilename));
	userfilename.toCharArray(init.data.userFile.name,sizeof(userfilename));
	uint32_t useraddress = createFile(&user);
	if(useraddress){
		init.data.userFile.address = useraddress;
	}
	else{
		Serial.println("Problem creating user file");
		return false;
	};

	//** generate runTime File
	//-- Set file name; save name to config; save name to uFile
	String runfilename = String("phRUN.ph");
	runfilename.toCharArray(run.data.name,sizeof(runfilename));
	runfilename.toCharArray(init.data.runFile.name,sizeof(runfilename));

	uint32_t runaddress = createFile(&run);
	if(runaddress){
		init.data.runFile.address = runaddress;
	}
	else{
		Serial.println("Problem creating runtTime file");
		return false;
	};

	//** generate runTime File
	//-- Set file name; save name to config; save name to uFile
	String makerfilename = String("MAKER.ph");
	makerfilename.toCharArray(maker.data.name,sizeof(makerfilename));
	makerfilename.toCharArray(init.data.makerFile.name,sizeof(makerfilename));

	uint32_t makeraddress = createFile(&maker);
	if(makeraddress){
		init.data.makerFile.address = makeraddress;
	}
	else{
		Serial.println("Problem creating maker file");
		return false;
	};


	//** generate paramFile (master list of params)
	//-- Set file name; save name to config; save name to uFile
	//-- This file needs to be made slightly different then all 
	//-- other files.  Master list containing up to 10,000 param packets
	String paramfilename = String("param.ph");
	paramfilename.toCharArray(paramFile.data.name,sizeof(paramfilename));
	paramfilename.toCharArray(init.data.paramFile.name,sizeof(paramfilename));


	if(SerialFlash.createErasable(paramFile.data.name, (sizeof(params))*10000 )) {
				
		Serial.print(paramFile.data.name);
		Serial.print(" created | ");

		// Open new file to get file address
		SerialFlashFile tmpFile = SerialFlash.open(paramFile.data.name);
		uint32_t paramaddress = tmpFile.getFlashAddress();

		// Save file address to uFile
		paramFile.data.address=paramaddress;
		init.data.paramFile.address = paramaddress;
		uint32_t bytesWritten = tmpFile.size();
		Serial.print(bytesWritten);
		Serial.println(" bytes written to file");
		tmpFile.close();
	}

	else{
		Serial.println("Problem creating paramFile");
		return false;
	};


	//** generate phPatternSet Files
	//-- Set file names; save names to config; save names to uFiles
	for(int f=0;f<phListCount;f++){
		String fileCount;
		if(f<10){
			fileCount = String("0" + String(f));
		}
		else{
			fileCount = String(f);
		}
		
		String pSetfilename = String("phL" + fileCount);
		pSetfilename = String(pSetfilename+".ph");
		pSetfilename.toCharArray(init.data.phSets[f].name,sizeof(pSetfilename));
		pSetfilename.toCharArray(playlist.data.name,sizeof(pSetfilename));
		uint32_t pSetaddress = createFile(&playlist);	
		if(pSetaddress){
			init.data.phSets[f].address = pSetaddress;
		}
		else{
			Serial.println("Problem creating prodigySet file");
			return false;
		};
	};	

	//** generate userPatternSet Files
	//-- Set file names; save names to config; save names to uFiles
	for(int f=0;f<userListCount;f++){
		String fileCount;
		if(f<10){
			fileCount = String("0" + String(f));
		}
		else{
			fileCount = String(f);
		}
		
		String userSetfilename = String("usL" + fileCount);
		userSetfilename = String(userSetfilename +".ph");
		userSetfilename.toCharArray(init.data.userSets[f].name,sizeof(userSetfilename));
		userSetfilename.toCharArray(playlist.data.name,sizeof(userSetfilename));
		uint32_t userSetaddress = createFile(&playlist);	
		if(userSetaddress){
			init.data.userSets[f].address = userSetaddress;
		}
		else{
			Serial.println("Problem creating userSet file");
			return false;
		};
	};

	//** generate playList Files
	//-- Set file names; save names to config; save names to uFiles
	for(int f=0;f<playListCount;f++){
		String fileCount;
		if(f<10){
			fileCount = String("0" + String(f));
		}
		else{
			fileCount = String(f);
		}
		String playListfilename = String("PLY" + fileCount);
		playListfilename = String(playListfilename+".ph");
		playListfilename.toCharArray(init.data.playList[f].name,sizeof(playListfilename));
		playListfilename.toCharArray(playlist.data.name,sizeof(playListfilename));
		uint32_t playListaddress = createFile(&playlist);	
		if(playListaddress){
			init.data.playList[f].address = playListaddress;
		}
		else{
			Serial.println("Problem creating playList file");
			return false;
		};
	};

	uint32_t initaddress = createFile(&init);
	if(initaddress){
		//init.data.runFile.address = runaddress;
	}
	else{
		Serial.println("Problem creating runtTime file");
		return false;
	};
	return true;
};

void phConfig::loadDefaults(){
	
	
	//Standard Protege HW Defaults
	hwf.data.propID=99228833;
	hwf.data.propType=PROTEGE_HOOP_V1;


	hwf.data.LEDCount = 130;
	hwf.data.LEDDataPin = 11;
	hwf.data.LEDcolorCorrectTubing=false;
	


	hwf.data.IRReceivePin = 3;
	hwf.data.IRTransmitPin = 5;

	hwf.data.hasIMU = true;	
	hwf.data.IMUInterruptPin = 9;

	hwf.data.regulatePower = true;
	hwf.data.voltageRefPin =0;
	hwf.data.maxVoltage=4.2;
    hwf.data.maxMilliAmp=500;
    

    hwf.data.FRAMCSPin = 16;
   

    hwf.data.maxBrightLevel = 200;


    

    //Factory default user settings
    user.data.brightLevelOnStartUp = 125;

    user.data.bootToLast = false;
    user.data.powerOnPatternGroup = PRODIGY_SET;
    user.data.powerOnGroupList = 0;
    user.data.powerOnGroupListEntry = 0;

    user.data.defaultTransitionTrigger = TIME_IN_MILLIS;
    user.data.defaultTransitionTimeMillis = 8000;
    user.data.defaultTransitionMode = TRANSITION_CUT;

    user.data.postIMURollDefaultOn = false;
    user.data.postBlurDefaultOn = true;
    user.data.postMotionBrightDefaultOn = false;

    user.data.defaultPostBlurAmount = 2;

    user.data.motionTriggeredPlaylistActive = false; 
    user.data.motionTriggeredPlaylistID = 20;

    user.data.favoritePlaylist = 0;

    params.data.makerIndex = 0;
    params.data.params[1].val[0] = 3;
    params.data.params[1].val[1] = 36;
    params.data.params[2].val[0] = 255;
    params.data.params[2].val[1] = 255;

    params.data.params[3].val[0] = 10;
    params.data.params[3].val[1] = 128;
    params.data.params[4].val[0] = 175;
    params.data.params[4].val[1] = 150;

    params.data.params[5].val[0] = 0;
    params.data.params[5].val[1] = 0;
    params.data.params[6].val[0] = 10;
    params.data.params[6].val[1] = 0;

    params.data.phToggle1 = false;
    params.data.phToggle2 = false;
    params.data.phToggle3 = false;
    params.data.phToggle4 = false;
};

//Playlist management
void phConfig::saveToPlaylist(uint8_t _playListIndex, uint8_t _patternGroup){

	//Open param file
	//SerialFlash.begin(16);
	SerialFlashFile tmpFile;
	tmpFile = SerialFlash.open(init.data.paramFile.name);
	
	uint32_t address = tmpFile.position();
	tmpFile.write(params.bytes,sizeof(paramPacket));
	tmpFile.close();
	switch(_patternGroup){

		case PRODIGY_SET:
		tmpFile = SerialFlash.open(init.data.phSets[_playListIndex].name);
		break;

		case USER_SET:		
		tmpFile = SerialFlash.open(init.data.userSets[_playListIndex].name);
		break;

		case PLAY_LIST:
		tmpFile = SerialFlash.open(init.data.playList[_playListIndex].name);
		break;	

		case MAKER_LIST:
		maker.data.defaultConfig[_playListIndex]=address;

		break;	
	}
	if(_patternGroup == MAKER_LIST){return;}
	
	plFile tmpPL;

	int bytesRead = tmpFile.read(tmpPL.bytes,sizeof(tmpPL));
	tmpFile.close();
	tmpPL.data.entries[tmpPL.data.nextEntryPos]=address;
	int thisEntry = tmpPL.data.nextEntryPos;
	tmpPL.data.nextEntryPos++;



	saveData(&tmpPL);	
	loadPlayList(_playListIndex,_patternGroup,tmpPL.data.nextEntryPos);
};

void phConfig::deletePlayListEntry(){
};

void phConfig::loadPlayList(uint8_t _playListIndex,uint8_t _patternGroup,uint8_t _listEntry=0){
	//phDebug(F("Loaing a playlist"));
	
	//SerialFlash.begin(16);
	SerialFlashFile tmpFile;
	switch(_patternGroup){

		case PRODIGY_SET:
		tmpFile = SerialFlash.open(init.data.phSets[_playListIndex].name);
		break;

		case USER_SET:		
		tmpFile = SerialFlash.open(init.data.userSets[_playListIndex].name);
		break;

		case PLAY_LIST:
		tmpFile = SerialFlash.open(init.data.playList[_playListIndex].name);
		break;		
		
	}

	int bytesRead = tmpFile.read(playlist.bytes,sizeof(playlist.data));
	run.data.currentPatternGroup = _patternGroup;
	run.data.currentGroupList = _playListIndex;
	run.data.currentListEntry = _listEntry;

	loadParamPacket(playlist.data.entries[_listEntry]);	
	tmpFile.close();
};

void phConfig::loadParamPacket(uint32_t _address){
	//phDebug(F("loading a param packet from playlist"));
	
	//SerialFlash.begin(16);
	SerialFlashFile tmpFile = SerialFlash.open(init.data.paramFile.name);
	tmpFile.seek(_address);
	int bytesRead = tmpFile.read(params.bytes,sizeof(params.data));
	tmpFile.close();
};

// This is pretty hacky
// But for now it works
uint16_t phConfig::procArray(uint32_t *array){
	uint32_t tmpArray[200];
	int t =0;

	for(int i=0;i<200;i++){
		if(array[i] != 0){
			tmpArray[t]=array[i];
			t++;
		}
	}
	for(int i=0;i<200;i++){
		array[i] = tmpArray[i];
	}
	return t;
};
template <typename U>
uint32_t phConfig::createFile(U *uFile){


	// Create new file using name saved in uFile
	if(SerialFlash.createErasable(uFile->data.name,sizeof(uFile->data) )) {
			
			Serial.print(uFile->data.name);
			Serial.print(" created | ");

			// Open new file to get file address
			SerialFlashFile tmpFile = SerialFlash.open(uFile->data.name);
			uint32_t addy = tmpFile.getFlashAddress();

			// Save file address to uFile
			uFile->data.address=addy;
			
			// copy current uFile data to external file & 
			// check data written length
			uint32_t bytesWritten = tmpFile.write(uFile->bytes,sizeof(uFile->data));
			
			Serial.print(bytesWritten);
			Serial.println(" bytes written to file");
			
			// close file
			tmpFile.close();

			// Return address to be saved in config file
			
			return addy;

		}
		else{
			Serial.println("File Create Failed");
			return(false);
		}
};
	

void phConfig::updateLEDCount(uint8_t _ledCount){
	hwf.data.LEDCount = _ledCount;
	saveData(&hwf);
};

template <typename U>
void phConfig::saveData(U *uFile){

	Serial.print(F("Opening File for Saving : "));
	Serial.println(uFile->data.name);
	SerialFlash.begin(16);
	// Open external backup of uFile
	SerialFlashFile tmpFile = SerialFlash.open(uFile->data.name);
		Serial.print(F("File Opened"));
		Serial.println();
		

	// Erase file, close, & open to reset offset
	tmpFile.erase();
	tmpFile.close();
	tmpFile = SerialFlash.open(uFile->data.name);

	// Write current uFile data to external backup & close
	tmpFile.write(uFile->bytes,sizeof(uFile->data));
	tmpFile.close();
		Serial.print(F("Data saved, File closed "));
		Serial.println();
		
};

template <typename U>
void phConfig::loadData(U *uFile){

	// get name of external copy from uFile data
	//SerialFlash.begin(16);
	Serial.print("Opening File - ");
	Serial.println(uFile->data.name);
	SerialFlashFile tmpFile = SerialFlash.open(uFile->data.name);
	int bytesRead = tmpFile.read(uFile->bytes,sizeof(uFile->data));	
	Serial.print("Reading sizeof uFile->data, bytes = ");
	Serial.println(sizeof(uFile->data));
	Serial.print("Acutal bytes read = " );
	Serial.println(bytesRead);
	
	tmpFile.close();
};