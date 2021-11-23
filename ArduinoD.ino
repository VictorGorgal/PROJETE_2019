#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <SoftwareSerial.h>

Adafruit_SSD1306 display(128, 64);  // Create display

SoftwareSerial mySerial(10, 11);

short posp = 0; //0
short pos1 = -1;
short oup = 0;
short odown = 0;
short hrs = 17; //17
short mins = 30; //0
short hrster = 18; //18
short minster = 30; //0
short segr = 0; //0
short minsr = 30; //30
short hrsr = 12; //12
short ds = 1;
short bpm;
short bpmex;
short reset1 = 0;
int med;
int medex1;
int medex2;
short ex = -1; //-1
long int t1 = 0;
long int t2 = 0;
long int t3 = 0;
String dados1;
String dados2;
boolean pos2 = 0;
boolean npos2 = 0;
boolean opos2 = 0;
boolean dom = 0; //0
boolean seg = 0;
boolean ter = 0;
boolean qua = 0;
boolean qui = 0;
boolean sex = 0;
boolean sab = 0;
boolean hatv = 0;
boolean atv = 0;
boolean de = 0;

void setup()  {                                             //inicio do void setup()
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(12, INPUT);

  delay(100);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();

  display.setTextColor(WHITE);

  display.setRotation(0);

  display.setTextWrap(true);

  display.dim(0);

  t1 = millis();
  
}

void loop(){                                              //inicio do void loop()

  //Serial.println(posp);

  if((millis() - t1) >= 1000){    //contando as horas
    t1=millis();
    segr++;
  }
  if(segr >= 60){
    segr = 0;
    minsr ++;
  }
  if(minsr >= 60){
    minsr = 0;
    hrsr ++;
  }
  if(hrsr >= 24){
    hrsr = 0;
    ds ++;
    ex = -1; //dar a opcao de escolher outro exercicio no dia seguinte
  }
  if(ds >= 8){
    ds = 1;
  }
    
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(0);


  while (mySerial.available() > 0) {
    dados1 = mySerial.readStringUntil(',');
    dados2 = mySerial.readStringUntil('.');
  }
  bpm = dados1.toInt();

  med = dados2.toInt();
  

  npos2 = digitalRead(12);    //detecta mudanca no botao de pos2 (selecionar)
  if (npos2 != opos2) {
    if (npos2 == HIGH) {
        pos1++;
    }
  }
  opos2 = npos2;

  

  if (posp == 0) {                                                                                     // tela 0
    while (digitalRead(9) == 0) {
      posp = 1;    // pressionar enter muda de pagina
      pos1 = 0;
      delay(50);
    }

    display.setTextSize(0);
    display.setTextColor(WHITE);

    display.setCursor(40, 0);
    display.println("Bem Vindo"); //"bem vindo"

    display.setCursor(60, 10);
    display.println("ao"); //ao

    display.setCursor(60, 55);
    display.println("selecionar>"); //"pressiona algo"

    display.setCursor(51, 40);  //mostra as horas
    if(hrsr < 10){
      display.print("0");
    }
    display.print(hrsr);
    display.print(":");
    if(minsr < 10){
      display.print("0");
    }
    display.print(minsr);

    display.setTextSize(2);
    display.setCursor(5, 20);
    display.println("ControlFit"); //"ControlFit"

  }

  if(posp == 1){                                                                                       //tela 1

    while (digitalRead(9) == 0) {
      posp = 2; // pressionar enter muda de pagina
      delay(50);
    }

    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.println(F("Insira o dia atual da semana ")); //insira o dia da semana atual
    
    display.setCursor(32, 30);
    display.setTextSize(2);
    display.fillRect(30, 27, 64, 20, WHITE);
    display.setTextColor(BLACK);

if (pos1 == 0) {       //mostrar e selecionar domingo
      display.println(F("<Dom>"));
      
      ds = 1;
        
      while(digitalRead(6) == 0){
          pos1 = 6;
          delay(50);
      }
  }

  if (pos1 == 1) {       //mostrar e selecionar domingo
      display.println(F("<Seg>"));
      
      ds = 2;
      Serial.println(ds);
        
      while(digitalRead(6) == 0){
          pos1 = 0;
          delay(50);
      }
  }

  if (pos1 == 2) {       //mostrar e selecionar domingo
      display.println(F("<Ter>"));

      ds = 3;
        
      while(digitalRead(6) == 0){
          pos1 = 1;
          delay(50);
      }
  }

  if (pos1 == 3) {       //mostrar e selecionar domingo
      display.println(F("<Qua>"));

      ds = 4;
        
      while(digitalRead(6) == 0){
          pos1 = 2;
          delay(50);
      }
  }

  if (pos1 == 4) {       //mostrar e selecionar domingo
      display.println(F("<Qui>"));

      ds = 5;
        
      while(digitalRead(6) == 0){
          pos1 = 3;
          delay(50);
      }
  }

  if (pos1 == 5) {       //mostrar e selecionar domingo
      display.println(F("<Sex>"));

      ds = 6;
        
      while(digitalRead(6) == 0){
          pos1 = 4;
          delay(50);
      }
  }

  if (pos1 == 6) {       //mostrar e selecionar domingo
      display.println(F("<Sab>"));

      ds = 7;
        
      while(digitalRead(6) == 0){
          pos1 = 5;
          delay(50);
      }
      
  }
  
  if(pos1 >= 7){
    pos1 = 0; 

  }
  }

  if(posp == 2){                                                                                      //tela 2

    while(hrsr < 0){
      hrsr++;
      delay(50);
    }

    while(minsr < 0){
      minsr++;
      delay(50);
    }
    
    while (digitalRead(9) == 0) {
      posp = 3; // pressionar enter muda de pagina
      pos1 = 0;
      delay(50);
    }
    while (digitalRead(6) == 0){
      posp = 1;
      delay(50);
    }
    
    display.setTextSize(0);
    display.setCursor(0, 0);
    display.println(F("insira a hora atual:")); //insira a hr e o dia da semana
    display.setCursor(50, 25);
    if(pos1 == 0){                     //hrsr selecionado
      display.fillRect(49, 24, 13, 9, WHITE);
      display.setTextColor(BLACK);
    if(hrsr < 10){
      display.print(F("0"));
    }
    display.print(hrsr);
    display.setTextColor(WHITE);
    display.print(F(":"));
    if(minsr < 10){
      display.print(F("0"));
    }
    display.println(minsr);
    
    if(digitalRead(7) != oup){             //aumentar ou diminuir variavel
        if(digitalRead(7) == 0){
          hrsr = hrsr+1;
          delay(50);
        }
      }
      oup = digitalRead(7);

      if(digitalRead(8) != odown){
        if(digitalRead(8) == 0){
          hrsr = hrsr-1;
          delay(50);
        }
      }
      odown = digitalRead(8);
      
    }
    if(pos1 == 1){                   //minsr selecionado
      display.fillRect(67, 24, 13, 9, WHITE);
      display.setTextColor(WHITE);
    if(hrsr < 10){
      display.print(F("0"));
    }
    display.print(hrsr);
    display.print(F(":"));
    display.setTextColor(BLACK);
    if(minsr < 10){
      display.print(F("0"));
    }
    display.println(minsr);

    if(digitalRead(7) != oup){
        if(digitalRead(7) == 0){
          minsr = minsr+1;
          delay(50);
        }
      }
      oup = digitalRead(7);

      if(digitalRead(8) != odown){
        if(digitalRead(8) == 0){
          minsr = minsr-1;
          delay(50);
        }
      }
      odown = digitalRead(8);
      
    }else{
      pos1 = 0;
    }
    
    display.setTextColor(WHITE); 
    display.setCursor(0, 55);
    display.println(F("<voltar   selecionar>"));
  }
  

  if (posp == 3) {                                                                                    //tela 3
    
    while (digitalRead(9) == 0) {
      posp = 4; // pressionar enter muda de pagina
      pos1 = 0;
      delay(50);
    }
    while (digitalRead(6) == 0){
      posp = 2;
      delay(50);
    }

    


    display.setTextSize(0);
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.println(F("selecione sua carga  horaria:"));

    display.setCursor(84, 25);
    if(hrs < 10){
      display.print(F("0"));
    }
    display.print(hrs);
    display.print(F(":"));
    if(mins < 10){
      display.print(F("0"));
    }
    display.print(mins);

    display.setCursor(84, 40);
    if(hrster < 10){
      display.print(F("0"));
    }
    display.print(hrster);
    display.print(F(":"));
    if(minster < 10){
      display.print(F("0"));
    }
    display.print(minster);   
    


    if (pos1 == 0) {                       //hrs selecionado    

      if(digitalRead(7) != oup){ //aumentar hrs
        if(digitalRead(7) == 0){
          hrs = hrs+1;
          delay(50);
        }
      }
      oup = digitalRead(7);

      if(digitalRead(8) != odown){ //diminuir hrs
        if(digitalRead(8) == 0){
          hrs = hrs-1;
          delay(50);
        }
      }
      odown = digitalRead(8);

      while(hrs < 0){  // limite
        hrs++;
        delay(50);
      }
      while(hrs >= 24){
        hrs = 23;
        delay(50);
      }
      
      display.fillRect(83, 24, 13, 9, WHITE);      

      display.setCursor(84, 25);
      display.setTextColor(BLACK);
      if(hrs < 10){
        display.print("0");
      }
      display.print(hrs);    
            

    }else if(pos1 == 1){                   //mins selecionados    

       while(mins < 0){  // limite
          mins = mins + 10;
          delay(50);
        }
        while(mins >= 60){
          mins = 50;
          delay(50);
        }
        
      display.fillRect(101, 24, 13, 9, WHITE); 
      display.setCursor(84, 25);
      
      display.print("  :");
      display.setTextColor(BLACK);
      if(mins < 10){
        display.print("0");
      }
      display.print(mins);      

      if(digitalRead(7) != oup){  // aumentar mins
        if(digitalRead(7) == 0){
          mins = mins+10;
          delay(50);
        }
      }
      oup = digitalRead(7);

      if(digitalRead(8) != odown){  // diminuir mins
        if(digitalRead(8) == 0){
          mins = mins-10;
          delay(50);
        }
      }
      odown = digitalRead(8);


    }else if(pos1 == 2){                   //hrster selecionado

      while(hrster < 0){  // limite
          hrster++;
          delay(50);
        }
        while(hrster >= 24){
          hrster = 23;
          delay(50);
        }

      display.fillRect(83, 39, 13, 9, WHITE);
      display.setCursor(84, 40);
      display.setTextColor(BLACK);
      
      if(hrster < 10){
        display.print("0");
      }
      display.print(hrster);

      if(digitalRead(7) != oup){ // aumentar hrster
        if(digitalRead(7) == 0){
          hrster = hrster+1;
          delay(50);
        }
      }
      oup = digitalRead(7);

      if(digitalRead(8) != odown){  //diminuir hrster
        if(digitalRead(8) == 0){
          hrster = hrster-1;
          delay(50);
        }
      }
      odown = digitalRead(8);
      
       
    }else if(pos1 ==3){                      //minster selecionado

      while(minster < 0){  // limite
          minster = minster + 10;
          delay(50);
        }
      while(minster >= 60){
          minster = 50;
          delay(50);
        }

      display.fillRect(101, 39, 13, 9, WHITE);
      display.setCursor(84, 40);
      
      display.print(F("  :"));
      display.setTextColor(BLACK);
      if(minster < 10){
        display.print(F("0"));
      }
      display.print(minster);

      if(digitalRead(7) != oup){  // aumentar minster
        if(digitalRead(7) == 0){
          minster = minster+10;
          delay(50);
        }
      }
      oup = digitalRead(7);

      if(digitalRead(8) != odown){  // diminuir minster
        if(digitalRead(8) == 0){
          minster = minster-10;
          delay(50);
        }
      }
      odown = digitalRead(8);
      
    }else{
      pos1 = 0;
    }

    
    display.setTextColor(WHITE);
    display.setCursor(0, 25);
    display.print(F("iniciar as: "));
    display.setCursor(0, 40);
    display.print(F("terminar as: "));

    display.setCursor(0, 55);
    display.println(F("<voltar   selecionar>"));

  }

  if (posp == 4) {                                                                                     //tela 4
    display.setCursor(0, 0);
    display.println(F("Selecione os seus    dias disponiveis: "));
    display.setCursor(32, 30);
    display.setTextSize(2);
    display.fillRect(30, 27, 64, 20, WHITE);
    display.setTextColor(BLACK);
    

    
    if (pos1 == 0) {       //mostrar e selecionar domingo
      display.println(F("<Dom>"));

      if(dom == LOW){
        while(digitalRead(9) == 0){
        dom = 1;
        delay(50);
        }
      }
        
      while(digitalRead(6) == 0){
          pos1 = 7;
          delay(50);
      }
      
    } else if(pos1 == 1){   //mostrar e selecionar seg
      display.println(F("<Seg>"));
      if(seg == LOW){
        while(digitalRead(9) == 0){
        seg = 1;
        delay(50);
        }
      }
      
                   
      while(digitalRead(6) == 0){
          pos1 = 0; 
          delay(50);
      }
      
    }else if(pos1 == 2){   //mostrar e selecionar ter
      display.println(F("<ter>"));
      if(ter == LOW){
        while(digitalRead(9) == 0){
        ter = 1;
        delay(50);
        }
      }
      

           
      while(digitalRead(6) == 0){
          pos1 = 1; 
          delay(50);
      }
           
    } else if(pos1 == 3){   //mostrar e selecionar qua
      display.println(F("<Qua>"));
      if(qua == LOW){
        while(digitalRead(9) == 0){
        qua = 1;
        delay(50);
        }
      }
      
        
    
      while(digitalRead(6) == 0){
          pos1 = 2; 
          delay(50);
      }
            
    }else if(pos1 == 4){   //mostrar e selecionar qui
      display.println(F("<Qui>"));
      if(qui == LOW){
        while(digitalRead(9) == 0){
        qui = 1;
        delay(50);
        }
      }
        
        
    
      while(digitalRead(6) == 0){
          pos1 = 3; 
          delay(50);
      }
            
    } else if(pos1 == 5){   //mostrar e selecionar sex
      display.println(F("<Sex>"));
      if(sex == LOW){
        while(digitalRead(9) == 0){
        sex = 1;
        delay(50);
        }
      }
      
      
      while(digitalRead(6) == 0){
          pos1 = 4; 
          delay(50);
      }  
           
    }else if(pos1 == 6){   //mostrar e selecionar sab
      display.println(F("<Sab>"));
      if(sab == LOW){
        while(digitalRead(9) == 0){
        sab = 1;
        delay(50);
        }
      }
        
       
      while(digitalRead(6) == 0){
          pos1 = 5; 
          delay(50);
      }    
          
    }else if(pos1 == 7){ //pronto para continuar
      
       
      
      display.fillRect(30, 27, 64, 20, BLACK);
      display.setTextColor(WHITE);
      display.setTextSize(0);
      display.setCursor(0, 55);
      display.println(F("<voltar   selecionar>"));
      while (digitalRead(9) == 0) {
      posp = 5; // pressionar enter muda de pagina
      pos1 = 0;
      delay(50);
    }    
    while (digitalRead(6) == 0){
      posp = 3;
      delay(50);
    }
  }else{
    pos1 = 0;
  }

if(pos1 != 7){
  if(dom == 1){     //mostrar check e a opÃ§Ã£o de voltar para o dia anterior
        display.drawLine(100, 25, 102, 27, WHITE);
        display.drawLine(102, 27, 106, 23, WHITE);

        if(pos1 == 0){
        while(digitalRead(9) == 0){
        dom = 0;
        delay(50);
      }
      }
      
    }if(seg == 1){
        display.drawLine(100, 30, 102, 32, WHITE);
        display.drawLine(102, 32, 106, 28, WHITE);

        if(pos1 == 1){
        while(digitalRead(9) == 0){
        seg = 0;
        delay(50);
      }
      }
      
    }if(ter == 1){
        display.drawLine(100, 35, 102, 37, WHITE);
        display.drawLine(102, 37, 106, 33, WHITE); 

        if(pos1 == 2){
        while(digitalRead(9) == 0){
        ter = 0;
        delay(50);
      }
      }
           
    }if(qua == 1){
        display.drawLine(100, 40, 102, 42, WHITE);
        display.drawLine(102, 42, 106, 38, WHITE);

        if(pos1 == 3){
        while(digitalRead(9) == 0){
        qua = 0;
        delay(50);
      }
      }
      
    }if(qui == 1){
        display.drawLine(100, 45, 102, 47, WHITE);
        display.drawLine(102, 47, 106, 43, WHITE);

        if(pos1 == 4){
        while(digitalRead(9) == 0){
        qui = 0;
        delay(50);
      }
      }
      
    }if(sex == 1){
        display.drawLine(100, 50, 102, 52, WHITE);
        display.drawLine(102, 52, 106, 48, WHITE);

        if(pos1 == 5){
        while(digitalRead(9) == 0){
        sex = 0;
        delay(50);
      }
      }
      
    }if(sab == 1){
        display.drawLine(100, 55, 102, 57, WHITE);
        display.drawLine(102, 57, 106, 53, WHITE);

        if(pos1 == 6){
        while(digitalRead(9) == 0){
        sab = 0;
        delay(50);
        }
      }      
    }
  }
}

  if(posp == 5){                                                                                  //tela 5
    
    while (digitalRead(9) == 0) {
      posp = 6; // pressionar enter muda de pagina
      pos1 = 0;
      delay(50);
    }    
    while (digitalRead(6) == 0){
      posp = 4;
      delay(50);
    }
    
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println(F("voce tem certeza     deste horario? ele sopodera ser trocado 2 vezes por mes"));
    display.setCursor(0, 55);
    display.println(F("<voltar   selecionar>"));
    
  }

  if(posp == 6){                                                                                                                                       //tela 6

    while (digitalRead(9) == 0) {
      posp = 7; // pressionar enter muda de pagina
      delay(50);
    }

    display.setTextColor(WHITE);
    display.setCursor(27,10);
    display.setTextSize(2);
    display.println(F("Pronto!"));
    display.setCursor(21, 55);
    display.setTextSize(0);
    display.println(F("Vamos exercitar?"));


  }



  if(posp == 7){                                                                                                                                       //tela 7

    display.setTextColor(WHITE);
    display.setTextSize(0); 
      
    
    if(ds == 1 && dom == 1 || ds == 2 && seg == 1 || ds == 3 && ter == 1 || ds == 4 && qua == 1 || ds == 5 && qui == 1 || ds == 6 && sex == 1 || ds == 7 && sab == 1){ //escolher exercicio
      de = 1;
      if(hrsr == hrs && minsr == mins && de == 1 && ex != -1){  //qnd o exercicio comeco
         hatv = 1;                      
         }

      if(hrsr == hrster && minsr == minster){  //qnd o exercicio termino          
       hatv = 0;          
      }
         
    }else{
      de = 0;
    }

      if(de == 1 && ex == -1){ //opcao da lista de exercicio

        display.fillRect(89, 54, 37, 10, WHITE);
        display.setCursor(90, 55);
        display.setTextColor(BLACK);
        display.println(F("Lista>"));
        
        while(digitalRead(9) == 0){
            posp = 9;
            delay(50);
        }
     }

    if(reset1 <= 2 && hatv == 0){
      display.setCursor(0, 55);  // dar a opcao de trocar a rotina
      display.setTextColor(WHITE);
      display.println(F("<Imprevisto?"));

      while (digitalRead(9) == 0){
      posp = 8; // pressionar enter muda de pagina
      delay(50);
      }
    }
        
        display.setCursor(0, 0);
        display.setTextSize(0);
        display.setTextColor(WHITE);
        display.print("bpm:");
        display.println(bpm);

        display.setCursor(34, 25);
        display.setTextSize(2);
        if(hrsr < 10){
          display.print("0");
        }
        display.print(hrsr);
        display.print(":");
        if(minsr < 10){
          display.print("0");
        }
        display.println(minsr);
        
        display.setTextSize(0);    //mostrar o dia da semana
        display.setCursor(95, 0);

        if(de == 1){
          display.print(">>");  // se de == 1, sinaliza
        }
        
        display.setCursor(110, 0);
        
              if(ds == 1){
          display.println(F("Dom")); // mostra ds na tela principal
        }else if(ds == 2){
          display.println(F("Seg"));
        }else if(ds == 3){
          display.println(F("Ter"));
        }else if(ds == 4){
          display.println(F("Qua"));
        }else if(ds == 5){
          display.println(F("Qui"));
        }else if(ds == 6){
          display.println(F("Sex"));
        }else if(ds == 7){
          display.println(F("Sab"));
        }        

        
       
       if(hrsr == hrs && minsr == mins-1 && segr > 50 && de == 1 && ex != -1){                                         //Inicio do exercicio
        
         display.fillRect(0, 20, 128, 50, BLACK);
         display.setTextColor(WHITE);
         display.setCursor(0, 30);
         display.setTextSize(0);
         display.print(F("Iniciando as medidas"));
         t2 = t1; // millis qnd a pessoa tive fznd ex.
         }


         if(hatv == 1 && (med > medex1 || med < medex2) && bpm > bpmex){  //para saber o qnt a pessoa fez exercicio

          t3 = t3 + (t1 - t2); // soma total dos milis durante ex.
          t2 = t1; // millis qnd a pessoa tive fznd ex.
          
         }         
         
         if(hatv == 1){   //em exercicio
          
         display.setCursor(28, 15);
         display.setTextColor(WHITE);
         display.println(F("em exercicio"));
         
        }
    }        
        
  if(posp == 8){      //resetar a rotina                                                                            tela 8
    
    while(digitalRead(6) == 0){
          posp = 7; 
          delay(50);
      }

    while (digitalRead(9) == 0) {
      posp = 0;
      ex = -1;
      reset1 ++;
      delay(50);
     }

      display.setCursor(0, 55);
    display.println(F("<voltar   selecionar>"));

      display.setCursor(0, 0);
      display.println(F("Voce tem certeza?    Isso so podera ser   efetuado 2 vezes por mes!"));

  }
  if(posp == 9){                                                                                                          //  tela 9

    while (digitalRead(9) == 0) {
        posp = 7; // pressionar enter muda de pagina
        delay(50);
      }
      display.setCursor(0, 1);           //mostrar a lista
      display.setTextColor(WHITE);
      display.println(F(">Caminhada"));

      display.setCursor(0, 11);
      display.println(F(">Corrida"));

      display.setCursor(0, 21);
      display.println(F(">Subir escadas"));

      display.setCursor(0, 31);
      display.println(F(">Pedalar"));

      display.setCursor(0, 41);
      display.println(F(">Polichinelo"));

      display.setCursor(0, 51);
      display.println(F(">Pular corda"));
      display.setTextColor(BLACK);
      
        
      
      if(pos1 == 0){               //selecionar elemento da lista
        
        display.fillRect(0, 0, 128, 9 , WHITE);
        display.setCursor(0, 1);
        display.println(F(">Caminhada"));

        ex = 0;
        
      }else if(pos1 == 1){

        display.fillRect(0, 10, 128, 9 , WHITE);
        display.setCursor(0, 11);
        display.println(F(">Corrida"));

        ex = 1;
        
      }else if(pos1 == 2){    

        display.fillRect(0, 20, 128, 9 , WHITE);
        display.setCursor(0, 21);
        display.println(F(">Subir escadas"));

        ex = 2;
        
      }else if(pos1 == 3){

        display.fillRect(0, 30, 128, 9 , WHITE);
        display.setCursor(0, 31);
        display.println(F(">Pedalar"));

        ex = 3;
        
      }else if(pos1 == 4){

        display.fillRect(0, 40, 128, 9 , WHITE);
        display.setCursor(0, 41);
        display.println(F(">Polichinelo"));

        ex = 4;
        
      }else if(pos1 == 5){

        display.fillRect(0, 50, 128, 9 , WHITE);
        display.setCursor(0, 51);
        display.println(F(">Pular corda"));

        ex = 5;
        
      }else{
        
        pos1 = 0;
        
      }
      
  }
    
  
  display.display();
  
}                                               //end of void loop()
