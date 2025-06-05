import paho.mqtt.client as mqtt
import time


broker = "broker.emqx.io" # Altere para o IP ou domínio do seu broker MQTT (ex: "broker.emqx.io")
port = 1883        
topico_led_control = "home/dispositivo01/led/control"

def publicar_comando_led(client, comando):
    """
    Publica um comando (LIGAR ou DESLIGAR) para o LED no tópico MQTT.
    """
    client.publish(topico_led_control, comando)
    print(f"Comando enviado: '{comando}' para o tópico '{topico_led_control}'")


client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION1, "PublisherLed")

print(f"Conectando ao broker MQTT em {broker}:{port}...")
client.connect(broker, port)
print("Conectado ao broker MQTT.")

try:
    while True:
       
        publicar_comando_led(client, "LIGAR")
        time.sleep(2) 

        publicar_comando_led(client, "DESLIGAR")
        time.sleep(2) 

except KeyboardInterrupt:
    print("\nPublisher de LED encerrado.")
    client.disconnect() # Desconecta do broker
    print("Desconectado do broker MQTT.")