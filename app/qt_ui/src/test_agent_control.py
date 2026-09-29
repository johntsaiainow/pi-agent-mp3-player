#!/usr/bin/env python3
import socket
import json
import sys
import time

SOCKET_PATH = "/tmp/pi_agent_mp3.sock"

def send_command(payload):
    try:
        client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        client.connect(SOCKET_PATH)
        client.sendall(json.dumps(payload).encode('utf-8'))
        
        response = client.recv(1024)
        client.close()
        return json.loads(response.decode('utf-8'))
    except Exception as e:
        print(f"[Error] Failed to connect or send message: {e}")
        return None

if __name__ == "__main__":
    print("=== Pi Agent MP3 Player Remote Control Test ===")
    
    # 1. 測試播放指定音訊
    song_path = "/home/john/Music/The United States/Don McLean - American Pie/01 - Don McLean - American Pie.flac"
    if len(sys.argv) > 1:
        song_path = sys.argv[1]

    print(f"\n1. Sending play_track: {song_path}")
    res = send_command({"action": "play_track", "path": song_path})
    print("Response:", res)

    time.sleep(2)

    # 2. 調整音量至 85%
    print("\n2. Setting volume to 85%")
    res = send_command({"action": "set_volume", "volume": 0.85})
    print("Response:", res)

    time.sleep(2)

    # 3. 取得當前播放狀態
    print("\n3. Querying player status")
    res = send_command({"action": "get_status"})
    print("Response:", res)

    time.sleep(2)

    # 4. 切換 播放/暫停
    print("\n4. Toggling Play/Pause")
    res = send_command({"action": "play_pause"})
    print("Response:", res)
