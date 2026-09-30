#!/usr/bin/env python3
import time
import socket
import json
import gpiod

BUTTON_PIN = 23
LED_PIN = 25
SOCKET_PATH = "/tmp/pi_agent_mp3.sock"

def send_ipc_command(action_dict):
    try:
        client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        client.connect(SOCKET_PATH)
        client.sendall(json.dumps(action_dict).encode('utf-8'))
        response = client.recv(1024)
        client.close()
        return json.loads(response.decode('utf-8'))
    except Exception:
        return None

def main():
    try:
        chip = gpiod.Chip('gpiochip4')
    except Exception as e:
        print(f"[AIY Service] GPIO Chip Init Error: {e}")
        return

    led_line = chip.get_line(LED_PIN)
    led_line.request(consumer="AIY_LED", type=gpiod.LINE_REQ_DIR_OUT)

    button_line = chip.get_line(BUTTON_PIN)
    button_line.request(consumer="AIY_Button", type=gpiod.LINE_REQ_EV_FALLING_EDGE)

    print("[AIY Service] Voice Kit v1 Bridge Started.")

    while True:
        status = send_ipc_command({"action": "get_status"})
        if status and status.get("isPlaying", False):
            led_line.set_value(1)
        else:
            led_line.set_value(0)

        event = button_line.event_wait(nsec=200000000)
        if event:
            print("[AIY Service] Button Pressed!")
            send_ipc_command({"action": "play_pause"})
            time.sleep(0.3)

if __name__ == "__main__":
    main()
