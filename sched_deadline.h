#ifndef SCHED_DEADLINE_H
#define SCHED_DEADLINE_H

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

struct sched_attr {
    	__u32 size;
	__u32 sched_policy;
	__u64 sched_flags;

	/* used by: SCHED_NORMAL, SCHED_BATCH */
	__s32 sched_nice;

	/* used by: SCHED_FIFO, SCHED_RR */
	__u32 sched_priority;

	/* used by: SCHED_DEADLINE (nsec) */
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
};

/* sched_policy */
#define SCHED_DEADLINE 6

/* helpers */
#define gettid() syscall(__NR_gettid)
int sched_setattr(pid_t pid, const struct sched_attr *attr, unsigned int flags) {
    return syscall(__NR_sched_setattr, pid, attr, flags);
}
int sched_getattr(pid_t pid, struct sched_attr *attr, unsigned int size, unsigned int flags) {
    return syscall(__NR_sched_getattr, pid, attr, size, flags);
}

#endif /* SCHED_DEADLINE_H */
