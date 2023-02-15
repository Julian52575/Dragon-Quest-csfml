#include "my_dragonquest.h"

static void friendship_ended_with_dq_ff_is_now_my_best_friend(
struct dragon_quest *dq)
{
    printf("free\n");
    free(dq->m[0]->e);
    free(dq->m);
    free(dq->i);

    free(dq);
}

int main(int ac, char **av)
{
    struct csfml_tools *ct = malloc(sizeof(struct csfml_tools) + 1);
    create_ct(&ct, "My Dragon Quest");
    struct dragon_quest *dq = malloc(sizeof(struct dragon_quest) + 1);
    init_dragonquest(&dq);

    game_window(ct, dq);

    free(ct);
    friendship_ended_with_dq_ff_is_now_my_best_friend(dq);
    return 0;
}
