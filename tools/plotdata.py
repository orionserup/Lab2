import matplotlib.pyplot as plt
import csv
import glob
import sys

def PlotCSVData(path, combined):
    files = glob.glob(path + "*.csv")
    readers = [ csv.reader(open(file)) for file in files ]
    datem = [ [ row for row in reader ] for reader in readers]
    xdata = [ [int(row[0]) for row in data] for data in datem ]
    ydata = [ [float(row[1]) for row in data] for data in datem]
    titles = [ file.replace(path, '').split('.csv')[0] for file in files]
    
    plt.xlabel("Number Of Elements")
    plt.ylabel("Time To Sort (ms)")

    if(combined == True):
        for i in range(len(xdata)):       
            plt.plot(xdata[i], ydata[i], '-', linewidth = 2)
            plt.title("Sort Timing")
            plt.legend(titles)    
            
        plt.savefig(path + "Sorts.png", dpi = 1200)
        plt.close()

    else:
        for i in range(len(xdata)):
            plt.xlabel("Number Of Elements")
            plt.ylabel("Time To Sort (ms)")
            plt.plot(xdata[i], ydata[i], '.')
            plt.title(titles[i])    
            plt.savefig(path + titles[i] + ".png")
            plt.close()


if __name__ == "__main__":

    path = "../data/"
    combined = False
    
    for arg in sys.argv:
        if arg == "--combined":
            combined = True
        elif "--path=" in arg:
            path = arg.split("--path=")[1]
        elif "-h" in arg or "--help" in arg:
            print("Usage: python plotdata.py [--combined] [--path=<path to data>]")
            exit()

    PlotCSVData(path, combined)