#include <ESP8266WiFi.h>
#include <PubSubClient.h> // Biblioteca para MQTT

// --- Configurações da Rede Wi-Fi ---
const char* ssid = "uaifai-tiradentes";   // Nome da sua rede Wi-Fi
const char* password = "bemvindoaocesar"; // Senha da sua rede Wi-Fi

// --- Configurações MQTT ---
const char* mqtt_server = "broker.emqx.io"; // Endereço do seu broker MQTT
const int mqtt_port = 1883;                 // Porta padrão do MQTT
const char* mqtt_client_id = "ESP8266_LED_Control"; // ID único para este cliente MQTT
const char* topic_led_control = "home/dispositivo01/led/control"; // Tópico para receber comandos para o LED
const char* topic_led_status = "home/dispositivo01/led/status";   // Tópico para publicar o estado atual do LED


const int ledPin = 2; // GPIO2 (geralmente o LED onboard azul da NodeMCU)

bool ledState = LOW; // Estado atual do LED (LOW = desligado, HIGH = ligado)

WiFiClient espClient;
PubSubClient client(espClient);

// --- Funções ---

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem MQTT recebida no topico: ");
  Serial.println(topic);
  Serial.print("Mensagem: ");
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Verifica se a mensagem é para controlar o LED
  if (String(topic) == topic_led_control) {
    if (message == "LIGAR") {
      digitalWrite(ledPin, HIGH);
      ledState = HIGH;
      Serial.println("LED ligado via MQTT");
      client.publish(topic_led_status, "LIGADO"); // Publica o novo status do LED
    } else if (message == "DESLIGAR") {
      digitalWrite(ledPin, LOW);
      ledState = LOW;
      Serial.println("LED desligado via MQTT");
      client.publish(topic_led_status, "DESLIGADO"); // Publica o novo status do LED
    } else {
      Serial.println("Comando de LED invalido. Use 'LIGAR' ou 'DESLIGAR'.");
    }
  }
}

//  reconectar ao broker MQTT
void reconnectMqtt() {
  // Loop até estar conectado
  while (!client.connected()) {
    Serial.print("Tentando conectar ao broker MQTT...");
    // Tenta conectar usando o Client ID definido
    if (client.connect(mqtt_client_id)) {
      Serial.println("conectado!");
      // Uma vez conectado, assina os tópicos que nos interessam
      client.subscribe(topic_led_control);
      Serial.print("Assinado ao topico: ");
      Serial.println(topic_led_control);
      // Publica o estado inicial do LED
      client.publish(topic_led_status, ledState == HIGH ? "LIGADO" : "DESLIGADO");
    } else {
      Serial.print("falha, rc=");
      Serial.print(client.state()); // Código de retorno da falha
      Serial.println(" tentando novamente em 5 segundos");
      // Espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Configuração do hardware
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState); // Define o estado inicial do LED (desligado)

  Serial.println("\nHardware configurado.");

  // Conecta ao Wi-Fi
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());

  // Configura o cliente MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback); 
}

void loop() {
  // Garante que o cliente MQTT esteja conectado
  if (!client.connected()) {
    reconnectMqtt();
  }
  client.loop(); // Processa mensagens MQTT pendentes e mantém a conexão ativa
}