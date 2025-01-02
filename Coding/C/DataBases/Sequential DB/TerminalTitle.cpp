#include <ncurses.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>

std::string run_command(const char* cmd) {
    std::ostringstream output;
    FILE* stream = popen(cmd, "r");
    if (stream) {
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), stream) != nullptr) {
            output << buffer;
        }
        pclose(stream);
    }
    return output.str();
}

void show_project_title() {
    initscr();
    noecho();
    curs_set(FALSE);
    int width, height;
    getmaxyx(stdscr, height, width); 

    clear();

    std::string large_text = run_command("figlet -w 150 'Sequential Database'");

    int line_start = height / 3; 
    std::istringstream text_stream(large_text);
    std::string line;
    while (std::getline(text_stream, line)) {
        mvprintw(line_start++, (width - line.size()) / 2, "%s", line.c_str());
    }

    const char* footer_left = "Prime Wadoud 2025";
    const char* footer_right = "Press ENTER to continue";

    mvprintw(height - 2, 2, "%s", footer_left);
    mvprintw(height - 2, width - strlen(footer_right) - 2, "%s", footer_right);

    refresh();

    while (getch() != '\n');

    endwin();
}
