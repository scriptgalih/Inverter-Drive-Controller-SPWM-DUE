void TC2_Handler()
{
   TC_GetStatus(TC0, 2);
//   digitalWrite(13, ledOn3 = !ledOn3);
   tempSine++;
//   if(tempSine%180==0){
//    digitalWrite(12, ledOn3 = !ledOn3);
//   }
}
void TC3_Handler()
{
   TC_GetStatus(TC1, 0);
//   digitalWrite(12, ledOn = !ledOn);
   tempTriangle++;
}
