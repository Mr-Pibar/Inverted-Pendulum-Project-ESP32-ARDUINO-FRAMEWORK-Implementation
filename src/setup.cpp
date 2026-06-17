#include <Arduino.h>
#include <FastAccelStepper.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <config.h>
#include <setup.h>
#include <oled.h>

static void Buzzer(int time_ms){
    gpio_set_level((gpio_num_t)BUZZER_PIN, 1);
    delay(time_ms);
    gpio_set_level((gpio_num_t)BUZZER_PIN, 0);
}

void Setup::FAST_ACCEL_STEPPER(FastAccelStepperEngine &engine, FastAccelStepper* &stepper){
    Serial.println("[DEBUG] BEGIN FAS SETUP");
    gpio_set_direction(((gpio_num_t) STEP_PIN), GPIO_MODE_OUTPUT);
    gpio_set_direction(((gpio_num_t) DIR_PIN), GPIO_MODE_OUTPUT);
    gpio_set_direction(((gpio_num_t) ENABLE_PIN), GPIO_MODE_OUTPUT);
    gpio_set_direction(((gpio_num_t) BUZZER_PIN), GPIO_MODE_OUTPUT);
    
    gpio_set_level((gpio_num_t)BUZZER_PIN, 0);
    
    engine.init();
    stepper = engine.stepperConnectToPin(STEP_PIN);

    if(stepper != nullptr){
        stepper->setDirectionPin(DIR_PIN);
        stepper->setEnablePin(ENABLE_PIN, true);
        stepper->enableOutputs();
    }

    Serial.println("[DEBUG] END FAS SETUP");

    delay(2000);

    Buzzer(1000);
}

void Setup::HOMING(FastAccelStepper* &stepper, Adafruit_SSD1306* display){
    gpio_set_direction(((gpio_num_t) HOME_PIN), GPIO_MODE_INPUT);
    Serial.println("[DEBUG] BEGIN HOMING");
    
    HOMING_OLED(display);

    //fast homing
    stepper->setSpeedInHz(4000);
    stepper->setAcceleration(3000);
    stepper->runForward();

    while(gpio_get_level((gpio_num_t) HOME_PIN) == HIGH){
        delay(1);
    }
    stepper->forceStop();

    delay(2000);
    Buzzer(500);

    //backoff
    stepper->setSpeedInHz(1000);
    stepper->setAcceleration(500);
    stepper->move(-ONE_REV_STEPPER);

    while(stepper->isRunning()){
        delay(1);
    }
    
    //slow homing
    stepper->setSpeedInHz(400);
    stepper->setAcceleration(200);
    stepper->runForward();

    while(gpio_get_level((gpio_num_t) HOME_PIN) == HIGH){
        delay(1);
    }
    stepper->forceStopAndNewPosition(0);

    //end 
    Serial.println("[DEBUG HOMING COMPLETE]");
    Serial.println("[DEBUG] CURRENT POS: ");
    Serial.println(stepper->getCurrentPosition());
    delay(2000);
}

void Setup::RAIL_COUNT(FastAccelStepper* &stepper, int32_t* RAIL_LENGTH, Adafruit_SSD1306* display){
    gpio_set_direction(((gpio_num_t) END_PIN), GPIO_MODE_INPUT);
    Serial.println("[DEBUG] BEGIN Measuring rail");

    RAIL_COUNT_OLED(display);

    Buzzer(100);
    delay(300);
    Buzzer(100);

    //fast homing
    stepper->setSpeedInHz(4000);
    stepper->setAcceleration(3000);
    stepper->runBackward();
    
    while(gpio_get_level((gpio_num_t) END_PIN) == HIGH){
        int32_t curr = stepper->getCurrentPosition();
        RAIL_DISPLAY_COUNT(display, curr);
        Serial.print("[DEBUG]: CURRENT POS:");
        Serial.println(curr);
        delay(1);
    }

    stepper->forceStop();
    delay(2000);
    Buzzer(500);

    //backoff
    stepper->setSpeedInHz(1000);
    stepper->setAcceleration(500);
    stepper->move(ONE_REV_STEPPER);

    while(stepper->isRunning()){
        int32_t curr = stepper->getCurrentPosition();
        RAIL_DISPLAY_COUNT(display, curr);
        Serial.print("[DEBUG]: CURRENT POS:");
        Serial.println(curr);
        delay(1);
    }

    //slow homing
    stepper->setSpeedInHz(400);
    stepper->setAcceleration(200);
    stepper->runBackward();

    while(gpio_get_level((gpio_num_t) END_PIN) == HIGH){
        int32_t curr = stepper->getCurrentPosition();
        RAIL_DISPLAY_COUNT(display, curr);
        Serial.print("[DEBUG]: CURRENT POS:");
        Serial.println(curr);
        delay(1);
    }

    stepper->forceStop();
    delay(2000);

    //end 

    int32_t temp = stepper->getCurrentPosition();

    Serial.println("[DEBUG] rail length: ");
    Serial.println(temp);
    
    //pass value;
    *RAIL_LENGTH = abs(temp);

    RAIL_LENGTH_OLED(display, (float)((float)(*RAIL_LENGTH) / (float)STEPS_PER_MM));

    //go to middle;
    int32_t middle = *RAIL_LENGTH / 2;

    delay(2000);

    CENTERING_OLED(display);

    Buzzer(500);

    Serial.println("[DEBUG] CENTERING");
    stepper->setSpeedInHz(3000);
    stepper->setAcceleration(1000);
    stepper->moveTo(-1 * middle);

    while(stepper->isRunning()){
        delay(1);
    }

    Serial.print("[DEBUG]: CURRENT POS:");
    Serial.println(stepper->getCurrentPosition());
    Serial.println("[DEBUG] DONE CENTERING");
    delay(2000);

    Buzzer(1000);
    delay(200);
    Buzzer(100);

    DONE_SETUP_OLED(display);
}   

void Setup::OLED(Adafruit_SSD1306* display){
    Wire.begin(OLED_SDA, OLED_SCL);
    
    if(!display->begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        while(true){
            Buzzer(500);
            delay(200);
        }
    }
    display->clearDisplay();
    delay(10);

    drawScreen_1(display);
}