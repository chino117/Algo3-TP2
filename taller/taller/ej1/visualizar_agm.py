import sys
import matplotlib.pyplot as plt

# Recibo dos archivos por parámetro <agm_path>.
# agm_path: archivo de AGM.
if len(sys.argv) < 2:
	print("Ejecutar pasando como primer parámetro el agm.")
	exit()

# Leo el archivo.
print("Leyendo AGM...")
agm_path = sys.argv[1]
agm_file = open(agm_path, "r")
m = int(agm_file.readline())
for i in range(0, m):
	(x1, y1, x2, y2) = agm_file.readline().split()
	plt.plot([float(x1), float(x2)], [float(y1), float(y2)],marker='o', linestyle='-', markersize=2, color='red', markerfacecolor='black', markeredgecolor='black')
print("Graficando AGM...")
plt.show()