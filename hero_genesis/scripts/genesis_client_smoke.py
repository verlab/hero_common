#!/usr/bin/env python3
"""Drive four HeRos over the engine socket and print /hero_N/odom-style state."""
import json
import socket
import time

HOST, PORT = "127.0.0.1", 11312


def main():
    sock = socket.create_connection((HOST, PORT), timeout=5)
    sock.settimeout(1.0)
    buf = ""
    last = 0.0
    t0 = time.time()
    while time.time() - t0 < 4.0:
        for i in range(4):
            sock.sendall((json.dumps({
                "type": "cmd_vel", "id": i,
                "lin": 0.08, "ang": 0.5 if i % 2 == 0 else -0.5,
            }) + "\n").encode("utf-8"))
            sock.sendall((json.dumps({
                "type": "led", "id": i,
                "r": float(i == 0), "g": float(i == 1), "b": float(i >= 2), "a": 1.0,
            }) + "\n").encode("utf-8"))
        try:
            chunk = sock.recv(65536).decode("utf-8", "replace")
        except socket.timeout:
            continue
        buf += chunk
        while "\n" in buf:
            line, buf = buf.split("\n", 1)
            if not line.strip():
                continue
            msg = json.loads(line)
            if msg.get("type") != "state":
                continue
            if msg["t"] - last < 0.49:
                continue
            last = msg["t"]
            bits = []
            for r in msg["robots"]:
                bits.append("hero_%d x=%.3f y=%.3f yaw=%.2f laser0=%.2f" % (
                    r["id"], r["x"], r["y"], r["yaw"], r["ranges"][0]))
            print("t=%.2f  %s" % (msg["t"], " | ".join(bits)))
    sock.close()


if __name__ == "__main__":
    main()
