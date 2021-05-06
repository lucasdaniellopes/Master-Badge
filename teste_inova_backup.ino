#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x38, 16, 2);

//Variavel que armazena os caracteres recebidos
char buf;
char buf2;

//Definicoes da porta do motor e seu estado de funcionamento
int porta_motor = 3;
int estado;
//Variaveis para controle do estado do motor
int estado_motor = 1;
//Variavel que armazena o nome dos funcionarios
String funcionarios[] = {"Lucas", "Brenda", "Islyn"};

String setor_solic;
int i;
void setup()
{

  lcd.begin(16,2);
  lcd.init();
  //Define a porta do motor de vibração como saida
  pinMode(porta_motor, OUTPUT);
  //Inicializa a serial
  Serial.begin(9600);
  //Informacoes iniciais
  Serial.println();
  Serial.println("Digite : ");
  Serial.println("0 - Para solicitar funcionario(a) Lucas");
  Serial.println("1 - Para solicitar funcionario(a) Brenda");
  Serial.println("2 - Para solicitar funcionario(a) Islyn");
  Serial.println();
  Serial.println("g - Para solicitar funcionario(a) na Gerencia");
  Serial.println("r - Para solicitar funcionario(a) nos Recursos Humanos" );
  Serial.println("e - Para solicitar funcionario(a) na Recepcao/entrada");
  Serial.println();
  Serial.println("Exemplo: r1");
}

void loop()
{
  //Aguarda os dados na serial
  while (Serial.available() > 0)
  {
    buf = Serial.read();

    local_solicitado();

    //Caso seja recebido o numero 1, chama o funcionario lucas
    if (buf == '0')
    {
      estado = 0;
      motor("vibra", estado_motor);
      mensagem_setor_funcio_solicitado();
    }

    //Caso seja recebido o numero 2, chama a funcionaria brenda
    if (buf == '1')
    {
      estado = 1;
      motor("vibra", estado_motor);
      mensagem_setor_funcio_solicitado();
    }

    //Caso seja recebido o numero 3, chama a funcionaria islyn
    if (buf == '2')
    {
      estado = 2;
      motor("vibra", estado_motor);
      mensagem_setor_funcio_solicitado();
    }
  }
}

//Rotina de envio da mensagem de retorno sobre o estado do funcionario
void mensagem_setor_funcio_solicitado()
{
  lcd.backlight();
  lcd.print("Setor Solicitado");
  lcd.setCursor(0, 1);
  lcd.print(setor_solic);
  Serial.print("Funcionario(a) ");



  if (estado == 0) {

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

void motor(String vibra, int estado_motor)
{
  for (int i = 0; i < 8 ; i = i + 1) {
    digitalWrite(porta_motor, estado_motor);
    delay(200);
    estado_motor = !estado_motor;
  }

}

void local_solicitado() {
  if (buf == 'g') {
    setor_solic = "Gerencia";
  }
  if (buf == 'r') {
    setor_solic = "Recursos Human.";
  }
  if (buf == 'e') {
    setor_solic = "Recepcao";
  }
}
