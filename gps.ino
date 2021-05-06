#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial serial1(10, 11); // RX, TX
TinyGPS gps1;

  float LATITUDE;
    float LONGITUDE;

void setup() {
  serial1.begin(9600);
  Serial.begin(9600);

  Serial.println("O GPS aguarda pelo sinal dos satelites...");
}

void loop() {


  bool recebido = false;

  while (serial1.available()) {
    char cIn = serial1.read();
    recebido = gps1.encode(cIn);
  }

  if (recebido) {
    Serial.println("----------------------------------------");

    //Latitude e Longitude
    long latitude, longitude;
    unsigned long idadeInfo;
    gps1.get_position(&latitude, &longitude, &idadeInfo);

  

    if (latitude != TinyGPS::GPS_INVALID_F_ANGLE) {
      Serial.print("Latitude: ");
      Serial.println(float(latitude) / 1000000, 6);
      LATITUDE = float(latitude) / 1000000, 6;
    }

    if (longitude != TinyGPS::GPS_INVALID_F_ANGLE) {
      Serial.print("Longitude: ");
      Serial.println(float(longitude) / 1000000, 6);
      LONGITUDE = float(longitude) / 1000000, 6;
    }

    if (idadeInfo != TinyGPS::GPS_INVALID_AGE) {
      Serial.print("Idade da Informacao (ms): ");
      Serial.println(idadeInfo);
    }


    //altitude
    float altitudeGPS;
    altitudeGPS = gps1.f_altitude();

    if ((altitudeGPS != TinyGPS::GPS_INVALID_ALTITUDE) && (altitudeGPS != 10000000)) {
      Serial.print("Altitude (cm): ");
      Serial.println(altitudeGPS);
    }


    //satelites e precisão
    unsigned short satelites;
    unsigned long precisao;
    satelites = gps1.satellites();
    precisao =  gps1.hdop();

    if (satelites != TinyGPS::GPS_INVALID_SATELLITES) {
      Serial.print("Satelites: ");
      Serial.println(satelites);
    }

    if (precisao != TinyGPS::GPS_INVALID_HDOP) {
      Serial.print("Precisao (centesimos de segundo): ");
      Serial.println(precisao);
    }


    //float distancia_entre;
    //distancia_entre = gps1.distance_between(lat1, long1, lat2, long2);

    //float sentido_para;
    //sentido_para = gps1.course_to(lat1, long1, lat2, long2);
    //                              0,06   0            4 -- 0,10
  }
 LOCAL();
}

void largura() {
  float distancia_entre;
  distancia_entre = gps1.distance_between(-7.021514, -37.288640, -7.021529, -37.288623);
  Serial.println(distancia_entre);
}

void comprimento() {
  float distancia_entre2;
  distancia_entre2 = gps1.distance_between(-7.021514, -37.288640, -7.021536, -37.288634);
  Serial.println(distancia_entre2);
}

void LOCAL() {
  if (LATITUDE < -7.021570 and LONGITUDE < -37.288637) {
    Serial.println("Funcionario esta na sala");
  }
  else {
    Serial.println("Funcionario esta no quarto");
  }
}
