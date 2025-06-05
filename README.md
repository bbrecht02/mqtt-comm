💡 Sistema de Controle de LED via MQTT com ESP8266
📄 Descrição do Projeto

Este projeto demonstra um sistema simples de Internet das Coisas (IoT) para controle remoto de um LED, utilizando o microcontrolador ESP8266 e o protocolo de comunicação MQTT (Message Queuing Telemetry Transport). O objetivo principal é ilustrar a comunicação bidirecional entre um dispositivo embarcado (ESP8266) e um cliente externo (Python Publisher) através de um broker MQTT.

A ESP8266 se conecta a uma rede Wi-Fi, assina um tópico MQTT para receber comandos e publica seu status em outro tópico. Um script Python atua como um publicador, enviando comandos "LIGAR" e "DESLIGAR" para o LED e podendo monitorar o status do dispositivo.
🌟 Funcionalidades

    Controle de LED Remoto: Ligar e desligar um LED (físico ou onboard da ESP8266) enviando mensagens MQTT.
    Comunicação Bidirecional: A ESP8266 recebe comandos e publica seu estado atual.
    Conectividade Wi-Fi: Utiliza a rede Wi-Fi local para comunicação.
    Protocolo MQTT: Emprega MQTT para uma troca de mensagens leve e eficiente.

🛠️ Hardware Necessário

    ESP8266: Placa de desenvolvimento NodeMCU ESP-12E (ou similar).
    LED: Um diodo emissor de luz (opcional, se usar o LED onboard).
    Resistor: 220 Ohm (necessário para LED externo).
    Protoboard e Jumpers: Para montagem do circuito.
    Cabo Micro-USB: Para alimentação e programação da ESP8266.

📦 Software Necessário

    Arduino IDE: Para programar a ESP8266.
        Instalar o suporte para placas ESP8266 (via Boards Manager).
        Instalar a biblioteca PubSubClient (por Nick O'Leary) via Gerenciador de Bibliotecas.
    Python 3: Para o script de publicação/controle.
        Instalar a biblioteca paho-mqtt: pip install paho-mqtt
    Broker MQTT: Um servidor MQTT para rotear as mensagens.
        Opções:
            Local: Mosquitto (recomendado para testes e desenvolvimento).
            Público: broker.emqx.io.
    Cliente MQTT para Testes (Opcional):
        MQTT Explorer: Ótimo para visualizar e publicar mensagens em tópicos.
