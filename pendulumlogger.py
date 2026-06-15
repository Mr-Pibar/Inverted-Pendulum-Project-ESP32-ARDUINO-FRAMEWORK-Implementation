import serial
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import csv
from datetime import datetime

# ==========================================
# LOGGING
# ==========================================

log_rows = []
saved = False

# ==========================================
# CONFIG
# ==========================================

PORT = "COM16"      # Change this
BAUD = 115200

STEPS_PER_CM = 500.0
PENDULUM_LENGTH_CM = 20

# ==========================================
# SERIAL
# ==========================================

ser = serial.Serial(PORT, BAUD, timeout=0.01)

# ==========================================
# LIVE STATE
# ==========================================

angle_deg = 0.0
angle_vel = 0.0
cmd = 0.0
speed = 0.0
cart_cm = 0.0
home_hit = 0
end_hit = 0

# ==========================================
# FIGURE
# ==========================================

fig, ax = plt.subplots(figsize=(10, 4))

ax.set_aspect("equal")

ax.set_xlim(-40, 40)
ax.set_ylim(-5, 30)

ax.set_title("Live Inverted Pendulum")

# Rail
ax.plot(
    [-40, 40],
    [0, 0],
    linewidth=3
)

# Cart
cart_width = 4
cart_height = 2

cart = plt.Rectangle(
    (-cart_width / 2, 0),
    cart_width,
    cart_height
)

ax.add_patch(cart)

# Pendulum
pendulum_line, = ax.plot([], [], lw=3)

# Pivot
pivot_dot, = ax.plot([], [], marker='o')

# Text
info_text = ax.text(
    0.02,
    0.95,
    "",
    transform=ax.transAxes,
    verticalalignment='top'
)

# ==========================================
# UPDATE
# ==========================================

def update(frame):

    global angle_deg
    global angle_vel
    global cmd
    global speed
    global cart_cm
    global home_hit
    global end_hit

    global saved
    global log_rows

    try:
        while ser.in_waiting:

            line = ser.readline().decode(
                errors="ignore"
            ).strip()

            if not line:
                continue

            parts = line.split(",")

            if len(parts) != 8:
                continue

            time_ms = int(parts[0])

            angle_deg = float(parts[1])
            angle_vel = float(parts[2])
            cmd = float(parts[3])
            speed = float(parts[4])

            cart_pos_steps = float(parts[5])

            home_hit = int(parts[6])
            end_hit = int(parts[7])

            cart_cm = cart_pos_steps / STEPS_PER_CM

            # Store every sample
            log_rows.append([
                time_ms,
                angle_deg,
                angle_vel,
                cmd,
                speed,
                cart_pos_steps,
                home_hit,
                end_hit
            ])

            # Save if rail limit hit
            if not saved and (home_hit or end_hit):

                filename = (
                    "pendulum_crash_" +
                    datetime.now().strftime("%Y%m%d_%H%M%S") +
                    ".csv"
                )

                with open(filename, "w", newline="") as f:

                    writer = csv.writer(f)

                    writer.writerow([
                        "time",
                        "angle",
                        "angleVel",
                        "cmd",
                        "speed",
                        "cartPos",
                        "home",
                        "end"
                    ])

                    writer.writerows(log_rows)

                print()
                print("=================================")
                print("LIMIT SWITCH HIT")
                print("Saved:", filename)
                print("Samples:", len(log_rows))
                print("=================================")
                print()

                saved = True

    except Exception as e:
        print(e)
    theta = np.radians(-angle_deg)

    cart.set_xy(
        (
            cart_cm - cart_width / 2,
            0
        )
    )

    pivot_x = cart_cm
    pivot_y = cart_height

    tip_x = pivot_x + PENDULUM_LENGTH_CM * np.sin(theta)
    tip_y = pivot_y + PENDULUM_LENGTH_CM * np.cos(theta)

    pendulum_line.set_data(
        [pivot_x, tip_x],
        [pivot_y, tip_y]
    )

    pivot_dot.set_data(
        [pivot_x],
        [pivot_y]
    )

    info_text.set_text(
        f"Angle: {angle_deg:.1f}°\n"
        f"Angular Vel: {angle_vel:.1f}°/s\n"
        f"Cart: {cart_cm:.2f} cm\n"
        f"Cmd: {cmd:.0f}\n"
        f"Speed: {speed:.0f}\n"
        f"HOME: {home_hit}\n"
        f"END: {end_hit}"
    )

    return (
        cart,
        pendulum_line,
        pivot_dot,
        info_text
    )

# ==========================================
# ANIMATION
# ==========================================

ani = FuncAnimation(
    fig,
    update,
    interval=20
)

plt.show()