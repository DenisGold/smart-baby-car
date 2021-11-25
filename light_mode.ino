int back_right = 7; // задний правий
int back_left = 6; // задний левый

int fordward_left_right = 5; // передний левый правый
int forward_right_left = 4; // передний правый левый
int forward_left_left = 3; // передний левый левый
int forward_right_right = 2; // передний правый правый

int buttonMode = 12;
int buttonModeLastState = 0;
String modes[4] = {"stroboscop", "light", "wave", "haos"};
int modesSize = sizeof(modes) / sizeof(modes[0]);
int modeIndex = 2;
String mode = modes[modeIndex];

int intervalValue = 0;

// stroboscop mode
boolean status = true; // флаг, что активна левая
boolean open = true; // флаг, включения
int interval[6]={50, 120, 90, 240, 150, 20};     // интервал включения/выключения LED
int intervalMode = 0;
int intervalModes = sizeof(interval) / sizeof(interval[0]);

//wave mode
int waveValue = 0;
int waveMax = 8;
int waveDelay = 75;

void setup()  { 
  Serial.begin(9600);
  pinMode(buttonMode, INPUT);

  // два вывода на выход
  pinMode(back_right, OUTPUT);
  pinMode(back_left, OUTPUT);
  pinMode(fordward_left_right, OUTPUT);
  pinMode(forward_right_left, OUTPUT);
  pinMode(forward_left_left, OUTPUT);
  pinMode(forward_right_right, OUTPUT);
} 
void loop()  { 
   int buttonModeState = digitalRead(buttonMode);
   if(buttonModeLastState != buttonModeState){
       if(buttonModeState == 1){
            modeIndex += 1;
            if(modeIndex == modesSize)
                modeIndex = 0;

            mode = modes[modeIndex];
       }
       buttonModeLastState = buttonModeState;
   }

    //Стробоскоп режим
    if(mode == "stroboscop"){
        intervalValue += 1;
        
        if(interval[intervalMode] == intervalValue){
            intervalValue = 0;

            if (open){// если true
                digitalWrite(status ? forward_left_left : fordward_left_right, HIGH);
                digitalWrite(status ? forward_right_right : forward_right_left, HIGH);
                digitalWrite(status ? back_right : back_left, HIGH);// если status == false то падаем на пин 3 иначе на пин 5
            }else{ // иначе
                digitalWrite(status ? forward_left_left : fordward_left_right, LOW);
                digitalWrite(status ? forward_right_right : forward_right_left, LOW);
                digitalWrite(status ? back_right : back_left, LOW);  // если status == false то падаем на пин 3 иначе на пин 5
            }
            intervalMode += 1;
            if(intervalMode == intervalModes)
                intervalMode = 0;

            delay(interval[intervalMode]);
            if (intervalMode == 5) // если последний проход по циклу
                status = !status; // передаем слово (меняем текущий пин) меняем false на true и наоборот;

            open = !open;
        }else{
            delay(1);
        }
    }else if(mode == "light"){
        digitalWrite(forward_left_left, HIGH);
        digitalWrite(fordward_left_right, HIGH);
        digitalWrite(forward_right_right, HIGH);
        digitalWrite(forward_right_left, HIGH);
        digitalWrite(back_right, HIGH);
        digitalWrite(back_left, HIGH);
        delay(1);

    }else if(mode == "wave"){
        
        if(waveValue == 0){
            digitalWrite(forward_left_left, HIGH);
            digitalWrite(back_left, HIGH);
        }
        if(waveValue == 1){
            digitalWrite(fordward_left_right, HIGH);
            digitalWrite(back_left, HIGH);
        }
        if(waveValue == 2){
            digitalWrite(forward_right_left, HIGH);
            digitalWrite(back_right, HIGH);
        }
        if(waveValue == 3){
            digitalWrite(forward_right_right, HIGH);
            digitalWrite(back_right, HIGH);
        }
        if(waveValue == 4){
            digitalWrite(forward_left_left, LOW);
        }
        if(waveValue == 5){
            digitalWrite(fordward_left_right, LOW);
            digitalWrite(back_left, LOW);
        }
        if(waveValue == 6){
            digitalWrite(forward_right_left, LOW);
        }
        if(waveValue == 7){
            digitalWrite(forward_right_right, LOW);
            digitalWrite(back_right, LOW);
        }

        waveValue += 1;
        if(waveValue == waveMax)
            waveValue = 0;
        
        delay(waveDelay);
    
    }else if(mode == "haos"){
        digitalWrite(forward_left_left, HIGH);
        digitalWrite(fordward_left_right, LOW);
        digitalWrite(forward_right_right, HIGH);
        digitalWrite(forward_right_left, LOW);
        digitalWrite(back_right, HIGH);
        digitalWrite(back_left, HIGH);
        
        delay(1);

    }
                     
}
