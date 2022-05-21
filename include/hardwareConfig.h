/**
 * @file conditionalCompilation.h
 * @author Jan Wielgus
 * @brief All macros that set drone at compilation time.
 * @date 2022-04-12
 */

#ifndef CONDITIONALCOMPILATION_h
#define CONDITIONALCOMPILATION_h


	// Available sensors
#define COLYBER_SENSOR_NO_SENSOR		0
#define COLYBER_SENSOR_MPU6050			1	// Acc + Gyro + Temperature
#define COLYBER_SENSOR_MPU6500SPI		2	// Acc + Gyro + Temperature
#define COLYBER_SENSOR_HMC5883L			3	// Magn
#define COLYBER_SENSOR_TINY_GPS_PLUS	4	// Gps
// add new sensor here...


	// Sensors selection (change sensor by setting proper value)
#define COLYBER_MAGN			COLYBER_SENSOR_NO_SENSOR			// TODO: calibrate magnetometer
#define COLYBER_2ND_ACC			COLYBER_SENSOR_NO_SENSOR			// TODO: not implemented yet
#define COLYBER_2ND_GYRO		COLYBER_SENSOR_NO_SENSOR			// TODO: not implemented yet
#define COLYBER_GPS				COLYBER_SENSOR_TINY_GPS_PLUS


	// Other flags (comment if want to deactivate)
// #define COLYBER_DEACTIVATE_MOTORS						// Motors won't spin




////////////////////////////////////////////////////////////////////////////////

	// Auto flags deduction (do not comment)
#if COLYBER_MAGN != COLYBER_SENSOR_NO_SENSOR
	#define COLYBER_USE_MAGN
#endif
#if COLYBER_2ND_ACC != COLYBER_SENSOR_NO_SENSOR
	#define COLYBER_USE_2ND_ACC
#endif
#if COLYBER_2ND_GYRO != COLYBER_SENSOR_NO_SENSOR
	#define COLYBER_USE_2ND_GYRO
#endif
#if COLYBER_GPS != COLYBER_SENSOR_NO_SENSOR
	#define COLYBER_USE_GPS
#endif


	// Validation (do not comment)
#if !( \
	COLYBER_2ND_ACC == COLYBER_SENSOR_NO_SENSOR || \
	COLYBER_2ND_ACC == COLYBER_SENSOR_MPU6050 || \
	COLYBER_2ND_ACC == COLYBER_SENSOR_MPU6500SPI \
	/* other accelerometers */ )
	#error "Invalid accelerometer"
#endif
#if !( \
	COLYBER_2ND_GYRO == COLYBER_SENSOR_NO_SENSOR || \
	COLYBER_2ND_GYRO == COLYBER_SENSOR_MPU6050 || \
	COLYBER_2ND_GYRO == COLYBER_SENSOR_MPU6500SPI \
	/* other gyroscopes */ )
	#error "Invalid gyroscope"
#endif
#if !( \
	COLYBER_MAGN == COLYBER_SENSOR_NO_SENSOR || \
	COLYBER_MAGN == COLYBER_SENSOR_HMC5883L \
	/* other magnetometers... */ )
	#error "Invalid magnetometer"
#endif
#if !( \
	COLYBER_GPS == COLYBER_SENSOR_NO_SENSOR || \
	COLYBER_GPS == COLYBER_SENSOR_TINY_GPS_PLUS \
	/* other gps sensors... */ )
	#error "Invalid gps sensor"
#endif


#endif // CONDITIONALCOMPILATION_h
