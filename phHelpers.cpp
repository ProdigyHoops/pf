#ifndef phHelpers_h
#include "prodigy.h"
#endif

extern "C"{
  int _getpid(){ return -1;}
  int _kill(int pid, int sig){ return -1; }
  int _write(){return -1;}
}


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
uint8_t u8WTF(int i, uint8_t s, int l, bool r){
	uint8_t shift = u82l(s,l);
	uint8_t val;
		if(!r){
		val = mod8((i+shift),l);
		}
		else{
		val = mod8( ((l+i)-shift),l);
		}
	return val;
};

/**
 * @brief      val to reverse
 *	
 * @param[in]  val   The value
 *
 * @return     revers of uint8_t
 */
uint8_t u8Rev(uint8_t val){
	uint8_t rev = 255 - val;
	return rev;
};

/**
 * @brief      { function_description }
 *
 * @param[in]  val     The value
 * @param[in]  lcount  The lcount
 *
 * @return     { description_of_the_return_value }
 */
uint8_t u82l(uint8_t val, int lcount){
	uint8_t u2l = map8(val,0,lcount);
	return u2l;
};

uint8_t u82lbRef(uint8_t &val){
	val = map8(val,0,pflow2.LEDCount);
	return val;
};



/**
 * @brief      { function_description }
 *
 * @param[in]  _bpm  The bpm
 *
 * @return     { description_of_the_return_value }
 */
uint8_t u8beat2l(uint8_t _bpm){
	uint8_t beatVal = beat8(_bpm);
	beatVal = u82l(beatVal,pflow2.LEDCount);
	return beatVal;
};

/**
 * @brief      { function_description }
 *
 * @param      togit  The togit
 *
 * @return     { description_of_the_return_value }
 */
bool tog(bool &togit){
	togit=!togit;
	return togit;
};

/**
 * @brief      { function_description }
 *
 * @param      tog        The tog
 * @param[in]  condition  The condition
 *
 * @return     { description_of_the_return_value }
 */
bool togIf(bool &tog,bool condition){
	if(condition){tog=!tog;}
	return tog;
};

/**
 * @brief      { function_description }
 *
 * @param      _val      The value
 * @param[in]  _lowLim   The low limit
 * @param[in]  _highLim  The high limit
 *
 * @return     { description_of_the_return_value }
 */
uint8_t u8Lim(uint8_t & _val, uint8_t _lowLim, uint8_t _highLim){
	if( _val <= _lowLim){_val = _lowLim; return _lowLim;}
	if( _val >= _highLim){_val = _highLim; return _highLim;}
	return _val;
};

/**
 * @brief      { function_description }
 *
 * @param      _val      The value
 * @param[in]  _toAdd    To add
 * @param[in]  _lowLim   The low limit
 * @param[in]  _highLim  The high limit
 *
 * @return     { description_of_the_return_value }
 */
uint8_t u8AddLim(uint8_t & _val, int _toAdd, uint8_t _lowLim, uint8_t _highLim){
	if(_val <= _lowLim || _val + _toAdd <= _lowLim){_val = _lowLim; return _lowLim;}
	if(_val >= _highLim || _val + _toAdd >= _lowLim){_val = _highLim; return _highLim;}
	_val = _val + _toAdd;
	return _val;
};

/**
 * @brief      { function_description }
 *
 * @param      _val      The value
 * @param[in]  _toAdd    To add
 * @param[in]  _lowLim   The low limit
 * @param[in]  _highLim  The high limit
 *
 * @return     { description_of_the_return_value }
 */
uint8_t u8AddLimSafe(uint8_t & _val, int _toAdd, uint8_t _lowLim, uint8_t _highLim){
	int intVal = (int)(_val + _toAdd);
	if(intVal <= _lowLim){ _val = _lowLim; return _val;}
	if(intVal >= _highLim){_val = _highLim;  return _val;}
	_val = _val + _toAdd;
	return _val;
};

/**
 * @brief      { function_description }
 *
 * @param[in]  lval    The lval
 * @param[in]  lcount  The lcount
 *
 * @return     { description_of_the_return_value }
 */
uint8_t lRev(uint8_t lval,uint8_t lcount){
	uint8_t val = lcount - lval;
	return val;
};

/**
 * @brief      { function_description }
 *
 * @param[in]  val    The value
 * @param[in]  power  The power
 *
 * @return     { description_of_the_return_value }
 */
uint8_t phEase(uint8_t val, float power){
	uint8_t eased =pow(val*pow(255,power-1),1/power);
 
  	return eased;
};

/**
 * @brief      { function_description }
 *
 * @param[in]  _chsv  The chsv
 */
void ledDoCHSV(CHSV _chsv){
	for(int l=0;l<pflow2.LEDCount;l++){
		pflow2.leds[l]=_chsv;
	}
};


void ledDoCRGB(CRGB _crgb){
	for(int l=0;l<pflow2.LEDCount;l++){
		pflow2.leds[l]=_crgb;
	}
};

/**
 * @brief      { function_description }
 *
 * @param[in]  _start  The start
 * @param[in]  _end    The end
 * @param[in]  _chsv   The chsv
 */
void ledDoRangeCHSV(uint8_t _start, uint8_t _end, CHSV _chsv){
	for(int l=_start;l<_end;l++){
		pflow2.leds[l]=_chsv;
	}
};

/**
 * @brief      { function_description }
 *
 * @param[in]  _start  The start
 * @param[in]  _end    The end
 * @param[in]  _crgb   The crgb
 */
void ledDoRangeCRGB(uint8_t _start, uint8_t _end, CRGB _crgb){
	for(int l=_start;l<_end;l++){
		pflow2.leds[l]=_crgb;
	}
};







phTicker::phTicker(){

	timebase=millis();
	tickMode=TPS_MODE;
	ticksPerSecond=500;
	//tickHigh=255;
};

bool phTicker::tickCheck(){
	getTick();
	if(lastTick == tick){
		return false;
	}
	else{
		lastTick=tick;
		return true;
	}
};

uint16_t phTicker::getTick(){



	switch(tickMode){
		case TPS_MODE:
		//	Serial.println("TPS MODE Getting Tick");
			elapsed = millis() - timebase;
		//	Serial.print("elapsed : ");
		//	Serial.print(elapsed);
			rawTick = elapsed/(1000/ticksPerSecond);
		//	Serial.print(" | rawTick : ");
		//	Serial.print(rawTick);
			tick = rawTick;
			tick %= tickHigh;
		//	Serial.print(" | tick : ");
		//	Serial.println(tickHigh);
			signedTick = tick - (tickWidth/2);						
			return tick;
		break;

		case BPM_IN:

		break;

		default:
		break;
	};
};

int16_t phTicker::getTickSigned(){
	getTick();
	return signedTick;	
};

void phTicker::setTPS(uint32_t _tps){

	ticksPerSecond = _tps;
};

void phTicker::setBPM(uint8_t _BPM){

	ticksBPM = _BPM;
};

void phTicker::setMode(uint8_t _mode){

	tickMode = _mode;
};

void phTicker::setTimebase(uint32_t _timebase){

	timebase = _timebase;
};

void phTicker::setTimebase(){

	timebase = millis();
};

void phTicker::setTickLimit(uint32_t _tickHigh){
	tickHigh = _tickHigh;
	tickWidth = tickHigh+1;
};

void phTicker::setTickRange(uint32_t _tickLow,uint32_t _tickHigh){
	tickLow = _tickLow;
	tickHigh = _tickHigh;
	tickWidth = (tickHigh - tickLow)+1;
};








/**
 * @brief      Constructs the object.
 */
phBeater::phBeater(){
};

/**
 * @brief      Destroys the object.
 */
phBeater::~phBeater(){
};

/**
 * @brief      { function_description }
 *
 * @param[in]  _bpm       The bpm
 * @param[in]  _timeBase  The time base
 */
void phBeater::update(uint32_t _bpm,uint32_t _timebase){
	if(_bpm != BPM || timebase != _timebase){

	BPM=_bpm;
	timebase = _timebase;

	bpm88 = (BPM)*256;

	bar8Counter=7;
	bar8Counted=false;	
	bar16Counter=15;
	bar16Counted=false;
	}

	u16Beat = beat16(BPM,timebase);
	u8Beat = scale16(u16Beat,256); 
	u82lBeat = scale16(u16Beat,pflow2.LEDCount);	
	beat64 = scale16(u16Beat,64);


	beatCountDown = 255-u8Beat;
	
	bar1 = false;
	bar4 = false;
	bar8 = false;
	bar16 = false;

	barDownBeat1=false;
	barDownBeat2=false;
	barDownBeat3=false;
	barDownBeat4=false;

	barUpBeat1=false;
	barUpBeat2=false;
	barUpBeat3=false;
	barUpBeat4=false;

	if(beat64 != 0){
		bar8Counted=false; bar16Counted=false;
	}

	switch(beat64){

		case 0:
			barDownBeat1 = true;

			if(!bar8Counted){
				bar8Counter++; 
				bar8Counter %= 8;
				bar8Counted=true;
			}
			if(!bar16Counted){
				bar16Counter++; 
				bar16Counter %= 16;
				bar16Counted=true;
			}
		break;

		case 8:
			barUpBeat1 = true;
		break;

		case 16:
			barDownBeat2 = true;
		break;

		case 24:
			barUpBeat2 = true;
		break;

		case 32:
			barDownBeat3 = true;
		break;

		case 40:
			barUpBeat3 = true;
		break;

		case 48:
			barDownBeat4 = true;
		break;

		case 56:
			barUpBeat4 = true;
		break;
	}

	switch(bar16Counter){

		case 0:
			bar1 = true;
		break;

		case 3:
			bar4 = true;
		break;

		case 7:
			bar8 = true;
		break;

		case 15:
			bar16 = true;
		break;
	}
};




phTimer::phTimer(){
};

void phTimer::setMillis(uint32_t _millis){
	
	timeMicros = _millis*1000;
	timeMillis=_millis;
	startTime=millis();
};

void phTimer::setMicros(uint32_t micros){

	timeMicros = micros;
};

void phTimer::start(){

	startTime=millis();
};

void phTimer::reSet(){

	startTime=millis();
	activated=true;
};

bool phTimer::running(){
	bool alrm = alarm();
	return !alrm;
};

bool phTimer::alarm(){
	if(millis() > (startTime+timeMillis) || activated==false){		
		return true;
	}
	else{
		return false;
	}
};

uint8_t phTimer::progress8(uint8_t scaleLow, uint8_t scaleHigh){
	uint32_t timePast = millis()-startTime;
	uint8_t prog8 = map(timePast,0,timeMillis,scaleLow,scaleHigh);

	return prog8;
};

uint8_t phTimer::remaining8(uint8_t scaleLow, uint8_t scaleHigh){
	uint8_t timePast = progress8();
	uint8_t remain8 = 255 - timePast;
	remain8 = map(remain8,255,0,scaleHigh,scaleLow);
	return remain8;
};





/**
 * @brief      doubleTapper constructor
 */
doubleTapper::doubleTapper(){

	lastTapTime=micros();
};

/**
 * @brief      Sets the tap interval millis.
 *
 * @param[in]  millisIn  The millis in
 */
void doubleTapper::setTapIntervalMillis(uint32_t millisIn){

	tapIntervalMicros=millisIn*1000;
};

/**
 * @brief      Sets the tap interval micros.
 *
 * @param[in]  microsIn  The micros in
 */
void doubleTapper::setTapIntervalMicros(uint32_t microsIn){
};

/**
 * @brief      triggers a tap->in
 *
 * @return     true: doubleTap triggered, false: not a double tap.
 */
bool doubleTapper::tapIt(){	
	thisTapTime = micros();

	if(doubleTapped){doubleTapped=false;}
	thisTimeDiff = thisTapTime - lastTapTime;
	if(thisTimeDiff<tapIntervalMicros){
		doubleTapped = true;
		Serial.println(F("DoubleTapp Triggered"));
	}
	lastTapTime = thisTapTime;
	return doubleTapped;
};



bpmDetector::bpmDetector(){

	lastBeatItTime=millis();	
};

bpmDetector::~bpmDetector(){
};

uint32_t bpmDetector::beatIt(){
	//Serial.println("beatingOff");
	thisBeatItTime = millis();
	timeDiff = thisBeatItTime - lastBeatItTime;

	if(timeDiff > timeOutMillis){
		beatItCounter=0;
		currentBPM =0;
		timeAverage = 0;
		lastBeatItTime=thisBeatItTime;
		return currentBPM;
	}
	else{

		if (beatItCounter==0){
			timeAverage = timeDiff;
			beatItCounter++;
			lastBeatItTime=thisBeatItTime;
			return currentBPM;
		}
		else{
			beatItCounter++;
			timeAverage = ((timeAverage*(beatItCounter-1))+timeDiff)/beatItCounter;
			lastBeatItTime=thisBeatItTime;
			timeBase = thisBeatItTime;
		}

		currentBPM = (secMilli / timeAverage);
		return currentBPM;
	}
};







shapeGenerator::shapeGenerator(){
	
	ticker.setTPS(10);
	
	rows=pflow2.LEDCount;
	columns = pflow2.LEDCount;
	matrix.resize(rows, std::vector<uint8_t>(columns, initialValue));

};

shapeGenerator::~shapeGenerator(){};

void shapeGenerator::resizeMatrix(uint8_t _x, uint8_t _y){
	matrix.resize(rows, std::vector<uint8_t>(columns, initialValue));
	//matrix.resize(x, std::vector<uint8_t>(y, 0));
};

void shapeGenerator::play(){
	ticker.setTickLimit(pflow2.LEDCount);
	FastLED.clear();
	uint16_t x = ticker.getTick();
		//Serial.println(x);
	uint8_t y = x;
	pflow2.leds[y*y] = CHSV(143,255,255);
		delay(1);

};

phWave::phWave(){};

uint8_t phWave::doWave(uint8_t _in){

	uint8_t mapIn = map(_in,0,width,0,255);

	uint8_t rawWave = sin8(mapIn);
	
		if(rev){
			rawWave = u8Rev(rawWave);
		}
	//mapOut = phEase(mapOut,.5);
		uint8_t mapOut = map8(rawWave,0,amp);
	return mapOut;

};



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
}


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



phMaker::phMaker(){

};

bool phMaker::load(){
	beat = &pflow2.beater;
	params = &pflow2.settings.params;
	leds = pflow2.leds;
};

void phMaker::run(){
};

void phMaker::die(){	
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