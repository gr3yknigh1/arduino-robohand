// подключаем необходимые библиотеки для работы MultiFuncShield

#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>
#include <SoftwareServo.h>

// подключаем библиотеку сервомотора

SoftwareServo myservo0;
SoftwareServo myservo1;
SoftwareServo myservo2;
SoftwareServo myservo3;
SoftwareServo myservo4; // создать серво-объект myservo для управления сервоприводом 
 
int potpin0 = 0;
int potpin1 = 1;
int potpin2 = 2;
int potpin3 = 3;
int potpin4 = 4; // Присваиваем имя potpin аналоговому выводу А0, к которому подключена средняя ножка потенциометра 
int val0; 
int val1;
int val2;
int val3;
int val4;// переменная считывания данных с аналогового входа
int ugol0; 
int ugol1;
int ugol2;
int ugol3;
int ugol4;
int Tekushiy_ugol0, Tekushiy_ugol1, Tekushiy_ugol2, Tekushiy_ugol3, Tekushiy_ugol4;
// переменная для хранения угла поворота сервы
 
void setup() 
{ 
  Timer1.initialize();
  MFS.initialize(&Timer1);    // инициализация multi-function shield library
  myservo0.attach(2); 
  myservo1.attach(3);
  myservo2.attach(5);
  myservo3.attach(6);
  myservo4.attach(8);// Подключаем цифровой вывод (pin 9) к сервомотору 
  Serial.begin(9600);  
}

 void Read_Pozition()
 {
  val0 = analogRead(potpin0);
  val1= analogRead(potpin1);
  val2 = analogRead(potpin2);
  val3 = analogRead(potpin3);
  val4 = analogRead(potpin4);

  ugol0 = map(val0, 0, 1024, 0, 170);// преобразуем его, чтобы использовать его с серво (значение от 0 до 180)
  ugol1 = map(val1, 0, 1024, 0, 170);// преобразуем его, чтобы использовать его с серво (значение от 0 до 180)
  ugol2 = map(val2, 0, 1024, 0, 170);// преобразуем его, чтобы использовать его с серво (значение от 0 до 180)
  ugol3 = map(val3, 0, 1024, 0, 170);// преобразуем его, чтобы использовать его с серво (значение от 0 до 180)
  ugol4 = map(val4, 0, 1024, 0, 170);
  
 }

 
void loop() 
{
  Read_Pozition();
   
  Tekushiy_ugol0 = ugol0;
  Tekushiy_ugol1 = ugol1;
  Tekushiy_ugol2 = ugol2;
  Tekushiy_ugol3 = ugol3;
  Tekushiy_ugol4 = ugol4;
  

  Read_Pozition();

  if(Tekushiy_ugol0 != ugol0)
  {
    
    myservo0.write(ugol0);
  }

    if(Tekushiy_ugol1 != ugol1)
  {
    myservo1.write(ugol1);
  }

    if(Tekushiy_ugol2 != ugol2)
  {
    myservo2.write(ugol2);
  }

    if(Tekushiy_ugol3 != ugol3)
  {
    myservo3.write(ugol3);
  }
 
    if(Tekushiy_ugol4 != ugol4)
  {
    myservo4.write(ugol4);
    Serial.println(ugol4);
  }
  
  delay(18);  // ждем, когда сервопривод отработает команду 
 
  SoftwareServo::refresh(); //команда обновления сервопривода, каждые 50 мс.
}
