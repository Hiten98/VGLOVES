//based on Will Donaldson and his instructable on how to use flex sensors: https://github.com/WillDonaldson/Flex-Glove/blob/master/Flex_Glove_Final_.ino
// only major difference: he uses servos to make a robotic hand, I pass it into unity to make a controller
//  Wiring convention is same as him:
/* Wiring Convention:
 *  Finger  | Lilypad Pin
 *  Thumb   | D5
 *  Index   | D6
 *  Middle  | D7
 *  Ring    | D8
 *  Pinky   | D9
 */

int angles[5];                                           //array for storing finger angles
int val;
int flexPins[]={A0,A1,A2,A3,A4};            //order of finger connections from thumb to little (ie: A0=thumb, A1=index,...etc.)

/*
 *  Below are the calibration offsets for flex sensors, top row is offset for relaxed finger, bottom row is offset for contracted finger.
 *  Columns, from left to right correspond from the thumb to pinky.
 *  Values from the output of Flex_Glove_Calibration.ino
 */
int flexsensorRange[2][5]= {{260, 400, 480, 230, 380},
                            {330, 500, 900, 360, 450}};

void setup() {
  Serial.begin(9600);                        //If you have issues with the baudrate and serial monitor see the Read Me file.
}

void loop() {
  for(int i=0; i<5; i+=1){                        //repeat process for each of the 5 fingers
    val=analogRead(flexPins[i]);                  //reads the position of the finger

    // mpa voltage read to angles[i]
    angles[i]=map(val, flexsensorRange[0][i], flexsensorRange[1][i], 0, 180);   //maps the value measured from the flex sensor and outputs an angle for the servo within the range finger motion


    angles[i]=constrain(angles[i], 0, 180);       //any values above/below the maximum/minimum calibration value are reset to the highest/lowest value within the acceptable range
    Serial.print(angles[i]);
    if(i==0) {
      Serial.write(angles[i] + ",,");     //write to serial port: thumb
    }
    if(i==1) {
      Serial.write(angles[i] + ",,");     //write to serial port: index
    }
    if(i==2) {
      Serial.write(angles[i] + ",,");     //write to serial port: middle
    }
    if(i==3) {
      Serial.write(angles[i] + ",,");     //write to serial port: ring
    }
    if(i==4) {
      Serial.write(angles[i]);     //write to serial port: little
    }
  }
  Serial.println();         //write a new line as a main delimiter
  delay(100);    //send an update after 100 ms
}
