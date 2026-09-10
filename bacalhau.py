# Complexidade O(1), pois é constante
n =  int(input())
indices = [0]*n

# Complexidade O(n)
for i in range(n):
    x, y = map(int, input().split())
    coordenada = [x, y, i]
    indices[i] = coordenada

# O sort do Python é um timsort, que tem complexidade O(nlogn), semelhante ao mergesort
indices.sort() 

# Retorna distância entre duas coordenadas
def distancia(coordenada1, coordenada2):
    return ((coordenada1[0] - coordenada2[0])**2 + (coordenada1[1] - coordenada2[1])**2)**(1/2)

# Retorna lista das tuplas com os índices com as menores distâncias de si mesmos

def acharMenoresDistancias(lista):
    # Os casos bases 2 e 3 tem O(1) pois são constantes
    tamanho = len(lista)
    if tamanho == 2:
        d = distancia(lista[0], lista[1])
        return [d, (lista[0][2], lista[1][2])]
    # Ta bem feio o código dessa parte mas funciona e tem complexidade constante então tanto faz
    if tamanho == 3:
        d1 = distancia(lista[0], lista[1])
        d2 = distancia(lista[0], lista[2])
        d3 = distancia(lista[1], lista[2])
        minimo = min(d1, d2, d3)
        if minimo == d1 and minimo == d2 and minimo == d3:
            return [minimo, (lista[0][2], lista[1][2]), (lista[0][2], lista[2][2]), (lista[1][2], lista[2][2])]
        if minimo == d1 and minimo == d2 and minimo != d3:
            return [minimo, (lista[0][2], lista[1][2]), (lista[0][2], lista[2][2])]
        if minimo == d1 and minimo != d2 and minimo == d3:
            return [minimo, (lista[0][2], lista[1][2]), (lista[1][2], lista[2][2])]
        if minimo != d1 and minimo == d2 and minimo == d3:
            return [minimo, (lista[0][2], lista[2][2]), (lista[1][2], lista[2][2])]
        if minimo == d1:
            return [minimo, (lista[0][2], lista[1][2])]
        elif minimo == d2:
            return [minimo, (lista[0][2], lista[2][2])]
        else:
            return [minimo, (lista[1][2], lista[2][2])]

    meio = tamanho//2
    # Há duas chamadas recursivas dividindo em duas partes pela metade, tendo essa seção O(logn)
    esquerda = acharMenoresDistancias(lista[:meio])
    direita = acharMenoresDistancias(lista[meio:])
    de = esquerda[0]
    dd = direita[0]

    if de > dd:
        return direita
    elif de < dd:
        return esquerda
    else:
        for i in range(1, len(direita)):
            esquerda.append(direita[i])
        return esquerda

resposta = acharMenoresDistancias(indices)

tamanho_resposta = len(resposta)

for i in range(1, tamanho_resposta):
    a = min(resposta[i][0], resposta[i][1])
    b = max(resposta[i][0], resposta[i][1])
    resposta[i] = (a, b)
    print(f'({resposta[i][0]},{resposta[i][1]})')

# Descontinuado porque descobri que é pra fazer em C