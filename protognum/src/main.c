#include "protognum.h"
#include <locale.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> // ADICIONADO PARA O KILL

// --- VARIÁVEIS GLOBAIS ---
char cmd_buffer[1024] = ""; 
int offset_l = 0, offset_r = 0; 

int main() {
    setlocale(LC_ALL, "");
    initscr(); 
    start_color();
    use_default_colors();
    noecho(); 
    keypad(stdscr, TRUE); 
    curs_set(0); 
    init_colors();

    FileItem items_l[MAX_ITEMS], items_r[MAX_ITEMS];
    char path_l[512], path_r[512];
    int sel_l = 0, sel_r = 0, count_l, count_r;
    int active_pane = 0; 
    PaneMode modo_l = MODO_FILE, modo_r = MODO_FILE;

    getcwd(path_l, 512); 
    strcpy(path_r, path_l);
    count_l = list_files(".", items_l); 
    count_r = list_files(".", items_r);

    while(1) {
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        int mid_x = max_x / 2;
        int max_view = max_y - 6;

        clear();
        
        // --- TÍTULO FIXO NO TOPO ---
        attron(COLOR_PAIR(3) | A_BOLD);
        mvprintw(0, (max_x/2) - 8, "⌬ PROTOGNUM ⌬");
        attroff(COLOR_PAIR(3) | A_BOLD);

        draw_interface(sel_l, count_l, items_l, sel_r, count_r, items_r, active_pane, cmd_buffer);

        // --- RENDERIZAR LADO ALPHA ---
        for(int i = offset_l; i < offset_l + max_view && i < count_l; i++) {
            int pair = (modo_l == MODO_ZEUS) ? 3 : (i == sel_l && active_pane == 0 ? 4 : 1);
            int row = i - offset_l + 3;
            if (active_pane == 0 && i == sel_l) {
                attron(COLOR_PAIR(pair) | A_BOLD);
                mvprintw(row, 1, " > %-25.25s ", items_l[i].name);
                attroff(COLOR_PAIR(pair) | A_BOLD);
            } else {
                attron(COLOR_PAIR(pair));
                mvprintw(row, 4, "%-25.25s ", items_l[i].name);
                attroff(COLOR_PAIR(pair));
            }
        }

        // --- RENDERIZAR LADO OMEGA ---
        for(int i = offset_r; i < offset_r + max_view && i < count_r; i++) {
            int pair = (modo_r == MODO_ZEUS) ? 3 : (i == sel_r && active_pane == 1 ? 4 : 1);
            int row = i - offset_r + 3;
            if (active_pane == 1 && i == sel_r) {
                attron(COLOR_PAIR(pair) | A_BOLD);
                mvprintw(row, mid_x + 1, " > %-25.25s ", items_r[i].name);
                attroff(COLOR_PAIR(pair) | A_BOLD);
            } else {
                attron(COLOR_PAIR(pair));
                mvprintw(row, mid_x + 4, "%-25.25s ", items_r[i].name);
                attroff(COLOR_PAIR(pair));
            }
        }

        refresh();
        int ch = getch();

        if (ch == 'q' || ch == KEY_F(10)) break;
        if (ch == '\t' || ch == '9') active_pane = !active_pane;

        // Atribuição tática do painel ativo
        FileItem *c_it = active_pane ? items_r : items_l;
        int *c_sel     = active_pane ? &sel_r : &sel_l;
        char *c_pa     = active_pane ? path_r : path_l;
        int *c_co      = active_pane ? &count_r : &count_l;
        PaneMode *c_mo = active_pane ? &modo_r : &modo_l;
        int *c_off     = active_pane ? &offset_r : &offset_l;

        // SCROLL
        if (ch == KEY_UP && *c_sel > 0) {
            (*c_sel)--;
            if (*c_sel < *c_off) (*c_off)--;
        }
        else if (ch == KEY_DOWN && *c_sel < *c_co - 1) {
            (*c_sel)++;
            if (*c_sel >= *c_off + max_view) (*c_off)++;
        }
        
        // --- FUNÇÕES F1-F5 ---
        else if (ch == KEY_F(1)) { def_prog_mode(); endwin(); system("sudo mount /dev/sdb1 /media"); reset_prog_mode(); refresh(); }
        else if (ch == KEY_F(2)) { *c_mo = MODO_FILE; chdir(getenv("HOME")); getcwd(c_pa, 512); *c_co = list_files(".", c_it); *c_sel = 0; *c_off = 0; }
        else if (ch == KEY_F(3)) { def_prog_mode(); endwin(); system("sudo cfdisk"); reset_prog_mode(); refresh(); }
        else if (ch == KEY_F(4)) { char cn[1024]; def_prog_mode(); endwin(); sprintf(cn, "sudo nano \"%s/%s\"", c_pa, c_it[*c_sel].name); system(cn); reset_prog_mode(); refresh(); }
        else if (ch == KEY_F(5)) { alternar_cores(); }

        // ZEUS G
        else if (ch == 'g' || ch == 'G') {
            cmd_buffer[0] = '\0';
            attron(COLOR_PAIR(3) | A_BOLD);
            mvprintw(max_y - 2, 1, " ⌬ ZEUS_RADAR: ");
            echo(); curs_set(1);
            char qq[256]; getnstr(qq, 255);
            noecho(); curs_set(0);
            if (strlen(qq) > 0) {
                *c_mo = MODO_ZEUS; *c_co = 3; *c_sel = 0; *c_off = 0;
                snprintf(c_it[0].name, 256, "⌬ ZEUS_LINK: %s", qq);
                strcpy(c_it[1].name, "⌬ ZEUS_STREAM (YOUTUBE)");
                strcpy(c_it[2].name, "⌬ ZEUS_RETURN (BACKSPACE)");
                zeus_loading_anim(max_y - 2, 1);
            }
        }
        
        // ENTER
        else if (ch == 10 || ch == KEY_ENTER) {
            if (strlen(cmd_buffer) > 0) {
                execute_tactic_prompt(max_y);
                *c_co = list_files(".", c_it);
                cmd_buffer[0] = '\0'; *c_off = 0;
            } 
            else if (*c_mo == MODO_ZEUS) {
                if (*c_sel == 2) { *c_mo = MODO_FILE; *c_co = list_files(".", c_it); *c_sel = 0; *c_off = 0; }
                else execute_zeus_action(c_it[0].name + 13, (*c_sel == 1));
            }
            else {
                if (c_it[*c_sel].is_dir) {
                    chdir(c_it[*c_sel].name);
                    getcwd(c_pa, 512); 
                    *c_co = list_files(".", c_it); *c_sel = 0; *c_off = 0;
                } 
                else {
                    char *fname = c_it[*c_sel].name;
                    if (fork() == 0) {
                        setsid();
                        int d_null = open("/dev/null", O_WRONLY);
                        dup2(d_null, 1); dup2(d_null, 2);
                        if (strstr(fname, ".mp3") || strstr(fname, ".wav") || strstr(fname, ".ogg")) {
                         // Versão Sênior: Remove o 'exec bash' e usa o binário global que instalamos
                        execlp("qterminal", "qterminal", "-e", "archonplayer", fname, (char *)NULL);
                        } else if (strstr(fname, ".jpg") || strstr(fname, ".png") || strstr(fname, ".gif")) {
                            execlp("nsxiv", "nsxiv", "-a", "-n", "1", fname, NULL);
                        } else {
                            execlp("qterminal", "qterminal", "-e", "nano", fname, NULL);
                        }
                        _exit(1);
                    }
                }
            }
        }

        // BACKSPACE
        else if (ch == KEY_BACKSPACE || ch == 127 || ch == 8) {
            int len = (int)strlen(cmd_buffer);
            if (len > 0) cmd_buffer[len - 1] = '\0';
            else if (*c_mo == MODO_ZEUS) { *c_mo = MODO_FILE; *c_co = list_files(".", c_it); *c_sel = 0; *c_off = 0; }
            else { chdir(".."); getcwd(c_pa, 512); *c_co = list_files(".", c_it); *c_sel = 0; *c_off = 0; }
        }
        // PROMPT
        else if (ch >= 32 && ch <= 126) {
            int len = (int)strlen(cmd_buffer);
            if (len < 1023) { cmd_buffer[len] = (char)ch; cmd_buffer[len + 1] = '\0'; }
        }
    }

    endwin();
    
    // --- PROTOCOLO DE FECHAMENTO TOTAL DO TERMINAL ---
    kill(getppid(), SIGKILL);
    
    return 0;
}
