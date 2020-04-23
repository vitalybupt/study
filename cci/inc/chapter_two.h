#ifndef CHAPTER_TWO_H
#define CHAPTER_TWO_H
void remove_dup(p_list l1, p_list l2);
p_node reverse_count(p_list l, unsigned count);
void delete_middle_node(p_list l, p_node n);
void partition_list(p_list l, unsigned long pivot);
p_list sum_list_1(p_list l1, p_list l2);
p_list sum_list_2(p_list l1, p_list l2);
bool check_palindrome(p_list l);
p_node check_intersection(p_list l1, p_list l2);
#endif
