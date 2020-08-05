#!/usr/bin/python
# coding=gbk
 
import argparse

'''
# 同一个network 的自动测试工具
# 如果将这三个参数在命令行里的位置时固定的，那么就可不需要前面哪个flag，
# 而是由参数在命令行里的位置来决定其含义。
# 当执行这个命令时，在命令行里输入：
# ntf_positional "icmp6" "two_node"  "linux"
'''
def test_create_tree():
    input = (1, none, 3, 2)
    
    return
if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("case",  help="the case you want to execute")
    parser.add_argument("topology",  help="network topology")
    parser.add_argument("os",  help="os deploy your software")
    nc = parser.parse_args()
    print(nc)
