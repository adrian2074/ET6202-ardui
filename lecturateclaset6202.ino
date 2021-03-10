
int data=2;
int clk=3;
int stb=4;
int a,b,c,d;
int caca;
byte dato1=0,dato2=0,dato3=0,dato4=0,dato5=0,dato6=0;
void setup() {
  // put your setup code here, to run once:
pinMode(data,OUTPUT);
pinMode(clk,OUTPUT);
pinMode(stb,OUTPUT);
pinMode(13,OUTPUT);
//digitalWrite(stb,LOW);
Serial.begin(9600);
}




// DISPLAY MODE


void configuracion_display()
  {
 // establecer mode del display   
digitalWrite(stb,HIGH);                                        // b1=0         b0=0  graficos 4 bits
digitalWrite(stb,LOW);                                         // b1=0         b0=1  grafico 5 bits
digitalWrite(clk, LOW);                                        // b1=1         b0=0  grafico 6 bits
shiftOut(data,clk,LSBFIRST,B00000011);   //envio modo b7...b0     b1=1         b0=1  grafico 7 bits
digitalWrite(stb,HIGH);                                        //b2..b5 no asignados
  
// establecer orden de datos  
                                                                // b4 y b5 no asignados
digitalWrite(stb,LOW);                                          // b3=0 modo de operacion normal b3=1 modo prueba
digitalWrite(clk, LOW);                                         // b2=0 incremento automatico de direccion para envio de datos b2=1 se debe establecer la direccion 
shiftOut(data,clk,LSBFIRST,B01000110);  //envio orden b7..b0    // b1=0 b0=0 modo escritura de pantalla
//digitalWrite(stb,HIGH);                                       // b1=1 b0=0 modo lectura teclas
 // pueden observar que al contrario de                         //valores fijos para b6=1 b7=0
 //escribir en pantalla en la lectura de teclas
 //no se pone la salida stb en alto al terminar este comando
  }


void leo()
{

digitalWrite(stb,HIGH);                                        //b2..b5 no asignados
  
// establecer orden de datos  
                                                                // b4 y b5 no asignados
digitalWrite(stb,LOW);                                          // b3=0 modo de operacion normal b3=1 modo prueba
digitalWrite(clk, LOW);                                         // b2=0 incremento automatico de direccion para envio de datos b2=1 se debe establecer la direccion 
shiftOut(data,clk,LSBFIRST,B01000110); 

}


void loop() {


configuracion_display();

while(1)
{
  
 pinMode(data,INPUT);
                                    
dato1 = shiftIn(data, clk, LSBFIRST);
dato2 = shiftIn(data, clk, LSBFIRST);
dato3 = shiftIn(data, clk, LSBFIRST);
dato4 = shiftIn(data, clk, LSBFIRST);
dato5 = shiftIn(data, clk, LSBFIRST);   
dato6 = shiftIn(data, clk, LSBFIRST);
/*Serial.print("los valores son:" );
Serial.print(dato1);
Serial.print(dato2);
Serial.print(dato3);
Serial.print(dato4);
Serial.print(dato5);
Serial.println(dato6);
while(1);
*/
pinMode(data,OUTPUT);

if(dato2==1)
digitalWrite(13,HIGH);
if(dato2==2)
digitalWrite(13,LOW);

}


//en este codigo se envian los dos comandos de configuracion luego se cambia data a modo entrada y se leen los 6 bytes de datos del scan
// en el caso de lectura del teclado no pongo en nivel bajo el clock antes de leer un byte
// el funcionamiento consiste en apagar y encender el led D13

}
