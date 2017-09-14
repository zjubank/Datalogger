#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

const int chipSelect = 10;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);           // select the pins used on the LCD panel

int lcd_key     = 0;
int adc_key_in  = 0;
bool ifPaused = false;

#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int read_LCD_buttons(){               // read the buttons
    adc_key_in = analogRead(0);       // read the value from the sensor 

    // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
    // we add approx 50 to those values and check to see if we are close
    // We make this the 1st option for speed reasons since it will be the most likely result

    if (adc_key_in > 1000) return btnNONE; 

    // For V1.1 us this threshold
    if (adc_key_in < 50)   return btnRIGHT;  
    if (adc_key_in < 250)  return btnUP; 
    if (adc_key_in < 450)  return btnDOWN; 
    if (adc_key_in < 650)  return btnLEFT; 
    if (adc_key_in < 850)  return btnSELECT;  

    return btnNONE;                // when all others fail, return this.
}

void autoEnter(int i) {
  if(i != 0 && i%32 == 0) {
    delay(1000);
    lcd.clear();
  }
  if(i != 0 && i%16 == 0 && i%32 != 0){
    lcd.setCursor(0,1);
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; 
  }

  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  lcd.print("Initializing...");

  if (!SD.begin(chipSelect)) {
    lcd.setCursor(0,1);
    lcd.print("Failed!");

    return;
  }
  lcd.setCursor(0,1);
  lcd.print("Initialized!");
}

void loop() {
  String dataString = "";

  if(ifPaused == true) {
    if(read_LCD_buttons() == btnSELECT) {
      // 防抖动
      delay(10);
      if(read_LCD_buttons() == btnSELECT) {
        // 等待按钮松开
        while(read_LCD_buttons() != btnNONE) {
          
        }
        // 清空buffer
        while (Serial.available() > 0) {
          Serial.read();
        }
        ifPaused = false;
        
        lcd.clear();
        lcd.print("Restarted.");
      }
      else {
        return;
      }
    }
    else {
      return;
    }
  }
  
  if(read_LCD_buttons() == btnSELECT) {
    delay(10);
    if(read_LCD_buttons() == btnSELECT) {
      // 等待按钮松开
      while(read_LCD_buttons() != btnNONE) {
        
      }
      ifPaused = true;
      
      lcd.clear();
      lcd.print("Input is paused.");
      lcd.setCursor(0,1);
      lcd.print("Press to restart");
    }
  }
  
  if( Serial.available() > 0 ) {
    delay(10);
    
    while (Serial.available() > 0) {
      char c = char(Serial.read());
      dataString += c;
    }
    Serial.print("Input: ");
    Serial.println(dataString);
    
    lcd.clear();
    for(int i = 0; i < dataString.length(); i++) {
      autoEnter(i);
      lcd.print(dataString.charAt(i));
    }

    // *如果数据速度很快,可以把打开文件放在loop外面
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
    }
    else {
      lcd.clear();
      lcd.print("Error in writing");
    }
  }
}

