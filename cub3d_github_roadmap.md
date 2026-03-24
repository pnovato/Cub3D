# cub3D — Roadmap do Projeto

> **Duração**: 2 semanas  
> **Convenção de branches**: `feat/nome-da-tarefa`  
> **Merge**: sempre via Pull Request com revisão do parceiro  

---

## Milestones

| # | Nome | Prazo |
|---|------|-------|
| 1 | Fundação | Fim da Semana 1 — Dia 5 |
| 2 | Parser completo | Fim da Semana 1 — Dia 7 |
| 3 | Raycasting + Render | Semana 2 — Dia 4 |
| 4 | Entrega | Fim da Semana 2 |

---

## Milestone 1 — Fundação

### Issue #1 — Definir structs principais
**Branch**: `feat/structs`  
**Responsável**: Ambos  

- [ ] Definir `t_data` (struct principal com ponteiros para as outras)
- [ ] Definir `t_texture` com `img_ptr`, `addr_img`, `bits_p_pixel`, `size_line`, `endian`, `t_width`, `t_height`
- [ ] Definir `t_map`
- [ ] Definir `t_player`
- [ ] Definir `t_ray`
- [ ] Definir enum `t_dir` { NO, SO, WE, EA }
- [ ] Criar header principal `cub3d.h`

---

### Issue #2 — Makefile e estrutura de pastas
**Branch**: `feat/makefile`  
**Responsável**: Ambos  

- [ ] Regras: `all`, `clean`, `fclean`, `re`
- [ ] Sem relink desnecessário
- [ ] Estrutura de pastas: `src/`, `include/`, `textures/`, `maps/`
- [ ] Compilar com flags: `-Wall -Wextra -Werror`
- [ ] Linkar com MLX e dependências (`-lmlx -lXext -lX11 -lm`)

---

### Issue #3 — Setup MLX
**Branch**: `feat/mlx-setup`  
**Responsável**: Pessoa 2  

- [ ] Inicializar `mlx_ptr` e `win_ptr` em `t_data`
- [ ] Criar janela com tamanho definido (ex: 1280x720)
- [ ] Implementar `mlx_loop` com hook de render
- [ ] Fechar com ESC (`mlx_key_hook`)
- [ ] Fechar com botão X da janela (`mlx_hook` evento `17`)
- [ ] Testar: janela abre e fecha corretamente

---

## Milestone 2 — Parser completo

### Issue #4 — Parsing dos identificadores
**Branch**: `feat/parser-identifiers`  
**Responsável**: Pessoa 1  

- [ ] Abrir arquivo e validar extensão `.cub`
- [ ] Ler linha por linha com `get_next_line`
- [ ] Identificar e guardar caminhos: `NO`, `SO`, `WE`, `EA`
- [ ] Identificar e guardar cores: `F` e `C`
- [ ] Validar formato RGB: 3 valores entre 0–255, separados por vírgula
- [ ] Detectar duplicatas (ex: dois `NO`)
- [ ] Erro claro se algum identificador estiver ausente

---

### Issue #5 — Parsing e validação do mapa
**Branch**: `feat/parser-map`  
**Responsável**: Pessoa 1  

- [ ] Detectar onde o mapa começa (primeira linha com `0`, `1` ou espaço)
- [ ] Guardar o mapa em matriz 2D (`char **`)
- [ ] Validar caracteres permitidos: `0`, `1`, `N`, `S`, `E`, `W`, ` `
- [ ] Verificar exatamente uma posição inicial do jogador
- [ ] Verificar que o mapa está cercado por paredes (`1`)
- [ ] Guardar posição e direção inicial do jogador em `t_player`
- [ ] Função para libertar memória do mapa

---

### Issue #6 — Error handling do parser
**Branch**: `feat/parser-errors`  
**Responsável**: Pessoa 1  

- [ ] Todas as mensagens de erro começam com `"Error\n"`
- [ ] Testar: arquivo inexistente
- [ ] Testar: extensão errada
- [ ] Testar: mapa não cercado
- [ ] Testar: caractere inválido no mapa
- [ ] Testar: múltiplas posições iniciais
- [ ] Testar: nenhuma posição inicial
- [ ] Testar: RGB fora do range (ex: `256,0,0`)
- [ ] Sem leaks no parser (valgrind)

---

### Issue #7 — Carregar texturas XPM
**Branch**: `feat/load-textures`  
**Responsável**: Pessoa 2  

- [ ] Carregar 4 texturas com `mlx_xpm_file_to_image`
- [ ] Chamar `mlx_get_data_addr` para cada textura
- [ ] Guardar `addr_img`, `bits_p_pixel`, `size_line`, `endian` em `t_texture`
- [ ] Guardar largura e altura de cada textura
- [ ] Erro se alguma textura não carregar
- [ ] Função para destruir texturas no fim

---

## Milestone 3 — Raycasting + Render

### Issue #8 — Algoritmo DDA
**Branch**: `feat/dda`  
**Responsável**: Pessoa 1  

- [ ] Calcular direção do raio por coluna de pixels
- [ ] Calcular `delta_dist_x` e `delta_dist_y`
- [ ] Calcular `step` e distância inicial (`side_dist`)
- [ ] Loop DDA: avançar até bater numa parede
- [ ] Determinar lado atingido (NS ou EW)
- [ ] Calcular distância perpendicular (corrigir fish-eye)
- [ ] Determinar coordenada X da textura (`wall_x`)
- [ ] Guardar resultados em `t_ray`

---

### Issue #9 — Renderização 3D
**Branch**: `feat/render`  
**Responsável**: Pessoa 2  

- [ ] Criar imagem buffer (`mlx_new_image`)
- [ ] Desenhar teto (cor sólida do `C`)
- [ ] Desenhar chão (cor sólida do `F`)
- [ ] Calcular altura da coluna de parede a partir da distância
- [ ] Selecionar textura correta pelo lado atingido (`t_dir`)
- [ ] Calcular coordenada Y da textura para cada pixel da coluna
- [ ] Ler cor do pixel da textura via `addr_img`
- [ ] Escrever coluna no buffer
- [ ] `mlx_put_image_to_window` no fim de cada frame

---

### Issue #10 — Colisão
**Branch**: `feat/collision`  
**Responsável**: Pessoa 1  

- [ ] Verificar se próxima posição é parede antes de mover
- [ ] Implementar sliding (deslizar ao longo da parede)
- [ ] Testar: não atravessa paredes em nenhuma direção

---

### Issue #11 — Controles do jogador
**Branch**: `feat/controls`  
**Responsável**: Pessoa 2  

- [ ] `W` / `S`: mover para frente e para trás
- [ ] `A` / `D`: strafe esquerda e direita
- [ ] Seta esquerda / direita: rotacionar câmera
- [ ] Atualizar vetor de direção e plano da câmera na rotação
- [ ] Integrar colisão aos controles
- [ ] Ajustar velocidades de movimento e rotação

---

## Milestone 4 — Entrega

### Issue #12 — Polimento final
**Branch**: `feat/polish`  
**Responsável**: Ambos  

- [ ] Norminette 100% em todos os ficheiros
- [ ] Valgrind sem leaks nem erros
- [ ] Testar todos os mapas do subject
- [ ] Testar mapas inválidos (error handling completo)
- [ ] Remover prints de debug e código comentado
- [ ] README com instruções de compilação e uso
- [ ] Makefile não relink

---

## Convenções Git

```
feat/nome     nova funcionalidade
fix/nome      correção de bug
refactor/nome reestruturação sem nova feature
test/nome     mapas ou scripts de teste
```

**Mensagens de commit** (em inglês, imperativo):
```
Add s_texture struct definition
Fix map validation for empty lines
Refactor parser to use get_next_line
```

---

## Checklist final antes da entrega

- [ ] `make` compila sem warnings
- [ ] `make fclean && make` funciona
- [ ] ESC e botão X fecham sem leaks
- [ ] Todos os mapas do subject funcionam
- [ ] Mapas inválidos dão `Error\n` e saem limpos
- [ ] `valgrind --leak-check=full` sem leaks
- [ ] Norminette sem erros
