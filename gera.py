import random

def gerar_cpf_formatado():
    # Gera os 9 primeiros dígitos
    d = [random.randint(0, 9) for _ in range(9)]
    
    # Cálculo do primeiro dígito verificador
    soma = sum(a * b for a, b in zip(d, range(10, 1, -1)))
    dv1 = (soma * 10 % 11) % 10
    d.append(dv1)
    
    # Cálculo do segundo dígito verificador
    soma = sum(a * b for a, b in zip(d, range(11, 1, -1)))
    dv2 = (soma * 10 % 11) % 10
    d.append(dv2)
    
    # Retorna no formato xxx.xxx.xxx-xx
    return f"{d[0]}{d[1]}{d[2]}.{d[3]}{d[4]}{d[5]}.{d[6]}{d[7]}{d[8]}-{d[9]}{d[10]}"

# Gera o arquivo com 4096 CPFs formatados
with open("cpfs.txt", "w") as f:
    for _ in range(4096):
        f.write(gerar_cpf_formatado() + "\n")

print("Arquivo cpfs.txt (formatado) gerado com sucesso!")