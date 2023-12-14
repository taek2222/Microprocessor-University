#define QI_SIZE 64
#define QO_SIZE 64

void q_init();
int qi_insert(char ch);
int qo_insert(char ch);
int qi_delete();
int qo_delete();

extern int fi, ri, fo, ro;
extern char qi[QI_SIZE], qo[QO_SIZE];
