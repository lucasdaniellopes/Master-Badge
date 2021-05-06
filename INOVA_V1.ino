#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x38,16,2);

//Variavel que armazena os caracteres recebidos
char buf;
 
//Definicoes da porta do motor e seu estado de funcionamento
int porta_motor = 3;
int estado; 
//Variaveis para controle do estado do motor
int estado_motor = 1;
//Variavel que armazena o nome dos funcionarios
String funcionarios[] = {"Lucas", "Brenda", "Islym"};
 
void setup(){
  
  //Define a porta do motor de vibração como saida
  pinMode(porta_motor, OUTPUT);
  //Inicializa a serial
  Serial.begin(9600);
  //Informacoes iniciais 
  Serial.println("Digite : ");
  Serial.println("0 - Para solicitar funcionario(a) Lucas");
  Serial.println("1 - Para solicitar funcionario(a) Brenda");
  Serial.println("2 - Para solicitar funcionario(a) Islym");
  Serial.println();
  lcd.init();
}
 
void loop(){
  //Aguarda os dados na serial
  while(Serial.available() > 0)
  {
    buf = Serial.read();
     
    //Caso seja recebido o numero 0, chama o funcionario lucas
    if (buf == '0')
    {
      estado = 0;
      motor();
      mensagem_setor_funcio_solicitado("Recursos Human.");
    }
     
    //Caso seja recebido o numero 1, chama a funcionaria brenda
    if (buf == '1')
    {
     estado = 1; 
     motor();
     mensagem_setor_funcio_solicitado("Recursos Human.");
    }
     
    //Caso seja recebido o numero 2, chama a funcionaria islyn  
    if (buf == '2')
    {
     estado = 2; 
     motor(); 
     mensagem_setor_funcio_solicitado("Recursos Human.");
    }   
  }
}
 
//Rotina de envio da mensagem de retorno sobre o estado do funcionario
void mensagem_setor_funcio_solicitado(String setor)
{
  
  lcd.backlight();
  lcd.print("Setor Solicitado");
  lcd.setCursor(0,1);
  lcd.print(setor);
  Serial.print("Funcionario(a) ");
  
  
  if (estado == 0){
    Serial.print(funcionarios[0]);
    Serial.print(" solicitado(a)");
    Serial.println();
    
  }

  if (estado == 1) {
    Serial.print(funcionarios[1]);
    Serial.print(" solicitado(a)");
    Serial.println();
  }

  if (estado == 2) {
    Serial.print(funcionarios[2]);
    Serial.print(" solicitado(a)");
    Serial.println();
  }
delay(4000);
  lcd.clear();
  lcd.noBacklight();
}

void motor()
{
  for (int i = 0; i < 8 ;i = i + 1){
    digitalWrite(porta_motor,estado_motor);
    delay(200);
    estado_motor = !estado_motor;
    }
 
}
