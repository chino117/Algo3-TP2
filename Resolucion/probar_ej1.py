from PIL import Image
import subprocess 
import os
import colorsys

def crear_colores(N=5):
    HSV_tuples = [(x * 1.0 / N, 0.5, 0.5) for x in range(N)]
    res = []
    for rgb in HSV_tuples:
        rgb = map(lambda x: int(x * 255), colorsys.hsv_to_rgb(*rgb))
        res.append(tuple(rgb))
    return res 

def preparar_img(path):
    img = Image.open(path).convert("L")
    m, n = img.size
    data = " ".join([str(i) for i in list(img.getdata())])
    return (n, m, f"{n} {m}\n {data}", img)

def armar_imagen(n, m ,data):
    split_data = [int(j) for i in data.splitlines() for j in i.split(" ") if j != '']
    uniques = set(split_data)

    colores = crear_colores(len(uniques))
    color_dict = dict(zip(uniques, colores))

    img = Image.new("RGB", (m, n))
    for i in range(0, n):
        for j in range(0, m):
            img.putpixel((j, i), color_dict[split_data[i*m + j]])
    return img

def correr(datos_img, k, metodo):
    completado = subprocess.run(["./bin/ej1", f"{metodo}", f"{k}"], capture_output=True, input=datos_img[2], text=True)
    if completado.returncode != 0:
        print(f"ERROR: El programa finalizo de forma incorrecta. Parametros usados: k={k} metodo={metodo}")
    else:
        img_generada = armar_imagen(datos_img[0], datos_img[1], str(completado.stdout))

        img_original = datos_img[3].convert("RGB")
        max_height = max(img_generada.height, img_original.height)
        total_width = img_generada.width + img_original.width

        comp_img = Image.new("RGB", (total_width, max_height))
        comp_img.paste(img_original, (0, 0))
        comp_img.paste(img_generada, (img_generada.width, 0))
        comp_img.show()

os.system("cd codigo/ej1/ && make")

carpeta = "datos_entrada/ej1/"
correr(preparar_img(carpeta + "test1.jpg"), 1000, 0)
correr(preparar_img(carpeta + "test1.jpg"), 1000, 1)
correr(preparar_img(carpeta + "test2.png"), 1000, 0)
correr(preparar_img(carpeta + "test2.png"), 1000, 1)
correr(preparar_img(carpeta + "test1.jpg"), 1000, 2)
correr(preparar_img(carpeta + "test2.png"), 1000, 2)
