import paho.mqtt.client as mqtt
import pandas as pd

mqtt_username = "username"
mqtt_password  = "Driehoek"
mqtt_topic = "Your Topic"
mqtt_topic_motor = "Motor"
mqtt_broker_ip = "192.168.2.2"

client = mqtt.Client()
client.username_pw_set(mqtt_username, mqtt_password)

def on_connect(client, userdata, flags, rc):
    print ("Connected!")

    client.subscribe(mqtt_topic)

def on_message(client, userdata, msg):

    print("Topic: ", msg.topic + "\nMessage: " + str(msg.payload))
    f = open("codes.txt", "r")
    value: str = msg.payload
    decoded = value.decode('utf-8')
    print(decoded)
    for x in f:
        if(decoded.strip()==x.strip()):
            print("blalba")
            client.publish(mqtt_topic_motor, payload="0", ratain=False)        

client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtt_broker_ip, 1883)

client.loop_forever()
client.disconnect()
