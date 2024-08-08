import pandas as pd
import sys

path = str(sys.argv[1])
dest = str(sys.argv[2])

tileset = pd.read_csv(path, header=None)
tileset += 1
tileset.to_csv(dest, header=None, index=None, sep=',', mode = 'a')
