#include "protognum.h"
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/wait.h>
#include <fcntl.h>

int esquema_atual = 0; 

// --- 1. MOTOR DE CORES (RESTAURADO) ---
void init_colors() {
    start_color();
    use_default_colors(); 
    init_pair(3, COLOR_CYAN, -1);   // ZEUS
    init_pair(5, COLOR_RED, -1);    // ALERTA

    if (esquema_atual == 0) { 
        init_pair(1, COLOR_GREEN, -1); init_pair(2, COLOR_WHITE, -1); init_pair(4, COLOR_YELLOW, -1);
    } else if (esquema_atual == 1) { 
        init_pair(1, COLOR_YELLOW, -1); init_pair(2, COLOR_WHITE, -1); init_pair(4, COLOR_GREEN, -1);
    } else if (esquema_atual == 2) { 
        init_pair(1, COLOR_RED, -1); init_pair(2, COLOR_WHITE, -1); init_pair(4, COLOR_YELLOW, -1);
    } else { 
        init_pair(1, COLOR_CYAN, -1); init_pair(2, COLOR_WHITE, -1); init_pair(4, COLOR_MAGENTA, -1);   
    }
}

void alternar_cores() {
    esquema_atual = (esquema_atual + 1) % 4;
    init_colors();
}

// --- 2. ANIMAÇÃO ZEUS ---
void zeus_loading_anim(int y, int x) {
    char *frames[] = { "[        ]", "[=       ]", "[==      ]", "[===     ]", 
                       "[====    ]", "[=====   ]", "[======  ]", "[======= ]", 
                       "[========]" };
    attron(COLOR_PAIR(3) | A_BOLD);
    for (int i = 0; i < 9; i++) {
        mvprintw(y, x, " ⚙ ZEUS_SYNC: %s ", frames[i]);
        refresh();
        usleep(35000); 
    }
    attroff(COLOR_PAIR(3) | A_BOLD);
}

// --- 3. MOTOR DE LISTAGEM ---
int list_files(const char *path, FileItem *items) {
    DIR *dir = opendir(path);
    if (!dir) return 0;
    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL && count < MAX_ITEMS) {
        if (strcmp(entry->d_name, ".") == 0) continue;
        strncpy(items[count].name, entry->d_name, 255);
        items[count].name[255] = '\0'; 
        items[count].is_dir = (entry->d_type == DT_DIR);
        count++;
    }
    closedir(dir);
    return count;
}

// --- 4. INTERFACE (RESTAURAÇÃO TOTAL DO VISUAL ORIGINAL) ---
void draw_interface(int sel_l, int count_l, FileItem *items_l, 
                    int sel_r, int count_r, FileItem *items_r, 
                    int active_pane, const char *cmd_ptr) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    int mid_x = max_x / 2;

    attron(COLOR_PAIR(1));
    box(stdscr, 0, 0); 
    mvhline(2, 0, ACS_HLINE, max_x);
    mvvline(3, mid_x, ACS_VLINE, max_y - 4); 
    mvprintw(1, 2, " ALPHA_NODE ");
    mvprintw(1, mid_x + 2, " OMEGA_NODE ");
    attroff(COLOR_PAIR(1));

    // TITULO CENTRAL
    attron(COLOR_PAIR(3) | A_BOLD);
    mvprintw(0, (max_x/2) - 8, " ⌬ PROTOGNUM ⌬ ");
    attroff(A_BOLD | COLOR_PAIR(3));

    // BARRA DE BOTÕES (IGUAL À FOTO)
    int pos = 1;
    char *btns[] = {"F1", "USB", "F2", "HOME", " G", "ZEUS", "F3", "DISK", "F4", "NANO", "F5", "CORES", "F10", "EXIT"};
    for(int i = 0; i < 14; i += 2) { 
        attron(COLOR_PAIR(4) | A_BOLD); 
        mvprintw(max_y - 1, pos, " %s ", btns[i]);
        pos += strlen(btns[i]) + 2;
        attroff(COLOR_PAIR(4) | A_BOLD);
        attron(COLOR_PAIR(1) | A_REVERSE); 
        mvprintw(max_y - 1, pos, " %s ", btns[i+1]);
        pos += strlen(btns[i+1]) + 2; 
        attroff(COLOR_PAIR(1) | A_REVERSE);
    }
    
    // PROMPT ORIGINAL
    attron(COLOR_PAIR(4) | A_BOLD);
    mvprintw(max_y - 2, 1, " ⌬ ARCHON: "); 
    attroff(COLOR_PAIR(4) | A_BOLD);
    printw("%s", cmd_ptr);
}

// --- 5. EXECUTOR TÁTICO ---
void execute_tactic_prompt(int max_y) {
    extern char cmd_buffer[1024]; 
    if (strlen(cmd_buffer) > 0) {
        def_prog_mode(); endwin(); 
        printf("\033[1;32m ⌬ [SISTEMA]: Executando protocolo...\033[0m\n\n");
        system(cmd_buffer);
        printf("\n\n ⌬ [ARCHON]: Pressione ENTER para retornar.");
        while(getchar() != '\n'); 
        cmd_buffer[0] = '\0'; 
        reset_prog_mode(); refresh();
    }
}
// --- 6. AÇÃO ZEUS ---
void execute_zeus_action(const char *query, int is_video) {
    zeus_loading_anim(LINES - 2, 1);
    char cmd[1024];
    const char *url = is_video ? "https://youtube.com" : "https://google.com";
    
    // 1. Detecta o que está disponível no Linux do usuário
    if (system("which brave > /dev/null 2>&1") == 0) {
        snprintf(cmd, sizeof(cmd), "brave --app=%s >/dev/null 2>&1 &", url);
    } 
    else if (system("which chromium > /dev/null 2>&1") == 0) {
        snprintf(cmd, sizeof(cmd), "chromium --app=%s >/dev/null 2>&1 &", url);
    } 
    else if (system("which google-chrome > /dev/null 2>&1") == 0) {
        snprintf(cmd, sizeof(cmd), "google-chrome --app=%s >/dev/null 2>&1 &", url);
    } 
    // 2. SOLUÇÃO UNIVERSAL: Se não tiver nenhum acima, usa o navegador padrão do sistema (Firefox, etc.)
    else {
        snprintf(cmd, sizeof(cmd), "xdg-open %s >/dev/null 2>&1 &", url);
    }
        
    system(cmd);
}


