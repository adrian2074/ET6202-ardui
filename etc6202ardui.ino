int data=2;
int clk=3;
int stb=4;
int a,b,c,d;
int cuenta;

void setup() {
 
              pinMode(data,OUTPUT);
              pinMode(clk,OUTPUT);
              pinMode(stb,OUTPUT);
              }



void configuracion_display()
  {
        // DISPLAY MODE                                               // b7=0 y b6=0 con valores fijos    
    digitalWrite(stb,HIGH);                                           // b2 a b5 no asignados
    digitalWrite(stb,LOW);                                            // b1 y b0 configuracion de bits de grafico
    digitalWrite(clk, LOW);                                           //00 - 4 bits 01 - 5 bits 10 - 6 bits 11 - 7 bits
    shiftOut(data,clk,LSBFIRST,B00000011);  //b7..b0




      // DISPLAY ORDEN
    digitalWrite(stb,HIGH);                                         // b4 y b5 no asignados
    digitalWrite(stb,LOW);                                          // b3=0 modo de operacion normal b3=1 modo prueba
    digitalWrite(clk, LOW);                                         // b2=0 incremento automatico de direccion para envio de datos b2=1 se debe establecer la direccion 
    shiftOut(data,clk,LSBFIRST,B01000100);  //envio orden b7..b0    // b1=0 b0=0 modo escritura de pantalla
    digitalWrite(stb,HIGH);  // establecer mode del display   
                
  }

void envio_datos(byte direccion,byte dato, byte brillo,bool punto)

// seleccionde direccion de datos digito1 
  {                 
  configuracion_display();
  //ASIGNA DIRECION EN MEMORIA DE DISPLAY   
  direccion &= B00001111;                                                      //b7=1  b6=1 valores fijos en datasheet
  digitalWrite(stb,LOW);                                                       //b4 y b5 no asignados 
  digitalWrite(clk, LOW);                                                      // de b0 a b3 direcciones de memoria para datos de display
  shiftOut(data,clk,LSBFIRST,B11000000+direccion); //direccion b7..b0          // los digitos estan en las ubicaciones 00h  02h  04h 06h  08h 0Ah 0Ch
                                                                               //
                                                               
  dato=convertir_dato(dato);                                                                  
                                                                  
 if(punto==true)                                                  //en este caso si queremos poner solo el primer digito la direccion seria B11000000
   dato=dato|B10000000;    
                                  //              b0    
//enviar dato a representar en pantalla                            //             ----
  digitalWrite(clk, LOW);                                          //         b5 | b6 | b1
  shiftOut(data,clk,LSBFIRST,dato);        //b7..b0                //             ----
  digitalWrite(stb,HIGH);                                          //         b4 |    | b2
 //CONFIGURA BRILLO EN PANTALLA                                    //              ---
 brillo &= B00000111;                                              //              b3    ° b7
 // control de de pantalla                                         //
  digitalWrite(stb,LOW);                                           //de b0 a b2 es el brillo de la pantalla valores 000 001 010 011 100 101 110 111  ultimo valor mas brillo
  digitalWrite(clk, LOW);                                          //b4 y b5 no asignados
  shiftOut(data,clk,LSBFIRST,B10001000|brillo);    //b7..b0        //b3=0 para escanear botones
                                                                   //b3=1 para mostrar datos en pantalla
                                                                   //b6=0 seteado fijo en datasheet  
                                                                   //b7=1 seteado fijo en data sheet    
  }


byte convertir_dato(byte datos)         //CONVIERTE DATOS A BCD
  {
      byte valor;
      if(datos==0)valor=B00111111;  
      if(datos==1)valor=B00000110;   
      if(datos==2)valor=B01011011;  
      if(datos==3)valor=B01001111;  
      if(datos==4)valor=B01100110; 
      if(datos==5)valor=B01101101;  
      if(datos==6)valor=B01111101; 
      if(datos==7)valor=B00000111;  
      if(datos==8)valor=B01111111;   
      if(datos==9)valor=B01101111;   
      

    return valor;
  
  }



void loop() {


  //delay(1000);

  for(cuenta=0;cuenta<1000;cuenta++)          //CONTADOR DE 0 A 1000 Y MUESTRA EN PANTALLA
    {
       a=cuenta/1000;
       b=(cuenta-a*1000)/100;
       c=(cuenta-a*1000-b*100)/10;
       d=(cuenta-a*1000-b*100-c*10);

      envio_datos(0,a,7,false);    //envio(direccion, valor, brillo,punto)  // el punto esta en el b7 de datos pero en en display puede no corresponder al digito.
      envio_datos(2,b,7,false);  // envio(direccion, valor, brillo, punto)   //muestra cuatro digitos
      envio_datos(4,c,7,false);  // envio(direccion, valor, brillo, punto)
      envio_datos(6,d,7,false);  // envio(direccion, valor, brillo, punto)
delay(1000);

}







}
