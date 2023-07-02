# Writes the intensities to one file.

import math

number = 1
size = 256
max_value = 255
expo = math.log(max_value)/(size - 1)
sin_arg = math.pi / (2 * size)

f = open("intensities.inc", "w")
f.write("table_intensities:")

for row in range(16):
    f.write("\n.db ")
    for column in range(16):
        index = row * 16 + column
        value = round(max_value * math.sin(sin_arg * index))
        print(index, value)
        f.write(hex(int(value)))
        if (column != 15):
            f.write(", ")

f.write("\n")
f.close()
