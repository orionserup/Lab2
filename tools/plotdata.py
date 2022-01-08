import matplotlib.pyplot as plt
import csv
import glob

if __name__ == "__main__":
    
    path = "../data/"
    files = glob.glob(path + "*.csv")
    readers = [ csv.reader(open(file)) for file in files ]
    datem = [ [ row for row in reader ] for reader in readers]
    xdata = [ [int(row[0]) for row in data] for data in datem ]
    ydata = [ [float(row[1]) for row in data] for data in datem]
    
    plt.xlabel("Number Of Elements")
    plt.ylabel("Time To Sort (ms)");
    for i in range(len(xdata)):
        plt.title(files[i].split(".csv")[0].replace(path, ''))
        plt.plot(xdata[i], ydata[i])
        plt.savefig(files[i].split(".csv")[0] + ".png")
        plt.close()
    
    

        
