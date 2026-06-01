import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# CSV format:
# time_ms,angle_deg,velocity_deg_s

data = pd.read_csv(
    "pendulum.csv",
    names=["t","angle","vel"]
)

L = 1.0  # arbitrary visual length

fig, ax = plt.subplots(figsize=(6,6))

ax.set_xlim(-1.2,1.2)
ax.set_ylim(-1.2,1.2)
ax.set_aspect('equal')

line, = ax.plot([], [], lw=3)
bob, = ax.plot([], [], 'o', markersize=12)

def update(frame):

    theta = np.radians(data["angle"][frame])

    # 0° = hanging down
    x = L * np.sin(theta)
    y = -L * np.cos(theta)

    line.set_data([0,x],[0,y])
    bob.set_data([x],[y])

    return line,bob

ani = FuncAnimation(
    fig,
    update,
    frames=len(data),
    interval=10,
    blit=True
)

plt.show()