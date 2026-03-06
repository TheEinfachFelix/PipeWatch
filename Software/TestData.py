import json
import time
import random
import paho.mqtt.client as mqtt
import random
from meshtastic.protobuf import mqtt_pb2, mesh_pb2, portnums_pb2

MQTT_BROKER = "192.168.178.116"
MQTT_TOPIC = "mesh/dach/i"

def generate_sensor_data():
    return {
        "WaterPresure": 1.75 + random.uniform(-0.05, 0.05),
        "WaterLevel": 26.3 + random.uniform(-0.5, 0.5),
        "Lightlevel": 260 + random.uniform(-40, 40),
        "AccelerationX": random.uniform(-0.1, 0.1),
        "AccelerationY": random.uniform(-0.1, 0.1),
        "AccelerationZ": 0.6 + random.uniform(-0.05, 0.05),
        "Temp_Out": 19 + random.uniform(-0.8, 0.8),
    }



client = mqtt.Client()
client.connect(MQTT_BROKER, 1883, 60)


def build_packet():
    payload_data = {
        "version": 1,
        "device": "TestNode",
        "uptime": int(time.time()),
        "state": "RUN",
        "data": json.dumps(generate_sensor_data())
    }
    payload_bytes = json.dumps(payload_data).encode()

    # Data payload
    data = mesh_pb2.Data()
    data.portnum = portnums_pb2.PortNum.TEXT_MESSAGE_APP
    data.payload = payload_bytes
    data.want_response = False

    # MeshPacket
    packet = mesh_pb2.MeshPacket()

    setattr(packet, "from", random.randint(1, 0xFFFFFFFF))
    packet.to = 0xFFFFFFFF
    packet.id = random.randint(1, 0xFFFFFFFF)
    packet.channel = 1
    packet.hop_limit = 4
    packet.want_ack = False
    packet.priority = 100

    packet.decoded.CopyFrom(data)

    # ServiceEnvelope
    env = mqtt_pb2.ServiceEnvelope()
    env.packet.CopyFrom(packet)
    env.channel_id = "IotDataLink"
    env.gateway_id = "!51d6c639"

    return env.SerializeToString()


while True:

    packet = build_packet()

    client.publish(MQTT_TOPIC, packet)

    print("Packet sent")

    time.sleep(5)