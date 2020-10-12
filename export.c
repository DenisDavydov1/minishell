#include "minishell.h"

void tenv_swap(t_env **e1, t_env **e2)
{
    char *tmp_name;
    char *tmp_value;

    tmp_name = (*e1)->name;
    tmp_value = (*e1)->value;
    (*e1)->name = (*e2)->name;
    (*e1)->value = (*e2)->value;
    (*e2)->name = tmp_name;
    (*e2)->value = tmp_value;
}

void bubble_sort(t_env *env)
{
    t_env *ptr_i;
    t_env *ptr_j;

    ptr_i = env;
    while (ptr_i)
    {
        
        ptr_j = env;
        while (ptr_j)
        {
            if (ft_strcmp(ptr_j->name, ptr_j->next->name) > 0)
            {
                
                tenv_swap(&ptr_j, &(ptr_j->next));
            }
            
            ptr_j = ptr_j->next;
            
        }
        
        ptr_i = ptr_i->next;
    }
    
    t_env *first = env;
    while (first)
	{
		printf("%s = %s\n", first->name, first->value);
		first = first->next;
	}
}

void ft_export(t_env *env)
{
    t_env *first;

    first = env;
    while (first)
	{
		printf("%s = %s\n", first->name, first->value);
		first = first->next;
	}

    //tenv_swap(&env, &(env->next));
    printf("\n\n");
    bubble_sort(env);
    
    
}
/*
e0->next = e1;
e1->next = e2;
e2->next = e3;

e0->next = e2;
e2->next = e1;
e1->next = e3;*/