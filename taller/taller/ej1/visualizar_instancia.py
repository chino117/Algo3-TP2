import sys
import matplotlib.pyplot as plt

# Recibo dos archivos por parámetro <input_file> <output_file>.
# input_file: instancia del problema.
# output_file: output del algoritmo con los clusters. (opcional)

if len(sys.argv) < 2:
	print("Ejecutar pasando como primer parámetro la instancia y opcionalmente como segundo parámetro el archivo de salida.")
	exit()

# Leo la instancia.
print("Leyendo instancia...")
input_path = sys.argv[1]
input_file = open(input_path, "r")
n = int(input_file.readline())
x = []
y = []
for i in range(0, n):
	(p_x, p_y) = input_file.readline().split()
	x.append(float(p_x))
	y.append(float(p_y))
input_file.close()

# Leo los clusters si existen.
cc = [0 for i in range(0, n)]
if len(sys.argv) >= 3:
	cc = []
	print("Leyendo clusters...")
	output_path = sys.argv[2]
	output_file = open(output_path, "r")
	for i in range(0, n):
		cc.append(int(output_file.readline()))
	output_file.close()

print("Mostrando gráfico...")
plt.scatter(x, y, c=cc)
plt.show()