#ifndef PROTOGNUM_H
#define PROTOGNUM_H

#include <ncurses.h>

// --- DEFINIÇÕES DE ELITE (MODULARIDADE) ---
#define MAX_ITEMS 100
#define MAX_PATH_LEN 512
#define MAX_QUERY 256

// --- ESTADOS DO SISTEMA (MODO ZEUS INTEGRADO) ---
typedef enum { 
    MODO_FILE, 
    MODO_ZEUS 
} PaneMode;

// --- ESTRUTURA DE DADOS DO SISTEMA ---
typedef struct {
    char name[256];
    int is_dir;
} FileItem;

// --- NUCLEO DE CORES E MOTOR DE LISTAGEM ---
void init_colors();
void alternar_cores(); 
int list_files(const char *path, FileItem *items);

// --- INTERFACE GRAFICA TATICA (UX SENIOR) ---
// Note o uso de 'PaneMode' para o desenho saber se o painel é Zeus ou File
void draw_interface(int sel_l, int count_l, FileItem *items_l, 
                    int sel_r, int count_r, FileItem *items_r, 
                    int active_pane, const char *cmd_ptr);

// --- MOTOR ZEUS & ANIMAÇÕES GOD ELITE ---
void zeus_loading_anim(int y, int x);
void execute_zeus_action(const char *query, int is_video);

// --- EXECUTOR DE COMANDOS (SISTEMA DE PAUSA) ---
void execute_tactic_prompt(int max_y);

#endif
