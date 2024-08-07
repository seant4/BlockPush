import pandas as pd

tileset = pd.read_csv("map2.csv", header=None)
tileset += 1
tileset.to_csv("map2.txt", header=None, index=None, sep=',', mode = 'a')
