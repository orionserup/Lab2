import matplotlib.pyplot as plt
import sys
import csv

if __name__ == "__main__":
    if len(sys.argv) > 1:
        reader = csv.reader(open(sys.argv[1]))
        data = [ row for row in reader]
        y = [float(point[1]) for point in data]
        x = [int(point[0]) for point in data]
        
        plt.plot(x, y)
        plt.xlabel("Number of Elements")
        plt.ylabel("Time in ms")
        plt.savefig(sys.argv[1].split(".csv")[0] + ".png")
        plt.show()

    else:
        print(sys.argv)
        print ("Usage : python[py][python3] plotdata.py {filename.csv}")