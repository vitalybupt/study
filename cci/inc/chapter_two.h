#ifndef CHAPTER_TWO_H
#define CHAPTER_TWO_H
void remove_dup(plist l1, plist l2);
pnode reverse_count(plist l, unsigned count);
void delete_middle_node(plist l, pnode n);
void partition_list(plist l, unsigned long pivot);
plist sum_list_1(plist l1, plist l2);
plist sum_list_2(plist l1, plist l2);
bool check_palindrome(plist l);
pnode check_intersection(plist l1, plist l2);
#endif
