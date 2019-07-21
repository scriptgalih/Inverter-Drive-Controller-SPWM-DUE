void parsing() {
  if (Serial1.available()) {
    if (Serial1.read() == '@') {
      ca = '@';
      for (int x = 0; x <= 80; x++) {
        string[x] = NULL;
      }
      //      Serial1.println("Mulai Rekam");
      while (ca != '#') {
        //        Serial1.println("rekam . . . ");
        if (Serial1.available()) {
          //           Serial1.println("adding charater . . . . . . . . . . . .");
          ca = Serial1.read();
          if (ca == '#') {
            break;
          }
          string[indx] = ca;
          indx++;
        }
      }
      //      Serial1.println(string);
      indx = 0;


      char *pt;
      pt = strtok (string, ",");
      int idx = 0;
      while (pt != NULL) {
        ubahData[idx] = atoi(pt);
        idx++;
        pt = strtok (NULL, ",");
      }
      if (ubahData[0] == 1) {
        setFreq = ubahData[1];
//        if (statIRAMS == 1) {

          if (setFreq >= 50) {
            setAmp = 1;
            Serial.println("satu");
          } else if (setFreq <= 20) {
            setAmp = 0.2;
            Serial.println("dua");
          } else {
            setAmp = (0.0267 * setFreq) - 0.3333;
            Serial.println("tiga");
          }
          TimerStart(TC0, 2, TC2_IRQn, setFreq * 360 / 2);
//        }
        Serial.println(setAmp);
      } else if (ubahData[0] == 2) {
        setCarrier = ubahData[1];
//        if (statIRAMS == 1) {
          TimerStart(TC1, 0, TC3_IRQn, setCarrier * 49 / 2);
//        }

      } else if (ubahData[0] == 0) {
        if (ubahData[1] == 1) {
          statIRAMS = 1;
          TimerStart(TC0, 2, TC2_IRQn, setFreq * 360 / 2);
          TimerStart(TC1, 0, TC3_IRQn, setCarrier * 49 / 2);
        } else if (ubahData[1] == 0) {
          digitalWrite(11, R);
          digitalWrite(7, 0);
          digitalWrite(10, 0);
          digitalWrite(8, 0);
          digitalWrite(12, 0);
          digitalWrite(9, 0);
          statIRAMS = 0;
          TimerStart(TC0, 2, TC2_IRQn, 0);
          TimerStart(TC1, 0, TC3_IRQn, 0);
        }
      }
      //      Serial.print("\nCEK SALEAE\t F:");Serial.print(setFreq);
      //      Serial.print("\t Carrier:");Serial.print(setCarrier);
      //      Serial.print("\t Amplitudo:");Serial.print(setAmp);
    }
  }
}

