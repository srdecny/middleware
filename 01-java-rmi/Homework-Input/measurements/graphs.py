import os
import sys
import matplotlib
import matplotlib.pyplot as plt
import csv
import glob
from matplotlib import rcParams
rcParams.update({'figure.autolayout': True})

basepath = sys.argv[1]
# basepath = "/home/srdecny/repos/middleware/01-java-rmi/Homework-Input/measurements"
TRANSITIVE_COUNT = 9

graphs = [
    ["Local", "baseline", 2],
    ["Remote Searcher", "remotesearcher", 3], 
    ["Remote Nodes", "remotenodes", 4], 
    ["Remote Searcher + Remote Nodes", "remotesearchernodes", 5],
]

for transitive in range(6, 6 + TRANSITIVE_COUNT):
    graphs.append([f"Transitive remote - {transitive - 5} neighbours", f"transitive{transitive - 5}", transitive])

dirs = ["localhost", "remote"]
for dir in dirs:
    measurements = glob.glob(f"{basepath}/{dir}/*.csv")
    measurements.sort(key=lambda x: int(os.path.basename(x)[:-4]))
    for graph in graphs:
        fig, ax = plt.subplots()
        description, filename, idx = graph
        for measurement in measurements:
            with open(measurement) as f:
                results = {}
                csvFile = csv.reader(f, delimiter=' ')
                header = next(csvFile)
                for row in csvFile:
                    row = [r for r in row if r != ""]
                    _, distance, *_ = row
                    datapoint = row[int(idx)]
                    if distance not in results:
                        results[distance] = []
                    results[distance].append(datapoint)
                xs = [x for x in map(int, sorted(results.keys()))]
                ys = [sum(map(int, results[k]))/len(results[k]) for k in sorted(results.keys())]
                line = ax.plot(xs, ys, 'o-', label=os.path.basename(measurement)[:-4] + " edges")

        ax.set_title(f"{dir} server, 1000 nodes, 50 path searches")
        ax.set_yscale('log')
        ax.set_xlabel('distance')
        ax.set_ylabel(f'{description} - average search time (ms)')
        ax.legend()
        plt.tight_layout()
        plt.savefig(f"{dir}/{filename}.png")
        plt.close()