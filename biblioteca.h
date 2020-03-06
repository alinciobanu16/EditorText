void eliminare_trailing(char s[1000][1000], int line);
void eliminare_starting(char s[1000][1000], int line);
void align_left(char original[1000][1000], int original_line_count,
 int start_line, int end_line);
void align_right(char original[1000][1000], int original_line_count,
 int start_line, int end_line);
void center(char original[1000][1000], int original_line_count,
 int start_line, int end_line);
void paragraf(char original[1000][1000], int original_line_count,
 int indent_length, int start_line, int end_line);
void justify(char original[1000][1000], int original_line_count,
 int start_line, int end_line);
void lists(char original[1000][1000], int original_line_count,
  char list_type, char special_character,
  int start_line, int end_line);
int compare(const void * a ,const void * b);
void sort(char original[1000][1000], int start_line,
 int end_line, char ordering);
void parametrii(char v[1000][1000], int i, int lines, int *arg1, int *arg2);
void wrap (char original[1000][1000], int *original_line_count,
 int max_line_length);