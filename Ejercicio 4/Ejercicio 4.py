from multiprocessing import Pool, cpu_count

# ***** INF-317 ******
#    PRIMER PARCIAL
#     EJERCICIO 4
# APELLIDO Y NOMBRE: MENACHO PACA JAVIER 
# CI: 12763905 LP

def serie(inicio,fin):
    s = []
    for i in range(inicio,fin+1):
        if i%2==0:
            if inicio==i:
                s.append(((i//2)**2)+1)
                s.append(inicio)
            else:
                s.append(i)
        else:
            if inicio==i:
                s.append((i//2)+1)
                s.append(((i//2)+1)**2+1)

            else:
                s.append((s[-1]+s[-2]+1))
    s.pop(0)
    return s
def serie2(n):
    cont=1
    l=[]
    for i in range(1,n+1):
        if i%2==0:
            l.append(i)
        else:
            l.append(cont**2+1)
            cont=cont+1
    return l

if __name__ == '__main__':
    n = 10000
    procesadores = cpu_count()  # Número de procesos a utilizar

    pool = Pool(processes=procesadores)

    tamanos = n // procesadores
    inicio = 1
    fin = inicio + tamanos

    results = []

    for _ in range(procesadores):
        results.append(pool.apply_async(serie, (inicio, fin)))
        inicio = fin+1
        fin = inicio + tamanos-1

    serieT = []

    for result in results:
        serieT.extend(result.get())

    print(serieT)