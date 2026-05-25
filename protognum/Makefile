# --- CONFIGURAÇÃO DO PROTOCOLO ---
TARGET  = bin/protognum
CC      = gcc

# Repositórios exatos fornecidos por você
PROTOGNUM_GIT = https://github.com/luiskallak-design/protognum
ARCHON_GIT    = https://github.com/luiskallak-design/archonplayer-tui

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

# Garante as pastas, as dependências externas e compila o binário
all: setup archon_dep $(TARGET)
	@echo -e "\n$(GREEN)$(BOLD)⌬ [PROTOGNUM] PROTOCOLO ATIVADO COM SUCESSO!$(RESET)"
	@echo -e "$(CYAN)❱❱ Alvo localizado em: $(TARGET)$(RESET)\n"

# Prepara o terreno (Pastas locais)
setup:
	@mkdir -p bin obj
	@echo -e "$(CYAN)⌬ INICIALIZANDO AMBIENTE DE RECON...$(RESET)"

# Exibe explicitamente as informações de clone de ambos os sistemas
archon_dep:
	@echo -e "$(WHITE)$(BOLD)⌬ [FONTE PROTOGNUM]$(RESET) $(CYAN)Sincronizado com: $(PROTOGNUM_GIT)$(RESET)"
	@if ! command -v archonplayer >/dev/null 2>&1; then \
		echo -e "$(WHITE)$(BOLD)⌬ [SINAL]$(RESET) $(BLUE)ArchonPlayer não detectado no sistema...$(RESET)"; \
		echo -e "$(WHITE)$(BOLD)⌬ [CLONANDO DEP]$(RESET) $(GREEN)Iniciando: git clone $(ARCHON_GIT)$(RESET)"; \
		git clone $(ARCHON_GIT) /tmp/archonplayer-tui; \
		cd /tmp/archonplayer-tui && \
		chmod +x install_deps.sh && sudo ./install_deps.sh && \
		cd archonplayer && \
		make && \
		sudo make install && \
		rm -rf /tmp/archonplayer-tui; \
		echo -e "$(CYAN)⌬ [ECOSISTEMA] ArchonPlayer forjado e linkado com sucesso!$(RESET)\n"; \
	else \
		echo -e "$(BLUE)⌬ [ECOSISTEMA] ArchonPlayer já integrado ao ecossistema global. Sincronizado.$(RESET)"; \
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

# Instalação Profissional
install: all
	@echo -e "$(CYAN)⌬ ENVIANDO BINÁRIO PARA O SISTEMA...$(RESET)"
	@mkdir -p $(DESTDIR)$(BINDIR)
	@install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/protognum
	@echo -e "\n$(GREEN)⌬ INSTALADO EM: $(BOLD)$(DESTDIR)$(BINDIR)$(RESET)"
	@echo -e "$(GREEN)⌬ DICA:$(RESET) $(BOLD)ZEUS-BROWSER$(RESET) detectado no horizonte."
