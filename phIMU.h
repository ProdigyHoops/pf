#ifndef phIMU_h
#define phIMU_h


enum Ascale {  AFS_2G = 0,  AFS_4G,  AFS_8G,  AFS_16G};
enum Gscale {  GFS_250DPS = 0,  GFS_500DPS,  GFS_1000DPS,  GFS_2000DPS};
enum Mscale {  MFS_14BITS = 0, MFS_16BITS };


class IMU{
	public:
	IMU();
	// Register Locations
		const static int AK8963_ADDRESS		= 	0x0C;
		const static int AK8963_WHO_AM_I  	=	0x00; // should return 0x48
		const static int AK8963_INFO     	=	0x01;
		const static int AK8963_ST1       	=	0x02;  // data ready status bit 0
		const static int AK8963_XOUT_L	 	=	0x03; // data
		const static int AK8963_XOUT_H	 	=	0x04;
		const static int AK8963_YOUT_L	 	=	0x05;
		const static int AK8963_YOUT_H	 	=	0x06;
		const static int AK8963_ZOUT_L		=	0x07;
		const static int AK8963_ZOUT_H		=	0x08;
		const static int AK8963_ST2       	=	0x09;  // Data overflow bit 3 and data read error status bit 2
		const static int AK8963_CNTL      	=	0x0A;  // Power down (0000), single-measurement (0001), self-test (1000) and Fuse ROM (1111) modes on bits 3:0
		const static int AK8963_ASTC      	=	0x0C;  // Self test control
		const static int AK8963_I2CDIS    	=	0x0F;  // I2C disable
		const static int AK8963_ASAX      	=	0x10;  // Fuse ROM x-axis sensitivity adjustment value
		const static int AK8963_ASAY      	=	0x11;  // Fuse ROM y-axis sensitivity adjustment value
		const static int AK8963_ASAZ      	=	0x12;  // Fuse ROM z-axis sensitivity adjustment value
		const static int SELF_TEST_X_GYRO 	=	0x00;                 
		const static int SELF_TEST_Y_GYRO 	=	0x01;                                                                          
		const static int SELF_TEST_Z_GYRO 	=	0x02;
		const static int SELF_TEST_X_ACCEL 	=	0x0D;
		const static int SELF_TEST_Y_ACCEL 	=	0x0E;   
		const static int SELF_TEST_Z_ACCEL 	=	0x0F;
		const static int SELF_TEST_A      	=	0x10;
		const static int XG_OFFSET_H      	=	0x13;  // User-defined trim values for gyroscope
		const static int XG_OFFSET_L      	=	0x14;
		const static int YG_OFFSET_H      	=	0x15;
		const static int YG_OFFSET_L      	=	0x16;
		const static int ZG_OFFSET_H      	=	0x17;
		const static int ZG_OFFSET_L      	=	0x18;
		const static int SMPLRT_DIV       	=	0x19;
		const static int CONFIG           	=	0x1A;
		const static int GYRO_CONFIG      	=	0x1B;
		const static int ACCEL_CONFIG    	=	0x1C;
		const static int ACCEL_CONFIG2    	=	0x1D;
		const static int LP_ACCEL_ODR     	=	0x1E;  
		const static int WOM_THR          	=	0x1F;   
		const static int MOT_DUR          	=	0x20;  // Duration counter threshold for motion interrupt generation, 1 kHz rate, LSB = 1 ms
		const static int ZMOT_THR         	=	0x21;  // Zero-motion detection threshold bits [7:0]
		const static int ZRMOT_DUR        	=	0x22;  // Duration counter threshold for zero motion interrupt generation, 16 Hz rate, LSB = 64 ms
		const static int FIFO_EN          	=	0x23;
		const static int I2C_MST_CTRL     	=	0x24;  
		const static int I2C_SLV0_ADDR    	=	0x25;
		const static int I2C_SLV0_REG     	=	0x26;
		const static int I2C_SLV0_CTRL    	=	0x27;
		const static int I2C_SLV1_ADDR    	=	0x28;
		const static int I2C_SLV1_REG     	=	0x29;
		const static int I2C_SLV1_CTRL    	=	0x2A;
		const static int I2C_SLV2_ADDR    	=	0x2B;
		const static int I2C_SLV2_REG     	=	0x2C;
		const static int I2C_SLV2_CTRL    	=	0x2D;
		const static int I2C_SLV3_ADDR    	=	0x2E;
		const static int I2C_SLV3_REG    	=	0x2F;
		const static int I2C_SLV3_CTRL   	=	0x30;
		const static int I2C_SLV4_ADDR    	=	0x31;
		const static int I2C_SLV4_REG     	=	0x32;
		const static int I2C_SLV4_DO      	=	0x33;
		const static int I2C_SLV4_CTRL    	=	0x34;
		const static int I2C_SLV4_DI      	=	0x35;
		const static int I2C_MST_STATUS   	=	0x36;
		const static int INT_PIN_CFG      	=	0x37;
		const static int INT_ENABLE       	=	0x38;
		const static int DMP_INT_STATUS   	=	0x39; 	// Check DMP interrupt
		const static int INT_STATUS       	=	0x3A;
		const static int ACCEL_XOUT_H     	=	0x3B;
		const static int ACCEL_XOUT_L     	=	0x3C;
		const static int ACCEL_YOUT_H     	=	0x3D;
		const static int ACCEL_YOUT_L     	=	0x3E;
		const static int ACCEL_ZOUT_H    	=	0x3F;
		const static int ACCEL_ZOUT_L     	=	0x40;
		const static int TEMP_OUT_H       	=	0x41;
		const static int TEMP_OUT_L       	=	0x42;
		const static int GYRO_XOUT_H      	=	0x43;
		const static int GYRO_XOUT_L      	=	0x44;
		const static int GYRO_YOUT_H      	=	0x45;
		const static int GYRO_YOUT_L      	=	0x46;
		const static int GYRO_ZOUT_H     	=	0x47;
		const static int GYRO_ZOUT_L      	=	0x48;
		const static int EXT_SENS_DATA_00 	=	0x49;
		const static int EXT_SENS_DATA_01 	=	0x4A;
		const static int EXT_SENS_DATA_02 	=	0x4B;
		const static int EXT_SENS_DATA_03 	=	0x4C;
		const static int EXT_SENS_DATA_04 	=	0x4D;
		const static int EXT_SENS_DATA_05 	=	0x4E;
		const static int EXT_SENS_DATA_06 	=	0x4F;
		const static int EXT_SENS_DATA_07 	=	0x50;
		const static int EXT_SENS_DATA_08 	=	0x51;
		const static int EXT_SENS_DATA_09 	=	0x52;
		const static int EXT_SENS_DATA_10 	=	0x53;
		const static int EXT_SENS_DATA_11 	=	0x54;
		const static int EXT_SENS_DATA_12 	=	0x55;
		const static int EXT_SENS_DATA_13 	=	0x56;
		const static int EXT_SENS_DATA_14 	=	0x57;
		const static int EXT_SENS_DATA_15 	=	0x58;
		const static int EXT_SENS_DATA_16 	=	0x59;
		const static int EXT_SENS_DATA_17 	=	0x5A;
		const static int EXT_SENS_DATA_18 	=	0x5B;
		const static int EXT_SENS_DATA_19 	=	0x5C;
		const static int EXT_SENS_DATA_20 	=	0x5D;
		const static int EXT_SENS_DATA_21 	=	0x5E;
		const static int EXT_SENS_DATA_22 	=	0x5F;
		const static int EXT_SENS_DATA_23 	=	0x60;
		const static int MOT_DETECT_STATUS 	=	0x61;
		const static int I2C_SLV0_DO      	=	0x63;
		const static int I2C_SLV1_DO      	=	0x64;
		const static int I2C_SLV2_DO      	=	0x65;
		const static int I2C_SLV3_DO      	=	0x66;
		const static int I2C_MST_DELAY_CTRL =	0x67;
		const static int SIGNAL_PATH_RESET  =	0x68;
		const static int MOT_DETECT_CTRL  	=	0x69;
		const static int USER_CTRL        	=	0x6A; 	// Bit 7 enable DMP, bit 3 reset DMP
		const static int PWR_MGMT_1       	=	0x6B;	// Device defaults to the SLEEP mode
		const static int PWR_MGMT_2       	=	0x6C;
		const static int DMP_BANK         	=	0x6D; 	// Activates a specific bank in the DMP
		const static int DMP_RW_PNT       	=	0x6E;	// Set read/write pointer to a specific start address in specified DMP bank
		const static int DMP_REG          	=	0x6F;  	// Register in DMP from which to read or to which to write
		const static int DMP_REG_1        	=	0x70;
		const static int DMP_REG_2        	=	0x71;
		const static int FIFO_COUNTH      	=	0x72;
		const static int FIFO_COUNTL      	=	0x73;
		const static int FIFO_R_W         	=	0x74;
		const static int WHO_AM_I_MPU9250 	=	0x75;	// Should return 0x71
		const static int XA_OFFSET_H      	=	0x77;
		const static int XA_OFFSET_L      	=	0x78;
		const static int YA_OFFSET_H      	=	0x7A;
		const static int YA_OFFSET_L      	=	0x7B;
		const static int ZA_OFFSET_H      	=	0x7D;
		const static int ZA_OFFSET_L      	=	0x7E;
	//End Register Locations
	
	bool ADO=false;
	uint8_t intPin=9;
	uint8_t adoPin=8;

	uint8_t Gscale = GFS_1000DPS;
	uint8_t Ascale = AFS_16G;
	uint8_t Mscale = MFS_16BITS; // Choose either 14-bit or 16-bit magnetometer resolution
	uint8_t Mmode = 0x06;        // 2 for 8 Hz, 6 for 100 Hz continuous magnetometer data read

	int MPU9250_ADDRESS;
	int AK8693_ADDRESS;


	float 	aRes, gRes, mRes;	// scale resolutions per LSB for the sensors
	int16_t accelCount[3];  	// Stores the 16-bit signed accelerometer sensor output
	int16_t gyroCount[3];   	// Stores the 16-bit signed gyro sensor output
	int16_t magCount[3];   		// Stores the 16-bit signed magnetometer sensor output
	float 	magCalibration[3] = {0, 0, 0};	// Factory mag calibration and mag bias
	float 	magbias[3] 	= {0, 0, 0};  		// Factory mag calibration and mag bias
	float 	gyroBias[3] = {0, 0, 0};		// Bias corrections for gyro and accelerometer
	float 	accelBias[3] = {0, 0, 0}; 		// Bias corrections for gyro and accelerometer
	int16_t tempCount;      	// temperature raw count output
	float   temperature;    	// Stores the real internal chip temperature in degrees Celsius
	float   SelfTest[6];    	// holds results of gyro and accelerometer self test
		                
	// global constants for 9 DoF fusion and AHRS (Attitude and Heading Reference System)
	float GyroMeasError = PI * (40.0f / 180.0f);   // gyroscope measurement error in rads/s (start at 40 deg/s)
	float GyroMeasDrift = PI * (0.0f  / 180.0f);   // gyroscope measurement drift in rad/s/s (start at 0.0 deg/s/s)
	float beta = sqrt(3.0f / 4.0f) * GyroMeasError;   // compute beta
	float zeta = sqrt(3.0f / 4.0f) * GyroMeasDrift;   // compute zeta, the other free parameter in the Madgwick scheme usually set to a small or zero value
	
	// these are the free parameters in the Mahony filter and fusion scheme, Kp for proportional feedback, Ki for integral
	const static int Kp = 2.0f * 5.0f; 
	const static int Ki = 0.0f;

	uint32_t count = 0, sumCount = 0; 			// used to control display output rate
	float pitch, yaw, roll;						// Post-processed YPR
	float deltat = 0.0f, sum = 0.0f;    		// integration interval for both filter schemes
	uint32_t lastUpdate = 0, firstUpdate = 0; 	// used to calculate integration interval
	uint32_t Now = 0;       					// used to calculate integration interval
	
	float ax, ay, az, gx, gy, gz, mx, my, mz; 	// variables to hold latest sensor data values 
	float qM[4] = {1.0f, 0.0f, 0.0f, 0.0f};    	// vector to hold quaternion
	float eInt[3] = {0.0f, 0.0f, 0.0f};       	// vector to hold integral error for Mahony method
	
	uint32_t updateInterval;
	bool calibrateOnStart=true;
	bool selfTestOnStart=true;


	void configHW(bool _ADO, uint8_t _intPin, uint8_t _adoPin);
	void configIMU(uint8_t _Ascale,uint8_t _Gscale, uint8_t _Mscale,uint8_t _Mmode);
	
	bool startUp();
	void postStartActions();
	void update();


	void initMPU9250();
	void initAK8963(float * destination);


	int16_t readTempData();
	void readMagData(int16_t * destination);
	void readGyroData(int16_t * destination);
	void readAccelData(int16_t * destination);


	void getAres();
	void getGres();
	void getMres();



	void selfTestMPU9250(float * destination);
	void calibrate(float * dest1, float * dest2);


	void MadgwickQuaternionUpdate(float ax, float ay, float az, float gx, float gy, float gz, float mx, float my, float mz);
 



	//Helper functions for reading data using Wire.h
	uint8_t readByte(uint8_t address, uint8_t subAddress);
	void readBytes(uint8_t address, uint8_t subAddress, uint8_t count, uint8_t * dest);
    void writeByte(uint8_t address, uint8_t subAddress, uint8_t data);

};



#endif