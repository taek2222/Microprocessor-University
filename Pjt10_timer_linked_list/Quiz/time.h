struct task {
	void (*fun)(char *);
	char	arg[8];
};
struct timer {
	int time;
	struct task	task;
	struct timer *link;
};
extern struct timer *Thead;

struct timer *get_timer();

void insert_timer(struct task *tskp, int ms);
void	tour_timer();
void	free_timer();
