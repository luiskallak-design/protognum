# --- CONFIGURAÇÃO DO PROTOCOLO ---
TARGET  = bin/protognum
CC      = gcc

# Repositório correto da dependência essencial
ARCHON_GIT = https://github.com/luiskallak-design/archonplayer-tui

# Variáveis de Portabilidade (O segredo para todas as distros)
PREFIX  ?= /usr/local
BINDIR  = $(PREFIX)/bin

# Cores do Sistema (Estética Grega/Archon)
CYAN    = \033[0;36m
RED     = \033[0;31m
GREEN   = \033[0;32m
WHITE   = \033[1;37m
BLUE    = \033[0;34m
BOLD    = \033[1m
RESET   = \033[0m

# FLAGS
CFLAGS  = -Iinclude -Wall -O2
LIBS    = -lncursesw

# ARQUIVOS
SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, obj/%.o, $(SRC))

# --- EXECUÇÃO ---

.PHONY: all clean setup install archon_dep

# CORREÇÃO: archon_dep adicionado aqui para garantir a execução antes da compilação
all: setup archon_dep $(TARGET)
	@echo -e "\n$(GREEN)$(BOLD)⌬ [PROTOGNUM] PROTOCOLO ATIVADO COM SUCESSO!$(RESET)"
	@echo -e "$(CYAN)❱❱ Alvo localizado em: $(TARGET)$(RESET)\n"

# Prepara o terreno (Pastas)
setup:
	@mkdir -p bin obj
	@echo -e "$(CYAN)⌬ INICIALIZANDO AMBIENTE DE RECON...$(RESET)"

# Verifica e instala o ArchonPlayer se não estiver presente no sistema
archon_dep:
	@if ! command -v archonplayer >/dev/null 2>&1; then \
		echo -e "$(WHITE)$(BOLD)⌬ [SINAL]$(RESET) $(BLUE)ArchonPlayer não detectado. Iniciando forja automática...$(RESET)"; \
		git clone $(ARCHON_GIT) /tmp/archonplayer-tui && \
		cd /tmp/archonplayer-tui/archonplayer && \
		make && \
		sudo make install && \
		rm -rf /tmp/archonplayer-tui; \
		echo -e "$(CYAN)⌬ [ECOSISTEMA] ArchonPlayer forjado e linkado com sucesso!$(RESET)\n"; \
	else \
		echo -e "$(BLUE)⌬ [ECOSISTEMA] ArchonPlayer já integrado ao ecossistema. Sincronizado.$(RESET)"; \
	fi

# Linkagem Final
$(TARGET): $(OBJ)
	@echo -e "$(CYAN)⌬ CONSOLIDANDO NÚCLEO: $(RESET)$@"
	@$(CC) $(OBJ) -o $(TARGET) $(LIBS)

# Compilação dos Módulos (Garante que a pasta obj existe)
obj/%.o: src/%.c | setup
	@echo -e "$(RED)⌬ PROCESSANDO CÓDIGO: $(RESET)$<"
	@$(CC) -c $< -o $@ $(CFLAGS)

# Limpeza (Éter)
clean:
	@rm -rf obj/*.o bin/*
	@echo -e "$(RED)⌬ LIMPANDO RASTROS DE OPERAÇÃO...$(RESET)"

# Instalação Profissional (Funciona no Arch, Debian, Fedora, etc.)
install: all
	@echo -e "$(CYAN)⌬ ENVIANDO BINÁRIO PARA O SISTEMA...$(RESET)"
	@mkdir -p $(DESTDIR)$(BINDIR)
	@install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/protognum
	@echo -e "\n$(GREEN)⌬ INSTALADO EM: $(BOLD)$(DESTDIR)$(BINDIR)$(RESET)"
	@echo -e "$(GREEN)⌬ DICA:$(RESET) $(BOLD)ZEUS-BROWSER$(RESET) detectado no horizonte."

