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
