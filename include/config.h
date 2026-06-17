#ifndef CONFIG_H
#define CONFIG_H

//stepper controls

#define STEP_PIN    26
#define DIR_PIN     27
#define ENABLE_PIN  14
#define BUZZER_PIN  23
#define ONE_REV_STEPPER 1600
#define STEPS_PER_MM 50


//encoder

#define ENCODER_A 34
#define ENCODER_B 35

//cart

#define HOME_PIN    25
#define END_PIN     33

//OLED I2C
#define OLED_SCL 18
#define OLED_SDA 19 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#endif