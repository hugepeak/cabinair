import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.animation as animation

input_file = open("output.txt","r")

line = input_file.readline().split()

x_size = line[0]
y_size = line[1]
z_size = line[2]

times = []
car_dict = {}
car_first_time = {}
car_last_time = {}

line = input_file.readline().split()

while line:
    if line[0] == "NewTime:": 
        times.append( int( line[1] ) )
    else:
        carID = int(line[3])
        if carID in car_dict:
            car_dict[carID][times[len(times)-1]] = [line[0],line[1],line[2]]
            car_last_time[carID] = times[len(times)-1]
        else:
            car_arr = {}
            car_arr[times[len(times)-1]] = [line[0],line[1],line[2]]
            car_dict[carID] = car_arr
            car_first_time[carID] = times[len(times)-1]

    line = input_file.readline().split()

car_list = sorted(car_dict.keys())

for time in times:

    for car in car_list:

        if time not in car_dict[car]:

            if time < car_first_time[car]:

                car_dict[car][time] = car_dict[car][car_first_time[car]]
                car_dict[car][time][2] = 0

            else:

                car_dict[car][time] = car_dict[car][car_last_time[car]]
                car_dict[car][time][2] = 0

data = []
timelist = sorted(car_dict[car].keys())

for car in car_list:

    cardata = np.empty(( 3, len(times) ))

    for time in timelist:
        for i in range( 3 ):
            cardata[i,time-timelist[0]] = car_dict[car][time][i]

    data.append( cardata )

def update_lines(num, dataLines, lines):
    for line, data in zip(lines, dataLines):
        # NOTE: there is no .set_data() for 3 dim data...
        line.set_data(data[0:2, num:num+2])
        line.set_3d_properties(data[2, num:num+2])
    return lines

# Attaching 3D axis to the figure
fig = plt.figure()
ax = p3.Axes3D(fig)

# Creating fifty line objects.
# NOTE: Can't pass empty arrays into 3d version of plot()
lines = [ax.plot(dat[0, 0:1], dat[1, 0:1], dat[2, 0:1])[0] for dat in data]

# Setting the axes properties
ax.set_xlim3d([0.0, float(x_size)])
ax.set_xlabel('X')

ax.set_ylim3d([0.0, float(y_size)])
ax.set_ylabel('Y')

ax.set_zlim3d([0.0, float(z_size)])
ax.set_zlabel('Z')

ax.set_title('3D Test')

# Creating the Animation object
line_ani = animation.FuncAnimation(fig, update_lines, len(car_list)-1, 
               fargs=(data, lines), interval=500, blit=False, repeat = True)
line_ani.save('example.mp4', fps=10, extra_args=['-vcodec', 'libx264'])

#plt.show()
