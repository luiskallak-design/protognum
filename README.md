# ⌬ PROTOGNUM ─ [CENTRAL DE COMANDO]
> **Gerenciador Tático Alpha Node** • *Engenharia de Baixo Nível & Operações de Núcleo*




## 📸 INTERFACE DO SISTEMA
![Banner Principal](protognum/assets/proto-theme1.png)
![Dashboard Alpha](protognum/assets/protoscreen.png)


---

## ⌨️ PROTOCOLO DE ATALHOS (CONSOLE)


| Tecla | Módulo | Função de Operação |
| :---: | :--- | :--- |
| **F1** | 💾 **USB** | Montagem segura em `/run/media/` via `udisksctl`. |
| **F2** | 🏠 **HOME** | Salto tático para o diretório `/home/$USER`. |
| **G**  | ⚡ **ZEUS** | **Recon:** Navegação Google Duck / YouTube. |
| **F3** | 💽 **DISK** | `cfdisk` - Gerenciador de partições. **[!] CUIDADO.** |
| **F4** | 📝 **NANO** | Editor de código e logs em tempo real. |
| **F5** | 🧠 **CORES** | Alternar esquemas de cores. |
| **F10**| ❌ **EXIT** | Desativação segura do sistema. |

---

## 📦 DEPENDÊNCIAS
`ncurses`, `networkmanager`, `udisks2`, `polkit`, `qterminal`, `nsxiv`.

## 🚀 RITUAL DE INSTALAÇÃO

O sistema possui uma forja inteligente que detecta o ambiente e baixa automaticamente o ecossistema de áudio necessário durante o processo.

### 1. Preparar o Terreno (Dependências)
Antes de compilar, garanta as ferramentas essenciais de compilação e as bibliotecas de sistema:

```bash
sudo pacman -S ncurses networkmanager udisks2 polkit qterminal nsxiv base-devel git make gcc
```

### 2. Clonagem da Central
Baixe o código-fonte original diretamente do repositório do Olimpo:

```bash
git clone https://github.com/luiskallak-design/protognum/protognum
cd protognum
```

### 3. Compilação e Instalação Global
Dispare a compilação do núcleo. O sistema verificará a presença do `archonplayer` e o integrará de forma automatizada caso necessário.

```bash
# Compila e prepara os binários locais
make

# Move o binário de forma segura para o caminho do sistema
sudo make install
```

---

## 🛰️ MÓDULOS DE VISUALIZAÇÃO


| Editor Nano | Visualização de Assets |
| :---: | :---: |
| ![Nano](protognum/assets/protonano.png) | ![Player](protognum/assets/protoplayer.png) |



---
**[⌬] STATUS:** *Sistema Operacional • Zeus-Browser ativo • Aguardando comandos.*
<!-- TAGS: archlinux terminal tui c-programming low-level sysadmin hacking aesthetic archon zeus-browser -->

