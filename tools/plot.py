import matplotlib.pyplot as plt
import sys
import csv

if __name__ == "__main__":
    if len(sys.argv) > 1:
        reader = csv.reader(open(sys.argv[1]))

        x = [int(row[0]) for row in reader]
        y = [float(row[1]) for row in reader]
        
        print(x)
        print(y)
        plt.plot(x, y)
        plt.show()

    else:
        print(sys.argv)
        print ("Usage : python[py][python3] plot.py {filename.csv}")