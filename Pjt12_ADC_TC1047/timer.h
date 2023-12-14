struct task{
	void (*fun)(char *);
	char arg[8];
};
#define MAX_TASK 16

struct task Task_q[MAX_TASK];
volatile int Task_f, Task_r;

struct timer {
	int		time;
	struct 	task	task;
	struct 	timer	*link;
};
extern struct timer *Thread;
struct timer *get_timer();

void timer_init();
void insert_timer(struct task *tskp, int ms);
void tour_timer(),free_timer();
void task_init();
int task_insert(struct task *tskp), task_delete(struct task *tskp);
void task_cmd(char *arg);
int qi_peek(), uart_peek();
void timer_expire(void);
