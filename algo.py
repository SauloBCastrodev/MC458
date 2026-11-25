import matplotlib.pyplot as plt

# 1. Definição da linha do tempo e do sinal de Clock
# Bordas de subida em t=5 e t=25; descida em t=15 e t=35
clk = [0]*5 + [1]*10 + [0]*10 + [1]*10 + [0]*6
n_samples = len(clk)

# 2. Mapeamento da entrada X
x = [0] * n_samples
for i in range(3, 8): x[i] = 1   # Cortado pela 1ª subida
for i in range(10, 14): x[i] = 1 # Contido no 1º pulso alto
for i in range(17, 20): x[i] = 1 # Entre os pulsos de clock
for i in range(22, 25): x[i] = 1 # Antes da 2ª subida (X=0 no instante t=25)
for i in range(27, 31): x[i] = 1 # Contido no 2º pulso alto
for i in range(33, 38): x[i] = 1 # Atravessa a 2ª descida

# 3. Inicialização e Simulação Lógica das Saídas
q1, q2, q3, q4, q5 = ([0]*n_samples for _ in range(5))

for i in range(1, n_samples):
    rising_edge = (clk[i-1] == 0 and clk[i] == 1)
    falling_edge = (clk[i-1] == 1 and clk[i] == 0)
    
    # Q1: Latch D (nível alto)
    q1[i] = x[i] if clk[i] == 1 else q1[i-1]
        
    # Q2: Flip-Flop D (borda de subida)
    q2[i] = x[i] if rising_edge else q2[i-1]
        
    # Q3: Flip-Flop D (borda de descida)
    q3[i] = x[i] if falling_edge else q3[i-1]
        
    # Q4: Flip-Flop JK (borda de subida) com J = NOT X, K = X
    if rising_edge:
        if x[i] == 0:  # J=1, K=0 -> Set
            q4[i] = 1
        else:          # J=0, K=1 -> Reset
            q4[i] = 0
    else:
        q4[i] = q4[i-1]
        
    # Q5: Flip-Flop T (borda de subida) com T = X
    if rising_edge:
        q5[i] = 1 - q5[i-1] if x[i] == 1 else q5[i-1]
    else:
        q5[i] = q5[i-1]

# 4. Desenho do Diagrama
fig, axs = plt.subplots(7, 1, figsize=(11, 9), sharex=True)
fig.suptitle('Diagrama de Tempo - Lógica Corrigida em Q4', fontsize=14, fontweight='bold')

sinais = [
    (clk, 'Clk', 'black'), (x, 'X', 'blue'),
    (q1, 'Q1\n(Latch)', 'red'), (q2, 'Q2\n(FF-D)', 'green'),
    (q3, 'Q3\n(FF-D Desc)', 'purple'), (q4, 'Q4\n(FF-JK J=X\')', 'orange'),
    (q5, 'Q5\n(FF-T)', 'orange')
]

tempo = list(range(n_samples))

for ax, (sinal, nome, cor) in zip(axs, sinais):
    ax.step(tempo, sinal, where='post', color=cor, linewidth=2.5)
    ax.set_ylabel(nome, rotation=0, labelpad=50, ha='left', fontweight='bold', va='center')
    ax.set_ylim(-0.2, 1.2)
    ax.set_yticks([0, 1])
    ax.grid(True, linestyle='--', alpha=0.5)
    
    for t in [5, 25]: ax.axvline(x=t, color='gray', linestyle='-', alpha=0.4) 
    for t in [15, 35]: ax.axvline(x=t, color='gray', linestyle='-', alpha=0.4)

axs[-1].set_xticks([]) 
plt.tight_layout()
plt.subplots_adjust(left=0.2)
plt.show()