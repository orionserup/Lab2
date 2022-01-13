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
    titles = [ file.replace(path, '').split('.csv')[0] for file in files]

    for i in range(len(xdata)):
        plt.xlabel("Number Of Elements")
        plt.ylabel("Time To Sort (ms)")
        plt.plot(xdata[i], ydata[i], 'r.')
        plt.title(titles[i])    
        plt.savefig(path + titles[i] + ".png")
        plt.close()
    

        
