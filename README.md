# 🕹️ cub3D - Nosso primeiro RayCaster

<div align="center">
  <img src="https://media.giphy.com/media/JIX9t2j0ZTN9S/giphy.gif" alt="Cat Typing GIF" />
</div>

## 👥 Autores
Projeto desenvolvido em dupla por:
* **Matheus Lessa**
* **Patrick Novato**

---

## 📜 Sobre o Projeto

O **cub3D** é um projeto da escola 42 inspirado no mundialmente famoso *Wolfenstein 3D*, considerado o primeiro jogo FPS (First-Person Shooter) da história. O objetivo deste projeto é criar uma visualização 3D dinâmica de um labirinto a partir de um mapa 2D, utilizando a técnica matemática de **Raycasting** e a biblioteca gráfica **miniLibX**.

Neste jogo, o jogador precisa navegar por um labirinto fechado. O projeto cobre conceitos essenciais como:
- Leitura e validação rigorosa de arquivos e configurações (Parsing).
- Matemática aplicada à computação gráfica (DDA, vetores, projeção de raios).
- Gerenciamento de eventos (teclado) e janelas.
- Manipulação e renderização de texturas e cores.

---

## 🛠️ Como Compilar e Rodar

O projeto foi desenvolvido em linguagem C. Para rodar o jogo na sua máquina, siga os passos abaixo:

### Pré-requisitos
Certifique-se de ter o compilador `gcc` (ou `cc`), o utilitário `make` e as dependências da `miniLibX` instaladas no seu sistema.

### Compilação
Clone este repositório e, na raiz do projeto, execute:
```bash
make
