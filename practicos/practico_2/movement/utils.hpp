
GLuint raw_texture_load(const char *filename, int width, int height);

void drawText(float coords[3], SDL_Rect area, GLuint * txtNum);
//void drawText(float coords[3], int txtNum)
SDL_Rect Load_string(char * text, SDL_Color clr, GLuint * txtNum, TTF_Font* tmpfont);
//void Load_string(char * text, SDL_Color clr, int txtNum, const char* file, int ptsize);
