# ⌬ PROTOGNUM ─ [CENTRAL DE COMANDO]
> **Gerenciador Tático Alpha Node** • *Ambiente de Recon e Operações Nucleares*

![Banner](assets/proto-theme1.png)

## ⚡ VISÃO GERAL
O **Protognum** é o coração da interface **Archon**. Um console de comando de baixo nível desenvolvido em C, focado em velocidade, estética hacker e controle total do hardware e redes.

---

## ⌨️ PROTOCOLO DE ATALHOS (CONSOLE)

Abaixo estão os comandos de resposta rápida integrados ao núcleo:


| Tecla | Módulo | Função de Operação |
| :---: | :--- | :--- |
| **F1** | 💾 **USB** | Montagem segura em `/run/media/` via `udisksctl`. |
| **F2** | 🏠 **HOME** | Salto tático para o diretório `/home/$USER`. |
| **G**  | ⚡ **ZEUS** | **Navegação de Recon:** Acesso direto ao **Google Duck** e **YouTube**. |
| **F3** | 💽 **DISK** | `cfdisk` - Gerenciador de partições. **[!] OPERE COM CUIDADO.** |
| **F4** | 📝 **NANO** | Editor de código e logs em tempo real. |
| **F5** | 🧠 **CORES** | Alternar esquemas de cores e monitoramento. |
| **F10**| ❌ **EXIT** | Desativação segura do Protocolo Protognum. |

---

## ⚠️ ALERTA DE SEGURANÇA [F3]
O módulo **DISK (cfdisk)** possui acesso direto às tabelas de partição do sistema. Modificações incorretas resultarão em **perda permanente de dados**. O uso do `pkexec` é exigido para esta operação.

---

## 📦 DEPENDÊNCIAS DO SISTEMA
Para que todos os módulos operem em sincronia, o ambiente deve possuir:


| Pacote | Função |
| :--- | :--- |
| `ncurses` | Renderização da interface TUI. |
| `networkmanager` | Módulo de conectividade e redes. |
| `udisks2` | Gerenciamento e montagem de volumes USB (F1). |
| `polkit` | Gerenciador de privilégios (`pkexec`) para F1/F3. |
| `qterminal` | Emulador de terminal nativo. |
| `nsxiv` | Visualização de ativos e imagens. |

### 🛠️ Instalação (Arch Linux / Archon):
```bash
sudo pacman -S ncurses networkmanager udisks2 polkit qterminal nsxiv base-devel
```

## 🚀 CONSTRUÇÃO DO NÚCLEO
```bash
# 1. Compilar o sistema
make

# 2. Instalação Global
sudo make install
```

---

## 📸 GALERIA DE RECONHECIMENTO


| Módulo Zeus (Navegação) | Dashboard Principal |
| :---: | :---: |
| ![Zeus](assets/prototheme4.png) | ![Dashboard](assets/protoscreen.png) |

| Editor Nano | Visualização de Assets |
| :---: | :---: |
| ![Nano](assets/protonano.png) | ![Player](assets/protoplayer.png) |

---
**[⌬] STATUS:** *Sistema Operacional • Zeus-Browser detectado • Aguardando comandos.*
