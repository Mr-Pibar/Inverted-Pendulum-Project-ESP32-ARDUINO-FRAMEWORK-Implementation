import serial
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Change COM port
ser = serial.Serial("COM16", 9600)

angle_deg = 0

# Pendulum length (visual only)
L = 1.0

fig, ax = plt.subplots(figsize=(6, 6))

ax.set_xlim(-1.2, 1.2)
ax.set_ylim(-1.2, 1.2)
ax.set_aspect("equal")
ax.grid(True)

rod, = ax.plot([], [], lw=3)
bob, = ax.plot([], [], "o", markersize=15)

title = ax.set_title("Angle = 0°")

def update(frame):
    global angle_deg

    while ser.in_waiting:
        try:
            line = ser.readline().decode().strip()

            t, angle, vel = map(float, line.split(","))

            angle_deg = angle

        except:
            pass

    theta = np.radians(angle_deg)

    # 0° = hanging down
    x = L * np.sin(theta)
    y = -L * np.cos(theta)

    rod.set_data([0, x], [0, y])
    bob.set_data([x], [y])

    title.set_text(f"Angle = {angle_deg:.1f}°")

    return rod, bob

ani = FuncAnimation(
    fig,
    update,
    interval=20,
    blit=True
)

plt.show()