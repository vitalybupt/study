#!/usr/bin/python
# coding=gbk
 
import argparse

# ͬһ��network ���Զ����Թ���
# ��������������������������λ��ʱ�̶��ģ���ô�Ϳɲ���Ҫǰ���ĸ�flag��
# �����ɲ��������������λ���������京�塣
# ��ִ���������ʱ���������������룺
# ntf_positional "icmp6" "two_node"  "linux"

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
