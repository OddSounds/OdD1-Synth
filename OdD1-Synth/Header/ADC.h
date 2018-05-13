#ifndef ADC_H_
#define ADC_H_

//How many knobs do I need?
typedef enum
{
	ANALOG_OSC1_WAVEFORM = 0,
	ANALOG_OSC2_WAVEFORM,
	ANALOG_OSC1_DUTY_CYCLE,
	ANALOG_OSC2_DUTY_CYCLE,
	TOTAL_ANALOG_READINGS //This many
}ANALOG_READING;

void ADC_Init();

void ADC_Update();

#endif /* ADC_H_ */